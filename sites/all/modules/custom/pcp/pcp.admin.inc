<?php
// $Id$

/**
 * Form builder; Configure PCP fields.
 *
 * @ingroup forms
 */
function pcp_admin_settings($form, &$form_state) {
  $form['general_settings'] = array(
    '#type' => 'fieldset',
    '#title' => 'General Settings',
  );
  $form['general_settings']['hide_block_on_complete'] = array(
    '#type' => 'checkbox',
    '#title' => 'Hide Block When Complete',
    '#default_value' => variable_get('pcp_hide_block_on_complete', 0),
    '#description' => t('When a user reaches 100% complete of their profile, do you want the profile complete percent block to go away? If so, check this box on.'),
  );
  if (variable_get('user_pictures', 0)) {
    $form['general_settings']['pcp_enable_user_picture'] = array(
      '#type' => 'checkbox',
      '#title' => 'Enable User Picture Support',
      '#default_value' => variable_get('pcp_enable_user_picture', 0),
      '#description' => t('Picture support has been turned on, do you want to make it required as part of Profile Complete Percent? Checking this box will make it required.'),
    );
  }

  $form['profile_field_settings'] = array(
    '#type' => 'fieldset',
    '#title' => 'Profile Field Settings',
    '#description' => t('Checking a profile field below will add that field to the logic of the complete percentage.'),
  );
  $options = pcp_admin_settings_form_data();
  if ($options['profile_fields_options']) {
    $form['profile_field_settings']['profile_fields'] = array(
      '#title' => t('Profile Fields'),
      '#type' => 'checkboxes',
      '#options' => $options['profile_fields_options'],
      '#default_value' => array_flip($options['default_values']),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function pcp_form_user_admin_settings_alter(&$form, &$form_state, $form_id) {
  if (user_access('administer pcp')) {
    $form['personalization']['pictures']['pcp_enable_user_picture'] = array(
      '#title' => 'Make required for PCP module',
      '#type' => 'checkbox',
      '#default_value' => variable_get('pcp_enable_user_picture', 0),
      '#description' => t('Checking this box will tag this field as a required field for completion of the users profile.'),
      '#weight' => -5,
    );
    $form['#submit'][] = 'pcp_admin_settings_submit';
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function pcp_form_field_ui_field_edit_form_alter(&$form, &$form_state, $form_id) {
  // @todo do we need user access check here?
  $tag = FALSE;
  $result = pcp_get_tagged_profile_fields($form['#field']['id']);
  if (!empty($result)) {
    $tag = TRUE;
  }

  $form['instance']['pcp_tag'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make required for PCP module'),
    '#description' => t('Checking this box will tag this field as a required field for completion of the users profile.'),
    '#default_value' => $tag,
    '#weight' => -5,
  );
  $form['#submit'][] = 'pcp_admin_settings_submit';
}

/**
 * Function that sets up parameters to be used 
 * when the pcp_admin_settings_form() function
 * is executed. 
 *
 * @return - assoc array
 *  ['profile_fields_options'] 
 *    - An associative array of all fields created from the profile module.
 *  ['default_values']
 *    - An indexed array of all (if any) default values for the form.
 */
function pcp_admin_settings_form_data() {
  $options = array();
  $options['profile_fields_options'] = pcp_get_profile_fields();
  $options['default_values'] = pcp_get_tagged_profile_fields();

  return $options;
}

/**
 * Submit callback.
 */
function pcp_admin_settings_submit($form, &$form_state) {
  switch ($form['#form_id']) {
    // admin/config/people/accounts
    case 'user_admin_settings':
      variable_set('pcp_enable_user_picture', $form_state['values']['pcp_enable_user_picture']);
      break;
    // admin/config/people/accounts/fields/[field_name]
    case 'field_ui_field_edit_form':
      $fid = $form['#field']['id'];
      db_delete('profile_pcp')
        ->condition('fid', $fid)
        ->execute();

      if ($form_state['values']['instance']['pcp_tag']) {
        db_insert('profile_pcp')
          ->fields(array('fid' => $fid))
          ->execute();
      }
      break;
    // admin/config/people/pcp
    default:
      // Provides the General Settings data
      variable_set('pcp_hide_block_on_complete', $form_state['values']['hide_block_on_complete']);
      variable_set('pcp_enable_user_picture', $form_state['values']['pcp_enable_user_picture']);

      // Process the profile fields that have been modified
      if ($form_state['values']['profile_fields']) {
        db_delete('profile_pcp')
          ->execute();
        foreach ($form_state['values']['profile_fields'] as $fid) {
          if ($fid) {
            db_insert('profile_pcp')
              ->fields(array('fid' => $fid))
              ->execute();
          }
        }
        drupal_set_message("Your settings have been saved.");
      }
  }
}