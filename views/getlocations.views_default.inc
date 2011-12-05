<?php

/**
 * @file
 * Provides Views 3 integration for getlocations.
 *
 */


/**
 * Implements hook_views_default_views().
 */
function getlocations_views_default_views() {
  $views = array();

  if (module_exists('location')) {
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
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['label'] = '';
    $handler->display->display_options['fields']['title']['exclude'] = TRUE;
    $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['title']['alter']['external'] = 0;
    $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
    $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['title']['alter']['html'] = 0;
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['title']['hide_empty'] = 0;
    $handler->display->display_options['fields']['title']['empty_zero'] = 0;
    $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
    $handler->display->display_options['fields']['title']['link_to_node'] = 0;
    /* Field: Content: Nid */
    $handler->display->display_options['fields']['nid']['id'] = 'nid';
    $handler->display->display_options['fields']['nid']['table'] = 'node';
    $handler->display->display_options['fields']['nid']['field'] = 'nid';
    $handler->display->display_options['fields']['nid']['label'] = '';
    $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 1;
    $handler->display->display_options['fields']['nid']['alter']['text'] = '<a href="/getlocations/node/[nid]">See [title] on a map</a> ';
    $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
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
    /* Contextual filter: Content: Nid */
    $handler->display->display_options['arguments']['nid']['id'] = 'nid';
    $handler->display->display_options['arguments']['nid']['table'] = 'node';
    $handler->display->display_options['arguments']['nid']['field'] = 'nid';
    $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
    $handler->display->display_options['arguments']['nid']['default_argument_skip_url'] = 0;
    $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
    $handler->display->display_options['arguments']['nid']['not'] = 0;
    /* Filter criterion: Content: Published */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'node';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['group'] = 0;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    /* Filter criterion: Location: Lid */
    $handler->display->display_options['filters']['lid']['id'] = 'lid';
    $handler->display->display_options['filters']['lid']['table'] = 'location';
    $handler->display->display_options['filters']['lid']['field'] = 'lid';
    $handler->display->display_options['filters']['lid']['operator'] = 'not empty';
    $handler->display->display_options['filters']['lid']['expose']['operator'] = FALSE;

    /* Display: Block 1 */
    $handler = $view->new_display('block', 'Block 1', 'block_1');
    $handler->display->display_options['block_description'] = 'View: Getlocations Node link to a map';

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
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Field: Content: Title */
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
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
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
    /* Contextual filter: Content: Nid */
    $handler->display->display_options['arguments']['nid']['id'] = 'nid';
    $handler->display->display_options['arguments']['nid']['table'] = 'node';
    $handler->display->display_options['arguments']['nid']['field'] = 'nid';
    $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
    $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
    $handler->display->display_options['arguments']['nid']['not'] = 0;
    /* Filter criterion: Content: Published */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'node';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['group'] = 0;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    /* Filter criterion: Location: Lid */
    $handler->display->display_options['filters']['lid']['id'] = 'lid';
    $handler->display->display_options['filters']['lid']['table'] = 'location';
    $handler->display->display_options['filters']['lid']['field'] = 'lid';
    $handler->display->display_options['filters']['lid']['operator'] = 'not empty';
    $handler->display->display_options['filters']['lid']['expose']['operator'] = FALSE;
    /* Filter criterion: Location: Latitude */
    $handler->display->display_options['filters']['latitude']['id'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['table'] = 'location';
    $handler->display->display_options['filters']['latitude']['field'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['operator'] = '!=';
    $handler->display->display_options['filters']['latitude']['value']['value'] = '0';
    /* Filter criterion: Location: Longitude */
    $handler->display->display_options['filters']['longitude']['id'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['table'] = 'location';
    $handler->display->display_options['filters']['longitude']['field'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['operator'] = '!=';
    $handler->display->display_options['filters']['longitude']['value']['value'] = '0';

    /* Display: Block 2 */
    $handler = $view->new_display('block', 'Block 2', 'block_2');
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'getlocations';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['defaults']['footer'] = FALSE;
    $handler->display->display_options['block_description'] = 'View: Getlocations map of a location';
    /* Footer: Global: Text area */
    $handler->display->display_options['footer']['area']['id'] = 'area';
    $handler->display->display_options['footer']['area']['table'] = 'views';
    $handler->display->display_options['footer']['area']['field'] = 'area';
    $handler->display->display_options['footer']['area']['empty'] = FALSE;
    $handler->display->display_options['footer']['area']['content'] = '<a href="/getlocations/node/!1">View %1 on a large map</a>';
    $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
    $handler->display->display_options['footer']['area']['tokenize'] = 1;

    $views[$view->name] = $view;


    /**
     * getlocations all nodes
     */
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
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Field: Content: Title */
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
    /* Filter criterion: Content: Published */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'node';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    /* Filter criterion: Location: Lid */
    $handler->display->display_options['filters']['lid']['id'] = 'lid';
    $handler->display->display_options['filters']['lid']['table'] = 'location';
    $handler->display->display_options['filters']['lid']['field'] = 'lid';
    $handler->display->display_options['filters']['lid']['operator'] = 'not empty';
    $handler->display->display_options['filters']['lid']['expose']['operator'] = FALSE;
    /* Filter criterion: Location: Latitude */
    $handler->display->display_options['filters']['latitude']['id'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['table'] = 'location';
    $handler->display->display_options['filters']['latitude']['field'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['operator'] = '!=';
    $handler->display->display_options['filters']['latitude']['value']['value'] = '0';
    /* Filter criterion: Location: Longitude */
    $handler->display->display_options['filters']['longitude']['id'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['table'] = 'location';
    $handler->display->display_options['filters']['longitude']['field'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['operator'] = '!=';
    $handler->display->display_options['filters']['longitude']['value']['value'] = '0';

    /* Display: Block 3 */
    $handler = $view->new_display('block', 'Block 3', 'block_3');
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'getlocations';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['block_description'] = 'View: Getlocations allnodes map';

    /* Display: Block 4 */
    $handler = $view->new_display('block', 'Block 4', 'block_4');
    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['title'] = 'List all locations';
    $handler->display->display_options['defaults']['pager'] = FALSE;
    $handler->display->display_options['pager']['type'] = 'mini';
    $handler->display->display_options['pager']['options']['items_per_page'] = '10';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['pager']['options']['id'] = '0';
    $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
    $handler->display->display_options['defaults']['fields'] = FALSE;
    $handler->display->display_options['block_description'] = 'View: Getlocations allnodes list';
    /* Field: Content: Title */
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
    $handler->display->display_options['fields']['title']['link_to_node'] = 1;
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
    $handler->display->display_options['defaults']['sorts'] = FALSE;
    /* Sort criterion: Content: Title */
    $handler->display->display_options['sorts']['title']['id'] = 'title';
    $handler->display->display_options['sorts']['title']['table'] = 'node';
    $handler->display->display_options['sorts']['title']['field'] = 'title';

    $views[$view->name] = $view;


  }
  elseif (module_exists('getlocations_fields')) {

    /**
    * getlocations node
    */
    $view = new view;
    $view->name = 'getlocations';
    $view->description = 'Create a block with a link to a map';
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
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Field: Content: Title */
    $handler->display->display_options['fields']['title']['id'] = 'title';
    $handler->display->display_options['fields']['title']['table'] = 'node';
    $handler->display->display_options['fields']['title']['field'] = 'title';
    $handler->display->display_options['fields']['title']['label'] = '';
    $handler->display->display_options['fields']['title']['exclude'] = TRUE;
    $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['title']['alter']['external'] = 0;
    $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
    $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['title']['alter']['html'] = 0;
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['title']['hide_empty'] = 0;
    $handler->display->display_options['fields']['title']['empty_zero'] = 0;
    $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
    $handler->display->display_options['fields']['title']['link_to_node'] = 0;
    /* Field: Content: Nid */
    $handler->display->display_options['fields']['nid']['id'] = 'nid';
    $handler->display->display_options['fields']['nid']['table'] = 'node';
    $handler->display->display_options['fields']['nid']['field'] = 'nid';
    $handler->display->display_options['fields']['nid']['label'] = '';
    $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 1;
    $handler->display->display_options['fields']['nid']['alter']['text'] = '<a href="/getlocations/node/[nid]">See [title] on a map</a> ';
    $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
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
    /* Contextual filter: Content: Nid */
    $handler->display->display_options['arguments']['nid']['id'] = 'nid';
    $handler->display->display_options['arguments']['nid']['table'] = 'node';
    $handler->display->display_options['arguments']['nid']['field'] = 'nid';
    $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
    $handler->display->display_options['arguments']['nid']['default_argument_skip_url'] = 0;
    $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
    $handler->display->display_options['arguments']['nid']['not'] = 0;
    /* Filter criterion: Content: Published */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'node';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['group'] = 0;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    /* Filter criterion: Getlocations Fields: Glid */
    $handler->display->display_options['filters']['glid']['id'] = 'glid';
    $handler->display->display_options['filters']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['glid']['field'] = 'glid';
    $handler->display->display_options['filters']['glid']['operator'] = 'not empty';
    $handler->display->display_options['filters']['glid']['expose']['operator'] = FALSE;

    /* Display: Block 1 */
    $handler = $view->new_display('block', 'Block 1', 'block_1');
    $handler->display->display_options['block_description'] = 'View: Getlocations Node link to a map';

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
    $handler->display->display_options['title'] = 'View location';
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Field: Content: Title */
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
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
    $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['title']['alter']['html'] = 0;
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['title']['hide_empty'] = 0;
    $handler->display->display_options['fields']['title']['empty_zero'] = 0;
    $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
    $handler->display->display_options['fields']['title']['link_to_node'] = 0;
    /* Field: Getlocations Fields: Glid */
    $handler->display->display_options['fields']['glid']['id'] = 'glid';
    $handler->display->display_options['fields']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['fields']['glid']['field'] = 'glid';
    $handler->display->display_options['fields']['glid']['label'] = '';
    $handler->display->display_options['fields']['glid']['exclude'] = TRUE;
    $handler->display->display_options['fields']['glid']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['external'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['html'] = 0;
    $handler->display->display_options['fields']['glid']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['glid']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['glid']['hide_empty'] = 0;
    $handler->display->display_options['fields']['glid']['empty_zero'] = 0;
    $handler->display->display_options['fields']['glid']['hide_alter_empty'] = 0;
    /* Field: Getlocations Fields: Latitude */
    $handler->display->display_options['fields']['latitude']['id'] = 'latitude';
    $handler->display->display_options['fields']['latitude']['table'] = 'getlocations_fields';
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
    /* Field: Getlocations Fields: Longitude */
    $handler->display->display_options['fields']['longitude']['id'] = 'longitude';
    $handler->display->display_options['fields']['longitude']['table'] = 'getlocations_fields';
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
    /* Field: Getlocations Fields: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'getlocations_fields';
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
    /* Contextual filter: Content: Nid */
    $handler->display->display_options['arguments']['nid']['id'] = 'nid';
    $handler->display->display_options['arguments']['nid']['table'] = 'node';
    $handler->display->display_options['arguments']['nid']['field'] = 'nid';
    $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
    $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
    $handler->display->display_options['arguments']['nid']['not'] = 0;
    /* Filter criterion: Content: Published */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'node';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['group'] = 0;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    /* Filter criterion: Getlocations Fields: Glid */
    $handler->display->display_options['filters']['glid']['id'] = 'glid';
    $handler->display->display_options['filters']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['glid']['field'] = 'glid';
    $handler->display->display_options['filters']['glid']['operator'] = 'not empty';
    $handler->display->display_options['filters']['glid']['expose']['operator'] = FALSE;
    /* Filter criterion: Getlocations Fields: Latitude */
    $handler->display->display_options['filters']['latitude']['id'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['latitude']['field'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['operator'] = '!=';
    $handler->display->display_options['filters']['latitude']['value']['value'] = '0';
    /* Filter criterion: Getlocations Fields: Longitude */
    $handler->display->display_options['filters']['longitude']['id'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['longitude']['field'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['operator'] = '!=';
    $handler->display->display_options['filters']['longitude']['value']['value'] = '0';

    /* Display: Block 2 */
    $handler = $view->new_display('block', 'Block 2', 'block_2');
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'getlocations';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['block_description'] = 'View: Getlocations map of a location';

    $views[$view->name] = $view;


    /**
     * getlocations all nodes
     */
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
    $handler->display->display_options['title'] = 'View all locations';
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Field: Content: Title */
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
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
    $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['title']['alter']['html'] = 0;
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['title']['hide_empty'] = 0;
    $handler->display->display_options['fields']['title']['empty_zero'] = 0;
    $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
    $handler->display->display_options['fields']['title']['link_to_node'] = 0;
    /* Field: Getlocations Fields: Glid */
    $handler->display->display_options['fields']['glid']['id'] = 'glid';
    $handler->display->display_options['fields']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['fields']['glid']['field'] = 'glid';
    $handler->display->display_options['fields']['glid']['label'] = '';
    $handler->display->display_options['fields']['glid']['exclude'] = TRUE;
    $handler->display->display_options['fields']['glid']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['external'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['html'] = 0;
    $handler->display->display_options['fields']['glid']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['glid']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['glid']['hide_empty'] = 0;
    $handler->display->display_options['fields']['glid']['empty_zero'] = 0;
    $handler->display->display_options['fields']['glid']['hide_alter_empty'] = 0;
    /* Field: Getlocations Fields: Latitude */
    $handler->display->display_options['fields']['latitude']['id'] = 'latitude';
    $handler->display->display_options['fields']['latitude']['table'] = 'getlocations_fields';
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
    /* Field: Getlocations Fields: Longitude */
    $handler->display->display_options['fields']['longitude']['id'] = 'longitude';
    $handler->display->display_options['fields']['longitude']['table'] = 'getlocations_fields';
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
    /* Field: Getlocations Fields: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'getlocations_fields';
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
    /* Filter criterion: Content: Published */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'node';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['group'] = 0;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    /* Filter criterion: Getlocations Fields: Glid */
    $handler->display->display_options['filters']['glid']['id'] = 'glid';
    $handler->display->display_options['filters']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['glid']['field'] = 'glid';
    $handler->display->display_options['filters']['glid']['operator'] = 'not empty';
    /* Filter criterion: Getlocations Fields: Latitude */
    $handler->display->display_options['filters']['latitude']['id'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['latitude']['field'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['operator'] = '!=';
    $handler->display->display_options['filters']['latitude']['value']['value'] = '0';
    /* Filter criterion: Getlocations Fields: Longitude */
    $handler->display->display_options['filters']['longitude']['id'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['longitude']['field'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['operator'] = '!=';
    $handler->display->display_options['filters']['longitude']['value']['value'] = '0';

    /* Display: Block 3 */
    $handler = $view->new_display('block', 'Block 3', 'block_3');
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'getlocations';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['defaults']['sorts'] = FALSE;
    $handler->display->display_options['block_description'] = 'View: Getlocations allnodes map';

    /* Display: Block 4 */
    $handler = $view->new_display('block', 'Block 4', 'block_4');
    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['title'] = 'List all locations';
    $handler->display->display_options['defaults']['pager'] = FALSE;
    $handler->display->display_options['pager']['type'] = 'mini';
    $handler->display->display_options['pager']['options']['items_per_page'] = '10';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['pager']['options']['id'] = '0';
    $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
    $handler->display->display_options['defaults']['fields'] = FALSE;

    /* Field: Content: Title */
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
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
    $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['title']['alter']['html'] = 0;
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['title']['hide_empty'] = 0;
    $handler->display->display_options['fields']['title']['empty_zero'] = 0;
    $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
    $handler->display->display_options['fields']['title']['link_to_node'] = 1;
    /* Field: Getlocations Fields: Glid */
    $handler->display->display_options['fields']['glid']['id'] = 'glid';
    $handler->display->display_options['fields']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['fields']['glid']['field'] = 'glid';
    $handler->display->display_options['fields']['glid']['label'] = '';
    $handler->display->display_options['fields']['glid']['exclude'] = TRUE;
    $handler->display->display_options['fields']['glid']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['external'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['html'] = 0;
    $handler->display->display_options['fields']['glid']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['glid']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['glid']['hide_empty'] = 0;
    $handler->display->display_options['fields']['glid']['empty_zero'] = 0;
    $handler->display->display_options['fields']['glid']['hide_alter_empty'] = 0;
    /* Field: Getlocations Fields: Latitude */
    $handler->display->display_options['fields']['latitude']['id'] = 'latitude';
    $handler->display->display_options['fields']['latitude']['table'] = 'getlocations_fields';
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
    /* Field: Getlocations Fields: Longitude */
    $handler->display->display_options['fields']['longitude']['id'] = 'longitude';
    $handler->display->display_options['fields']['longitude']['table'] = 'getlocations_fields';
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
    /* Field: Getlocations Fields: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'getlocations_fields';
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
    $handler->display->display_options['defaults']['sorts'] = FALSE;
    /* Sort criterion: Content: Title */
    $handler->display->display_options['sorts']['title']['id'] = 'title';
    $handler->display->display_options['sorts']['title']['table'] = 'node';
    $handler->display->display_options['sorts']['title']['field'] = 'title';
    $handler->display->display_options['block_description'] = 'View: Getlocations Block allnodes list';

    $views[$view->name] = $view;


    /**
    * getlocations nearby
    */
    $view = new view;
    $view->name = 'getlocations_map_nearby';
    $view->description = 'Provide a map of all nearby location enabled nodes.';
    $view->tag = 'getlocations view';
    $view->base_table = 'node';
    $view->human_name = 'Getlocations map nearby';
    $view->core = 7;
    $view->api_version = '3';
    $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

    /* Display: Defaults */
    $handler = $view->new_display('default', 'Defaults', 'default');
    $handler->display->display_options['title'] = 'Nearby Locations';
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Field: Content: Title */
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
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
    $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['title']['alter']['html'] = 0;
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['title']['hide_empty'] = 0;
    $handler->display->display_options['fields']['title']['empty_zero'] = 0;
    $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
    $handler->display->display_options['fields']['title']['link_to_node'] = 0;
    /* Field: Getlocations Fields: Glid */
    $handler->display->display_options['fields']['glid']['id'] = 'glid';
    $handler->display->display_options['fields']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['fields']['glid']['field'] = 'glid';
    $handler->display->display_options['fields']['glid']['label'] = '';
    $handler->display->display_options['fields']['glid']['exclude'] = TRUE;
    $handler->display->display_options['fields']['glid']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['external'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['html'] = 0;
    $handler->display->display_options['fields']['glid']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['glid']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['glid']['hide_empty'] = 0;
    $handler->display->display_options['fields']['glid']['empty_zero'] = 0;
    $handler->display->display_options['fields']['glid']['hide_alter_empty'] = 0;
    /* Field: Getlocations Fields: Latitude */
    $handler->display->display_options['fields']['latitude']['id'] = 'latitude';
    $handler->display->display_options['fields']['latitude']['table'] = 'getlocations_fields';
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
    /* Field: Getlocations Fields: Longitude */
    $handler->display->display_options['fields']['longitude']['id'] = 'longitude';
    $handler->display->display_options['fields']['longitude']['table'] = 'getlocations_fields';
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
    /* Field: Getlocations Fields: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'getlocations_fields';
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
    /* Sort criterion: Getlocations Fields: Distance / Proximity */
    $handler->display->display_options['sorts']['distance']['id'] = 'distance';
    $handler->display->display_options['sorts']['distance']['table'] = 'getlocations_fields';
    $handler->display->display_options['sorts']['distance']['field'] = 'distance';
    $handler->display->display_options['sorts']['distance']['nid_arg'] = 'nid';
    $handler->display->display_options['sorts']['distance']['nid_loc_field'] = '';
    /* Contextual filter: Content: Nid */
    $handler->display->display_options['arguments']['nid']['id'] = 'nid';
    $handler->display->display_options['arguments']['nid']['table'] = 'node';
    $handler->display->display_options['arguments']['nid']['field'] = 'nid';
    $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
    $handler->display->display_options['arguments']['nid']['default_argument_skip_url'] = 0;
    $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
    $handler->display->display_options['arguments']['nid']['not'] = 1;
    /* Filter criterion: Content: Published */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'node';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = 1;
    $handler->display->display_options['filters']['status']['group'] = 0;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    /* Filter criterion: Getlocations Fields: Glid */
    $handler->display->display_options['filters']['glid']['id'] = 'glid';
    $handler->display->display_options['filters']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['glid']['field'] = 'glid';
    $handler->display->display_options['filters']['glid']['operator'] = 'not empty';
    $handler->display->display_options['filters']['glid']['expose']['operator'] = FALSE;
    /* Filter criterion: Getlocations Fields: Latitude */
    $handler->display->display_options['filters']['latitude']['id'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['latitude']['field'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['operator'] = '!=';
    $handler->display->display_options['filters']['latitude']['value']['value'] = '0';
    /* Filter criterion: Getlocations Fields: Longitude */
    $handler->display->display_options['filters']['longitude']['id'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['longitude']['field'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['operator'] = '!=';
    $handler->display->display_options['filters']['longitude']['value']['value'] = '0';
    /* Filter criterion: Getlocations Fields: Distance / Proximity */
    $handler->display->display_options['filters']['distance']['id'] = 'distance';
    $handler->display->display_options['filters']['distance']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['distance']['field'] = 'distance';
    $handler->display->display_options['filters']['distance']['operator'] = 'dist';
    $handler->display->display_options['filters']['distance']['value'] = array();

    /* Display: Block 5 */
    $handler = $view->new_display('block', 'Block 5', 'block_5');
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'getlocations';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['block_description'] = 'View: Getlocations Block nearby map';

    /* Display: Block 6 */
    $handler = $view->new_display('block', 'Block 6', 'block_6');
    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['title'] = 'List nearby locations';
    $handler->display->display_options['defaults']['pager'] = FALSE;
    $handler->display->display_options['pager']['type'] = 'mini';
    $handler->display->display_options['pager']['options']['items_per_page'] = '10';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['pager']['options']['id'] = '0';
    $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: Content: Title */
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
    $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
    $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['title']['alter']['html'] = 0;
    $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['title']['hide_empty'] = 0;
    $handler->display->display_options['fields']['title']['empty_zero'] = 0;
    $handler->display->display_options['fields']['title']['hide_alter_empty'] = 0;
    $handler->display->display_options['fields']['title']['link_to_node'] = 1;
    /* Field: Getlocations Fields: Glid */
    $handler->display->display_options['fields']['glid']['id'] = 'glid';
    $handler->display->display_options['fields']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['fields']['glid']['field'] = 'glid';
    $handler->display->display_options['fields']['glid']['label'] = '';
    $handler->display->display_options['fields']['glid']['exclude'] = TRUE;
    $handler->display->display_options['fields']['glid']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['external'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['html'] = 0;
    $handler->display->display_options['fields']['glid']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['glid']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['glid']['hide_empty'] = 0;
    $handler->display->display_options['fields']['glid']['empty_zero'] = 0;
    $handler->display->display_options['fields']['glid']['hide_alter_empty'] = 0;
    /* Field: Getlocations Fields: Latitude */
    $handler->display->display_options['fields']['latitude']['id'] = 'latitude';
    $handler->display->display_options['fields']['latitude']['table'] = 'getlocations_fields';
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
    /* Field: Getlocations Fields: Longitude */
    $handler->display->display_options['fields']['longitude']['id'] = 'longitude';
    $handler->display->display_options['fields']['longitude']['table'] = 'getlocations_fields';
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
    /* Field: Getlocations Fields: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'getlocations_fields';
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
    $handler->display->display_options['block_description'] = 'View: Getlocations Block nearby list';

    $views[$view->name] = $view;


    /**
    * getlocations show all locations of all types
    */
    $view = new view;
    $view->name = 'getlocations_show_all';
    $view->description = 'Show all of all types';
    $view->tag = 'getlocations view';
    $view->base_table = 'getlocations_fields';
    $view->human_name = 'Getlocations show all';
    $view->core = 7;
    $view->api_version = '3';
    $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

    /* Display: Defaults */
    $handler = $view->new_display('default', 'Defaults', 'default');
    $handler->display->display_options['title'] = 'Show all locations';
    $handler->display->display_options['access']['type'] = 'none';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Footer: Global: Text area */
    $handler->display->display_options['footer']['area']['id'] = 'area';
    $handler->display->display_options['footer']['area']['table'] = 'views';
    $handler->display->display_options['footer']['area']['field'] = 'area';
    $handler->display->display_options['footer']['area']['empty'] = FALSE;
    /* Field: Getlocations Fields: Glid */
    $handler->display->display_options['fields']['glid']['id'] = 'glid';
    $handler->display->display_options['fields']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['fields']['glid']['field'] = 'glid';
    $handler->display->display_options['fields']['glid']['label'] = '';
    $handler->display->display_options['fields']['glid']['exclude'] = TRUE;
    $handler->display->display_options['fields']['glid']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['external'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['html'] = 0;
    $handler->display->display_options['fields']['glid']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['glid']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['glid']['hide_empty'] = 0;
    $handler->display->display_options['fields']['glid']['empty_zero'] = 0;
    $handler->display->display_options['fields']['glid']['hide_alter_empty'] = 1;
    /* Field: Getlocations Fields: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'getlocations_fields';
    $handler->display->display_options['fields']['name']['field'] = 'name';
    $handler->display->display_options['fields']['name']['label'] = '';
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
    $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
    /* Field: Getlocations Fields: Latitude */
    $handler->display->display_options['fields']['latitude']['id'] = 'latitude';
    $handler->display->display_options['fields']['latitude']['table'] = 'getlocations_fields';
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
    $handler->display->display_options['fields']['latitude']['hide_alter_empty'] = 1;
    /* Field: Getlocations Fields: Longitude */
    $handler->display->display_options['fields']['longitude']['id'] = 'longitude';
    $handler->display->display_options['fields']['longitude']['table'] = 'getlocations_fields';
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
    $handler->display->display_options['fields']['longitude']['hide_alter_empty'] = 1;
    /* Filter criterion: Getlocations Fields: Glid */
    $handler->display->display_options['filters']['glid']['id'] = 'glid';
    $handler->display->display_options['filters']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['glid']['field'] = 'glid';
    $handler->display->display_options['filters']['glid']['operator'] = 'not empty';
    /* Filter criterion: Getlocations Fields: Latitude */
    $handler->display->display_options['filters']['latitude']['id'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['latitude']['field'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['operator'] = '!=';
    $handler->display->display_options['filters']['latitude']['value']['value'] = '0';
    /* Filter criterion: Getlocations Fields: Longitude */
    $handler->display->display_options['filters']['longitude']['id'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['longitude']['field'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['operator'] = '!=';
    $handler->display->display_options['filters']['longitude']['value']['value'] = '0';

    /* Display: Block 7 */
    $handler = $view->new_display('block', 'Block 7', 'block_7');
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'getlocations';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['block_description'] = 'View: Getlocations Block all types map';

    $handler->display->display_options['defaults']['footer'] = FALSE;
    /* Footer: Global: Text area */
    $handler->display->display_options['footer']['area']['id'] = 'area';
    $handler->display->display_options['footer']['area']['table'] = 'views';
    $handler->display->display_options['footer']['area']['field'] = 'area';
    $handler->display->display_options['footer']['area']['empty'] = TRUE;
    $handler->display->display_options['footer']['area']['content'] = '<a href="/getlocations_showall">View on a large map</a>';
    $handler->display->display_options['footer']['area']['format'] = 'full_html';
    $handler->display->display_options['footer']['area']['tokenize'] = 0;

    /* Display: Page */
    $handler = $view->new_display('page', 'Page', 'page_1');
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'getlocations';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['path'] = 'getlocations_showall';

    $views[$view->name] = $view;



    /**
    * getlocations show all users
    */
    $view = new view;
    $view->name = 'getlocations_map_allusers';
    $view->description = 'Show a map of all users';
    $view->tag = 'getlocations view';
    $view->base_table = 'users';
    $view->human_name = 'Getlocations map allusers';
    $view->core = 7;
    $view->api_version = '3';
    $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

    /* Display: Defaults */
    $handler = $view->new_display('default', 'Defaults', 'default');
    $handler->display->display_options['title'] = 'All user locations';
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['access']['perm'] = 'access user profiles';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Footer: Global: Text area */
    $handler->display->display_options['footer']['area']['id'] = 'area';
    $handler->display->display_options['footer']['area']['table'] = 'views';
    $handler->display->display_options['footer']['area']['field'] = 'area';
    $handler->display->display_options['footer']['area']['empty'] = FALSE;
    /* Field: User: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'users';
    $handler->display->display_options['fields']['name']['field'] = 'name';
    $handler->display->display_options['fields']['name']['label'] = '';
    $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['name']['alter']['external'] = 0;
    $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 0;
    $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['name']['alter']['html'] = 0;
    $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['name']['hide_empty'] = 0;
    $handler->display->display_options['fields']['name']['empty_zero'] = 0;
    $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
    $handler->display->display_options['fields']['name']['link_to_user'] = 0;
    $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
    $handler->display->display_options['fields']['name']['format_username'] = 1;
    /* Field: Getlocations Fields: Glid */
    $handler->display->display_options['fields']['glid']['id'] = 'glid';
    $handler->display->display_options['fields']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['fields']['glid']['field'] = 'glid';
    $handler->display->display_options['fields']['glid']['label'] = '';
    $handler->display->display_options['fields']['glid']['exclude'] = TRUE;
    $handler->display->display_options['fields']['glid']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['external'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['html'] = 0;
    $handler->display->display_options['fields']['glid']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['glid']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['glid']['hide_empty'] = 0;
    $handler->display->display_options['fields']['glid']['empty_zero'] = 0;
    $handler->display->display_options['fields']['glid']['hide_alter_empty'] = 1;
    /* Field: Getlocations Fields: Latitude */
    $handler->display->display_options['fields']['latitude']['id'] = 'latitude';
    $handler->display->display_options['fields']['latitude']['table'] = 'getlocations_fields';
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
    $handler->display->display_options['fields']['latitude']['hide_alter_empty'] = 1;
    /* Field: Getlocations Fields: Longitude */
    $handler->display->display_options['fields']['longitude']['id'] = 'longitude';
    $handler->display->display_options['fields']['longitude']['table'] = 'getlocations_fields';
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
    $handler->display->display_options['fields']['longitude']['hide_alter_empty'] = 1;
    /* Filter criterion: User: Active */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'users';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = '1';
    $handler->display->display_options['filters']['status']['group'] = 0;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    /* Filter criterion: Getlocations Fields: Glid */
    $handler->display->display_options['filters']['glid']['id'] = 'glid';
    $handler->display->display_options['filters']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['glid']['field'] = 'glid';
    $handler->display->display_options['filters']['glid']['operator'] = 'not empty';
    /* Filter criterion: Getlocations Fields: Latitude */
    $handler->display->display_options['filters']['latitude']['id'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['latitude']['field'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['operator'] = '!=';
    $handler->display->display_options['filters']['latitude']['value']['value'] = '0';
    /* Filter criterion: Getlocations Fields: Longitude */
    $handler->display->display_options['filters']['longitude']['id'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['longitude']['field'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['operator'] = '!=';
    $handler->display->display_options['filters']['longitude']['value']['value'] = '0';

    /* Display: Block 8 */
    $handler = $view->new_display('block', 'Block 8', 'block_8');
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'getlocations';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['defaults']['footer'] = FALSE;
    $handler->display->display_options['block_description'] = 'View: Getlocations allusers map';
    /* Footer: Global: Text area */
    $handler->display->display_options['footer']['area']['id'] = 'area';
    $handler->display->display_options['footer']['area']['table'] = 'views';
    $handler->display->display_options['footer']['area']['field'] = 'area';
    $handler->display->display_options['footer']['area']['empty'] = FALSE;
    $handler->display->display_options['footer']['area']['content'] = '<a href="/getlocations_allusers">Show on a large map</a>';
    $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
    $handler->display->display_options['footer']['area']['tokenize'] = 0;

    /* Display: Page */
    $handler = $view->new_display('page', 'Page 2', 'page_2');
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'getlocations';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['path'] = 'getlocations_allusers';

    $views[$view->name] = $view;


    /**
    * getlocations link to a user on a map
    */

    $view = new view;
    $view->name = 'getlocations_user';
    $view->description = 'Create a block with a link to a map';
    $view->tag = 'getlocations view';
    $view->base_table = 'users';
    $view->human_name = 'Getlocations User';
    $view->core = 7;
    $view->api_version = '3';
    $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

    /* Display: Defaults */
    $handler = $view->new_display('default', 'Defaults', 'default');
    $handler->display->display_options['title'] = 'View user locations';
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['access']['perm'] = 'access user profiles';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Field: User: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'users';
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
    $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 0;
    $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['name']['alter']['html'] = 0;
    $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['name']['hide_empty'] = 0;
    $handler->display->display_options['fields']['name']['empty_zero'] = 0;
    $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
    $handler->display->display_options['fields']['name']['link_to_user'] = 0;
    $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
    $handler->display->display_options['fields']['name']['format_username'] = 1;
    /* Field: User: Uid */
    $handler->display->display_options['fields']['uid']['id'] = 'uid';
    $handler->display->display_options['fields']['uid']['table'] = 'users';
    $handler->display->display_options['fields']['uid']['field'] = 'uid';
    $handler->display->display_options['fields']['uid']['label'] = '';
    $handler->display->display_options['fields']['uid']['alter']['alter_text'] = 1;
    $handler->display->display_options['fields']['uid']['alter']['text'] = '<a href="/getlocations/user/[uid]">See [name] on a map</a>';
    $handler->display->display_options['fields']['uid']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['uid']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['uid']['alter']['external'] = 0;
    $handler->display->display_options['fields']['uid']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['uid']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['uid']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['uid']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['uid']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['uid']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['uid']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['uid']['alter']['html'] = 0;
    $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['uid']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['uid']['hide_empty'] = 0;
    $handler->display->display_options['fields']['uid']['empty_zero'] = 0;
    $handler->display->display_options['fields']['uid']['hide_alter_empty'] = 1;
    $handler->display->display_options['fields']['uid']['link_to_user'] = 0;
    /* Contextual filter: User: Uid */
    $handler->display->display_options['arguments']['uid']['id'] = 'uid';
    $handler->display->display_options['arguments']['uid']['table'] = 'users';
    $handler->display->display_options['arguments']['uid']['field'] = 'uid';
    $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'user';
    $handler->display->display_options['arguments']['uid']['default_argument_options']['user'] = FALSE;
    $handler->display->display_options['arguments']['uid']['default_argument_skip_url'] = 0;
    $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['arguments']['uid']['break_phrase'] = 0;
    $handler->display->display_options['arguments']['uid']['not'] = 0;
    /* Filter criterion: User: Active */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'users';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = '1';
    $handler->display->display_options['filters']['status']['group'] = 0;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    /* Filter criterion: Getlocations Fields: Glid */
    $handler->display->display_options['filters']['glid']['id'] = 'glid';
    $handler->display->display_options['filters']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['glid']['field'] = 'glid';
    $handler->display->display_options['filters']['glid']['operator'] = 'not empty';

    /* Display: Block 9 */
    $handler = $view->new_display('block', 'Block 9', 'block_9');
    $handler->display->display_options['block_description'] = 'View: Getlocations user map';

    $views[$view->name] = $view;


    /**
    * getlocations show all users nearby
    */
    $view = new view;
    $view->name = 'getlocations_map_nearby_users';
    $view->description = 'Show a map of nearby users';
    $view->tag = 'getlocations view';
    $view->base_table = 'users';
    $view->human_name = 'Getlocations map nearby users';
    $view->core = 7;
    $view->api_version = '3';
    $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

    /* Display: Defaults */
    $handler = $view->new_display('default', 'Defaults', 'default');
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['access']['perm'] = 'access user profiles';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    /* Footer: Global: Text area */
    $handler->display->display_options['footer']['area']['id'] = 'area';
    $handler->display->display_options['footer']['area']['table'] = 'views';
    $handler->display->display_options['footer']['area']['field'] = 'area';
    $handler->display->display_options['footer']['area']['empty'] = FALSE;
    /* Field: User: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'users';
    $handler->display->display_options['fields']['name']['field'] = 'name';
    $handler->display->display_options['fields']['name']['label'] = '';
    $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['name']['alter']['external'] = 0;
    $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 0;
    $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['name']['alter']['html'] = 0;
    $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['name']['hide_empty'] = 0;
    $handler->display->display_options['fields']['name']['empty_zero'] = 0;
    $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
    $handler->display->display_options['fields']['name']['link_to_user'] = 0;
    $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
    $handler->display->display_options['fields']['name']['format_username'] = 1;
    /* Field: Getlocations Fields: Glid */
    $handler->display->display_options['fields']['glid']['id'] = 'glid';
    $handler->display->display_options['fields']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['fields']['glid']['field'] = 'glid';
    $handler->display->display_options['fields']['glid']['label'] = '';
    $handler->display->display_options['fields']['glid']['exclude'] = TRUE;
    $handler->display->display_options['fields']['glid']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['external'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['html'] = 0;
    $handler->display->display_options['fields']['glid']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['glid']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['glid']['hide_empty'] = 0;
    $handler->display->display_options['fields']['glid']['empty_zero'] = 0;
    $handler->display->display_options['fields']['glid']['hide_alter_empty'] = 1;
    /* Field: Getlocations Fields: Latitude */
    $handler->display->display_options['fields']['latitude']['id'] = 'latitude';
    $handler->display->display_options['fields']['latitude']['table'] = 'getlocations_fields';
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
    $handler->display->display_options['fields']['latitude']['hide_alter_empty'] = 1;
    /* Field: Getlocations Fields: Longitude */
    $handler->display->display_options['fields']['longitude']['id'] = 'longitude';
    $handler->display->display_options['fields']['longitude']['table'] = 'getlocations_fields';
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
    $handler->display->display_options['fields']['longitude']['hide_alter_empty'] = 1;
    /* Field: Getlocations Fields: Name */
    $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
    $handler->display->display_options['fields']['name_1']['table'] = 'getlocations_fields';
    $handler->display->display_options['fields']['name_1']['field'] = 'name';
    $handler->display->display_options['fields']['name_1']['label'] = '';
    $handler->display->display_options['fields']['name_1']['exclude'] = TRUE;
    $handler->display->display_options['fields']['name_1']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['external'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['name_1']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['name_1']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['html'] = 0;
    $handler->display->display_options['fields']['name_1']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['name_1']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['name_1']['hide_empty'] = 0;
    $handler->display->display_options['fields']['name_1']['empty_zero'] = 0;
    $handler->display->display_options['fields']['name_1']['hide_alter_empty'] = 1;
    /* Sort criterion: Getlocations Fields: Distance */
    $handler->display->display_options['sorts']['distance']['id'] = 'distance';
    $handler->display->display_options['sorts']['distance']['table'] = 'getlocations_fields';
    $handler->display->display_options['sorts']['distance']['field'] = 'distance';
    $handler->display->display_options['sorts']['distance']['origin'] = 'uid_arg';
    $handler->display->display_options['sorts']['distance']['nid_arg'] = 'null';
    $handler->display->display_options['sorts']['distance']['nid_loc_field'] = '';
    $handler->display->display_options['sorts']['distance']['uid_arg'] = 'uid';
    $handler->display->display_options['sorts']['distance']['uid_loc_field'] = '';
    /* Contextual filter: User: Uid */
    $handler->display->display_options['arguments']['uid']['id'] = 'uid';
    $handler->display->display_options['arguments']['uid']['table'] = 'users';
    $handler->display->display_options['arguments']['uid']['field'] = 'uid';
    $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
    $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'user';
    $handler->display->display_options['arguments']['uid']['default_argument_options']['user'] = FALSE;
    $handler->display->display_options['arguments']['uid']['default_argument_skip_url'] = 0;
    $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['arguments']['uid']['break_phrase'] = 0;
    $handler->display->display_options['arguments']['uid']['not'] = 1;
    /* Filter criterion: User: Active */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'users';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['value'] = '1';
    $handler->display->display_options['filters']['status']['group'] = 0;
    $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
    /* Filter criterion: Getlocations Fields: Glid */
    $handler->display->display_options['filters']['glid']['id'] = 'glid';
    $handler->display->display_options['filters']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['glid']['field'] = 'glid';
    $handler->display->display_options['filters']['glid']['operator'] = 'not empty';
    /* Filter criterion: Getlocations Fields: Latitude */
    $handler->display->display_options['filters']['latitude']['id'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['latitude']['field'] = 'latitude';
    $handler->display->display_options['filters']['latitude']['operator'] = '!=';
    $handler->display->display_options['filters']['latitude']['value']['value'] = '0';
    /* Filter criterion: Getlocations Fields: Longitude */
    $handler->display->display_options['filters']['longitude']['id'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['longitude']['field'] = 'longitude';
    $handler->display->display_options['filters']['longitude']['operator'] = '!=';
    $handler->display->display_options['filters']['longitude']['value']['value'] = '0';
    /* Filter criterion: Getlocations Fields: Distance */
    $handler->display->display_options['filters']['distance']['id'] = 'distance';
    $handler->display->display_options['filters']['distance']['table'] = 'getlocations_fields';
    $handler->display->display_options['filters']['distance']['field'] = 'distance';
    $handler->display->display_options['filters']['distance']['operator'] = 'dist';
    $handler->display->display_options['filters']['distance']['value'] = array(
      'latitude' => '',
      'longitude' => '',
      'php_code' => '',
      'nid_arg' => 'null',
      'nid_loc_field' => '',
      'uid_arg' => 'uid',
      'uid_loc_field' => '',
      'search_distance' => '100',
      'search_units' => 'km',
    );
    $handler->display->display_options['filters']['distance']['origin'] = 'uid_arg';

    /* Display: Block 10 */
    $handler = $view->new_display('block', 'Block 10', 'block_10');
    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['title'] = 'Nearby users';
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'getlocations';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['defaults']['footer'] = FALSE;
    $handler->display->display_options['block_description'] = 'View: Getlocations users nearby map';
    /* Footer: Global: Text area */
    $handler->display->display_options['footer']['area']['id'] = 'area';
    $handler->display->display_options['footer']['area']['table'] = 'views';
    $handler->display->display_options['footer']['area']['field'] = 'area';
    $handler->display->display_options['footer']['area']['empty'] = FALSE;
    $handler->display->display_options['footer']['area']['content'] = '<a href="/getlocations_users_nearby/!1">Show on a large map</a>';
    $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
    $handler->display->display_options['footer']['area']['tokenize'] = 1;
    $handler->display->display_options['defaults']['sorts'] = FALSE;

    /* Display: Block 11 */
    $handler = $view->new_display('block', 'Block 11', 'block_11');
    $handler->display->display_options['defaults']['title'] = FALSE;
    $handler->display->display_options['title'] = 'List nearby users';
    $handler->display->display_options['defaults']['pager'] = FALSE;
    $handler->display->display_options['pager']['type'] = 'mini';
    $handler->display->display_options['pager']['options']['items_per_page'] = '10';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['pager']['options']['id'] = '0';
    $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: User: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'users';
    $handler->display->display_options['fields']['name']['field'] = 'name';
    $handler->display->display_options['fields']['name']['label'] = '';
    $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['name']['alter']['external'] = 0;
    $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 0;
    $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 0;
    $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['name']['alter']['html'] = 0;
    $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['name']['hide_empty'] = 0;
    $handler->display->display_options['fields']['name']['empty_zero'] = 0;
    $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
    $handler->display->display_options['fields']['name']['link_to_user'] = 1;
    $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
    $handler->display->display_options['fields']['name']['format_username'] = 1;
    /* Field: Getlocations Fields: Glid */
    $handler->display->display_options['fields']['glid']['id'] = 'glid';
    $handler->display->display_options['fields']['glid']['table'] = 'getlocations_fields';
    $handler->display->display_options['fields']['glid']['field'] = 'glid';
    $handler->display->display_options['fields']['glid']['label'] = '';
    $handler->display->display_options['fields']['glid']['exclude'] = TRUE;
    $handler->display->display_options['fields']['glid']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['external'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['glid']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['glid']['alter']['html'] = 0;
    $handler->display->display_options['fields']['glid']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['glid']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['glid']['hide_empty'] = 0;
    $handler->display->display_options['fields']['glid']['empty_zero'] = 0;
    $handler->display->display_options['fields']['glid']['hide_alter_empty'] = 1;
    /* Field: Getlocations Fields: Latitude */
    $handler->display->display_options['fields']['latitude']['id'] = 'latitude';
    $handler->display->display_options['fields']['latitude']['table'] = 'getlocations_fields';
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
    $handler->display->display_options['fields']['latitude']['hide_alter_empty'] = 1;
    /* Field: Getlocations Fields: Longitude */
    $handler->display->display_options['fields']['longitude']['id'] = 'longitude';
    $handler->display->display_options['fields']['longitude']['table'] = 'getlocations_fields';
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
    $handler->display->display_options['fields']['longitude']['hide_alter_empty'] = 1;
    /* Field: Getlocations Fields: Name */
    $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
    $handler->display->display_options['fields']['name_1']['table'] = 'getlocations_fields';
    $handler->display->display_options['fields']['name_1']['field'] = 'name';
    $handler->display->display_options['fields']['name_1']['label'] = '';
    $handler->display->display_options['fields']['name_1']['exclude'] = TRUE;
    $handler->display->display_options['fields']['name_1']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['external'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['name_1']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['name_1']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['name_1']['alter']['html'] = 0;
    $handler->display->display_options['fields']['name_1']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['name_1']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['name_1']['hide_empty'] = 0;
    $handler->display->display_options['fields']['name_1']['empty_zero'] = 0;
    $handler->display->display_options['fields']['name_1']['hide_alter_empty'] = 1;
    $handler->display->display_options['block_description'] = 'View: Getlocations list users nearby';

    /* Display: Page */
    $handler = $view->new_display('page', 'Page', 'page_1');
    $handler->display->display_options['defaults']['style_plugin'] = FALSE;
    $handler->display->display_options['style_plugin'] = 'getlocations';
    $handler->display->display_options['defaults']['style_options'] = FALSE;
    $handler->display->display_options['defaults']['row_plugin'] = FALSE;
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['defaults']['row_options'] = FALSE;
    $handler->display->display_options['path'] = 'getlocations_users_nearby';

    $views[$view->name] = $view;


  }

  return $views;
}
