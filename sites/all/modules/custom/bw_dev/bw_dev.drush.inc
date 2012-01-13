<?php


/**
 * Implements hook_drush_command().
 */
function bw_dev_drush_command() {
  $items['bw-dev-dependencies'] = array(
    'description' => 'Enable dependencies of existing modules.',
    // 'arguments' => array(),
    'aliases' => array('dep'),
  );
  return $items;
}


/**
 * Command callback. Enable one or more extensions from downloaded projects.
 */
function drush_bw_dev_dependencies() {
  // Include update engine so we can use update_check_incompatibility().
  drush_include_engine('drupal', 'update');

  $extinfo = new _bw_dev_ExtensionInfo();
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


class _bw_dev_ExtensionInfo {

  protected $extensionInfo;

  function __construct() {
    $this->refresh();
  }

  function refresh() {
    $this->extensionInfo = drush_get_extensions();
  }

  function enabledKeys() {
    $result = array();
    foreach ($this->extensionInfo as $key => $info) {
      if ($info->status) {
        $result[] = $key;
      }
    }
    return $result;
  }

  function classify(&$list) {
    $modules = array();
    $themes = array();
    drush_pm_classify_extensions($list, $modules, $themes, $this->extensionInfo);
    return array($modules, $themes);
  }

  function checkCompatibility($extensions) {
    $ok = TRUE;
    foreach ($extensions as $name) {
      // Check if is compatible with Drupal core.
      if (update_check_incompatibility($name, $this->extensionInfo[$name]->type)) {
        drush_set_error('DRUSH_PM_ENABLE_MODULE_INCOMPATIBLE', dt(
          '!name is incompatible with the Drupal version.',
          array('!name' => $name)
        ));
        $ok = FALSE;
      }
    }
    return $ok;
  }

  function checkModuleDependencies($modules) {
    return drush_check_module_dependencies($modules, $this->extensionInfo);
  }

  function unmetDependencies($dependencies) {
    $unmet_dependencies = array();
    foreach ($dependencies as $module => $info) {
      if (!empty($info['unmet-dependencies'])) {
        foreach ($info['unmet-dependencies'] as $unmet_module) {
          $unmet_project = drush_pm_find_project_from_extension($unmet_module);
          if (!empty($unmet_project)) {
            $unmet_dependencies[$module][$unmet_project] = $unmet_project;
          }
        }
      }
    }
    return $unmet_dependencies;
  }

  function warnUnmetProjects($unmet_dependencies) {
    $msgs = array();
    $unmet_project_list = array();
    foreach ($unmet_dependencies as $module => $unmet_projects) {
      $unmet_project_list = array_merge($unmet_project_list, $unmet_projects);
      $msgs[] = dt("!module requires !unmet-projects", array(
        '!unmet-projects' => implode(', ', $unmet_projects),
        '!module' => $module
      ));
    }
    return array($unmet_project_list, $msgs);
  }

  function downloadMissingProjects($dependencies) {
    $recheck = FALSE;
    $unmet_dependencies = $this->unmetDependencies($dependencies);
    if (!empty($unmet_dependencies)) {
      list($unmet_project_list, $msgs) = $this->warnUnmetProjects($unmet_dependencies);
      $confirmed = drush_confirm(dt(
        "The following projects have unmet dependencies:\n!list\nWould you like to download them?",
        array('!list' => implode("\n", $msgs))
      ));
      if ($confirmed) {
        $result = drush_invoke_process_args('pm-download', $unmet_project_list, array('y' => TRUE));
        // Refresh module cache after downloading the new modules.
        $this->refresh();
        $recheck = TRUE;
      }
    }
    return $recheck;
  }

  function expandToDependencies($modules, $dependencies) {
    $all_dependencies = array();
    $required_by = array();
    $dependencies_ok = TRUE;
    foreach ($dependencies as $key => $info) {
      if (isset($info['error'])) {
        unset($modules[$key]);
        $dependencies_ok = drush_set_error($info['error']['code'], $info['error']['message']);
      }
      elseif (!empty($info['dependencies'])) {
        // Make sure we have an assoc array.
        $assoc = drupal_map_assoc($info['dependencies']);
        foreach ($assoc as $dep) {
          $required_by[$dep][$key] = $key;
        }
        $all_dependencies = array_merge($all_dependencies, $assoc);
      }
    }
    if (!$dependencies_ok) {
      return FALSE;
    }
    $modules = array_diff(array_merge($modules, $all_dependencies), pm_module_list());
    // Discard modules which doesn't meet requirements.
    require_once drush_get_context('DRUSH_DRUPAL_ROOT') . '/includes/install.inc';
    foreach ($modules as $key => $module) {
      // Check to see if the module can be installed/enabled (hook_requirements).
      // See @system_modules_submit
      if (!drupal_check_module($module)) {
        unset($modules[$key]);
        drush_set_error('DRUSH_PM_ENABLE_MODULE_UNMEET_REQUIREMENTS', dt(
          'Module !module doesn\'t meet the requirements to be enabled.',
          array('!module' => $module)
        ));
        _drush_log_drupal_messages();
        return FALSE;
      }
    }
    return array($modules, $required_by);
  }

  function toBeEnabled($modules) {
    $to_be_enabled = array();
    foreach ($modules as $module) {
      if (!$this->extensionInfo[$module]->status) {
        $to_be_enabled[$module] = $module;
      }
    }
    return $to_be_enabled;
  }

  function extensionPath($name) {
    return dirname($this->extensionInfo[$name]->filename);
  }
}











