<?php


class bw_migrate_Migration_node_faqItem extends bw_migrate_Migration {

  public function _init($src, $dest, $map) {

    $this->description = t('FAQ');

    $dest->node('faq_item');
    $src->primary('id');

    $q = $src->rox_select('faq');
    $q->fields('faq', array(
      'id', 'QandA', 'updated', 'created',
      'Active', 'SortOrder', 'IdCategory', 'PageTitle',
    ));

    $map->word('title', 'qanda', 'FaqQ_');
    $map->word('body', 'qanda', 'FaqA_');
    $map->foreignKey('field_faq_category', 'idcategory', 'term_faq_categories');
    $map->uidAdmin('uid');
    $map->uidAdmin('revision_uid');
    $map->strtotime('created', 'created');
    $map->strtotime('changed', 'updated');

    // Unmapped fields
    $src->ignore(array(
      'qanda', 'active', 'sortorder', 'idcategory',
      'pagetitle',
    ));
    $dest->ignore(array(
      // These are all dealt with in $dest->node().
    ));
  }
}



