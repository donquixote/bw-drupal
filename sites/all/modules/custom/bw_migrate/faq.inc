<?php


class FaqTermMigration extends BWMigration {

  protected function _init($src, $dest, $map) {

    $this->description = 'Migrate FAQ categories from the source database to taxonomy terms';

    $dest->entity('term', 'faq_categories');

    $src->id('Topic ID', 'varchar');
    $src->rox_select('faqcategories')
      ->fields('faqcategories', array('id', 'Description', 'SortOrder'))
    ;

    $map->map('name', 'name_en');
    $map->map('description', 'name_en');
  }

  public function prepareRow($current_row) {
    $current_row->name_en = $this->getTranslation($current_row->description);
  }
}


class FaqNodeMigration extends BWMigration {

  public function _init($src, $dest, $map) {

    $this->description = t('FAQ');
    $this->dependencies = array('FaqTerm');

    $dest->node('faq_item');

    $src->id('FAQ ID.');
    $q = $src->rox_select('faq');
    $q->fields('faq', array(
      'id', 'QandA', 'updated', 'created',
      'Active', 'SortOrder', 'IdCategory', 'PageTitle',
    ));
    $q->leftJoin('faqcategories', 'fc', 'faq.IdCategory = fc.id');
    $q->addExpression('fc.Description', 'faq_category');

    // Mapped fields
    $map->map('title', 'title')->description('Mapping something to node title');

    // To maintain node identities between the old and new systems (i.e., have
    // the same unique IDs), map the ID column from the old system to nid and
    // set is_new to TRUE.
    $map->map('nid', 'id')->description('Preserve old FAQ ID as nid in Drupal');
    $map->map('is_new')->defaultValue(TRUE);

    $map->map('body', 'body');

    $map->map('field_faq_category', 'category');

    // Unmapped destination fields
    //$this->addUnmigratedDestinations(array('name', 'created', 'changed', 'status',
    //  'promote', 'revision', 'language'));
  }

  public function prepareRow($current_row) {
    $current_row->title = $this->getTranslation('FaqQ_' . $current_row->qanda);
    $current_row->body = $this->getTranslation('FaqA_' . $current_row->qanda);
    $current_row->category = $this->getTranslation($current_row->faq_category);
  }

}



