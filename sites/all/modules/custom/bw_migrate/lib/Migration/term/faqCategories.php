<?php


class bw_migrate_Migration_term_faq_categories extends bw_migrate_Migration {

  protected function _init($src, $dest, $map) {

    $this->description = 'Migrate FAQ categories from the source database to taxonomy terms';

    $dest->dest('Term', 'faq_categories');
    $src->primary('id', 'varchar');

    $q = $src->rox_select('faqcategories', 'f');
    $q->fields('f', array('id', 'Description', 'SortOrder'));

    $map->word('name', 'description');
    $map->word('description', 'description');
    // $map->uid('uid')->defaultValue(1);
    $map->map('weight', 'sortorder');

    $src->ignore(array());
    $dest->ignore(array(
      'format', 'parent_name', 'parent', 'path',
    ));
  }
}



