<?php
// $Id: boxes.admin.inc,v 1.5.2.4.2.1 2010/09/30 18:22:40 adrian Exp $

/**
 * Generate form for creating new boxes.
 */
function boxes_add_form($form, $form_state, $plugin_key) {
  $form_state['box'] = boxes_factory($plugin_key);
  $form = boxes_box_form($form, $form_state);
  $form['delta'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine name'),
    '#description' => t('Lowercase letters, numbers and underscores only'),
    '#required' => true,
    '#element_validate' => array('boxes_validate_delta'),
    '#size' => 32,
    '#maxlength' => 32,
    '#weight' => -20,
  );
  $form['submit']['#attributes']['class'] = array();
  return $form;
}

/**
 * Validate handler for box delta.
 */
function boxes_validate_delta($element, &$form_state) {
  if (!preg_match('!^[a-z0-9_]+$!', $element['#value'])) {
    form_error($element, t('The machine-readable name must contain only lowercase letters, numbers, and underscores.'));
  }
  if ((strpos($element['#value'], 'boxes_add__') === 0) || boxes_box_load($element['#value'])) {
    form_error($element, t('The machine-readable name is already taken.'));
  }
}

/**
 * Submit handler for box_add_form.
 */
function boxes_add_form_submit($form, &$form_state) {
  $box = boxes_factory($form_state['values']['plugin_key'], $form_state['values']);
  $box->save();
  drupal_set_message(t('%name has been created.', array('%name' => $box->description)));
  $form_state['redirect'] = 'admin/structure/block';
}

/**
 * Box deletion form.
 */
function boxes_delete_form($form, $form_state, $box) {
  $form['delta'] = array(
    '#type' => 'hidden',
    '#value' => $box->delta,
  );
  if (($box->export_type & EXPORT_IN_DATABASE) && ($box->export_type & EXPORT_IN_CODE)) {
    return confirm_form($form, t('Are you sure you want to revert the block %name?', array('%name' => $box->title)), 'admin/structure/block', '', t('Revert'), t('Cancel'));
  }
  elseif (!($box->export_type & EXPORT_IN_CODE)) {
    return confirm_form($form, t('Are you sure you want to delete the block %name?', array('%name' => $box->title)), 'admin/structure/block', '', t('Delete'), t('Cancel'));
  }
  drupal_not_found();
  die;
}

/**
 * Submit handler for boxes_delete_form
 */
function boxes_delete_form_submit($form, &$form_state) {
  boxes_box_load($form_state['values']['delta'])->delete();
  $form_state['redirect'] = 'admin/structure/block';
}

/**
 * Theme function for the form.
 */
function theme_boxes_box($variables) {
  $block = $variables['block'];
  $output = "<div id='boxes-box-" . $block['delta'] . "' class='boxes-box" . (!empty($block['editing']) ? ' boxes-box-editing' : '') . "'>";
  $output .= '<div class="boxes-box-content">' . $block['content'] . '</div>';
  if (!empty($block['controls'])) {
    $output .= '<div class="boxes-box-controls">';
    $output .= $block['controls'];
    $output .= '</div>';
  }
  if (!empty($block['editing'])) {
    $output .= '<div class="box-editor">' . drupal_render($block['editing']) . '</div>';
  }
  $output .= '</div>';
  return $output;
}
