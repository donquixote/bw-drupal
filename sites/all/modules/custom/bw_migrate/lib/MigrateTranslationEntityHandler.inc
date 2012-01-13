<?php
/**
 * @file
 * Support for destination translatable fields
 * (requires entity_translation module)
 *
 * Adapted from
 * http://drupal.org/node/929402#comment-5382644
 * Thx "das-peter", "bastnic".
 */


/**
 * Destination class implementing translatable fields
 *
 * How to use:
 * Just map the $entity->language field to the appropriate language code.
 *
 * @TODO Would be nice to move some parts of this into migrate itself
 */
class MigrateTranslationEntityHandler extends MigrateDestinationHandler {

  /**
   * registers all entites as handled by this class
   */
  public function __construct() {
    $this->registerTypes(array('entity'));
  }

  /**
   * Handles Entity Translations
   *
   * @TODO Add support for node based translations
   *
   * @param stdClass $entity
   *   The entity to save or create.
   * @param stdClass $source_row
   *   Row from the source db. Not actually used.
   */
  public function prepare(stdClass $entity, stdClass $source_row) {
    $migration = Migration::currentMigration();
    $entity_type = $migration->getDestination()->getEntityType();

    if (entity_translation_enabled($entity_type) && property_exists($entity, 'nid') && $entity->nid) {
      $translation_handler = entity_translation_get_handler($entity_type, $entity);

      // Load translations if necessary
      if (!property_exists($entity, 'translations')) {
        $entity->translations = $translation_handler->getTranslations();
      }

      // Content based translation
      if (in_array($entity->type, variable_get('entity_translation_entity_types', array()))) {
        $this->_fieldTranslation($entity, $translation_handler);
      }
      // Node based translation
      else {
        $this->_nodeTranslation($entity);
      }
    }
  }

  protected function _fieldTranslation($entity, $translation_handler) {
    dpm('good types');
    // Translation needed?
    if (!isset($entity->translations->data[$entity->language])) {
      dpm('translation needed');

      $changed = (property_exists($entity, 'changed'))? $entity->changed : time();

      // Add the new translation and store it
      $translation_handler->setTranslation(array(
        'translate' => 0,
        'status' => $entity->status,
        'language' => $entity->language,
        'source' => $entity->translations->original,
        'uid' => $entity->uid,
        'created' => $entity->created,
        'changed' => $changed,
      ));
    }
    // Preserve original language setting
    $entity->language = $entity->translations->original;
  }

  protected function _nodeTranslation($entity) {
    // Load old node to make sure it's the right id -
    // mapping of migrate is not language sensitive
    $current_node = node_load($entity->nid);

    // "Fix" mapping "issue" - should be solved withing migrate itself
    if ($current_node->language != $entity->language) {

      // Check if there was a translation before - if not save the tnid
      $tnid = $current_node->tnid;
      if (!$tnid) {
        $current_node->tnid = $current_node->nid;
        node_save($current_node);
      }

      // Load the translation of the node if there is one
      $nodes = node_load_multiple(array(), array('tnid' => $current_node->tnid, 'language' => $entity->language));

      // If there was a translation -
      // map these information in the current entity
      if (count($nodes)) {
        $matching_node = reset($nodes);
        // Change Id's to the matching node
        $entity->nid = $matching_node->nid;
        $entity->vid = $matching_node->vid;
        $entity->translations = $matching_node->translations;
      }
      else {
        // Tehere was no node with this language - create a new one
        unset(
          $entity->nid,
          $entity->translations,
          $entity->vid
        );
      }
      // Make sure the translation nodes are grouped properly
      $entity->tnid = $current_node->tnid;
    }
  }
}
