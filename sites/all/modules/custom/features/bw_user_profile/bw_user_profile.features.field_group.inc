<?php

/**
 * Implementation of hook_field_group_default_field_groups().
 */
function bw_user_profile_field_group_default_field_groups() {
  $field_groups = array();

  // Exported field_group: 'user-user-form-group_accommodation'
  $field_groups['user-user-form-group_accommodation'] = array(
    'group_name' => 'group_accommodation',
    'entity_type' => 'user',
    'bundle' => 'user',
    'mode' => 'form',
    'parent_name' => 'group_profile',
    'label' => 'Accommodation',
    'weight' => '3',
    'children' => array(
      '0' => 'field_max_number_of_guests',
      '1' => 'field_max_length_of_stay',
      '2' => 'field_i_live_with',
      '3' => 'field_accommodation',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => NULL,
    ),
  );

  // Exported field_group: 'user-user-form-group_contact_information'
  $field_groups['user-user-form-group_contact_information'] = array(
    'group_name' => 'group_contact_information',
    'entity_type' => 'user',
    'bundle' => 'user',
    'mode' => 'form',
    'parent_name' => 'group_profile',
    'label' => 'Contact information',
    'weight' => '2',
    'children' => array(
      '0' => 'field_firstname',
      '1' => 'field_secondname',
      '2' => 'field_lastname',
      '3' => 'field_street',
      '4' => 'field_housenumber',
      '5' => 'field_zipcode',
      '6' => 'field_phone_home',
      '7' => 'field_phone_mobile',
      '8' => 'field_website',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => NULL,
    ),
  );

  // Exported field_group: 'user-user-form-group_interests'
  $field_groups['user-user-form-group_interests'] = array(
    'group_name' => 'group_interests',
    'entity_type' => 'user',
    'bundle' => 'user',
    'mode' => 'form',
    'parent_name' => 'group_profile',
    'label' => 'Interests',
    'weight' => '4',
    'children' => array(
      '0' => 'field_hobbies',
      '1' => 'field_books',
      '2' => 'field_music',
      '3' => 'field_films',
      '4' => 'field_organisations_i_belong_to',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => NULL,
    ),
  );

  // Exported field_group: 'user-user-form-group_preferences'
  $field_groups['user-user-form-group_preferences'] = array(
    'group_name' => 'group_preferences',
    'entity_type' => 'user',
    'bundle' => 'user',
    'mode' => 'form',
    'parent_name' => '',
    'label' => 'Preferences',
    'weight' => '1',
    'children' => array(
      '0' => 'account',
      '1' => 'timezone',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => NULL,
    ),
  );

  // Exported field_group: 'user-user-form-group_profile'
  $field_groups['user-user-form-group_profile'] = array(
    'group_name' => 'group_profile',
    'entity_type' => 'user',
    'bundle' => 'user',
    'mode' => 'form',
    'parent_name' => '',
    'label' => 'Profile',
    'weight' => '0',
    'children' => array(
      '0' => 'group_accommodation',
      '1' => 'group_profile_summary',
      '2' => 'group_interests',
      '3' => 'group_contact_information',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => NULL,
    ),
  );

  // Exported field_group: 'user-user-form-group_profile_summary'
  $field_groups['user-user-form-group_profile_summary'] = array(
    'group_name' => 'group_profile_summary',
    'entity_type' => 'user',
    'bundle' => 'user',
    'mode' => 'form',
    'parent_name' => 'group_profile',
    'label' => 'Profile Summary',
    'weight' => '1',
    'children' => array(
      '0' => 'field_profile_summary',
      '1' => 'field_gender',
      '2' => 'field_birth_date',
      '3' => 'field_occupation',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => NULL,
    ),
  );

  return $field_groups;
}
