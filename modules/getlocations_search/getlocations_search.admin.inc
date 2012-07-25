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
  $form['getlocations_search_defaults']['method'] = getlocations_element_dd(
    t('Input type'),
    $getlocations_search_defaults['method'],
    $options
  );
  $form['getlocations_search_defaults']['autocomplete_bias'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Viewport bias'),
    '#description' => t('Bias the Google Autocomplete results to the area on the map.'),
    '#default_value' => ($getlocations_search_defaults['autocomplete_bias'] ? $getlocations_search_defaults['autocomplete_bias'] : 0),
    '#return_value' => 1,
  );

  // country restriction
  $form['getlocations_search_defaults']['restrict_by_country'] = getlocations_element_map_checkbox(
    t('Restrict by country'),
    $getlocations_search_defaults['restrict_by_country'],
    t('Restrict searches to the country set below. Works with Google Autocomplete.')
  );
  $form['getlocations_search_defaults']['restrict_by_country']['#suffix'] = '<div id="getlocations_search_country">';
  $countries = getlocations_get_countries_list();
  $form['getlocations_search_defaults']['country'] = getlocations_element_dd(
    t('Search country'),
    $getlocations_search_defaults['country'],
    $countries
  );
  $form['getlocations_search_defaults']['country']['#suffix'] = '</div>';

  $form['getlocations_search_defaults']['use_geolocation_button'] = getlocations_element_map_checkbox(
    t('Provide Browser based geocoding option'),
    $getlocations_search_defaults['use_geolocation_button'],
    t('Use the browser to find a location. For gps enabled mobile devices.')
  );

  // taxonomy support
  if ($vocab_list) {
    $form['getlocations_search_defaults']['vocab'] = getlocations_element_dd(
      t('Vocabulary'),
      $getlocations_search_defaults['vocab'],
      $vocab_list
    );
    $vocab_opts = array('dropdown' => t('Dropdown'), 'autocomplete' => t('Autocomplete'));
    $form['getlocations_search_defaults']['vocab_element'] = getlocations_element_dd(
      t('Vocabulary Selection method'),
      $getlocations_search_defaults['vocab_element'],
      $vocab_opts
    );
  }

  $form['getlocations_search_defaults']['search_distance'] = getlocations_element_search_distance(
    $getlocations_search_defaults['search_distance'],
    t('Search distance'),
    t('The distance away from the center to search for locations.')
  );

  $form['getlocations_search_defaults']['search_units'] = getlocations_element_distance_unit(
    $getlocations_search_defaults['search_units']
  );

  // are there any modules providing locations?
  if (getlocations_search_do_types()) {

    $form['getlocations_search_defaults']['search_limits'] = getlocations_element_map_limits(
      $getlocations_search_defaults['search_limits']
    );

    $opts = array('all' => t('Show All'), 'node' => t('Nodes'));
    $opts['user'] = t('Users');
    if (module_exists('taxonomy')) {
      $opts['term'] = t('Terms');
    }
    if (module_exists('comment')) {
      $opts['comment'] = t('Comments');
    }
    $form['getlocations_search_defaults']['search_type'] = getlocations_element_dd(
      t('Restrict the search'),
      $getlocations_search_defaults['search_type'],
      $opts,
      t('The default for the type of content location.')
    );
  }
  else {
    $form['getlocations_search_defaults']['search_limits'] = array(
      '#type' => 'value',
      '#value' => 0,
    );
    $form['getlocations_search_defaults']['search_type'] = array(
      '#type' => 'value',
      '#value' => 'all',
    );
  }

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

  if (getlocations_search_do_types()) {
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
  }
  else {
    $form['getlocations_search_defaults']['display_search_limits'] =  array(
      '#type' => 'value',
      '#value' => 0,
    );
    $form['getlocations_search_defaults']['display_search_type'] = array(
      '#type' => 'value',
      '#value' => 0,
    );
  }
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

  $form['getlocations_search_defaults']['markerclusterer_title'] = getlocations_element_map_tf(
    t('Markerclusterer tooltip'),
    $getlocations_search_defaults['markerclusterer_title'],
    t('The text of a Markerclusterer tooltip'),
    30,
    64,
    TRUE
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
