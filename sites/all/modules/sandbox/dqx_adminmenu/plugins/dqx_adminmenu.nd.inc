<?php


/**
 * Implements hook_dqx_adminmenu_structure_alter()
 */
function nd_dqx_adminmenu_structure_alter($structure) {

  foreach (node_get_types() as $type) {
    $type_path = 'admin/content/node-type/' . str_replace('_', '-', $type->type);
    $display_path = $type_path . '/display';
    $nd_path = 'admin/build/ds/layout/' . str_replace('_', '-', $type->type);
    if ($structure->hasSubmenu($type_path)) {
      if (module_exists('nd') && user_access('administer nd')) {
        $structure->setSubmenu($display_path, new _dqx_adminmenu_DisplayFieldsTablePlugin($type));
      }
    }
  }
}


class _dqx_adminmenu_DisplayFieldsTablePlugin {

  protected $_type;
  protected $_typePath;
  protected $_displayPath;
  protected $_ndPath;

  function __construct($type) {
    $this->_type = $type;
    $this->_typePath = 'admin/content/node-type/'. str_replace('_', '-', $type->type);
    $this->_displayPath = $type_path .'/display';
    $this->_ndPath = 'admin/build/ds/layout/'. str_replace('_', '-', $type->type);
  }

  function render(_dqx_adminmenu_MenuTree $tree) {
    $type_path = 'admin/content/node-type/'. str_replace('_', '-', $this->_type->type);
    $nd_root = 'admin/build/ds/layout/'. str_replace('_', '-', $this->_type->type);
    $cck_root = $type_path . '/display';
    $all_build_modes = ds_get_build_modes(NULL, TRUE);
    $build_modes = $all_build_modes['nd'];
    if (!empty($build_modes)) {
      $exclude_matrix = variable_get('nd_buildmodes_exclude', array());
      $excluded_build_modes = $exclude_matrix[$this->_type->type];

      $nd_items = array();
      $cck_item_groups = array();
      foreach ($build_modes as $key => $build_mode) {
        $cck_path = $this->_cckBuildModePath($key, $type_path);
        $nd_item_groups[$cck_path][$key] = $tree->getItem($nd_root .'/'. $key);
      }

      $html = '';
      foreach ($nd_item_groups as $cck_path => $nd_items) {
        $cck_item = $tree->getItem($cck_path);
        $options = is_array($cck_item['localized_options']) ? $cck_item['localized_options'] : array();
        $title = t('CCK: !link_title', array('!link_title' => $cck_item['title']));
        $cck_link = $cck_item ? l($title, $cck_item['link_path'], $options) : '';
        $rowspan = count($nd_items);
        $tbody = '';
        $cck_cell = '<td class="dqx_adminmenu-display-cck" rowspan="'. $rowspan .'">'. $cck_link .'</td>';
        foreach ($nd_items as $key => $nd_item) {
          // Check if build mode is excluded for this object type.
          $tr_attr = dqx_adminmenu_tag_attributes();
          $excluded = TRUE && isset($exclude_build_modes[$key]) && ($exclude_build_modes[$key] == TRUE);
          if ($excluded) {
            $tr_attr->addClass('nd-excluded');
          }
          $options = is_array($nd_item['localized_options']) ? $nd_item['localized_options'] : array();
          $title = t('ND: !link_title', array('!link_title' => $nd_item['title']));
          $nd_link = $nd_item ? l($title, $nd_item['link_path'], $options) : '';
          $tbody .= '<tr><td class="dqx_adminmenu-display-nd">'. $nd_link .'</td>'. $cck_cell .'</tr>';
          $cck_cell = '';
        }
        $html .= '<tbody>' . $tbody . '</tbody>';
      }

      $title_cck = t('CCK');
      $title_nd = t('Display suite (nd)');
      return <<<EOT
<table class="dqx_adminmenu-table">
<thead><tr><td class="no-link">$title_cck</td><td class="no-link">$title_nd</td></tr></thead>
$html
</table>
EOT;
    }
  }

  protected function _cckBuildModePath($nd_key, $type_path) {
    if (is_numeric($nd_key) || $nd_key === 'sticky') {
      return $type_path .'/display/nd';
    }
    else if ($nd_key === 'full' || $nd_key === 'teaser') {
      return $type_path .'/display';
    }
    else {
      return $type_path .'/display/'. $nd_key;
    }
  }
}



