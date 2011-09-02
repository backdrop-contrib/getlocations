<?php

// using version 3 googlemaps API

/**
 * @file
 * getlocations module administration functions.
 */

/**
 * Function to display the getlocations admin settings form
 * @return
 *   Returns the form.
 */
function getlocations_settings_form() {
  $getlocations_defaults = getlocations_defaults();

  $form = array();
  $form['getlocations_default'] = array(
    '#type' => 'fieldset',
    '#title' => t('Get locations map settings'),
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );
  $form['getlocations_default']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Default width'),
    '#default_value' => $getlocations_defaults['width'],
    '#size' => 25,
    '#maxlength' => 25,
    '#description' => t('The default width of a Google map, as a CSS length or percentage. Examples: <em>50px</em>, <em>5em</em>, <em>2.5in</em>, <em>95%</em>'),
    '#required' => TRUE,
  );
  $form['getlocations_default']['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Default height'),
    '#default_value' => $getlocations_defaults['height'],
    '#size' => 25,
    '#maxlength' => 25,
    '#description' => t('The default height of a Google map, as a CSS length or percentage. Examples: <em>50px</em>, <em>5em</em>, <em>2.5in</em>, <em>95%</em>'),
    '#required' => TRUE,
  );
  $form['getlocations_default']['latlong'] = array(
    '#type' => 'textfield',
    '#title' => t('Map center'),
    '#default_value' => $getlocations_defaults['latlong'],
    '#size' => 50,
    '#maxlength' => 255,
    '#description' => t('The default center coordinates of Google map, expressed as a decimal latitude and longitude, separated by a comma.'),
    '#required' => TRUE,
  );
  $form['getlocations_default']['zoom'] = array(
    '#type' => 'select',
    '#title' => t('Zoom'),
    '#default_value' => $getlocations_defaults['zoom'],
    '#options' => drupal_map_assoc(range(0, 17)),
    '#description' => t('The default zoom level of a Google map.'),
  );
  $form['getlocations_default']['controltype'] = array(
    '#type' => 'select',
    '#title' => t('Zoom Control type'),
    '#options' => array(
      'none' => t('None'),
      'default' => t('Default'),
      'small' => t('Small'),
      'large' => t('Large'),
    ),
    '#default_value' => $getlocations_defaults['controltype'],
  );
  $form['getlocations_default']['pancontrol'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Pan control'),
    '#default_value' => $getlocations_defaults['pancontrol'],
    '#return_value' => 1,
  );
  $form['getlocations_default']['mtc'] = array(
    '#type' => 'select',
    '#title' => t('Map Control Type'),
    '#options' => array(
      'none' => t('None'),
      'standard' => t('Horizontal bar'),
      'menu' => t('Dropdown'),
    ),
    '#default_value' => $getlocations_defaults['mtc'],
  );

  $form['getlocations_default']['maptype'] = array(
    '#type' => 'select',
    '#title' => t('Default map type'),
    '#default_value' => $getlocations_defaults['maptype'],
    '#options' => array(
      'Map' => t('Standard street map'),
      'Satellite' => t('Standard satellite map'),
      'Hybrid' => t('Hybrid satellite map'),
      'Physical' => t('Terrain map'),
    ),
  );
  $form['getlocations_default']['baselayers']['Map'] = array(
    '#type' => 'checkbox',
    '#title' => t('Standard street map'),
    '#description' => t('The standard default street map.'),
    '#default_value' => $getlocations_defaults['baselayers']['Map'],
    '#return_value' => 1,
    '#prefix' => '<fieldset><legend>' . t('Enable map types') . '</legend>',
  );
  $form['getlocations_default']['baselayers']['Satellite'] = array(
    '#type' => 'checkbox',
    '#title' => t('Standard satellite map'),
    '#description' => t('Satellite view without street overlay.'),
    '#default_value' => $getlocations_defaults['baselayers']['Satellite'],
    '#return_value' => 1,
  );
  $form['getlocations_default']['baselayers']['Hybrid'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hybrid satellite map'),
    '#description' => t('Satellite view with street overlay.'),
    '#default_value' => $getlocations_defaults['baselayers']['Hybrid'],
    '#return_value' => 1,
  );
  $form['getlocations_default']['baselayers']['Physical'] = array(
    '#type' => 'checkbox',
    '#title' => t('Terrain map'),
    '#description' => t('Map with physical data (terrain, vegetation.)'),
    '#default_value' => $getlocations_defaults['baselayers']['Physical'],
    '#return_value' => 1,
    '#suffix' => '</fieldset>',
  );
  $form['getlocations_default']['behavior']['scale'] = array(
    '#type' => 'checkbox',
    '#title' => t('Scale'),
    '#description' => t('Show scale'),
    '#default_value' =>  $getlocations_defaults['behavior']['scale'],
    '#return_value' => 1,
  );
  $form['getlocations_default']['behavior']['overview'] = array(
    '#type' => 'checkbox',
    '#title' => t('Overview map'),
    '#description' => t('Show overview map'),
    '#default_value' =>  $getlocations_defaults['behavior']['overview'],
    '#return_value' => 1,
  );
  $form['getlocations_default']['behavior']['overview_opened'] = array(
    '#type' => 'checkbox',
    '#title' => t('Overview map state'),
    '#description' => t('Show overview map as open by default'),
    '#default_value' =>  $getlocations_defaults['behavior']['overview_opened'],
    '#return_value' => 1,
  );
  $form['getlocations_default']['behavior']['scrollwheel'] = array(
    '#type' => 'checkbox',
    '#title' => t('Scrollwheel'),
    '#description' => t('Enable scrollwheel zooming'),
    '#default_value' =>  $getlocations_defaults['behavior']['scrollwheel'],
    '#return_value' => 1,
  );
  $form['getlocations_default']['streetview_show'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show streetview button'),
    '#default_value' =>  $getlocations_defaults['streetview_show'],
    '#return_value' => 1,
  );

  $form['getlocations_default']['trafficinfo'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Traffic information'),
    '#default_value' =>  $getlocations_defaults['trafficinfo'],
    '#description' => t('Google trafficinfo layer, limited availability.'),
    '#return_value' => 1,
  );
  $form['getlocations_default']['bicycleinfo'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Bicycling information'),
    '#default_value' =>  $getlocations_defaults['bicycleinfo'],
    '#description' => t('Google bicycling layer, limited availability.'),
    '#return_value' => 1,
  );
  $form['getlocations_default']['panoramio_show'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Panoramio'),
    '#default_value' =>  $getlocations_defaults['panoramio_show'],
    '#description' => t('Google panoramio picture links.'),
    '#return_value' => 1,
  );
  $form['getlocations_default']['poi_show'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Points of Interest'),
    '#default_value' =>  $getlocations_defaults['poi_show'],
    '#description' => t('Show Google points of interest icons.'),
    '#return_value' => 1,
  );
  $form['getlocations_default']['transit_show'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Transit Points'),
    '#default_value' =>  $getlocations_defaults['transit_show'],
    '#description' => t('Show Google transit points icons.'),
    '#return_value' => 1,
  );

  // default marker
  $options = getlocations_get_marker_titles();
  $form['getlocations_default']['map_marker'] = array(
    '#type' => 'select',
    '#title' => t('Map marker'),
    '#options' => $options,
    '#default_value' => $getlocations_defaults['map_marker'],
  );

  $form['getlocations_default']['minzoom'] = array(
    '#type' => 'select',
    '#title' => t('Minimum Zoom'),
    '#default_value' => $getlocations_defaults['minzoom'],
    '#options' => drupal_map_assoc(range(0, 17)),
    '#description' => t('The Minimum zoom level at which markers will be visible.'),
  );
  $form['getlocations_default']['maxzoom'] = array(
    '#type' => 'select',
    '#title' => t('Maximum Zoom'),
    '#default_value' => $getlocations_defaults['maxzoom'],
    '#options' => drupal_map_assoc(range(0, 17)),
    '#description' => t('The Maximum zoom level at which markers will be visible.'),
  );
  $form['getlocations_default']['nodezoom'] = array(
    '#type' => 'select',
    '#title' => t('Default Zoom for Single location'),
    '#default_value' => $getlocations_defaults['nodezoom'],
    '#options' => drupal_map_assoc(range(0, 17)),
    '#description' => t('The Default zoom level for a single marker.'),
  );
  $form['getlocations_default']['useinfobubble'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Infobubble'),
    '#default_value' =>  $getlocations_defaults['useinfobubble'],
    '#description' => t('Use Infobubble library instead of default Google Infowindow.'),
    '#return_value' => 1,
  );
  $form['getlocations_default']['usemarkermanager'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Marker manager'),
    '#default_value' =>  $getlocations_defaults['usemarkermanager'],
    '#description' => t('Use Marker manager. Switching this off will use no manager'),
    '#return_value' => 1,
  );

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
  if (!$form_state['values']['getlocations_default']['baselayers'][$form_state['values']['getlocations_default']['maptype']]) {
    form_error($form['getlocations_default']['baselayers']['maptype'], t('The default map type must be an enabled baselayer!'));
  }
}

/**
 * Rebuild marker js.
 */
function _getlocations_rebuild_marker_js_submit($form, &$form_state) {
  getlocations_regenerate_markers();
  drupal_set_message(t('Marker cache regenerated.'));
}

