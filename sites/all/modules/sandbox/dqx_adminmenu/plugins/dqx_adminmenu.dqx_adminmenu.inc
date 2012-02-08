<?php


function dqx_adminmenu_dqx_adminmenu_items() {
  return _dqx_adminmenu_icon_items();
}


function dqx_adminmenu_dqx_adminmenu_items_alter($items) {

  // change weights and titles
  $items->itemSetWeight('admin/build', -8);
  $items->itemSetTitle('admin/build', t('Build'));
  $items->itemSetTitle('admin/content', t('Content'));
  $items->itemSetTitle('admin/settings', t('Configure'));
  $items->itemSetTitle('admin/user', t('People'));
}


function dqx_adminmenu_dqx_adminmenu_structure_alter($structure) {
  $structure->submenuSetAttribute('admin', 'id', 'dqx_adminmenu-admin');
  $structure->submenuSetAttribute('dqx-adminmenu-user', 'id', 'dqx_adminmenu-user');
  $structure->submenuSetInlineChild('admin/dqx-adminmenu', 'admin/dqx-adminmenu/flush-cache');

  // Some more "inline child" stuff, that we don't want to make separate plugins for.
  foreach (array(
    'admin/content/backup_migrate/export',
    'admin/content/backup_migrate/destination/list',
    'admin/content/backup_migrate/profile/list',
    'admin/content/backup_migrate/schedule/list',
    'admin/content/nodewords/meta-tags',
    'admin/build/block/list',
    'admin/build/views/tools',
    'admin/settings/date-time/formats',
    'admin/messaging/settings',
    'admin/settings/imageapi/config',
    'admin/user/captcha/captcha',
    // ubercart
    // 'admin/store/settings',
    'admin/store/settings/cart/edit',
    'admin/store/settings/checkout/edit',
    'admin/store/settings/countries/edit',
    'admin/store/settings/orders/edit',
    'admin/store/settings/payment/edit',
    'admin/store/settings/products/edit',
    'admin/store/settings/store/edit',
    'admin/store/settings/quotes/methods',
    'admin/store/ca/overview',
  ) as $parent => $child) {
    if (is_numeric($parent)) {
      $fragments = explode('/', $child);
      $parent = implode('/', array_slice($fragments, 0, count($fragments) - 1));
    }
    $structure->submenuSetInlineChild($parent, $child);
  }
}


/**
 * Build icon menu links; mostly containing maintenance helpers.
 *
 * @see theme_admin_menu_links()
 */
function _dqx_adminmenu_icon_items() {

  $items = array();
  $items['admin/dqx-adminmenu'] = _dqx_adminmenu_icon_item();
  // Add link to manually run cron.
  $items['admin/dqx-adminmenu/cron'] = array(
    'title' => t('Run cron'),
    'weight' => 50,
    'access' => user_access('administer site configuration'),
    'link_path' => 'admin/reports/status/run-cron',
  );
  // Add link to run update.php.
  $items['admin/dqx-adminmenu/update'] = array(
    'title' => t('Run updates'),
    'weight' => 50,
    'access' => ($GLOBALS['user']->uid == 1 || !empty($GLOBALS['update_free_access'])),
    'link_path' => base_path() . 'update.php',
    'localized_options' => array(
      'external' => TRUE,
    ),
  );
  // Add items to flush caches.
  $items['admin/dqx-adminmenu/flush-cache'] = array(
    'title' => t('Flush all caches'),
    'weight' => 20,
    // @todo Add permission to flush cashes.
    'access' => user_access('administer site configuration'),
    'link_path' => 'admin/dqx-adminmenu/flush-cache',
    'localized_options' => array(
      'attributes' => array('class' => 'dqx_adminmenu-redirect'),
    ),
    'redirect' => TRUE,
    'action' => TRUE,
  );
  $caches = array(
    // 'admin_menu' => t('Administration menu'),
    'cache' => t('Cache tables'),
    'menu' => t('Menu rebuild'),
    'css-js' => t('CSS+JS+Page'),
    'theme' => t('Theme registry'),
  );
  foreach ($caches as $arg => $title) {
    $items['admin/dqx-adminmenu/flush-cache/' . $arg] = array(
      'title' => $title,
      'link_path' => 'admin/dqx-adminmenu/flush-cache/' . $arg,
      'access' => user_access('administer site configuration'),
      'action' => TRUE,
      'redirect' => TRUE,
    );
  }
  // Add link to toggle developer modules (performance).
  $saved_state = variable_get('admin_menu_devel_modules_enabled', NULL);
  $items['admin/dqx-adminmenu/toggle-modules'] = array(
    'title' => isset($saved_state) ? t('Enable developer modules') : t('Disable developer modules'),
    'weight' => 88,
    'access' => user_access('administer site configuration'),
    'link_path' => 'admin/dqx-adminmenu/toggle-modules',
    'redirect' => TRUE,
    'action' => TRUE,
  );

  // Add Devel module links.
  if (module_exists('devel')) {
    // Add variable editor.
    $items['admin/dqx-adminmenu/devel-variables'] = array(
      'title' => t('Variable editor'),
      'weight' => 20,
      'access' => user_access('access devel information'),
      'link_path' => 'devel/variable',
    );
  }

  foreach ($items as $path => $item) {
    if (!empty($item['action'])) {
      @$items[$path]['localized_options']['attributes']['class'] .= ' dqx_adminmenu-action';
      unset($items[$path]['action']);
    }
    if (!empty($item['redirect'])) {
      @$items[$path]['localized_options']['attributes']['class'] .= ' dqx_adminmenu-redirect';
      unset($items[$path]['redirect']);
    }
  }

  return $items;
}


function _dqx_adminmenu_icon_item() {

  $icon_src = theme_get_setting('toggle_favicon') ? theme_get_setting('favicon') : base_path() . 'misc/favicon.ico';
  $icon_img = '<img id="dqx_adminmenu-icon-img" src="' . $icon_src . '" width="16" height="16" alt="' . t('Home') . '" />';

  return array(
    'title' => $icon_img,
    'access' => TRUE,  // everyone should see the front page
    'weight' => -100,
    'link_path' => '<front>',
    'localized_options' => array(
      'attributes' => array('id' => 'dqx_adminmenu-icon-link'),
      'html' => TRUE,
    ),
  );
}


