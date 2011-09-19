<?php

/**
 * Implementation of hook_profile_details().
 */
function bewelcome_profile_details() {
  return array(
    'name' => 'BeWelcome on Drupal',
    'description' => 'BeWelcome on Drupal - experimental.',
    'old_short_name' => 'BeWelcome',
  );
}

/**
 * Implementation of hook_profile_modules().
 */
function bewelcome_profile_modules() {
  $modules = array(
     // Drupal core
    'image',
    'block',
    'comment',
    'blog',
    'filter',
    'help',
    'menu',
    'node',
    'openid',
    'search',
    'system', 
    'taxonomy',
    'text',
    'user',
    // Admin
    'admin_menu',
    // Views
    'views',
    // OG
    'og', 'og_ui', 'og_views',
    // CTools
    'ctools',
    // Features
    'features',
    // Token
    'pathauto', 'token',
    // Messaging
    'privatemsg', 'pm_email_notify',
    // Development
    'openidadmin', 'devel', 'migrate',
    'views_ui', 
    // This BW module has all other BW dependencies
    'bewelcome_main',
  );
  return $modules;
}


/**
 * Implementation of hook_profile_task_list().
 */
function bewelcome_profile_task_list() {
}

/**
 * Implementation of hook_profile_tasks().
 */
function bewelcome_profile_tasks(&$task, $url) {
}


/**
 * Alter some forms implementing hooks in system module namespace
 * This is a trick for hooks to get called, otherwise we cannot alter forms
 */

/**
 * @TODO: This might be impolite/too aggressive. We should at least check that
 * other install profiles are not present to ensure we don't collide with a
 * similar form alter in their profile.
 *
 * Set BeWelcome as default install profile.
 */
function system_form_install_select_profile_form_alter(&$form, $form_state) {
  foreach($form['profile'] as $key => $element) {
    $form['profile'][$key]['#value'] = 'bewelcome';
  }
}

/**
 * Set English as default language.
 * 
 * If no language selected, the installation crashes. I guess English should be the default 
 * but it isn't in the default install. @todo research, core bug?
 */
function system_form_install_select_locale_form_alter(&$form, $form_state) {
  $form['locale']['en']['#value'] = 'en';
}

/**
 * Alter the install profile configuration form and provide timezone location options.
 */
function system_form_install_configure_form_alter(&$form, $form_state) {
  $form['site_information']['site_name']['#default_value'] = 'BeWelcome on Drupal';
  $form['site_information']['site_mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST'];
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
  $form['admin_account']['account']['mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST'];

  if (function_exists('date_timezone_names') && function_exists('date_timezone_update_site')) {
    $form['server_settings']['date_default_timezone']['#access'] = FALSE;
    $form['server_settings']['#element_validate'] = array('date_timezone_update_site');
    $form['server_settings']['date_default_timezone_name'] = array(
      '#type' => 'select',
      '#title' => t('Default time zone'),
      '#default_value' => NULL,
      '#options' => date_timezone_names(FALSE, TRUE),
      '#description' => t('Select the default site time zone. If in doubt, choose the timezone that is closest to your location which has the same rules for daylight saving time.'),
      '#required' => TRUE,
    );
  }
}

function bewelcome_install() {
  // check http://drupal.org/node/585012
  theme_enable(array('bewelcometheme', 'seven'));
  variable_set('theme_default', 'bwminimal');
  variable_set('admin_theme', 'bwminimal');
}