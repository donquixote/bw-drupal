<?php


function crumbs_admin_entities_form() {

  _crumbs_include();

  $form = array();

  $form['settings'] = array(
    '#type' => 'textarea',
    '#title' => t('Parent paths for entity types and bundles.'),
    '#rows' => 24,
    // TODO: Add a CSS file? Or totally revamp this settings form?
    '#attributes' => array('style' => 'font-family:"Courier new", monospace;'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );

  $active_record = _crumbs_admin_entities_active_record();
  $form['settings']['#default_value'] = $active_record->getAsText();

  return $form;
}


function _crumbs_admin_entities_active_record() {
  static $_instance;
  if (!isset($_instance)) {
    $_instance = new crumbs_ActiveRecord_EntitySettings('crumbs_entity_settings');
  }
  return $_instance;
}


function crumbs_admin_entities_form_submit($form, &$form_state) {

  $active_record = _crumbs_admin_entities_active_record();
  $text = $form_state['values']['settings'];
  $active_record->setAsText($text);
  $active_record->save();
}
