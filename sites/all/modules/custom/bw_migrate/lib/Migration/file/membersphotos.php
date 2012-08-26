<?php


class bw_migrate_Migration_file_membersphotos extends bw_migrate_Migration {

  protected function _init($src, $dest, $map) {

    // See http://drupal.org/node/1349726 "MigrateDestinationFile"
    $dest->dest('file', array(

      // have the file copied from the provided URI to Drupal.
      'copy_file' => TRUE,

      // scheme/directory to use as file copy destination
      // Default is 'public://', whatever that means
      'copy_destination' => 'public://userpics/',

      // Clean up on rollback.
      'preserve_files' => FALSE,
    ));
    $src->primary('id');

    $q = $src->rox_select_members('m', 'u');
    $q->innerJoin('membersphotos', 'p', 'm.id = p.IdMember');
    $q->fields('p', array(
      'id', 'FilePath',
      'IdMember', 'SortOrder',
      'updated', 'created',
      'comment'
    ));
    $q->fields('m', array(
      'Username',
    ));

    $map->uid('uid', 'idmember');
    $map->strtotime('timestamp', 'created');

    $map->map('filename', 'filepath');
    $map->map('uri', 'username');

    $dest->ignore(array(
      'path',
      'status',  // ?
      'filemime',  // optional
      // These fields are only used in copy_blob option.
      'contents',
    ));
    $src->ignore(array(
      'sortorder', 'updated', 'comment',
    ));
  }

  /**
   * This function is called by the parent prepareRow().
   */
  protected function _prepareRow($row) {
    $base = 'http://www.bewelcome.org';
    $row->filepath = basename($row->filepath);
    $row->username = $base . '/members/avatar/' . $row->username;
  }

  /**
   * Solve the chicken-egg-problem membersphotos vs user
   */
  protected function createStub($migration) {
    $method = __METHOD__;
    $machine_name = $this->machineName;
    $machine_name_foreign = $migration->machineName;
    $txt = <<<EOT
This is a stub file created in $method
for migration $machine_name_foreign.
It is going to be replaced, next time you run 'drush mi $machine_name'.
EOT;
    $filename = 'stub-'. md5(microtime(TRUE) . rand()) .'.txt';
    $destination = "public://migrate-stubs/$filename";
    $file = file_save_data($txt, $destination);
    return empty($file->fid) ? FALSE : array($file->fid);
  }
}


