<?php
/**
 * @file
 * bw_user_profile.ds.inc
 */

/**
 * Implementation of hook_ds_custom_fields_info().
 */
function bw_user_profile_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass;
  $ds_field->api_version = 1;
  $ds_field->field = 'bw_full_name';
  $ds_field->label = 'Full name';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'profile2' => 'profile2',
  );
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
print $entity->field_firstname[\'und\'][0][\'value\'] . \' \' . $entity->field_secondname[\'und\'][0][\'value\'] . \' \' . $entity->field_lastname[\'und\'][0][\'value\'];
?>',
      'format' => 'ds_code',
    ),
    'use_token' => 1,
  );
  $export['bw_full_name'] = $ds_field;

  return $export;
}

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
        0 => 'bw_full_name',
        1 => 'field_photos',
        2 => 'field_profile_summary',
        3 => 'field_birth_date',
        4 => 'field_occupation',
        5 => 'field_gender',
        6 => 'field_street',
        7 => 'group_contactinfo',
        8 => 'field_housenumber',
        9 => 'field_zipcode',
        10 => 'field_phone_home',
        11 => 'field_im',
        12 => 'field_website',
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
      'bw_full_name' => 'left',
      'field_photos' => 'left',
      'field_profile_summary' => 'left',
      'field_birth_date' => 'left',
      'field_occupation' => 'left',
      'field_gender' => 'left',
      'field_street' => 'left',
      'group_contactinfo' => 'left',
      'field_max_length_of_stay' => 'right',
      'field_housenumber' => 'left',
      'field_zipcode' => 'left',
      'field_max_number_of_guests' => 'right',
      'field_phone_home' => 'left',
      'field_i_live_with' => 'right',
      'field_films' => 'right',
      'field_im' => 'left',
      'field_books' => 'right',
      'field_website' => 'left',
      'field_hobbies' => 'right',
      'field_music' => 'right',
      'field_organisations_i_belong_to' => 'right',
    ),
    'classes' => array(),
  );
  $export['profile2|main|default'] = $ds_layout;

  return $export;
}
