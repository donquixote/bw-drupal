<?php


/**
 * Crumbs plugin.
 * Adapted from the native crumbs plugin for og.
 */
class bw_groups_CrumbsMonoPlugin implements crumbs_MonoPlugin {

  function describe($api) {
    return t('Breadcrumbs for BW Groups');
  }

  function findParent__node_x($path, $item) {
    $node = $item['map'][1];
    if (isset($node->group_audience['und'])) {
      foreach ($node->group_audience['und'] as $group_info) {
        // Just pick the first one..
        $gid = $group_info['gid'];
        $row = db_query("SELECT * FROM {og} WHERE gid = :gid", array(':gid' => $gid))->fetchObject();
        if ($row && $row->entity_type === 'node') {
          $etid = $row->etid;
          switch ($node->type) {
            case 'group_discussion':
              return "node/$etid/forum";
          }
        }
      }
    }
  }
}
