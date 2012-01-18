<?php


function content_dqx_adminmenu_items_alter($items) {

  // root for the content table
  $item = $items->getItem('node/add');
  $item['weight'] = -9;
  $items->addItem('admin/node-types', $item);

  // some modifications in the content submenu
  $items->itemSetValue('admin/node-types', 'title', t('Node'));
  // $items->itemSetValue('node/add', 'weight', 0);
}


/**
 * Implements hook_dqx_adminmenu_structure_alter()
 */
function content_dqx_adminmenu_structure_alter($structure) {

  foreach (node_get_types() as $type) {

    $type_path = 'admin/content/node-type/' . str_replace('_', '-', $type->type);
    $fields_path = $type_path . '/fields';
    $display_path = $type_path . '/display';

    if ($structure->hasSubmenu($type_path)) {
      $structure->submenuAddClass($type_path, 'dqx_adminmenu-node-type');

      // edit type
      $structure->itemSetTitle($type_path . '/edit', t('Edit type'));
      $structure->itemSetWeight($type_path . '/edit', -5);

      // display
      $structure->itemSetTitle($display_path, t('Display'));
      $structure->itemSetWeight($display_path, 20);

      // fields
      $structure->itemSetTitle($fields_path, t('Fields (!count)', array(
        '!count' => $structure->submenuCountChildren($fields_path)
      )));
      $structure->submenuSetInlineChild($type_path, $type_path . '/fields');
    }
  }

  $structure->setSubmenu('admin/node-types', new _dqx_adminmenu_ContentTablePlugin());

  // We don't need the "Create content" in the "Content" menu anymore.
  $structure->submenuRemoveChild('admin/content', 'node/add');
}


/**
 * This only makes sense in combination with admin_views.
 * I recommend this module anyway, so we assume that it is enabled.
 */
class _dqx_adminmenu_ContentTablePlugin {

  protected function _getColumns($tree) {
    $cols = array();
    $cols['celltip'] = '';
    if ($tree->pathAccess('admin/content/node')) {
      $cols['list'] = 'List';
    }
    $cols['create'] = 'Create';
    if (user_access('administer content types')) {
      $cols['submenu'] = '';
    }
    return $cols;
  }

  protected function _buildMatrix(array $types, array &$cols, _dqx_adminmenu_MenuTree $tree) {
    $cols_cellcount = array();
    $rows_cellcount = array();
    $matrix = array();
    foreach ($types as $type) {
      $type->slug = str_replace('_', '-', $type->type);
      $type->attr = dqx_adminmenu_class_attribute('node-type node-type-'. $type->type);
      $row_cellcount = 0;
      $row_cells = array();
      $submenu_key = 'admin/content/node-type/' . $type->slug;
      $submenu = $tree->renderMenu($submenu_key);
      if ($submenu) {
        $type->attr->addClass('expandable');
        $type->submenu = $submenu;
      }
      foreach ($cols as $key => $title) {
        $method = '_cell__'. $key;
        $td_attr = dqx_adminmenu_class_attribute('td-' . $key);
        if ($submenu && $key === 'create') {
          $td_attr->addClass('expandable');
        }
        if ($key === 'space') {
          $cell = '';
        }
        elseif ($key === 'celltip') {
          $cell = '';
          $td_attr->addClass('td-celltip-left');
        }
        elseif (method_exists($this, $method)) {
          $cell = $this->$method($type, $td_attr, $tree);
          if ($cell && !$td_attr->hasClass('no-access')) {
            ++$cols_cellcount[$key];
            ++$row_cellcount;
          }
          else {
            $td_attr->addClass('empty');
          }
        }
        $row_cells[$key] = array($td_attr, $cell);
      }
      if ($row_cellcount) {
        $matrix[$type->type] = $row_cells;
      }
    }
    foreach ($cols_cellcount as $key => $count) {
      if (!$count) {
        unset($cols[$key]);
      }
    }
    $keys_reverse = array_reverse(array_keys($cols));
    if ($keys_reverse[0] === 'space') {
      unset($cols['space']);
    }
    if ($keys_reverse[0] === 'submenu' && $keys_reverse[1] === 'space') {
      unset($cols['space']);
    }
    return $matrix;
  }

  protected function _renderHeader(array $cols) {
    $html = '';
    foreach ($cols as $key => $title) {
      switch ($key) {
        case 'submenu':
          $html .= '<td class="td-submenu"></td>';
          break;
        case 'celltip':
          $html .= '<td class="td-celltip"></td>';
          break;
        default:
          $html .= '<td class="no-link">'. $title .'</td>';
      }
    }
    return '<thead><tr>'. $html .'</tr></thead>';
  }

  protected function _renderFooter(array $cols, _dqx_adminmenu_MenuTree $tree) {
    if ($tree->pathAccess('admin/content/types/add')) {
      $link = l('Add type', 'admin/content/types/add');
      $cells['create'] = $link;
      $cell_classes['create'] = 'admin-content-type-add';
      $row = '';
      foreach ($cols as $key => $title) {
        $class = isset($cell_classes[$key]) ? $cell_classes[$key] : 'no-link';
        $class .= " td-$key";
        $cell = isset($cells[$key]) ? $cells[$key] : '';
        $row .= '<td class="'. $class . '">'. $cell .'</td>';
      }
      $space_row = '<td class="no-link" colspan="' . count($cols) . '">&nbsp;</td>';
      return '<tfoot><tr class="space">' . $space_row . '</tr><tr>' . $row . '</tr></tfoot>';
    }
  }

  function render(_dqx_adminmenu_MenuTree $tree) {
    $cols = $this->_getColumns($tree);
    $types = array();
    $order = array();
    foreach (node_get_types() as $type) {
      $types[$type->type] = clone $type;
      $order[$type->type] = $type->name;
    }
    array_multisort($order, $types);

    $matrix = $this->_buildMatrix($types, $cols, $tree);

    $html = '';
    foreach ($types as $type) {
      if ($matrix[$type->type]) {
        $row_html = '';
        foreach ($cols as $key => $title) {
          list($td_attr, $cell) = $matrix[$type->type][$key];
          $td_attr->addClass('td-' . $key);
          $row_html .= $td_attr->TD($cell);
        }
        $html .= $type->attr->TR($row_html);
      }
    }
    $tbody = '<tbody>'. $html .'</tbody>';

    $thead = $this->_renderHeader($cols);
    $tfoot = $this->_renderFooter($cols, $tree);
    return '<table class="celltip">'. $thead . $tfoot . $tbody .'</table>';
  }

  protected function _cell__celltip($type, $tr_attr) {
    return '';
  }

  protected function _cell__list($type, $td_attr) {
    $q = db_query("SELECT COUNT(nid) n FROM {node} WHERE type = '%s'", $type->type);
    if ($row = db_fetch_object($q)) {
      $title = '<span class="node-count">' . $row->n . '</span>';
    }
    else {
      $title = 'list';
    }
    return l($title, 'admin/content/node', array(
      'query' => array('type' => $type->type),
      'html' => TRUE,
    ));
  }

  protected function _cell__create($type, $td_attr, $tree) {
    $link_attr = $tree->itemLinkAttributes('node/add/' . $type->slug, $td_attr);
    if (!$link_attr) {
      return '<!-- ' . $type->slug . ' -->';
    }
    else {
      return $link_attr->A($type->name);
    }
  }

  protected function _cell__configure($type, $td_attr) {
    return l('conf', 'admin/content/node-type/' . $type->slug);
  }

  protected function _cell__fields($type, $td_attr) {
    return l('fields', 'admin/content/node-type/' . $type->slug .'/fields');
  }

  protected function _cell__display($type, $td_attr) {
    return l('display', 'admin/content/node-type/' . $type->slug .'/display');
  }

  protected function _cell__submenu($type, $td_attr, $tree) {
    if ($type->submenu) {
      return '<div>' . $type->submenu . '</div>';
    }
  }
}

