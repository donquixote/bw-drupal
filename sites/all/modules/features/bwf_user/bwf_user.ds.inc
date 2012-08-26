<?php
/**
 * @file
 * bwf_user.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function bwf_user_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'user|user|default';
  $ds_fieldsetting->entity_type = 'user';
  $ds_fieldsetting->bundle = 'user';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'name' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['user|user|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'user|user|full';
  $ds_fieldsetting->entity_type = 'user';
  $ds_fieldsetting->bundle = 'user';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'name' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['user|user|full'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function bwf_user_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'user|user|default';
  $ds_layout->entity_type = 'user';
  $ds_layout->bundle = 'user';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'name',
      ),
    ),
    'fields' => array(
      'name' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['user|user|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'user|user|full';
  $ds_layout->entity_type = 'user';
  $ds_layout->bundle = 'user';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'header' => array(
        0 => 'name',
        1 => 'field_firstname',
        2 => 'field_secondname',
        3 => 'field_lastname',
        4 => 'field_occupation',
        5 => 'field_website',
        6 => 'field_birth_date',
        7 => 'field_gender',
      ),
      'left' => array(
        0 => 'field_phone_home',
        1 => 'privatemsg_send_new_message',
        2 => 'field_profile_summary',
        3 => 'field_im',
        4 => 'field_books',
        5 => 'field_films',
        6 => 'field_organisations_i_belong_to',
        7 => 'group_audience',
        8 => 'field_music',
        9 => 'group_summary',
        10 => 'field_hobbies',
        11 => 'group_interests',
        12 => 'group_groups',
        13 => 'group_contact',
        14 => 'summary',
      ),
      'right' => array(
        0 => 'field_postal_address',
        1 => 'field_geo_location',
        2 => 'field_location',
        3 => 'group_location',
        4 => 'group_accomodation',
        5 => 'group_pictures',
        6 => 'field_photos',
        7 => 'field_i_live_with',
        8 => 'field_max_length_of_stay',
        9 => 'field_max_number_of_guests',
      ),
    ),
    'fields' => array(
      'name' => 'header',
      'field_phone_home' => 'left',
      'field_firstname' => 'header',
      'field_secondname' => 'header',
      'privatemsg_send_new_message' => 'left',
      'field_profile_summary' => 'left',
      'field_lastname' => 'header',
      'field_im' => 'left',
      'field_occupation' => 'header',
      'field_books' => 'left',
      'field_website' => 'header',
      'field_films' => 'left',
      'field_birth_date' => 'header',
      'field_gender' => 'header',
      'field_organisations_i_belong_to' => 'left',
      'group_audience' => 'left',
      'field_music' => 'left',
      'group_summary' => 'left',
      'field_hobbies' => 'left',
      'field_postal_address' => 'right',
      'group_interests' => 'left',
      'group_groups' => 'left',
      'field_geo_location' => 'right',
      'field_location' => 'right',
      'group_contact' => 'left',
      'summary' => 'left',
      'group_location' => 'right',
      'group_accomodation' => 'right',
      'group_pictures' => 'right',
      'field_photos' => 'right',
      'field_i_live_with' => 'right',
      'field_max_length_of_stay' => 'right',
      'field_max_number_of_guests' => 'right',
    ),
    'classes' => array(),
  );
  $export['user|user|full'] = $ds_layout;

  return $export;
}
