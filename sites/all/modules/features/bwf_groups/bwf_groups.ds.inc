<?php
/**
 * @file
 * bwf_groups.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function bwf_groups_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass;
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'comment|comment_node_group_discussion|default';
  $ds_fieldsetting->entity_type = 'comment';
  $ds_fieldsetting->bundle = 'comment_node_group_discussion';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'links' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'post_date' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'ds_post_date_long',
    ),
    'permalink' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bw_forum_author_pane' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bw_forum_forum_jump_links' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['comment|comment_node_group_discussion|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass;
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'comment|comment_node_group|default';
  $ds_fieldsetting->entity_type = 'comment';
  $ds_fieldsetting->bundle = 'comment_node_group';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'submitted' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'ds_user_picture' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'ds_picture_thumb-50',
    ),
  );
  $export['comment|comment_node_group|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass;
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|group_discussion|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'group_discussion';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => 'h3',
        'class' => '',
      ),
    ),
    'links' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'comments' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'post_date' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'ds_post_date_medium',
    ),
    'bw_forum_author_pane' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bw_forum_forum_jump_links' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|group_discussion|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass;
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|group_discussion|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'group_discussion';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => 'h3',
        'class' => '',
      ),
    ),
    'links' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'comments' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'author' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'author',
    ),
    'post_date' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'ds_post_date_privatemsg_current_day',
    ),
    'bw_forum_author_pane' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'bw_forum_forum_jump_links' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|group_discussion|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass;
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|group|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'group';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'comments' => array(
      'weight' => '4',
      'label' => 'above',
      'format' => 'default',
    ),
    'author' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'author',
    ),
    'views_content_ds__bw_group_posts' => array(
      'weight' => '3',
      'label' => 'above',
      'format' => 'panel_pane_1',
    ),
    'views_content_ds__bw_group_members' => array(
      'weight' => '6',
      'label' => 'above',
      'format' => 'panel_pane_2',
    ),
  );
  $export['node|group|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass;
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|group|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'group';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'views_content_ds__bw_group_posts' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'panel_pane_1',
    ),
  );
  $export['node|group|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass;
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|group|group_forum';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'group';
  $ds_fieldsetting->view_mode = 'group_forum';
  $ds_fieldsetting->settings = array(
    'views_content_ds__bw_group_posts' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'panel_pane_1',
    ),
  );
  $export['node|group|group_forum'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass;
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|group|group_members';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'group';
  $ds_fieldsetting->view_mode = 'group_members';
  $ds_fieldsetting->settings = array(
    'views_content_ds__bw_group_members' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'panel_pane_1',
    ),
  );
  $export['node|group|group_members'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function bwf_groups_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass;
  $ds_layout->api_version = 1;
  $ds_layout->id = 'comment|comment_node_group_discussion|default';
  $ds_layout->entity_type = 'comment';
  $ds_layout->bundle = 'comment_node_group_discussion';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'bw_forum_post';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'header_left' => array(
        0 => 'post_date',
      ),
      'bottom_middle_right' => array(
        0 => 'links',
      ),
      'header_right' => array(
        0 => 'permalink',
      ),
      'left' => array(
        0 => 'bw_forum_author_pane',
      ),
      'middle' => array(
        0 => 'comment_body',
      ),
      'bottom_left' => array(
        0 => 'bw_forum_forum_jump_links',
      ),
    ),
    'fields' => array(
      'post_date' => 'header_left',
      'links' => 'bottom_middle_right',
      'permalink' => 'header_right',
      'bw_forum_author_pane' => 'left',
      'comment_body' => 'middle',
      'bw_forum_forum_jump_links' => 'bottom_left',
    ),
    'classes' => array(),
  );
  $export['comment|comment_node_group_discussion|default'] = $ds_layout;

  $ds_layout = new stdClass;
  $ds_layout->api_version = 1;
  $ds_layout->id = 'comment|comment_node_group|default';
  $ds_layout->entity_type = 'comment';
  $ds_layout->bundle = 'comment_node_group';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'bw_shout';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'left' => array(
        0 => 'ds_user_picture',
      ),
      'main' => array(
        0 => 'title',
        1 => 'comment_body',
      ),
      'bottom' => array(
        0 => 'submitted',
      ),
    ),
    'fields' => array(
      'ds_user_picture' => 'left',
      'title' => 'main',
      'comment_body' => 'main',
      'submitted' => 'bottom',
    ),
    'classes' => array(),
  );
  $export['comment|comment_node_group|default'] = $ds_layout;

  $ds_layout = new stdClass;
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|group_discussion|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'group_discussion';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'bw_forum_post';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'header_left' => array(
        0 => 'post_date',
      ),
      'left' => array(
        0 => 'bw_forum_author_pane',
      ),
      'middle' => array(
        0 => 'title',
        1 => 'body',
      ),
      'bottom_left' => array(
        0 => 'bw_forum_forum_jump_links',
      ),
      'bottom_middle_right' => array(
        0 => 'links',
      ),
      'comments_region' => array(
        0 => 'comments',
      ),
    ),
    'fields' => array(
      'post_date' => 'header_left',
      'bw_forum_author_pane' => 'left',
      'title' => 'middle',
      'body' => 'middle',
      'bw_forum_forum_jump_links' => 'bottom_left',
      'links' => 'bottom_middle_right',
      'comments' => 'comments_region',
    ),
    'classes' => array(),
  );
  $export['node|group_discussion|default'] = $ds_layout;

  $ds_layout = new stdClass;
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|group_discussion|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'group_discussion';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'bw_forum_post';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 0,
    'regions' => array(
      'header_left' => array(
        0 => 'post_date',
      ),
      'middle' => array(
        0 => 'title',
        1 => 'body',
      ),
      'left' => array(
        0 => 'author',
        1 => 'bw_forum_author_pane',
      ),
      'bottom_middle' => array(
        0 => 'links',
      ),
      'bottom_left' => array(
        0 => 'bw_forum_forum_jump_links',
      ),
      'comments_region' => array(
        0 => 'comments',
      ),
    ),
    'fields' => array(
      'post_date' => 'header_left',
      'title' => 'middle',
      'body' => 'middle',
      'author' => 'left',
      'bw_forum_author_pane' => 'left',
      'links' => 'bottom_middle',
      'bw_forum_forum_jump_links' => 'bottom_left',
      'comments' => 'comments_region',
    ),
    'classes' => array(),
  );
  $export['node|group_discussion|full'] = $ds_layout;

  $ds_layout = new stdClass;
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|group|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'group';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 0,
    'regions' => array(
      'left' => array(
        0 => 'field_group_picture',
        1 => 'body',
        2 => 'views_content_ds__bw_group_posts',
        3 => 'comments',
      ),
      'right' => array(
        0 => 'author',
        1 => 'views_content_ds__bw_group_members',
      ),
    ),
    'fields' => array(
      'field_group_picture' => 'left',
      'body' => 'left',
      'views_content_ds__bw_group_posts' => 'left',
      'comments' => 'left',
      'author' => 'right',
      'views_content_ds__bw_group_members' => 'right',
    ),
    'classes' => array(),
  );
  $export['node|group|default'] = $ds_layout;

  $ds_layout = new stdClass;
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|group|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'group';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'views_content_ds__bw_group_posts',
      ),
    ),
    'fields' => array(
      'views_content_ds__bw_group_posts' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|group|full'] = $ds_layout;

  $ds_layout = new stdClass;
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|group|group_forum';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'group';
  $ds_layout->view_mode = 'group_forum';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'views_content_ds__bw_group_posts',
      ),
    ),
    'fields' => array(
      'views_content_ds__bw_group_posts' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|group|group_forum'] = $ds_layout;

  $ds_layout = new stdClass;
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|group|group_members';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'group';
  $ds_layout->view_mode = 'group_members';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'views_content_ds__bw_group_members',
      ),
    ),
    'fields' => array(
      'views_content_ds__bw_group_members' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|group|group_members'] = $ds_layout;

  $ds_layout = new stdClass;
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|group|group_wiki';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'group';
  $ds_layout->view_mode = 'group_wiki';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_wiki_text',
      ),
    ),
    'fields' => array(
      'field_wiki_text' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|group|group_wiki'] = $ds_layout;

  $ds_layout = new stdClass;
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|group|group_wiki_edt';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'group';
  $ds_layout->view_mode = 'group_wiki_edt';
  $ds_layout->layout = 'onecol';
  $ds_layout->settings = array(
    'css_id' => '',
    'class' => '',
    'sticky' => 0,
    'layout' => 'onecol',
    'hide_sidebars' => 0,
    'pipeline' => 'standard',
    'hide_empty_regions' => FALSE,
    'ds_panels' => TRUE,
    'did' => '7',
    'theme' => 'panels_onecol',
  );
  $export['node|group|group_wiki_edt'] = $ds_layout;

  $ds_layout = new stdClass;
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|group|group_wikiedit';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'group';
  $ds_layout->view_mode = 'group_wikiedit';
  $ds_layout->layout = 'onecol';
  $ds_layout->settings = array(
    'css_id' => '',
    'class' => '',
    'sticky' => 0,
    'layout' => 'onecol',
    'hide_sidebars' => 0,
    'pipeline' => 'standard',
    'hide_empty_regions' => FALSE,
    'ds_panels' => TRUE,
    'did' => '8',
    'theme' => 'panels_onecol',
  );
  $export['node|group|group_wikiedit'] = $ds_layout;

  return $export;
}
