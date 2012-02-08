<?php


/**
 * Implements hook_drush_command().
 */
function drux_drush_command() {
  $items['drux-enable-dependencies'] = array(
    'description' => 'Download and enable dependencies of existing modules.',
    // 'arguments' => array(),
    'aliases' => array('dep'),
  );
  $items['drux-find-obsolete'] = array(
    'description' => 'Find modules that are not direct or indirect dependencies of the modules given as arguments',
    'arguments' => array(
      'modules' => 'List of modules to seed the dependencies.',
    ),
    'aliases' => array('obs'),
  );
  return $items;
}


/**
 * Command callback. Enable one or more extensions from downloaded projects.
 */
function drush_drux_enable_dependencies() {

  // Include update engine so we can use update_check_incompatibility().
  drush_include_engine('drupal', 'update');

  $extinfo = new drux_ExtensionInfo();
  $enabled_keys = $extinfo->enabledKeys();

  $recheck = TRUE;
  while ($recheck) {
    $recheck = FALSE;

    // Classify extensions in themes, modules or unknown.
    list($modules, $themes) = $extinfo->classify($enabled_keys);

    $extensions = array_merge($modules, $themes);

    // Discard incompatible extensions.
    $break = !$extinfo->checkCompatibility($extensions);
    if ($break) {
      return;
    }

    if (!empty($modules)) {
      // Check module dependencies.
      $dependencies = $extinfo->checkModuleDependencies($modules);
      $recheck = $extinfo->downloadMissingProjects($dependencies);
    }
  }

  if (!empty($modules)) {
    list($modules, $required_by) = $extinfo->expandToDependencies($modules, $dependencies);
    if ($modules === FALSE) {
      return;
    }
  }

  $modules = $extinfo->toBeEnabled($modules);

  if (empty($modules)) {
    return drush_log(dt('There were no extensions that could be enabled.'), 'ok');
  }

  $modules_text = array();
  foreach ($modules as $module) {
    if (!empty($required_by[$module])) {
      $required_by_text = implode(', ', $required_by[$module]);
      $modules_text[$module] = " - $module, required by [$required_by_text]";
    }
    else {
      $modules_text[$module] = " - $module";
    }
  }

  drush_print(dt(
    "The following extensions will be enabled:\n!extensions\n", 
    array('!extensions' => implode("\n", $modules_text))
  ));

  if(!drush_confirm(dt('Do you really want to continue?'))) {
    return drush_user_abort();
  }

  // Enable modules and pass dependency validation in form submit.
  if (!empty($modules)) {
    drush_module_enable($modules);
    drush_system_modules_form_submit(pm_module_list());
  }

  // Inform the user of final status.
  $rsc = drush_db_select(
    'system',
    array('name', 'status'),
    'name IN (:extensions)',
    array(':extensions' => $extensions)
  );
  $problem_extensions = array();
  $searchpath = array();
  while ($extension = drush_db_fetch_object($rsc)) {
    if ($extension->status) {
      drush_log(dt(
        '!extension was enabled successfully.',
        array('!extension' => $extension->name)
      ), 'ok');
      $searchpath[] = $extinfo->extensionPath($extension->name);
    }
    else {
      $problem_extensions[] = $extension->name;
    }
  }
  // Add all modules that were enabled to the drush
  // list of commandfiles (if they have any).  This
  // will allow these newly-enabled modules to participate
  // in the post_pm_enable hook.
  if (!empty($searchpath)) {
    _drush_add_commandfiles($searchpath);
  }
  if (!empty($problem_extensions)) {
    return drush_set_error('DRUSH_PM_ENABLE_EXTENSION_ISSUE', dt(
      'There was a problem enabling !extension.',
      array('!extension' => implode(',', $problem_extensions))
    ));
  }
}


function drush_drux_enable_dependencies_() {

  // xautoload should find that..
  $extinfo = new drux_ExtensionInfo();
  $tracker = new drux_DependencyTracker($extinfo);
  $tracker->requireModules($extinfo->enabledKeys());

  while ($dl = $tracker->toBeDownloaded()) {
    $extinfo->confirmDownload($dl);
  }

  while ($en = $tracker->toBeEnabled()) {
    $extinfo->confirmEnable($en);
    $tracker->refresh();
  }
}


function drush_drux_find_obsolete() {

  $args = drux_parse_arguments(func_get_args());

  // xautoload should find that..
  $extinfo = new drux_ExtensionInfo();
  $tracker = new drux_DependencyTracker($extinfo);
  $tracker->requireModules(array(
    'field', 'field_sql_storage', 'filter', 'image', 'list', 'node', 'number',
    'system', 'taxonomy', 'text', 'user'
  ));
  $tracker->requireModules($args);
  $obsolete = $tracker->obsoleteModules();
  print count($obsolete) . "\n";
  print implode(" ", $obsolete) . "\n";
}


/**
 * Sanitize user provided arguments to several pm commands.
 *
 * Return an array of arguments off a space and/or comma separated values. It also
 * lowercase arguments and optionally convert dashes to underscores.
 */
function drux_parse_arguments($args, $dashes_to_underscores = TRUE, $lowercase = TRUE) {
  $arguments = _convert_csv_to_array($args);
  foreach ($arguments as $key => $argument) {
    $argument = ($dashes_to_underscores) ? strtr($argument, '-', '_') : $argument;
    if ($lowercase) {
      $arguments[$key] = strtolower($argument);
    }
  }
  return $arguments;
}



