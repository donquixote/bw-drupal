<?php
/**
 * @file
 * bw_user_profile.field_group.inc
 */

/**
 * Implementation of hook_field_group_info().
 */
function bw_user_profile_field_group_info() {
  $export = array();

  $field_group = new stdClass;
  $field_group->api_version = 1;
  $field_group->identifier = 'group_accomodation|profile2|main|form';
  $field_group->group_name = 'group_accomodation';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'main';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Accomodation',
    'weight' => '9',
    'children' => array(
      0 => 'field_i_live_with',
      1 => 'field_max_length_of_stay',
      2 => 'field_max_number_of_guests',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_accomodation|profile2|main|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->api_version = 1;
  $field_group->identifier = 'group_contact_details|profile2|main|form';
  $field_group->group_name = 'group_contact_details';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'main';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Contact Details',
    'weight' => '12',
    'children' => array(
      0 => 'field_im',
      1 => 'field_phone_home',
      2 => 'field_website',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_contact_details|profile2|main|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->api_version = 1;
  $field_group->identifier = 'group_likes_hobbies|profile2|main|form';
  $field_group->group_name = 'group_likes_hobbies';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'main';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Likes and Hobbies',
    'weight' => '11',
    'children' => array(
      0 => 'field_books',
      1 => 'field_films',
      2 => 'field_hobbies',
      3 => 'field_music',
      4 => 'field_organisations_i_belong_to',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_likes_hobbies|profile2|main|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->api_version = 1;
  $field_group->identifier = 'group_location|profile2|main|form';
  $field_group->group_name = 'group_location';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'main';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Location',
    'weight' => '10',
    'children' => array(
      0 => 'field_geocoded',
      1 => 'field_housenumber',
      2 => 'field_street',
      3 => 'field_zipcode',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_location|profile2|main|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->api_version = 1;
  $field_group->identifier = 'group_name|profile2|main|form';
  $field_group->group_name = 'group_name';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'main';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_personal';
  $field_group->data = array(
    'label' => 'Name',
    'weight' => '15',
    'children' => array(
      0 => 'field_firstname',
      1 => 'field_lastname',
      2 => 'field_secondname',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_name|profile2|main|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->api_version = 1;
  $field_group->identifier = 'group_personal|profile2|main|form';
  $field_group->group_name = 'group_personal';
  $field_group->entity_type = 'profile2';
  $field_group->bundle = 'main';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Personal',
    'weight' => '2',
    'children' => array(
      0 => 'group_name',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_personal|profile2|main|form'] = $field_group;

  return $export;
}
