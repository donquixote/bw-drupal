<?php


function user_dqx_adminmenu_items() {
  $items = array();
  if ($uid = $GLOBALS['user']->uid) {
    $items = _dqx_adminmenu_user_items($uid);
    if (FALSE) {
      $account_items = _dqx_adminmenu_router_items("path LIKE 'user/%/%%'  OR  path = 'user/%'", array(), array(
        'user/%' => 'user/' . $uid,
      ));
      $items = array_merge($items, $account_items);
    }
  }
  return $items;
}


function user_dqx_adminmenu_items_alter($items) {
  $items->parentMap('user/' . $GLOBALS['user']->uid, 'dqx-adminmenu-user/account');
}


/**
 * Build user/action links; mostly account information and links.
 *
 * @see theme_admin_menu_links()
 */
function _dqx_adminmenu_user_items($uid) {
  // dummy parent item
  $items['dqx-adminmenu-user'] = array();
  /*
  $items['dqx-adminmenu-user/counter'] = array(
    'title' => _dqx_adminmenu_get_user_count(),
    'weight' => -90,
    'localized_options' => array('attributes' => array(
      'id' => 'dqx_adminmenu-user-counter',
      'title' => t('Current anonymous / authenticated users'),
    )),
    'link_path' => (user_access('administer users') ? 'admin/user/user' : 'user'),
    'access' => TRUE,
  );
  */
  $items['dqx-adminmenu-user/account'] = array(
    'title' => $GLOBALS['user']->name,
    'weight' => -99,
    'localized_options' => array(
      'attributes' => array('id' => 'dqx_adminmenu-user-account'),
    ),
    'link_path' => 'user/' . $uid,
    'access' => TRUE,
  );
  $items['dqx-adminmenu-user/logout'] = array(
    'title' => t('Log out'),
    'weight' => -100,
    'attributes' => array('id' => 'dqx_adminmenu-user-logout'),
    'link_path' => 'logout',
    'access' => TRUE,
  );

  return $items;
}


function _dqx_adminmenu_get_user_count() {
  $interval = time() - variable_get('user_block_seconds_online', 900);
  $count_anon = sess_count($interval);
  $count_auth = db_result(db_query("SELECT COUNT(DISTINCT uid) FROM {sessions} WHERE uid > 0 AND timestamp >= %d", $interval));

  return t('@count-anon / @count-auth', array('@count-anon' => $count_anon, '@count-auth' => $count_auth));
}


