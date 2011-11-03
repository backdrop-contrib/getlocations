<?php

/**
 * @file
 * getlocations module administration functions.
 * using version 3 googlemaps API
 */

/**
 * Function to display the getlocations admin settings form
 * @return
 *   Returns the form.
 */
function getlocations_settings_form() {
  $getlocations_defaults = getlocations_defaults();
  drupal_add_js(GETLOCATIONS_PATH .'/js/getlocations_admin.js');

  $form = array();

  $form['rebuild'] = array(
    '#type' => 'fieldset',
    '#title' => t('Regenerate Getlocations marker cache'),
    '#description' => t('If you are having problems with markers, or have modified the .ini files in the markers folder, click here to rebuild the marker cache file.'),
  );
  if ( file_default_scheme() != 'public') {
    $form['rebuild']['getlocations_private_markerfile'] = array(
      '#type' => 'textfield',
      '#title' => t('Path to getlocations_markers.js'),
      '#description' => t('You are using the <em>Private</em> download method. For markers to work properly. you must press the <em>Regenerate</em> button, manually copy js/getlocations_markers.js from the files directory to a location accessible by the webserver, and enter the file path relative to the Drupal root (including the filename) in this field. Example: <em>sites/default/misc/getlocations_markers.js</em>'),
      '#default_value' => variable_get('getlocations_private_markerfile', ''),
    );
  }
  $form['rebuild']['rebuild_marker_js'] = array(
    '#type' => 'submit',
    '#value' => t('Regenerate'),
    '#submit' => array('_getlocations_rebuild_marker_js_submit'),
  );

  $form['getlocations_default'] = array(
    '#type' => 'fieldset',
    '#title' => t('Get locations map settings'),
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );
  $form['getlocations_default']['width'] = getlocations_element_map_tf(
    t('Default width'),
    $getlocations_defaults['width'],
    10,
    10,
    t('The default width of a Google map, as a CSS length or percentage. Examples: <em>50px</em>, <em>5em</em>, <em>2.5in</em>, <em>95%</em>')
  );
  $form['getlocations_default']['height'] = getlocations_element_map_tf(
    t('Default height'),
    $getlocations_defaults['height'],
    10,
    10,
    t('The default height of a Google map, as a CSS length or percentage. Examples: <em>50px</em>, <em>5em</em>, <em>2.5in</em>, <em>95%</em>')
  );

  $form['getlocations_default']['styles'] = array(
    '#type' => 'textarea',
    '#title' => t('Default styles'),
    '#default_value' => $getlocations_defaults['styles'],
    '#description' => t('The default styles of a Google map. Use !link for generating your styles', array('!link' => l('http://gmaps-samples-v3.googlecode.com/svn/trunk/styledmaps/wizard/', 'http://gmaps-samples-v3.googlecode.com/svn/trunk/styledmaps/wizard/', array('external' => TRUE)))),
  );

  $form['getlocations_default']['latlong'] = getlocations_element_map_tf(
    t('Map center'),
    $getlocations_defaults['latlong'],
    30,
    30,
    t('The default center coordinates of a Google map, expressed as a decimal latitude and longitude, separated by a comma. This must not be 0,0')
  );

  $form['getlocations_default']['zoom'] = getlocations_element_map_zoom(
    t('Zoom'),
    $getlocations_defaults['zoom'],
    t('The default zoom level of a Google map.')
  );

  $form['getlocations_default']['controltype'] = getlocations_element_map_zoom_controltype($getlocations_defaults['controltype']);
  $form['getlocations_default']['pancontrol'] = getlocations_element_map_checkbox(
    t('Show Pan control'),
    $getlocations_defaults['pancontrol']
  );

  $form['getlocations_default']['mtc'] = getlocations_element_map_mtc($getlocations_defaults['mtc']);

  $baselayers = array();
  foreach ($getlocations_defaults['baselayers'] AS $key => $value) {
    $baselayers[$key] = $value;
  }
  $form['getlocations_default']['maptype'] = getlocations_element_map_maptype($getlocations_defaults['maptype'], $baselayers);

  $form['getlocations_default']['baselayers']['Map'] = getlocations_element_map_baselayers_map($getlocations_defaults['baselayers']['Map']);
  $form['getlocations_default']['baselayers']['Satellite'] = getlocations_element_map_baselayers_satellite($getlocations_defaults['baselayers']['Satellite']);
  $form['getlocations_default']['baselayers']['Hybrid'] = getlocations_element_map_baselayers_hybrid($getlocations_defaults['baselayers']['Hybrid']);
  $form['getlocations_default']['baselayers']['Physical'] = getlocations_element_map_baselayers_physical($getlocations_defaults['baselayers']['Physical']);

  $form['getlocations_default']['behavior']['scale'] = getlocations_element_map_checkbox(
     t('Scale'),
     $getlocations_defaults['behavior']['scale'],
     t('Show scale')
  );

  $form['getlocations_default']['behavior']['overview'] = getlocations_element_map_checkbox(
    t('Overview map'),
    $getlocations_defaults['behavior']['overview'],
    t('Show overview map')
  );

  $form['getlocations_default']['behavior']['overview_opened'] = getlocations_element_map_checkbox(
    t('Overview map state'),
    $getlocations_defaults['behavior']['overview_opened'],
    t('Show overview map as open by default')
  );

  $form['getlocations_default']['behavior']['scrollwheel'] = getlocations_element_map_checkbox(
    t('Scrollwheel'),
    $getlocations_defaults['behavior']['scrollwheel'],
    t('Enable scrollwheel zooming')
  );

  $form['getlocations_default']['draggable'] = getlocations_element_map_checkbox(
    t('Draggable'),
    $getlocations_defaults['draggable'],
    t('Enable dragging the map.')
  );

  $form['getlocations_default']['streetview_show'] = getlocations_element_map_checkbox(
    t('Show streetview button'),
    $getlocations_defaults['streetview_show']
  );

  $form['getlocations_default']['trafficinfo'] = getlocations_element_map_checkbox(
    t('Enable Traffic information'),
    $getlocations_defaults['trafficinfo'],
    t('Google trafficinfo layer, limited availability.')
  );

  $form['getlocations_default']['bicycleinfo'] = getlocations_element_map_checkbox(
    t('Enable Bicycling information'),
    $getlocations_defaults['bicycleinfo'],
    t('Google bicycling layer, limited availability.')
  );

  $form['getlocations_default']['panoramio_show'] = getlocations_element_map_checkbox(
    t('Enable Panoramio'),
    $getlocations_defaults['panoramio_show'],
    t('Google panoramio picture links.')
  );

  $form['getlocations_default']['poi_show'] = getlocations_element_map_checkbox(
    t('Show Points of Interest'),
    $getlocations_defaults['poi_show'],
    t('Show Google points of interest icons.')
  );

  $form['getlocations_default']['transit_show'] = getlocations_element_map_checkbox(
    t('Show Transit Points'),
    $getlocations_defaults['transit_show'],
    t('Show Google transit points icons.')
  );

  // default marker
  $markers = getlocations_get_marker_titles();
  $form['getlocations_default']['map_marker'] = getlocations_element_map_marker(
    t('Default Map marker'),
    $markers,
    $getlocations_defaults['map_marker']
  );
  if (module_exists('location_user')) {
    $form['getlocations_default']['user_map_marker'] = getlocations_element_map_marker(
      t('Default User Map marker'),
      $markers,
      $getlocations_defaults['user_map_marker']
    );
  }

  $form['getlocations_default']['markeraction'] = getlocations_element_map_markeraction(
    $getlocations_defaults['markeraction']
  );

  $form['getlocations_default']['minzoom'] = getlocations_element_map_zoom(
    t('Minimum Zoom'),
    $getlocations_defaults['minzoom'],
    t('The Minimum zoom level at which markers will be visible.')
  );
  $form['getlocations_default']['maxzoom'] = getlocations_element_map_zoom(
    t('Maximum Zoom'),
    $getlocations_defaults['maxzoom'],
    t('The Maximum zoom level at which markers will be visible.')
  );
  $form['getlocations_default']['nodezoom'] = getlocations_element_map_zoom(
    t('Default Zoom for Single location'),
    $getlocations_defaults['nodezoom'],
    t('The Default zoom level for a single marker.')
  );

  $form['getlocations_default']['usemarkermanager'] = getlocations_element_map_checkbox(
    t('Use Marker manager'),
    $getlocations_defaults['usemarkermanager'],
    t('Use Marker manager. Switching this off will use no manager')
  );

  $form['getlocations_default']['pansetting'] = getlocations_element_map_pansetting($getlocations_defaults['pansetting']);

  $form['getlocations_default']['returnlink_page_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show link back to page'),
    '#default_value' =>  $getlocations_defaults['returnlink_page_enable'],
    '#return_value' => 1,
  );
  $form['getlocations_default']['returnlink_page_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Text of page return link'),
    '#default_value' => $getlocations_defaults['returnlink_page_link'],
    '#size' => 30,
    '#description' => t('Use %t to insert the page title'),
    '#prefix' => '<div id="wrap-page-link">',
    '#suffix' => '</div>',
  );
  if (module_exists('location_user')) {
    $form['getlocations_default']['returnlink_user_enable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show link back to user'),
      '#default_value' =>  $getlocations_defaults['returnlink_user_enable'],
      '#return_value' => 1,
    );
    $form['getlocations_default']['returnlink_user_link'] = array(
      '#type' => 'textfield',
      '#title' => t('Text of user return link'),
      '#default_value' => $getlocations_defaults['returnlink_user_link'],
      '#size' => 30,
      '#description' => t('Use %n to insert the user name'),
      '#prefix' => '<div id="wrap-user-link">',
      '#suffix' => '</div>',
    );
  }

  // node markers
  $form['getlocations_node_marker'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content type markers'),
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );
  $getlocations_node_marker = variable_get('getlocations_node_marker', array('enable' => 0));
  $form['getlocations_node_marker']['enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Markers for Content types'),
    '#default_value' =>  $getlocations_node_marker['enable'],
    '#return_value' => 1,
  );
  $types = getlocations_get_types();
  $typect = 0;
  foreach ($types AS $type => $name) {
    $form['getlocations_node_marker']['content_type'][$type]['map_marker'] = getlocations_element_map_marker(
      t('%name Map marker', array('%name' => $name)),
      $markers,
      (isset($getlocations_node_marker['content_type'][$type]['map_marker']) ? $getlocations_node_marker['content_type'][$type]['map_marker'] : $getlocations_defaults['map_marker'])
    );

    if (! $typect) {
      $form['getlocations_node_marker']['content_type'][$type]['map_marker']['#prefix'] = '<div id="wrap-getlocations-node-markers">';
    }
    $typect++;
  }
  $form['getlocations_node_marker']['content_type'][$type]['map_marker']['#suffix'] = '</div>';

/*

  // vocabulary markers
  $types = getlocations_get_vocabularies();
  if ($types) {
    $form['getlocations_vocabulary_marker'] = array(
      '#type' => 'fieldset',
      '#title' => t('Taxonomy Vocabulary markers'),
      // This will store all the defaults in one variable.
      '#tree' => TRUE,
    );
    $getlocations_vocabulary_marker = variable_get('getlocations_vocabulary_marker', array('enable' => 0));
    $form['getlocations_vocabulary_marker']['enable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable Markers for Vocabularies'),
      '#default_value' =>  $getlocations_vocabulary_marker['enable'],
      '#return_value' => 1,
    );
    $typect = 0;
    foreach ($types AS $type => $name) {

      $form['getlocations_vocabulary_marker']['vocabulary'][$type]['map_marker'] = getlocations_element_map_marker(
        t('%name Map marker', array('%name' => $name)),
        $markers,
        (isset($getlocations_vocabulary_marker['vocabulary'][$type]['map_marker']) ? $getlocations_vocabulary_marker['vocabulary'][$type]['map_marker'] : $getlocations_defaults['map_marker'])
      );
      if (! $typect) {
        $form['getlocations_vocabulary_marker']['vocabulary'][$type]['map_marker']['#prefix'] = '<div id="wrap-getlocations-vocabulary-markers">';
      }
      $typect++;
    }
    $form['getlocations_vocabulary_marker']['vocabulary'][$type]['map_marker']['#suffix'] = '</div>';
  }
  // roles markers
  $form['getlocations_roles_marker'] = array(
    '#type' => 'fieldset',
    '#title' => t('Role markers'),
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );
  $getlocations_roles_marker = variable_get('getlocations_roles_marker', array('enable' => 0));
  $form['getlocations_roles_marker']['enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Markers for Roles'),
    '#default_value' =>  $getlocations_roles_marker['enable'],
    '#return_value' => 1,
  );
  $types = user_roles(TRUE);
  $typect = 0;
  foreach ($types AS $type => $name) {

    $form['getlocations_roles_marker']['roles'][$type]['map_marker'] = getlocations_element_map_marker(
      t('%name Map marker', array('%name' => $name)),
      $markers,
      (isset($getlocations_roles_marker['roles'][$type]['map_marker']) ? $getlocations_roles_marker['roles'][$type]['map_marker'] : $getlocations_defaults['map_marker'])
    );
    if (! $typect) {
      $form['getlocations_roles_marker']['roles'][$type]['map_marker']['#prefix'] = '<div id="wrap-getlocations-roles-markers">';
    }
    $typect++;
  }
  $form['getlocations_roles_marker']['roles'][$type]['map_marker']['#suffix'] = '</div>';
*/
  if (module_exists('colorbox')) {
    $form['getlocations_colorbox'] = array(
      '#type' => 'fieldset',
      '#title' => t('Colorbox settings'),
      // This will store all the defaults in one variable.
      '#tree' => TRUE,
    );
    $getlocations_colorbox = variable_get('getlocations_colorbox', array(
      'enable' => 0,
      'width' => 600,
      'height' => 600,
    ));
    $form['getlocations_colorbox']['enable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable Colorbox'),
      '#default_value' =>  $getlocations_colorbox['enable'],
      '#return_value' => 1,
      '#description' => t('Show Getlocations in a Colorbox.'),
    );
    $form['getlocations_colorbox']['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Colorbox width'),
      '#default_value' => $getlocations_colorbox['width'],
      '#size' => 5,
      '#required' => TRUE,
      // need this to get validation to work
      '#parents' => array('getlocations_colorbox', 'width'),
      '#prefix' => '<div id="wrap-getlocations-colorbox">',
    );
    $form['getlocations_colorbox']['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Colorbox height'),
      '#default_value' => $getlocations_colorbox['height'],
      '#size' => 5,
      '#required' => TRUE,
      // need this to get validation to work
      '#parents' => array('getlocations_colorbox', 'height'),
      '#suffix' => '</div>',
    );
  }

  $form['getlocations_paths'] = array(
    '#type' => 'fieldset',
    '#title' => t('Javascript paths'),
    '#description' => t('For advanced users who want to supply their own javascript.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );
  $getlocations_paths = variable_get('getlocations_paths', array(
    'infobubble_path' => GETLOCATIONS_PATH .'/js/infobubble.js',
    'infobubble_options_path' => GETLOCATIONS_PATH .'/js/infobubble_options.js',
    'markermanager_path' => GETLOCATIONS_PATH .'/js/markermanager.js')
  );
  $form['getlocations_paths']['infobubble_path'] = getlocations_element_path(
    t('Path to InfoBubble javascript file'),
    $getlocations_paths['infobubble_path'],
    60,
    128,
    t('Where the InfoBubble javascript file is located.')
  );
  $form['getlocations_paths']['infobubble_options_path'] = getlocations_element_path(
    t('Path to InfoBubble options javascript file'),
    $getlocations_paths['infobubble_options_path'],
    60,
    128,
    t('Where the InfoBubble options javascript file is located. If this file does not exist the default settings will be used.')
  );

  $form['getlocations_paths']['markermanager_path'] = getlocations_element_path(
    t('Path to markermanager javascript file'),
    $getlocations_paths['markermanager_path'],
    60,
    128,
    t('Where the markermanager javascript file is located.')
  );

  $form['#validate'][] = 'getlocations_settings_validate';

  return system_settings_form($form);

}

function getlocations_settings_validate($form, &$form_state) {

  if (! getlocations_latlon_check(  $form_state['values']['getlocations_default']['latlong']  )   ) {
    form_set_error('getlocations_default][latlong', t('Map coordinates must be expressed as a decimal latitude and longitude, separated by a comma.'));
  }
  $found = FALSE;
  foreach ($form_state['values']['getlocations_default']['baselayers'] as $l) {
    if ($l) {
      $found = TRUE;
      break;
    }
  }
  if (!$found) {
    form_set_error('getlocations_default][baselayers', t('You must select at least one baselayer!'));
  }

  // Check that the default map type is sane.
#  if (!$form_state['values']['getlocations_default']['baselayers'][$form_state['values']['getlocations_default']['maptype']]) {
#    form_error($form['getlocations_default']['baselayers']['maptype'], t('The default map type must be an enabled baselayer!'));
#  }

  if ( $form_state['values']['getlocations_default']['returnlink_page_enable'] && empty($form_state['values']['getlocations_default']['returnlink_page_link'])) {
    form_set_error('getlocations_default][returnlink_page_link', t('Page return link must be filled in'));
  }
#  if (module_exists('location_user')) {
#    if ( $form_state['values']['getlocations_default']['returnlink_user_enable'] && empty($form_state['values']['getlocations_default']['returnlink_user_link'])) {
#      form_set_error('getlocations_default][returnlink_user_link', t('User return link must be filled in'));
#    }
#  }
  if (module_exists('colorbox') && isset($form_state['values']['getlocations_colorbox']['enable']) && $form_state['values']['getlocations_colorbox']['enable']) {
    if (empty($form_state['values']['getlocations_colorbox']['width']) || ! is_numeric($form_state['values']['getlocations_colorbox']['width']) || $form_state['values']['getlocations_colorbox']['width'] < 1 ) {
      form_set_error('getlocations_colorbox][width', t('Colorbox width must be a number'));
    }
    if (empty($form_state['values']['getlocations_colorbox']['height']) || ! is_numeric($form_state['values']['getlocations_colorbox']['height']) || $form_state['values']['getlocations_colorbox']['height'] < 1 ) {
      form_set_error('getlocations_colorbox][height', t('Colorbox height must be a number'));
    }
  }

  $list = array('Map', 'Satellite', 'Hybrid', 'Physical');
  $found = FALSE;
  foreach ($list AS $maptype) {
    if ($form_state['values']['getlocations_default']['maptype'] == $maptype && $form_state['values']['getlocations_default']['baselayers'][$maptype] ) {
      $found = TRUE;
      break;
    }
  }
  if (! $found) {
    // force a setting
    $form_state['values']['getlocations_default']['maptype'] = 'Map';
    $form_state['values']['getlocations_default']['baselayers']['Map'] = 1;
  }

}

/**
 * Rebuild marker js.
 */
function _getlocations_rebuild_marker_js_submit($form, &$form_state) {
  getlocations_regenerate_markers();
  drupal_set_message(t('Marker cache regenerated.'));
}

