<?php


class crumbs_ActiveRecord_EntitySettings {

  protected $settings_key;
  protected $settings;

  function __construct($settings_key) {
    $this->settings_key = $settings_key;
    $this->load();
  }

  function load() {
    $this->settings = variable_get($this->settings_key, array());
  }

  function getAsText() {
    $indent = 0;
    $sections = array();
    foreach (array(
      // Only some types supported yet.
      'node' => 'node/%',
      'user' => 'user/%',
    ) as $type => $route) {
      $type_info = entity_get_info($type);
      $lines = array();
      $type_settings = isset($this->settings[$type]) ? $this->settings[$type] : array();
      $path = isset($type_settings['*']) ? $type_settings['*'] : '?';
      $k = "$type.*";
      $lines[$k] = $path;
      foreach ($type_info['bundles'] as $bundle => $bundle_info) {
        $path = isset($type_settings[$bundle]) ? $type_settings[$bundle] : '?';
        $k = "$type.$bundle";
        $lines[$k] = $path;
        $l = strlen($k);
        $indent = ($indent > $l) ? $indent : $l;
      }
      if (count($lines)) {
        $sections[$type] = $lines;
      }
    }
    foreach ($sections as $type => $lines) {
      foreach ($lines as $k => $path) {
        $space = str_repeat(' ', $indent - strlen($k));
        $lines[$k] = "$k $space= $path";
      }
      $sections[$type] = implode("\n", $lines);
    }
    return implode("\n\n", $sections);
  }

  function setAsText($text) {
    $lines = explode("\n", $text);
    foreach ($lines as $line) {
      if (preg_match('#^([^\.]+)\.(\S+)\s*\=\s*(.*+)$#', $line, $m)) {
        list(,$type, $bundle, $path) = $m;
        if ($path === '?') {
          unset($this->settings[$type][$bundle]);
        }
        else {
          $this->settings[$type][$bundle] = $path;
        }
      }
    }
  }

  function save() {
    variable_set($this->settings_key, $this->settings);
  }
}
