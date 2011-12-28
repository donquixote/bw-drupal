<?php


abstract class bw_migrate_Migration_node_pr9photo extends bw_migrate_Migration {

  protected function _init($src, $dest, $map) {

    $this->description = t('FAQ');

    $src->primary('fid');
    $dest->node('pr9photo');

    $q = $src->rox_select('files', 'f');
    $q->fields('f', array('fid', 'filepath', 'filename'));

    // Mapped fields
    $map->map('title', 'title');

    $map->map('body', 'body');
    $map->map('field_faq_category', 'category');

    $dest->ignoreFields(array(
      'name', 'created', 'changed', 'status', 'promote', 'revision', 'language',
    ));
  }
}



