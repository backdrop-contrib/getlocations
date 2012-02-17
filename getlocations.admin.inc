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
    '#description' => t('If you are having problems with markers, or have changed anything in the markers library, click here to rebuild the marker cache file.'),
  );
  if (file_default_scheme() != 'public') {
    $form['rebuild']['getlocations_private_markerfile'] = array(
      '#type' => 'textfield',
      '#title' => t('Path to getlocations_markers.js'),
      '#description' => t('You are using the <em>Private</em> download method. For markers to work properly. you must press the <em>Regenerate</em> button, manually copy js/getlocations_markers.js from the files directory to a location accessible by the webserver, and enter the file path relative to the Drupal root (including the filename) in this field. Example: <em>sites/default/misc/getlocations_markers.js</em>'),
      '#default_value' => variable_get('getlocations_private_markerfile', ''),
    );
  }
  if (! getlocations_get_markerfile()) {
    $form['rebuild']['errmsg'] = array(
      '#value' => '<p class="messages error">' . t('You need to regenerate the markers, file not found.') . '</p>'
    );
  }
  $form['rebuild']['rebuild_marker_js'] = array(
    '#type' => 'submit',
    '#value' => t('Regenerate'),
    '#submit' => array('_getlocations_rebuild_marker_js_submit'),
  );

  // google api3 key
  $apikey = variable_get('getlocations_api3_key', '');
  $form['api3'] = array(
    '#type' => 'fieldset',
    '#title' => t('Google API key'),
    '#description' => t('This key is currently not required by Google.'),
    '#collapsible' => TRUE,
    #'#collapsed' => ($apikey ? TRUE : FALSE),
    '#collapsed' => TRUE,
  );
  $form['api3']['getlocations_api3_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Your Google maps API Version 3 key'),
    '#default_value' => $apikey,
    '#description' => t('For more information about this key see this !u', array('!u' => l('page on google', 'http://code.google.com/apis/maps/documentation/javascript/tutorial.html#api_key', array('attributes' => array('target'=>'_blank'))))),
    '#size' => 95,
    '#required' => FALSE,
  );

  $form['getlocations_default'] = array(
    '#type' => 'fieldset',
    '#title' => t('Getlocations Default map settings'),
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

  $form['getlocations_default'] += getlocations_map_display_options_form($getlocations_defaults);

  // default node marker
  $markers = getlocations_get_marker_titles();
  $form['getlocations_default']['node_map_marker'] = getlocations_element_map_marker(
    t('Default Content Map marker'),
    $markers,
    $getlocations_defaults['node_map_marker']
  );

  if (module_exists('getlocations_fields')) {
    if (getlocations_check_user() || getlocations_check_profile2()) {
      // default user marker
      $form['getlocations_default']['user_map_marker'] = getlocations_element_map_marker(
        t('Default User Map marker'),
        $markers,
        $getlocations_defaults['user_map_marker']
      );
    }
    if (getlocations_get_vocabularies()) {
      // default vocabulary marker
      $form['getlocations_default']['vocabulary_map_marker'] = getlocations_element_map_marker(
        t('Default Vocabulary Map marker'),
        $markers,
        $getlocations_defaults['vocabulary_map_marker']
      );
    }
    if ( getlocations_check_comment()) {
      // default comment marker
      $form['getlocations_default']['comment_map_marker'] = getlocations_element_map_marker(
        t('Default Comment Map marker'),
        $markers,
        $getlocations_defaults['comment_map_marker']
      );
    }
    // default input marker
    $form['getlocations_default']['input_map_marker'] = getlocations_element_map_marker(
      t('Default Input Map marker'),
      $markers,
      $getlocations_defaults['input_map_marker']
    );
  }

  $form['getlocations_default']['markeractiontype'] = getlocations_element_map_markeractiontype(
    $getlocations_defaults['markeractiontype']
  );
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

  // marker manager
  $form['getlocations_default']['markermanagertype'] = getlocations_element_markermanagertype($getlocations_defaults['markermanagertype']);
  $form['getlocations_default']['usemarkermanager'] = getlocations_element_map_checkbox(
    t('Use Marker manager'),
    $getlocations_defaults['usemarkermanager'],
    t('Use Marker manager. Switching this off will use no manager.')
  );
  $form['getlocations_default']['useclustermanager'] = getlocations_element_map_checkbox(
    t('Use Cluster manager'),
    $getlocations_defaults['useclustermanager'],
    t('Use Cluster manager. Switching this off will use no manager.')
  );

  if (file_exists(GETLOCATIONS_PATH . '/getlocations.markerclusterer_override.inc')) {
    module_load_include('inc', 'getlocations', 'getlocations.markercluster_override');
  }
  else {
    module_load_include('inc', 'getlocations', 'getlocations.markercluster');
  }
  $form['getlocations_default']['markerclusterer_style'] = getlocations_element_markerclusterer_style($getlocations_defaults['markerclusterer_style']);
  $form['getlocations_default']['markerclusterer_zoom'] = getlocations_element_markerclusterer_zoom($getlocations_defaults['markerclusterer_zoom']);
  $form['getlocations_default']['markerclusterer_size'] = getlocations_element_markerclusterer_size($getlocations_defaults['markerclusterer_size']);

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

  if (module_exists('getlocations_fields')) {
    if (getlocations_check_user() || getlocations_check_profile2()) {
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

    if (getlocations_get_vocabularies()) {
      $form['getlocations_default']['returnlink_term_enable'] = array(
        '#type' => 'checkbox',
        '#title' => t('Show link back to term'),
        '#default_value' =>  $getlocations_defaults['returnlink_term_enable'],
        '#return_value' => 1,
      );
      $form['getlocations_default']['returnlink_term_link'] = array(
        '#type' => 'textfield',
        '#title' => t('Text of term return link'),
        '#default_value' => $getlocations_defaults['returnlink_term_link'],
        '#size' => 30,
        '#description' => t('Use %n to insert the term name'),
        '#prefix' => '<div id="wrap-term-link">',
        '#suffix' => '</div>',
      );
    }

    if (getlocations_check_comment()) {
      $form['getlocations_default']['returnlink_comment_enable'] = array(
        '#type' => 'checkbox',
        '#title' => t('Show link back to comment'),
        '#default_value' =>  $getlocations_defaults['returnlink_comment_enable'],
        '#return_value' => 1,
      );
      $form['getlocations_default']['returnlink_comment_link'] = array(
        '#type' => 'textfield',
        '#title' => t('Text of comment return link'),
        '#default_value' => $getlocations_defaults['returnlink_comment_link'],
        '#size' => 30,
        '#description' => t('Use %n to insert the comment subject'),
        '#prefix' => '<div id="wrap-comment-link">',
        '#suffix' => '</div>',
      );
    }
  }

  $form['getlocations_default']['use_https'] = array(
    '#type' => 'value',
    '#value' =>  $getlocations_defaults['use_https'],
  );

  // node type markers
  if ($types = getlocations_get_types()) {
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
    $typect = 0;
    foreach ($types AS $type => $name) {
      $form['getlocations_node_marker']['content_type'][$type]['map_marker'] = getlocations_element_map_marker(
        t('%name Map marker', array('%name' => $name)),
        $markers,
        (isset($getlocations_node_marker['content_type'][$type]['map_marker']) ? $getlocations_node_marker['content_type'][$type]['map_marker'] : $getlocations_defaults['node_map_marker'])
      );
      // for jquery
      if (! $typect) {
        $form['getlocations_node_marker']['content_type'][$type]['map_marker']['#prefix'] = '<div id="wrap-getlocations-node-markers">';
      }
      $typect++;
    }
    $form['getlocations_node_marker']['content_type'][$type]['map_marker']['#suffix'] = '</div>';
  }

  // vocabulary markers
  if (module_exists('getlocations_fields') && $types = getlocations_get_vocabularies()) {
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
        (isset($getlocations_vocabulary_marker['vocabulary'][$type]['map_marker']) ? $getlocations_vocabulary_marker['vocabulary'][$type]['map_marker'] : $getlocations_defaults['vocabulary_map_marker'])
      );
      // for jquery
      if (! $typect) {
        $form['getlocations_vocabulary_marker']['vocabulary'][$type]['map_marker']['#prefix'] = '<div id="wrap-getlocations-vocabulary-markers">';
      }
      $typect++;
    }
    $form['getlocations_vocabulary_marker']['vocabulary'][$type]['map_marker']['#suffix'] = '</div>';
  }

  // colorbox
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

  $getlocations_paths = getlocations_paths_get();
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

  $form['getlocations_paths']['markerclusterer_path'] = getlocations_element_path(
    t('Path to markerclusterer javascript file'),
    $getlocations_paths['markerclusterer_path'],
    60,
    128,
    t('Where the markerclusterer javascript file is located.')
  );

  unset($form['#theme']);
  $form['#theme'] = 'getlocations_settings_form';
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

  if (isset($form_state['values']['getlocations_default']['returnlink_page_enable']) && $form_state['values']['getlocations_default']['returnlink_page_enable'] && empty($form_state['values']['getlocations_default']['returnlink_page_link'])) {
    form_set_error('getlocations_default][returnlink_page_link', t('Page return link must be filled in'));
  }
  if (module_exists('getlocations_fields')) {
    if (isset($form_state['values']['getlocations_default']['returnlink_user_enable']) && $form_state['values']['getlocations_default']['returnlink_user_enable'] && empty($form_state['values']['getlocations_default']['returnlink_user_link'])) {
      form_set_error('getlocations_default][returnlink_user_link', t('User return link must be filled in'));
    }
    if (isset($form_state['values']['getlocations_default']['returnlink_term_enable']) && $form_state['values']['getlocations_default']['returnlink_term_enable'] && empty($form_state['values']['getlocations_default']['returnlink_term_link'])) {
      form_set_error('getlocations_default][returnlink_term_link', t('Term return link must be filled in'));
    }
    if (isset($form_state['values']['getlocations_default']['returnlink_comment_enable']) && $form_state['values']['getlocations_default']['returnlink_comment_enable'] && empty($form_state['values']['getlocations_default']['returnlink_comment_link'])) {
      form_set_error('getlocations_default][returnlink_comment_link', t('Comment return link must be filled in'));
    }
  }
  if (! $form_state['values']['getlocations_default']['markermanagertype']) {
    $form_state['values']['getlocations_default']['usemarkermanager'] = 0;
    $form_state['values']['getlocations_default']['useclustermanager'] = 0;
  }
  elseif ($form_state['values']['getlocations_default']['markermanagertype'] == 1) {
    $form_state['values']['getlocations_default']['useclustermanager'] = 0;
  }
  elseif ($form_state['values']['getlocations_default']['markermanagertype'] == 2) {
    $form_state['values']['getlocations_default']['usemarkermanager'] = 0;
  }

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

  // markers
  if (isset($form_state['values']['getlocations_node_marker']) && ! $form_state['values']['getlocations_node_marker']['enable']) {
    unset($form_state['values']['getlocations_node_marker']);
  }
  if (isset($form_state['values']['getlocations_vocabulary_marker']) && ! $form_state['values']['getlocations_vocabulary_marker']['enable']) {
    unset($form_state['values']['getlocations_vocabulary_marker']);
  }
}

/**
 * Rebuild marker js.
 */
function _getlocations_rebuild_marker_js_submit($form, &$form_state) {
  getlocations_regenerate_markers();
  drupal_set_message(t('Marker cache regenerated.'));
}
