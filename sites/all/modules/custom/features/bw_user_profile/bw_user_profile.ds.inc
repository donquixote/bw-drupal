<?php
/**
 * @file
 * bw_user_profile.ds.inc
 */

/**
 * Implementation of hook_ds_layout_settings_info().
 */
function bw_user_profile_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass;
  $ds_layout->api_version = 1;
  $ds_layout->id = 'profile2|main|default';
  $ds_layout->entity_type = 'profile2';
  $ds_layout->bundle = 'main';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'regions' => array(
      'left' => array(
        0 => 'field_photos',
        1 => 'field_profile_summary',
        2 => 'field_birth_date',
        3 => 'field_occupation',
        4 => 'field_gender',
        5 => 'field_firstname',
        6 => 'field_lastname',
        7 => 'field_secondname',
        8 => 'group_contactinfo',
        9 => 'field_street',
        10 => 'field_housenumber',
        11 => 'field_zipcode',
        12 => 'field_phone_home',
        13 => 'field_im',
        14 => 'field_website',
      ),
      'right' => array(
        0 => 'field_max_length_of_stay',
        1 => 'field_max_number_of_guests',
        2 => 'field_i_live_with',
        3 => 'field_films',
        4 => 'field_books',
        5 => 'field_hobbies',
        6 => 'field_music',
        7 => 'field_organisations_i_belong_to',
      ),
    ),
    'fields' => array(
      'field_photos' => 'left',
      'field_profile_summary' => 'left',
      'field_birth_date' => 'left',
      'field_occupation' => 'left',
      'field_gender' => 'left',
      'field_firstname' => 'left',
      'field_lastname' => 'left',
      'field_secondname' => 'left',
      'group_contactinfo' => 'left',
      'field_max_length_of_stay' => 'right',
      'field_street' => 'left',
      'field_max_number_of_guests' => 'right',
      'field_housenumber' => 'left',
      'field_i_live_with' => 'right',
      'field_zipcode' => 'left',
      'field_films' => 'right',
      'field_phone_home' => 'left',
      'field_im' => 'left',
      'field_books' => 'right',
      'field_hobbies' => 'right',
      'field_website' => 'left',
      'field_music' => 'right',
      'field_organisations_i_belong_to' => 'right',
    ),
    'classes' => array(),
  );
  $export['profile2|main|default'] = $ds_layout;

  return $export;
}
