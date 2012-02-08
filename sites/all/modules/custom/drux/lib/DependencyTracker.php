<?php


class drux_DependencyTracker {

  protected $extinfo;
  protected $en = array();
  protected $dl = array();
  protected $visited = array();
  protected $obsolete = array();

  function __construct($extensionInfo) {
    $this->extinfo = $extensionInfo;
    $enabled = $extensionInfo->enabledKeys();
    $this->obsolete = array_combine($enabled, $enabled);
  }

  function requireModules($modules) {
    foreach ($modules as $module) {
      if (!isset($this->visited[$module])) {
        $this->visited[$module] = $module;
        $this->_requireModule($module);
        $dependencies = $this->extinfo->moduleDependencies($module);
        if (!empty($dependencies)) {
          $this->requireModules($dependencies);
        }
      }
    }
  }

  function modulesToDownload() {
    return $this->dl;
  }

  function modulesToEnable() {
    return $this->en;
  }

  function obsoleteModules() {
    return $this->obsolete;
  }

  /**
   * This is called when new modules have been downloaded or enabled.
   */
  function refresh() {
    $missing = array_values($this->dl + $this->en);
    $this->dl = array();
    $this->en = array();
    $this->visited = array();
    $this->requireModules($missing);
  }

  protected function _requireModule($module) {
    $status = $this->extinfo->moduleStatus($module);
    if (!isset($status)) {
      $this->dl[$module] = $module;
    }
    elseif (!$status) {
      $this->en[$module] = $module;
    }
    unset($this->obsolete[$module]);
  }
}
