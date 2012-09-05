<?php

/**
 * @file
 * Provides Views 3 integration for getlocations.
 */

/**
 * Implementation of hook_views_default_views().
 */
function getlocations_views_default_views() {
  $views = array();

  /**
   * getlocations node
   */

  $view = new view;
  $view->name = 'getlocations';
  $view->description = 'A link and block view for getlocations.';
  $view->tag = 'getlocations view';
  $view->base_table = 'node';
  $view->human_name = 'Getlocations';
  $view->core = 7;
  $view->api_version = '3';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'View locations';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Node: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['text'] = 'See [title] on a map';
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['path'] = 'getlocations/node/[nid]';
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Argument: Node: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['style_plugin'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['nid']['not'] = 0;
  /* Filter: Node: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter: Location: Lid */
  $handler->display->display_options['filters']['lid']['id'] = 'lid';
  $handler->display->display_options['filters']['lid']['table'] = 'location';
  $handler->display->display_options['filters']['lid']['field'] = 'lid';
  $handler->display->display_options['filters']['lid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['lid']['expose']['operator'] = FALSE;
  /* Filter: Location: Latitude */
  $handler->display->display_options['filters']['latitude']['id'] = 'latitude';
  $handler->display->display_options['filters']['latitude']['table'] = 'location';
  $handler->display->display_options['filters']['latitude']['field'] = 'latitude';
  $handler->display->display_options['filters']['latitude']['operator'] = '!=';
  $handler->display->display_options['filters']['latitude']['value']['value'] = '0';
  $handler->display->display_options['filters']['latitude']['allow_null'] = 1;
  /* Filter: Location: Longitude */
  $handler->display->display_options['filters']['longitude']['id'] = 'longitude';
  $handler->display->display_options['filters']['longitude']['table'] = 'location';
  $handler->display->display_options['filters']['longitude']['field'] = 'longitude';
  $handler->display->display_options['filters']['longitude']['operator'] = '!=';
  $handler->display->display_options['filters']['longitude']['value']['value'] = '0';
  $handler->display->display_options['filters']['longitude']['allow_null'] = 1;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');

  $views[$view->name] = $view;


  /**
   * getlocations map
   */
  $view = new view;
  $view->name = 'getlocations_map';
  $view->description = 'Provide a map of a location enabled node.';
  $view->tag = 'getlocations view';
  $view->base_table = 'node';
  $view->human_name = 'Getlocations map';
  $view->core = 7;
  $view->api_version = '3';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'View locations';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  /* Field: Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Location: Lid */
  $handler->display->display_options['fields']['lid']['id'] = 'lid';
  $handler->display->display_options['fields']['lid']['table'] = 'location';
  $handler->display->display_options['fields']['lid']['field'] = 'lid';
  $handler->display->display_options['fields']['lid']['label'] = '';
  $handler->display->display_options['fields']['lid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['lid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['lid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['lid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['lid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['lid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['lid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['lid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['lid']['hide_alter_empty'] = 0;
  /* Field: Location: Latitude */
  $handler->display->display_options['fields']['latitude']['id'] = 'latitude';
  $handler->display->display_options['fields']['latitude']['table'] = 'location';
  $handler->display->display_options['fields']['latitude']['field'] = 'latitude';
  $handler->display->display_options['fields']['latitude']['label'] = '';
  $handler->display->display_options['fields']['latitude']['exclude'] = TRUE;
  $handler->display->display_options['fields']['latitude']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['external'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['latitude']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['latitude']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['html'] = 0;
  $handler->display->display_options['fields']['latitude']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['latitude']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['latitude']['hide_empty'] = 0;
  $handler->display->display_options['fields']['latitude']['empty_zero'] = 0;
  $handler->display->display_options['fields']['latitude']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['latitude']['style'] = 'dd';
  /* Field: Location: Longitude */
  $handler->display->display_options['fields']['longitude']['id'] = 'longitude';
  $handler->display->display_options['fields']['longitude']['table'] = 'location';
  $handler->display->display_options['fields']['longitude']['field'] = 'longitude';
  $handler->display->display_options['fields']['longitude']['label'] = '';
  $handler->display->display_options['fields']['longitude']['exclude'] = TRUE;
  $handler->display->display_options['fields']['longitude']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['external'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['longitude']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['longitude']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['html'] = 0;
  $handler->display->display_options['fields']['longitude']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['longitude']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['longitude']['hide_empty'] = 0;
  $handler->display->display_options['fields']['longitude']['empty_zero'] = 0;
  $handler->display->display_options['fields']['longitude']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['longitude']['style'] = 'dd';
  /* Field: Location: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'location';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 0;
  /* Field: Node: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['type']['alter']['external'] = 0;
  $handler->display->display_options['fields']['type']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['type']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['type']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['type']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['type']['empty_zero'] = 0;
  $handler->display->display_options['fields']['type']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['type']['link_to_node'] = 0;
  $handler->display->display_options['fields']['type']['machine_name'] = 1;

  /* Argument: Node: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['style_plugin'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['nid']['not'] = 0;

  /* Filter: Node: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter: Location: Lid */
  $handler->display->display_options['filters']['lid']['id'] = 'lid';
  $handler->display->display_options['filters']['lid']['table'] = 'location';
  $handler->display->display_options['filters']['lid']['field'] = 'lid';
  $handler->display->display_options['filters']['lid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['lid']['expose']['operator'] = FALSE;
  /* Filter: Location: Latitude */
  $handler->display->display_options['filters']['latitude']['id'] = 'latitude';
  $handler->display->display_options['filters']['latitude']['table'] = 'location';
  $handler->display->display_options['filters']['latitude']['field'] = 'latitude';
  $handler->display->display_options['filters']['latitude']['operator'] = '!=';
  $handler->display->display_options['filters']['latitude']['value']['value'] = '0';
  /* Filter: Location: Longitude */
  $handler->display->display_options['filters']['longitude']['id'] = 'longitude';
  $handler->display->display_options['filters']['longitude']['table'] = 'location';
  $handler->display->display_options['filters']['longitude']['field'] = 'longitude';
  $handler->display->display_options['filters']['longitude']['operator'] = '!=';
  $handler->display->display_options['filters']['longitude']['value']['value'] = '0';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'getlocations';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  $handler->display->display_options['defaults']['row_options'] = FALSE;

  $views[$view->name] = $view;


  // getlocations all nodes
  $view = new view;
  $view->name = 'getlocations_map_allnodes';
  $view->description = 'Provide a map of all location enabled nodes.';
  $view->tag = 'getlocations view';
  $view->base_table = 'node';
  $view->human_name = 'Getlocations map allnodes';
  $view->core = 7;
  $view->api_version = '3';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'View locations';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  /* Field: Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Location: Lid */
  $handler->display->display_options['fields']['lid']['id'] = 'lid';
  $handler->display->display_options['fields']['lid']['table'] = 'location';
  $handler->display->display_options['fields']['lid']['field'] = 'lid';
  $handler->display->display_options['fields']['lid']['label'] = '';
  $handler->display->display_options['fields']['lid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['lid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['lid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['lid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['lid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['lid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['lid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['lid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['lid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['lid']['hide_alter_empty'] = 0;
  /* Field: Location: Latitude */
  $handler->display->display_options['fields']['latitude']['id'] = 'latitude';
  $handler->display->display_options['fields']['latitude']['table'] = 'location';
  $handler->display->display_options['fields']['latitude']['field'] = 'latitude';
  $handler->display->display_options['fields']['latitude']['label'] = '';
  $handler->display->display_options['fields']['latitude']['exclude'] = TRUE;
  $handler->display->display_options['fields']['latitude']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['external'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['latitude']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['latitude']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['latitude']['alter']['html'] = 0;
  $handler->display->display_options['fields']['latitude']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['latitude']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['latitude']['hide_empty'] = 0;
  $handler->display->display_options['fields']['latitude']['empty_zero'] = 0;
  $handler->display->display_options['fields']['latitude']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['latitude']['style'] = 'dd';
  /* Field: Location: Longitude */
  $handler->display->display_options['fields']['longitude']['id'] = 'longitude';
  $handler->display->display_options['fields']['longitude']['table'] = 'location';
  $handler->display->display_options['fields']['longitude']['field'] = 'longitude';
  $handler->display->display_options['fields']['longitude']['label'] = '';
  $handler->display->display_options['fields']['longitude']['exclude'] = TRUE;
  $handler->display->display_options['fields']['longitude']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['external'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['longitude']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['longitude']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['longitude']['alter']['html'] = 0;
  $handler->display->display_options['fields']['longitude']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['longitude']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['longitude']['hide_empty'] = 0;
  $handler->display->display_options['fields']['longitude']['empty_zero'] = 0;
  $handler->display->display_options['fields']['longitude']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['longitude']['style'] = 'dd';
  /* Field: Location: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'location';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 0;
  /* Field: Node: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['type']['alter']['external'] = 0;
  $handler->display->display_options['fields']['type']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['type']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['type']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['type']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['type']['empty_zero'] = 0;
  $handler->display->display_options['fields']['type']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['type']['link_to_node'] = 0;
  $handler->display->display_options['fields']['type']['machine_name'] = 1;

  /* Filter: Node: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter: Location: Lid */
  $handler->display->display_options['filters']['lid']['id'] = 'lid';
  $handler->display->display_options['filters']['lid']['table'] = 'location';
  $handler->display->display_options['filters']['lid']['field'] = 'lid';
  $handler->display->display_options['filters']['lid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['lid']['expose']['operator'] = FALSE;
  /* Filter: Location: Latitude */
  $handler->display->display_options['filters']['latitude']['id'] = 'latitude';
  $handler->display->display_options['filters']['latitude']['table'] = 'location';
  $handler->display->display_options['filters']['latitude']['field'] = 'latitude';
  $handler->display->display_options['filters']['latitude']['operator'] = '!=';
  $handler->display->display_options['filters']['latitude']['value']['value'] = '0';
  /* Filter: Location: Longitude */
  $handler->display->display_options['filters']['longitude']['id'] = 'longitude';
  $handler->display->display_options['filters']['longitude']['table'] = 'location';
  $handler->display->display_options['filters']['longitude']['field'] = 'longitude';
  $handler->display->display_options['filters']['longitude']['operator'] = '!=';
  $handler->display->display_options['filters']['longitude']['value']['value'] = '0';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'getlocations';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  $handler->display->display_options['defaults']['row_options'] = FALSE;


  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'getlocations';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  $handler->display->display_options['defaults']['row_options'] = FALSE;

  $handler->display->display_options['path'] = 'getlocations_all';

  $views[$view->name] = $view;

  return $views;
}
