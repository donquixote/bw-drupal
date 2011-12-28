<?php
/**
 * @file
 * bw_frontpage.views_default.inc
 */

/**
 * Implementation of hook_views_default_views().
 */
function bw_frontpage_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'frontpage_slider';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Frontpage slider';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'slideshow';
  $handler->display->display_options['style_options']['slideshow_type'] = 'views_slideshow_cycle';
  $handler->display->display_options['style_options']['slideshow_skin'] = 'default';
  $handler->display->display_options['style_options']['skin_info'] = array(
    'class' => 'default',
    'name' => 'Default',
    'module' => 'views_slideshow',
    'path' => '',
    'stylesheets' => array(),
  );
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['type'] = 'views_slideshow_pager_fields';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['views_slideshow_pager_fields_fields'] = array(
    'title' => 0,
    'field_bw_front_image' => 0,
  );
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_controls']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_controls']['type'] = 'views_slideshow_controls_text';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_slide_counter']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['type'] = 'views_slideshow_pager_fields';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['views_slideshow_pager_fields_fields'] = array(
    'title' => 0,
    'field_bw_front_image' => 0,
  );
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['type'] = 'views_slideshow_controls_text';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_slide_counter']['weight'] = '1';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['timeout'] = '5000';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['speed'] = '700';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['delay'] = '0';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['start_paused'] = 0;
  $handler->display->display_options['style_options']['views_slideshow_cycle']['remember_slide_days'] = '1';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['items_per_slide'] = '1';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['cleartype'] = 0;
  $handler->display->display_options['style_options']['views_slideshow_cycle']['cleartypenobg'] = 0;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_bw_front_image']['id'] = 'field_bw_front_image';
  $handler->display->display_options['fields']['field_bw_front_image']['table'] = 'field_data_field_bw_front_image';
  $handler->display->display_options['fields']['field_bw_front_image']['field'] = 'field_bw_front_image';
  $handler->display->display_options['fields']['field_bw_front_image']['label'] = '';
  $handler->display->display_options['fields']['field_bw_front_image']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_bw_front_image']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_bw_front_image']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_bw_front_image']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_bw_front_image']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_bw_front_image']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_bw_front_image']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_bw_front_image']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_bw_front_image']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_bw_front_image']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_bw_front_image']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_bw_front_image']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_bw_front_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_bw_front_image']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_bw_front_image']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_bw_front_image']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_bw_front_image']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['field_bw_front_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_bw_front_image']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_bw_front_image']['field_api_classes'] = 0;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'bw_front_image' => 'bw_front_image',
  );
  $handler->display->display_options['filters']['type']['group'] = 0;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['block_description'] = 'BW frontpage slider';
  $export['frontpage_slider'] = $view;

  return $export;
}