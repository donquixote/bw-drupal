<?php

/**
 * @file
 * Support for media destinations.
 */

class MigrateMediaFieldHandler extends MigrateFileFieldHandler {
  public function __construct() {
    $this->registerTypes(array('media'));
  }

  /**
   * Parses file information to create an appropriate data array.
   *
   * @param $entity
   * @param array $field_info
   * @param array $instance
   * @param $migration
   * @param $arguments
   * @param $value
   *
   * @return array
   */
  protected function buildFileArray($entity, array $field_info, array $instance, $migration, $arguments, $value) {
    static $fids;
drush_print('in media handler');
    // Is the value a straight path, or JSON containing a set of properties?
    if ($value{0} == '{') {
      $properties = drupal_json_decode($value);
      if (!empty($properties['path'])) {
        $path = $properties['path'];
      }
      // Properties passed in with the image override any set via arguments
      if (!empty($properties['fid'])) {
        $arguments['fid'] = $properties['fid'];
      }
      if (!empty($properties['title'])) {
        $arguments['title'] = $properties['title'];
      }
      if (!empty($properties['data'])) {
        $arguments['data'] = $properties['data'];
      }
    }
    else {
      $path = $value;
    }

    // One can override a file_function via CLI or drushrc.php
    if ($migration->getOption('file_function')) {
      $file_function = $migration->getOption('file_function');
    }
    else {
      $file_function = $arguments['file_function'];
    }

    if ($arguments['source_path']) {
      $full_path = rtrim($arguments['source_path'], "/\\") .
        '/' . ltrim($path, "/\\");
    }
    else {
      $full_path = $path;
    }

    if (!empty($arguments['fid'])) {
      $file = file_load($arguments['fid']);
    }
    else {

      $remote = FALSE;

      // Check that source exists. If not, mark the entity as 'needs_update' and bail.
      // Sometimes the source file arrives later, when rsync is slower than DB.
      if (!is_file($full_path)) {
        // is_file() won't handle URLs, check to see if we have a remote file
        // (only relevant in the file_copy case)
        if ($file_function == 'file_copy') {
          $headers = @get_headers($full_path);
          if (is_array($headers) && preg_match('%^HTTP/[0-9]\.[0-9] 200 OK$%', $headers[0])) {
            $remote = TRUE;
          }
        }
        if (!$remote) {
          $migration->saveMessage(t('Source file does not exist: !path',
            array('!path' => $full_path)), Migration::MESSAGE_WARNING);
          $migration->needsUpdate = TRUE;
          return;
        }
      }

      $destination_dir = variable_get('file_default_scheme', 'public') . '://';
      file_prepare_directory($destination_dir, FILE_CREATE_DIRECTORY);
      if ($remote) {
        $destination_file = $destination_dir . "/" . basename($full_path);
      }
      else {
        $destination_file = file_stream_wrapper_uri_normalize($destination_dir . "/" . str_replace('/', '-', $full_path));
      }

      $real_destination_file = drupal_realpath($destination_file);
      $source = (object) array(
        'uri' => $full_path,
        'status' => FILE_STATUS_PERMANENT,
        'uid' => isset($entity->uid) ? isset($entity->uid) : 0,
        'filename' => basename($full_path),
        'filemime' => file_get_mimetype($full_path),
        'timestamp' => REQUEST_TIME,
      );

      // Check that destination does not exist. If it does, reuse it and return.
      if (file_exists($real_destination_file)) {
        // Save this file to DB.
        if ($existing_files = file_load_multiple(array(), array('uri' => $destination_file))) {
          // Existing record exists. Reuse it. TODO: Perhaps we never should re-use records.
          $file = reset($existing_files);
          $file = file_save($file);
        }
        else {
          // Get this orphaned file into the file table.
          $file = clone $source;
          $file->fid = NULL;
          $file->uri = $destination_file;
          $file->status = FILE_STATUS_PERMANENT;
          $file = file_save($file);
        }
      }
      else {
        migrate_instrument_start('MigrateMediaFieldHandler file_function');
        switch ($file_function) {
          case 'file_copy':
            if ($remote) {
              $result = @copy($source->uri, $destination_file);
              if ($result) {
                $source->uri = $destination_file;
                $file = file_save($source);
              }
              else {
                $migration->saveMessage(t('Unable to copy file from !source',
                  array('!source' => $source->uri)));
              }
            }
            else {
              $file = file_copy($source, $destination_dir, $arguments['file_replace']);
            }
            break;
          case 'file_move':
            // file_move() does a copy then delete which slow. So we implement our own.
            if (file_prepare_directory($destination_dir, FILE_CREATE_DIRECTORY)) {
              if (rename($source->uri, $real_destination_file)) {
                $file = clone $source;
                $file->fid = NULL;
                $file->uri = $destination_file;
                $file->status = FILE_STATUS_PERMANENT;
                $file = file_save($file);

                // Inform modules that the file has been copied.
                module_invoke_all('file_copy', $file, $source);
                break;
              }
              else {
                $migration->saveMessage(t('Unable to rename !source to !uri', array('!source' => $source->uri, '!uri' => $destination_file)), Migration::MESSAGE_ERROR);
                return;
              }
            }
            else {
              $migration->saveMessage(t('Unable to prepare directory !dir', array('!dir' => $destination_dir)), Migration::MESSAGE_ERROR);
              return;
            }
            break;
          case 'file_fast':
            // Keep re-using an existing file. We still benefit from the file_exists() check above.
            if (!isset($fids[$source])) {
              $full_path = DRUPAL_ROOT . '/misc/druplicon.png';
              $source = (object) array(
                'uri' => $full_path,
                'status' => FILE_STATUS_PERMANENT,
                'uid' => isset($entity->uid) ? isset($entity->uid) : 0,
                'filename' => basename($full_path),
                'filemime' => file_get_mimetype($full_path),
                'timestamp' => REQUEST_TIME,
              );
              $file = file_copy($source, $destination_dir, FILE_EXISTS_RENAME);
              $fid = $file->fid;
            }
            else {
              $file = new stdClass();
              $file->fid = $fids[$source];
            }
            break;
        }
        migrate_instrument_stop('MigrateMediaFieldHandler file_function');
      }
    }

    if ($file) {
      // Build up a return object.
      $object_field['fid'] = $file->fid;
      if (!empty($arguments['title'])) {
        $object_field['title'] = $arguments['title'];
      }
      else {
        $object_field['title'] = NULL;
      }
      if (!empty($arguments['data'])) {
        $object_field['data'] = $arguments['data'];
      }
      else {
        $object_field['data'] = NULL;
      }
      return $object_field;
    }
    else {
      $migration->saveMessage(t('Unable to create file record for !path', array('!path' => $full_path)), Migration::MESSAGE_ERROR);
    }
  }

  /**
   * Arguments for a media_field migration.
   *
   * @param source_path
   *   Path to source file.
   * @param file_function
   *   file_fast, file_move, or file_copy.
   * @param file_replace
   *   Value of $replace in that file function. Does not apply to file_fast(). Defaults to FILE_EXISTS_RENAME.
   * @param language
   *   Language of the text (defaults to destination language)
   * @param fid
   *   File identifier for an existing file, or
   *   array('source_field' => 'source_field_name') to obtain the fid value from
   *   the query field named source_field_name.
   * @param title
   *   String to be used as the title value for all file fields, or
   *   array('source_field' => 'source_field_name') to obtain the title value from
   *   the query field named source_field_name.
   * @param data
   *   Additional data, or
   *   array('source_field' => 'source_field_name') to obtain the data value from
   *   the query field named source_field_name.
   */
  static function arguments($source_path = NULL, $file_function = 'file_copy', $file_replace = FILE_EXISTS_RENAME, $language = NULL, $fid = NULL, $title = NULL, $data = NULL) {
    return get_defined_vars();
  }
}

/**
 * Destination class implementing migration into media entities.
 */
class MigrateDestinationMedia extends MigrateDestinationFile {
  /**
   * List of node migrations, whose bodies need image references fixed up.
   *
   * @var array
   */
  protected $sourceMigrations = array();

  /**
   * Node ID of the node whose body is currently being rewritten.
   *
   * @var int
   */
  protected $parentNid;

  /**
   * Return an options array for media destinations.
   *
   * @param array $source_migrations
   *  List of node migrations, whose bodies need image references fixed up.
   * @param boolean $copy_file
   *  TRUE to have the file copied from the provided URI to Drupal. Defaults to FALSE.
   * @param string $copy_destination
   *  If $copy_file is TRUE, the scheme/directory to use as the destination for the copied file.
   *  Defaults to 'public://'.
   * @param string $language
   *  Default language for files created via this destination class.
   * @param string $text_format
   *  Default text format for files created via this destination class.
   */
  static public function options($copy_file, $copy_destination, $language, $text_format, $source_migrations = array()) {
    return compact('copy_file', 'copy_destination', 'language', 'text_format', 'source_migrations');
  }

  /**
   * Basic initialization
   *
   * @param array $options
   *  Options applied to files.
   */
  public function __construct($media_type = 'default', array $options = array()) {
    if (isset($options['source_migrations'])) {
      $this->sourceMigrations = $options['source_migrations'];
    }
    parent::__construct($options);
    $this->entityType = 'media';
    $this->bundle = $media_type;
  }

  /**
   * Returns a list of fields available to be mapped for the entity type (bundle)
   *
   * @return array
   *  Keys: machine names of the fields (to be passed to addFieldMapping)
   *  Values: Human-friendly descriptions of the fields.
   */
  public function fields() {
    // First get the file fields
    $fields = parent::fields();

    $fields += migrate_handler_invoke_all('Media', 'fields');

    return $fields;
  }

  /**
   * The file import method calls file_save(), which invokes media hooks but does
   * not call media_save(), thus fields are not saved. So, we do the media_save()
   * ourselves after file_save().
   *
   * @param $file
   *  File object to build. This is the complete object after saving.
   * @param $source_row
   *  Raw source data object - passed through to complete handlers.
   */
  public function complete($file, stdClass $source_row) {
    parent::complete($file, $source_row);
    media_save($file);
  }

  /**
   * Called at the completion of a migration into a media destination. Rewrite
   * <img> tags into the media module's embedded JSON references.
   */
  public function postImport() {
    migrate_instrument_start('MigrateDestinationMedia postImport');
    // Scan the destination nodes
    foreach ($this->sourceMigrations as $source_migration) {
      $migration = MigrationBase::getInstance($source_migration);
      $map = $migration->getMap();
      foreach ($map as $map_row) {
        $this->parentNid = $map_row->destid1;
        $node = node_load($this->parentNid);
        $body = $node->body[LANGUAGE_NONE][0]['value'];
        // Quickly skip any non-candidates
        if (!strstr($body, 'img')) {
          continue;
        }
        // Pass full img tags into the callback
        $new_body = preg_replace_callback('|<img [^>]*>|i', array($this, 'replaceCallback'),
          $body);
        $node->body[LANGUAGE_NONE][0]['value'] = $new_body;
        node_save($node);
      }
    }
    migrate_instrument_stop('MigrateDestinationMedia postImport');
  }

  /**
   * If a referenced image can be found in the files table, replace the <img> tag
   * with a media JSON reference.
   *
   * @param array $matches
   */
  protected function replaceCallback(array $matches) {
    $src_matches = array();
    // Default to the original <img> tag
    $result = $matches[0];
    // Extract the src parameter
    if (preg_match('|src=[\'"]([^\'"]+)[\'"]|i', $matches[0], $src_matches)) {
      // Replace the scheme and host portions of the referenced URL with the
      // Drupal scheme as it's saved in the file_unmanaged table
      $src = preg_replace('|^https?://[^/]+/|', $this->copyDestination, $src_matches[1]);
      $file = db_select('file_managed', 'f')
              ->fields('f', array('fid'))
              ->condition('filename', basename($src))
              ->execute()
              ->fetchObject();
      if ($file) {
        // Update file_usage
        // Note: Usages not cleaned up on file_delete() - NYI in media module
        file_usage_add($file, 'media', 'node', $this->parentNid);

        // TODO: Anything to do about alt/title?
        $image_info = array(
          'type' => 'media',
          'view_mode' => 'media_large',
          'fid' => $file->fid,
          'attributes' => array(
            'alt' => '',
            'title' => '',
            'class' => 'media-image',
            'typeof' => 'foaf:Image',
            'wysiwyg' => 1,
          ),
        );
        $result = '[[' . drupal_json_encode($image_info) . ']]';
      }
    }
    return $result;
  }
}
