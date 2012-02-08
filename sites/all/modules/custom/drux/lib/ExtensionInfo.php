<?php


/**
 * This code is just adapted from drush pm, and sliced into separate methods.
 * It does not pretend to be quality code, but at least it's not one big
 * function.
 */
class drux_ExtensionInfo {

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

  function moduleDependencies($module) {
    if (isset($this->extensionInfo[$module])) {
      return array_keys($this->extensionInfo[$module]->requires);
    }
  }

  function moduleStatus($module) {
    if (isset($this->extensionInfo[$module])) {
      return $this->extensionInfo[$module]->status;
    }
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

