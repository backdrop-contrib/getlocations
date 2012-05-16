<?php

/**
 * @file
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
 * getlocations_search module administration functions.
 */

/**
 * Function to display the getlocations_search admin settings form
 * @return
 *   Returns the form.
 */
function getlocations_search_settings_form() {

  $getlocations_search_defaults = getlocations_search_defaults();
  drupal_add_js(GETLOCATIONS_SEARCH_PATH . '/js/getlocations_search_admin.js');
  $form = array();

  $form['getlocations_search_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Getlocations Search Default settings'),
    '#description' => t('The settings here will provide the defaults for Getlocations Search.'),
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );

  $options = array('google_ac' => t('Google Places Autocomplete'), 'text' => t('Textfield'));
  $vocab_list = FALSE;
  if (module_exists('taxonomy')) {
    $options['vocab'] = t('Vocabulary');
    $vocab_list = getlocations_search_get_vocabularies();
  }
  $form['getlocations_search_defaults']['method'] = array(
    '#type' => 'select',
    '#title' => t('Input type'),
    '#options' => $options,
    '#default_value' => $getlocations_search_defaults['method'],
  );
  // taxonomy support
  if ($vocab_list) {
    $form['getlocations_search_defaults']['vocab'] = array(
      '#type' => 'select',
      '#title' => t('Vocabulary'),
      '#options' => $vocab_list,
      '#default_value' => $getlocations_search_defaults['vocab'],
    );
    $vocab_opts = array('dropdown' => t('Dropdown'), 'autocomplete' => t('Autocomplete'));
    $form['getlocations_search_defaults']['vocab_element'] = array(
      '#type' => 'select',
      '#title' => t('Vocabulary Selection method'),
      '#options' => $vocab_opts,
      '#default_value' => $getlocations_search_defaults['vocab_element'],
    );
  }

#  $markers = getlocations_get_marker_titles();
#  $form['getlocations_search_defaults']['search_map_marker'] = getlocations_element_map_marker(
#    t('Search Map marker'),
#    $markers,
#    $getlocations_search_defaults['search_map_marker'],
#    ''
#  );

  $form['getlocations_search_defaults']['search_distance'] = getlocations_fields_element_search_distance($getlocations_search_defaults['search_distance'], t('Search distance'), t('The distance away from the center to search for locations.'));

  $form['getlocations_search_defaults']['search_units'] = getlocations_fields_element_distance_unit($getlocations_search_defaults['search_units']);

  $form['getlocations_search_defaults']['search_limits'] = getlocations_element_map_limits($getlocations_search_defaults['search_limits']);

  $opts = array('all' => t('Show All'), 'node' => t('Nodes'));
  $opts['user'] = t('Users');
  if (module_exists('taxonomy')) {
    $opts['term'] = t('Terms');
  }
  if (module_exists('comment')) {
    $opts['comment'] = t('Comments');
  }
  $form['getlocations_search_defaults']['search_type'] = array(
    '#type' => 'select',
    '#title' => t('Restrict the search'),
    '#options' => $opts,
    '#default_value' => $getlocations_search_defaults['search_type'],
    '#description' => t('The default for the type of content location.'),
  );

  $form['getlocations_search_defaults']['display_search_distance'] = getlocations_element_map_checkbox(
    t('Display Search distance box'),
    $getlocations_search_defaults['display_search_distance'],
    t('Allow users to modify the search distance.')
  );
  $form['getlocations_search_defaults']['display_search_units'] = getlocations_element_map_checkbox(
    t('Display Search units dropdown'),
    $getlocations_search_defaults['display_search_units'],
    t('Allow users to modify the search units.')
  );
  $form['getlocations_search_defaults']['display_search_limits'] = getlocations_element_map_checkbox(
    t('Display Search limits dropdown'),
    $getlocations_search_defaults['display_search_limits'],
    t('Allow users to modify the search limits.')
  );

  $form['getlocations_search_defaults']['display_search_type'] = getlocations_element_map_checkbox(
    t('Display Search type dropdown'),
    $getlocations_search_defaults['display_search_type'],
    t('Allow users to modify the search type.')
  );

  $form['getlocations_search_defaults']['display_dms'] = getlocations_element_map_checkbox(
    t('Show Latitude/Longitude in Degrees, minutes, seconds'),
    $getlocations_search_defaults['display_dms'],
    ''
  );

  $form['getlocations_search_defaults'] += getlocations_map_display_basics_form($getlocations_search_defaults);

  $form['getlocations_search_defaults'] += getlocations_map_display_options_form($getlocations_search_defaults, FALSE, TRUE);

  $form['getlocations_search_defaults']['markeractiontype'] = getlocations_element_map_markeractiontype(
    $getlocations_search_defaults['markeractiontype']
  );
  $form['getlocations_search_defaults']['markeraction'] = getlocations_element_map_markeraction(
    $getlocations_search_defaults['markeraction']
  );

  $form['getlocations_search_defaults']['minzoom'] = getlocations_element_map_zoom(
    t('Minimum Zoom'),
    $getlocations_search_defaults['minzoom'],
    t('The Minimum zoom level at which markers will be visible.')
  );

  $form['getlocations_search_defaults']['maxzoom'] = getlocations_element_map_zoom(
    t('Maximum Zoom'),
    $getlocations_search_defaults['maxzoom'],
    t('The Maximum zoom level at which markers will be visible.')
  );

  $form['getlocations_search_defaults']['nodezoom'] = getlocations_element_map_zoom(
    t('Default Zoom for Single location'),
    $getlocations_search_defaults['nodezoom'],
    t('The Default zoom level for a single marker.')
  );
  // marker manager
  $form['getlocations_search_defaults']['markermanagertype'] = getlocations_element_markermanagertype($getlocations_search_defaults['markermanagertype']);
  $form['getlocations_search_defaults']['usemarkermanager'] = getlocations_element_map_checkbox(
    t('Use Marker manager'),
    $getlocations_search_defaults['usemarkermanager'],
    t('Use Marker manager. Switching this off will use no manager.')
  );
  $form['getlocations_search_defaults']['useclustermanager'] = getlocations_element_map_checkbox(
    t('Use Cluster manager'),
    $getlocations_search_defaults['useclustermanager'],
    t('Use Cluster manager. Switching this off will use no manager.')
  );

  if (file_exists(GETLOCATIONS_PATH . '/getlocations.markerclusterer_override.inc')) {
    module_load_include('inc', 'getlocations', 'getlocations.markercluster_override');
  }
  else {
    module_load_include('inc', 'getlocations', 'getlocations.markercluster');
  }
  $form['getlocations_search_defaults']['markerclusterer_style'] = getlocations_element_markerclusterer_style($getlocations_search_defaults['markerclusterer_style']);
  $form['getlocations_search_defaults']['markerclusterer_title'] =  array(
    '#type' => 'textfield',
    '#title' => t('Markerclusterer tooltip'),
    '#default_value' => $getlocations_search_defaults['markerclusterer_title'],
    '#size' => 30,
    '#description' => t('The text of a Markerclusterer tooltip'),
  );
  $form['getlocations_search_defaults']['markerclusterer_zoom'] = getlocations_element_markerclusterer_zoom($getlocations_search_defaults['markerclusterer_zoom']);
  $form['getlocations_search_defaults']['markerclusterer_size'] = getlocations_element_markerclusterer_size($getlocations_search_defaults['markerclusterer_size']);
  $form['getlocations_search_defaults']['markerclusterer_minsize'] = getlocations_element_markerclusterer_minsize($getlocations_search_defaults['markerclusterer_minsize']);

  $form['getlocations_search_paths'] = array(
    '#type' => 'fieldset',
    '#title' => t('Javascript paths'),
    '#description' => t('For advanced users who want to supply their own javascript.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );
  $getlocations_search_paths = variable_get('getlocations_search_paths', array('getlocations_search_path' => GETLOCATIONS_SEARCH_PATH . '/js/getlocations_search.js'));
  $form['getlocations_search_paths']['getlocations_search_path'] = getlocations_element_path(
    t('Path to getlocations_search javascript file'),
    $getlocations_search_paths['getlocations_search_path'],
    70,
    128,
    t('Where the getlocations_search javascript file is located.')
  );

  $form = system_settings_form($form);
  unset($form['#theme']);
  $form['#theme'] = 'getlocations_search_settings_form';
  return $form;

}
