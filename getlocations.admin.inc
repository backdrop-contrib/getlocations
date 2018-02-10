<?php

/**
 * @file
 * getlocations.admin.inc
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
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
  backdrop_add_js(getlocations_paths_get('getlocations_admin_path'));

  $form = array();

  $pagetitle = '<div><h4>' . t('Getlocations base settings') . '</h4><p>' . t('The settings selected here will be used as the starting point for all other Google maps.') . '</p></div>';
  $form['pagetitle'] = array('#markup' => $pagetitle);

  $form['rebuild'] = array(
    '#type' => 'fieldset',
    '#title' => t('Regenerate Getlocations marker cache'),
    '#description' => t('If you are having problems with markers, or have changed anything in the markers library, click on the Regenerate button.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $c = count(getlocations_get_marker_titles());
  if (! $c) {
    if (getlocations_regenerate_markers()) {
      $c = count(getlocations_get_marker_titles());
    }
  }

  if ($c) {
    $rebuildmsg = '<p>' . format_plural($c, 'You have 1 marker installed.', 'You have @count markers installed.') . '</p>';
  }
  else {
    $rebuildmsg = '<p class="error">' . t('WARNING! NO markers found.') . '</p>';
  }
  $form['rebuild']['msg'] = array('#markup' => $rebuildmsg);

  if (file_default_scheme() != 'public') {
    $form['rebuild']['getlocations_private_markerfile'] = getlocations_element_map_tf(
      t('Path to getlocations_markers.js'),
      $getlocations_defaults['private_markerfile'],
      t('You are using the <em>Private</em> download method. For markers to work properly. you must press the <em>Regenerate</em> button, manually copy js/getlocations_markers.js from the files directory to a location accessible by the webserver, and enter the file path relative to the Backdrop root (including the filename) in this field. Example: <em>sites/default/misc/getlocations_markers.js</em>'),
      60,
      255,
      FALSE
    );
  }
  if (! getlocations_get_markerfile()) {
    $form['rebuild']['msg'] = array(
      '#markup' => '<p class="messages error">' . t('You need to regenerate the markers, file not found.') . '</p>'
    );
  }
  $form['rebuild']['rebuild_marker_js'] = array(
    '#type' => 'submit',
    '#value' => t('Regenerate'),
    '#submit' => array('_getlocations_rebuild_marker_js_submit'),
  );
  $form['rebuild']['getlocations_flush'] = getlocations_element_map_checkbox(
    t('Flush marker cache'),
    $getlocations_defaults['flush_marker_cache'],
    t('Include the marker cache when the Backdrop cache is flushed.')
  );

  // google api3 key
  $api3_group = $getlocations_defaults['api3_group'];
  $form['api3_group'] = array(
    '#type' => 'fieldset',
    '#title' => t('Google API key'),
    '#description' => t('This key may be required by Google for full functionality.'),
    '#collapsible' => TRUE,
    #'#collapsed' => ($apikey ? TRUE : FALSE),
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  );
  $form['api3_group']['api3_key'] = getlocations_element_map_tf(
    t('Your Google maps API Version 3 key'),
    $api3_group['api3_key'],
    t('For more information about this key see this !u', array('!u' => l(t('page on google'), 'http://code.google.com/apis/maps/documentation/javascript/tutorial.html#api_key', array('attributes' => array('target' => '_blank'))))),
    95,
    255,
    FALSE
  );
  $form['api3_group']['api3_clientID'] = getlocations_element_map_tf(
    t('Your Google maps API Version 3 clientID'),
    $api3_group['api3_clientID'],
    t('For more information about this see this !u', array('!u' => l(t('page on google'), 'https://developers.google.com/maps/documentation/javascript/get-api-key#client-id', array('attributes' => array('target' => '_blank'))))),
    95,
    255,
    FALSE
  );
  $form['api3_group']['api3_signature'] = getlocations_element_map_tf(
    t('Your Google maps API Version 3 signature'),
    $api3_group['api3_signature'],
    t('For more information about this see this !u', array('!u' => l(t('page on google'), 'https://developers.google.com/maps/documentation/javascript/get-api-key#client_id_and_signature', array('attributes' => array('target' => '_blank'))))),
    95,
    255,
    FALSE
  );
  $form['api3_group']['api3_channel'] = getlocations_element_map_tf(
    t('Your Google maps API Version 3 channel'),
    $api3_group['api3_channel'],
    t('For more information about this see this !u', array('!u' => l(t('page on google'), 'https://developers.google.com/maps/documentation/javascript/get-api-key#channel-reports', array('attributes' => array('target' => '_blank'))))),
    95,
    255,
    FALSE
  );
  $form['api3_group']['api3_signed_in'] = getlocations_element_map_checkbox(
    t('Signed in'),
    $api3_group['api3_signed_in'],
    t('Provide the Sign in link on the map.')
  );

  // mapquest
  $mapquest_lic =  $getlocations_defaults['mapquest_lic'];
  $form['mapquest_lic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mapquest key'),
    '#description' => t('This key is required if you want to use Mapquest maps and services.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  );
  $form['mapquest_lic']['key'] =  getlocations_element_map_tf(
    t('Mapquest key'),
    $mapquest_lic['key'],
    '',
    40
  );
  $form['mapquest_lic']['type'] = getlocations_element_dd(
    t('Mapquest type'),
    $mapquest_lic['type'],
    array('o' => t('Open'), 'l' => t('Licensed'))
  );

  // Thunderforest and Opencyclemaps
  $thunderforest_lic = $getlocations_defaults['thunderforest_lic'];
  $form['thunderforest_lic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Thunderforest maps API key'),
    '#description' => t('This key is required if you want to use !u maps.', array('!u' => l(t('thunderforest and opencyclemaps'), 'http://thunderforest.com/docs/apikeys/', array('attributes' => array('target' => '_blank'))))),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  );
  $form['thunderforest_lic']['key'] = getlocations_element_map_tf(
    t('Thunderforest key'),
    $thunderforest_lic['key'],
    t('After entering the key you should save the form, this will present further settings.'),
    40
  );

  // openweathermap
  $openweathermap_lic = $getlocations_defaults['openweathermap_lic'];
  $form['openweathermap_lic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Openweathermap API key'),
    '#description' => t('This key is required if you want to use !u maps.', array('!u' => l(t('openweathermaps'), 'http://openweathermap.org/', array('attributes' => array('target' => '_blank'))))),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  );
  $form['openweathermap_lic']['key'] = getlocations_element_map_tf(
    t('Openweathermap key'),
    $openweathermap_lic['key'],
    t('After entering the key you should save the form, this will present further settings.'),
    40
  );

  // $what3words
  $what3words_lic = getlocations_w3w_get_lic();
  $form['what3words_lic'] = array(
    '#type' => 'fieldset',
    '#title' => t('what3words API key'),
    '#description' => t('This key is required if you want to use !u services.', array('!u' => l(t('what3words'), 'https://developer.what3words.com/', array('attributes' => array('target' => '_blank'))))),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  );
  $form['what3words_lic']['key'] = getlocations_element_map_tf(
    t('what3words key'),
    $what3words_lic['key'],
    t('After entering the key you should save the form, this will present further settings.'),
    40
  );
  $form['what3words_lic']['url'] = getlocations_element_map_tf(
    t('what3words URL'),
    (! empty($what3words_lic['url']) ? $what3words_lic['url'] : GETLOCATIONS_W3W_URL),
    '',
    40
  );

  // map version
  $map_version = $getlocations_defaults['map_version'];
  $form['map_version'] =  array(
    '#type' => 'fieldset',
    '#title' => t('Google Map version'),
    '#description' => t('The map version is normally provided automatically, only use this if you wish to override it.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['map_version']['map_version'] = getlocations_element_map_tf(
    t('Google maps version number'),
    $map_version,
    '',
    5,
    10,
    FALSE
  );

  // preview
  $form['getlocations_preview'] = array(
    '#type' => 'fieldset',
    '#title' => t('Getlocations Preview'),
    '#description' => t('A preview of the current map settings.') . '<br />' . t('You can adjust the default Map center, Zoom and Default map type by changing the map.') . '<br />' . t('For all other changes use the form. Remember to Save configuration when you are done.'),
    // This will store all the defaults in one variable.
    '#tree' => FALSE,
  );


#  $shapes = getlocations_shapes_settings();
#  $getlocations_defaults += $shapes;

#  $sv_group = config_get('getlocations.sv', 'settings');
#  $getlocations_defaults += $sv_group;

#  $form['getlocations_preview']['preview_map'] = array('#markup' => '');
  // add the preview map here
  $preview_map = '';
  $extcontrol = 'preview_map';
  $mapid = getlocations_setup_map($getlocations_defaults, FALSE, FALSE, FALSE, $extcontrol);
  $minmaxes = '';
  $latlons = array();
  getlocations_js_settings_do($getlocations_defaults, $latlons, $minmaxes, $mapid, FALSE, $extcontrol);
  $preview_map = theme('getlocations_show', array('width' => $getlocations_defaults['width'] , 'height' => $getlocations_defaults['height'] , 'defaults' => $getlocations_defaults, 'mapid' => $mapid, 'latlons' => $latlons, 'minmaxes' => $minmaxes, 'type' => '', 'node' => ''));
  $form['getlocations_preview']['preview_map']['#markup'] = '<div id="getlocations_preview_map">' . $preview_map . '</div>';


  $form['getlocations_default'] = array(
    '#type' => 'fieldset',
    '#title' => t('Getlocations Default map settings'),
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
    #'#tree' => FALSE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['getlocations_default'] += getlocations_map_display_basics_form($getlocations_defaults);
  $form['getlocations_default'] += getlocations_map_display_options_form($getlocations_defaults);

  // default node marker
  $markers = getlocations_get_marker_titles();
  $desc = '';
  if (getlocations_check_entity_type('node')) {
    $desc = t('In use');
  }
  $form['getlocations_default']['node_map_marker'] = getlocations_element_map_marker(
    t('Default Content Map marker'),
    $markers,
    $getlocations_defaults['node_map_marker'],
    $desc
  );

  // default user marker
  $desc = '';
  if (getlocations_check_entity_type('user')) {
    $desc = t('In use');
  }
  $form['getlocations_default']['user_map_marker'] = getlocations_element_map_marker(
    t('Default User Map marker'),
    $markers,
    $getlocations_defaults['user_map_marker'],
    $desc
  );
  if (module_exists('taxonomy')) {
    // default vocabulary marker
    $desc = '';
    if (getlocations_get_vocabularies()) {
      $desc = t('In use');
    }
    $form['getlocations_default']['vocabulary_map_marker'] = getlocations_element_map_marker(
      t('Default Vocabulary Map marker'),
      $markers,
      $getlocations_defaults['vocabulary_map_marker'],
      $desc
    );
    $form['getlocations_default']['term_map_marker'] = getlocations_element_map_marker(
      t('Default Term Map marker'),
      $markers,
      $getlocations_defaults['term_map_marker'],
      ''
    );
  }
  if (module_exists('comment')) {
    // default comment marker
    $desc = '';
    if (getlocations_check_entity_type('comment')) {
      $desc = t('In use');
    }
    $form['getlocations_default']['comment_map_marker'] = getlocations_element_map_marker(
      t('Default Comment Map marker'),
      $markers,
      $getlocations_defaults['comment_map_marker'],
      $desc
    );
  }

  if (module_exists('getlocations_fields')) {
    // default input marker
    $form['getlocations_default']['input_map_marker'] = getlocations_element_map_marker(
      t('Default Input Map marker'),
      $markers,
      $getlocations_defaults['input_map_marker'],
      t('The draggable marker used on add/edit maps.')
    );
  }

  $form['getlocations_default'] += getlocations_markeraction_form($getlocations_defaults);

  if (module_exists('getdirections')) {
    $form['getlocations_default']['getdirections_link'] = getlocations_element_map_checkbox(
      t('Link to Getdirections in bubble'),
      $getlocations_defaults['getdirections_link'],
      t('Include a link to the Getdirections page in InfoBubble/InfoWindow.')
    );
  }

  // views_search options
  if (module_exists('getlocations_fields') && module_exists('views')) {
    $form['getlocations_default'] += getlocations_fields_views_search_form($getlocations_defaults);
  }
  else {
    $form['getlocations_default']['show_search_distance'] = array('#type' => 'value', '#value' => 0);
    $form['getlocations_default']['views_search_group']['views_search_marker_enable'] = array('#type' => 'value', '#value' => 0);
    $form['getlocations_default']['views_search_group']['views_search_radshape_enable'] = array('#type' => 'value', '#value' => 0);
    $form['getlocations_default']['views_search_group']['views_search_center'] = array('#type' => 'value', '#value' => 0);
    $form['getlocations_default']['views_search_group']['views_search_marker'] = array('#type' => 'value', '#value' => $getlocations_defaults['views_search_group']['views_search_marker']);
    $form['getlocations_default']['views_search_group']['views_search_marker_toggle'] = array('#type' => 'value', '#value' => $getlocations_defaults['views_search_group']['views_search_marker_toggle']);
    $form['getlocations_default']['views_search_group']['views_search_marker_toggle_active'] = array('#type' => 'value', '#value' => $getlocations_defaults['views_search_group']['views_search_marker_toggle_active']);
    $form['getlocations_default']['views_search_group']['views_search_radshape_strokecolor'] = array('#type' => 'value', '#value' => $getlocations_defaults['views_search_group']['views_search_radshape_strokecolor']);
    $form['getlocations_default']['views_search_group']['views_search_radshape_strokeopacity'] = array('#type' => 'value', '#value' => $getlocations_defaults['views_search_group']['views_search_radshape_strokeopacity']);
    $form['getlocations_default']['views_search_group']['views_search_radshape_strokeweight'] = array('#type' => 'value', '#value' => $getlocations_defaults['views_search_group']['views_search_radshape_strokeweight']);
    $form['getlocations_default']['views_search_group']['views_search_radshape_fillcolor'] = array('#type' => 'value', '#value' => $getlocations_defaults['views_search_group']['views_search_radshape_fillcolor']);
    $form['getlocations_default']['views_search_group']['views_search_radshape_fillopacity'] = array('#type' => 'value', '#value' => $getlocations_defaults['views_search_group']['views_search_radshape_fillopacity']);
    $form['getlocations_default']['views_search_group']['views_search_radshape_toggle'] = array('#type' => 'value', '#value' => $getlocations_defaults['views_search_group']['views_search_radshape_toggle']);
    $form['getlocations_default']['views_search_group']['views_search_radshape_toggle_active'] = array('#type' => 'value', '#value' => $getlocations_defaults['views_search_group']['views_search_radshape_toggle_active']);
  }

  $form['getlocations_default']['preload_data'] = getlocations_element_map_checkbox(
    t('Preload marker data'),
    $getlocations_defaults['preload_data'],
    t('This will load all the data for InfoBubble/InfoWindow or link beforehand. This may result in slower initial page loads but faster marker click response.')
  );

  $form['getlocations_default']['nodezoom'] = getlocations_element_map_zoom(
    t('Default Zoom for Single location'),
    $getlocations_defaults['nodezoom'],
    t('The Default zoom level for a single marker.')
  );

  // marker managers
  $form['getlocations_default']['markermanagertype'] = getlocations_element_markermanagertype($getlocations_defaults['markermanagertype']);

  // markermanager
  $form['getlocations_default'] += getlocations_markermanager_form($getlocations_defaults);

  // markerclusterer
  $form['getlocations_default'] += getlocations_markercluster_form($getlocations_defaults);

  $form['getlocations_default']['pansetting'] = getlocations_element_map_pansetting($getlocations_defaults['pansetting']);

  $returnlink_group = $getlocations_defaults['returnlink_group'];
  $form['getlocations_default']['returnlink_page_enable'] = getlocations_element_map_checkbox(
    t('Show link back to page'),
    $returnlink_group['returnlink_page_enable']
  );

  $form['getlocations_default']['returnlink_page_link'] = getlocations_element_map_tf(
    t('Text of page return link'),
    $returnlink_group['returnlink_page_link'],
    t('Use %t to insert the page title'),
    30,
    64
  );
  $form['getlocations_default']['returnlink_page_link']['#prefix'] = '<div id="wrap-page-link">';
  $form['getlocations_default']['returnlink_page_link']['#suffix'] = '</div>';

  if (module_exists('getlocations_fields')) {
    if (getlocations_check_entity_type('user')) {
      $form['getlocations_default']['returnlink_user_enable'] = getlocations_element_map_checkbox(
        t('Show link back to user'),
        $returnlink_group['returnlink_user_enable']
      );
      $form['getlocations_default']['returnlink_user_link'] = getlocations_element_map_tf(
        t('Text of user return link'),
        $returnlink_group['returnlink_user_link'],
        t('Use %n to insert the user name'),
        30,
        64
      );
      $form['getlocations_default']['returnlink_user_link']['#prefix'] = '<div id="wrap-user-link">';
      $form['getlocations_default']['returnlink_user_link']['#suffix'] = '</div>';
    }

    if (module_exists('taxonomy')) {
      if (getlocations_get_vocabularies()) {
        $form['getlocations_default']['returnlink_term_enable'] = getlocations_element_map_checkbox(
          t('Show link back to term'),
          $returnlink_group['returnlink_term_enable']
        );
      }
      $form['getlocations_default']['returnlink_term_link'] = getlocations_element_map_tf(
        t('Text of term return link'),
        $returnlink_group['returnlink_term_link'],
        t('Use %n to insert the term name'),
        30,
        64
      );
      $form['getlocations_default']['returnlink_term_link']['#prefix'] = '<div id="wrap-term-link">';
      $form['getlocations_default']['returnlink_term_link']['#suffix'] = '</div>';
    }

    if (getlocations_check_entity_type('comment')) {
      $form['getlocations_default']['returnlink_comment_enable'] = getlocations_element_map_checkbox(
        t('Show link back to comment'),
        $returnlink_group['returnlink_comment_enable']
      );
      $form['getlocations_default']['returnlink_comment_link'] = getlocations_element_map_tf(
        t('Text of comment return link'),
        $returnlink_group['returnlink_comment_link'],
        t('Use %n to insert the comment subject'),
        30,
        64
      );
      $form['getlocations_default']['returnlink_comment_link']['#prefix'] = '<div id="wrap-comment-link">';
      $form['getlocations_default']['returnlink_comment_link']['#suffix'] = '</div>';
    }
  }

  $form['getlocations_default']['getlocations_js_weight'] = getlocations_element_map_tf(
    t('Getlocations Javascript weight'),
    $getlocations_defaults['getlocations_js_weight'],
    t('Set the weight of the getlocations javascript loading, only change this if you are having problems. For advanced users only.'),
    5,
    99,
    TRUE
  );

  // TODO
/*
  // node type markers
  if ($types = getlocations_get_types()) {
    $form['getlocations_node_marker'] = array(
      '#type' => 'fieldset',
      '#title' => t('Content type markers'),
      // This will store all the defaults in one variable.
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $getlocations_node_marker = config_get('getlocations_node_marker', array('enable' => 0));
    $form['getlocations_node_marker']['enable'] = getlocations_element_map_checkbox(
      t('Enable Markers for Content types'),
      $getlocations_node_marker['enable']
    );
    $typect = 0;
    foreach ($types AS $type => $name) {
      $field_names = getlocations_get_fieldname2($type, 'node');
      foreach ($field_names AS $field_name) {
        $form['getlocations_node_marker']['content_type'][$type]['field_name'][$field_name]['map_marker'] = getlocations_element_map_marker(
          t('%name Map marker, field %field', array('%name' => $name, '%field' => $field_name)),
          $markers,
          (isset($getlocations_node_marker['content_type'][$type]['field_name'][$field_name]['map_marker']) ? $getlocations_node_marker['content_type'][$type]['field_name'][$field_name]['map_marker'] : $getlocations_defaults['node_map_marker'])
        );
        // for jquery
        if (! $typect) {
          $form['getlocations_node_marker']['content_type'][$type]['field_name'][$field_name]['map_marker']['#prefix'] = '<div id="wrap-getlocations-node-markers">';
        }
        $typect++;
      }
    }
    $form['getlocations_node_marker']['content_type'][$type]['field_name'][$field_name]['map_marker']['#suffix'] = '</div>';
  }

  if (module_exists('taxonomy')) {
    // vocabulary markers
    if ($types = getlocations_get_vocabularies()) {
      $module = getlocations_get_current_supported_module();
      $form['getlocations_vocabulary_marker'] = array(
        '#type' => 'fieldset',
        '#title' => t('Taxonomy Vocabulary markers'),
        // This will store all the defaults in one variable.
        '#tree' => TRUE,
        '#description' => t('Vocabularies with a %module field.', array('%module' => $module)),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );
      $getlocations_vocabulary_marker = config_get('getlocations_vocabulary_marker', array('enable' => 0));
      $form['getlocations_vocabulary_marker']['enable'] = getlocations_element_map_checkbox(
        t('Enable Markers for Vocabularies'),
        $getlocations_vocabulary_marker['enable']
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

    // term markers
    $form['getlocations_term_marker'] = array(
      '#type' => 'fieldset',
      '#title' => t('Term markers'),
      // This will store all the defaults in one variable.
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $getlocations_term_marker = config_get('getlocations_term_marker', array('enable' => 0, 'vids' => 0, 'max_depth' => ''));
    $form['getlocations_term_marker']['enable'] = getlocations_element_map_checkbox(
      t('Enable Markers for Terms'),
      $getlocations_term_marker['enable'],
      t('Select Vocabularies enabled in a %termref field', array('%termref' => 'Term reference'))
    );
    $options = array(0 => '- Select -');
    foreach (taxonomy_vocabulary_get_names() as $vocab) {
      $options[$vocab->vid] = $vocab->name;
    }
    $vids = array();
    if (is_array($getlocations_term_marker['vids'])) {
      $vids = array_keys($getlocations_term_marker['vids']);
    }

    $form['getlocations_term_marker']['vids'] = getlocations_element_dd(
      t('Vocabulary to specify markers for'),
      $vids,
      $options,
      t('Select one or more vocabularies, then Save Configuration to set up the markers.'),
      TRUE
    );
    $form['getlocations_term_marker']['vids']['#prefix'] = '<div id="wrap-getlocations-term-markers">';

    if ($getlocations_term_marker['enable'] && $getlocations_term_marker['vids']) {
      $depth = is_numeric($getlocations_term_marker['max_depth']) && $getlocations_term_marker['max_depth'] > 0 ? $getlocations_term_marker['max_depth'] : NULL;
      $vids = $getlocations_term_marker['vids'];
      foreach ($vids AS $vid) {
        $terms = taxonomy_get_tree($vid, 0, $depth);
        foreach ($terms AS $term) {
          $tid = $term->tid;
          $name = $term->name;
          $form['getlocations_term_marker']['vid'][$vid]['term'][$tid]['map_marker'] = getlocations_element_map_marker(
            t('%name Map marker', array('%name' => $name)),
            $markers,
            (isset($getlocations_term_marker['vid'][$vid]['term'][$tid]['map_marker']) ? $getlocations_term_marker['vid'][$vid]['term'][$tid]['map_marker'] : $getlocations_defaults['term_map_marker'])
          );
        }
      }
    }
    $form['getlocations_term_marker']['max_depth'] = getlocations_element_map_tf(
      t('Maximum depth'),
      $getlocations_term_marker['max_depth'],
      t('The maximum depth for hierarchical vocabulary to specify markers for. Leave blank for all levels.'),
      5
    );
    $form['getlocations_term_marker']['max_depth']['#suffix'] = '</div>';
  }
*/

/*
  // colorbox
  if (module_exists('colorbox')) {
    $getlocations_colorbox = getlocations_colorbox_settings();
    $form['getlocations_colorbox'] = array(
      '#type' => 'fieldset',
      '#title' => t('Colorbox settings'),
      // This will store all the defaults in one variable.
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['getlocations_colorbox']['enable'] = getlocations_element_map_checkbox(
      t('Enable Colorbox'),
      $getlocations_colorbox['enable'],
      t('Show Getlocations in a Colorbox.')
    );
    $form['getlocations_colorbox']['width'] = getlocations_element_map_tf(
      t('Colorbox width'),
      $getlocations_colorbox['width'],
      '',
      5,
      10,
      TRUE
    );
    // need this to get validation to work
    $form['getlocations_colorbox']['width']['#parents'] = array('getlocations_colorbox', 'width');
    $form['getlocations_colorbox']['height'] = getlocations_element_map_tf(
      t('Colorbox height'),
      $getlocations_colorbox['height'],
      '',
      5,
      10,
      TRUE
    );
    // need this to get validation to work
    $form['getlocations_colorbox']['height']['#parents'] = array('getlocations_colorbox', 'height');
    $form['getlocations_colorbox']['marker_enable'] = getlocations_element_map_checkbox(
      t('Enable Marker picker'),
      $getlocations_colorbox['marker_enable'],
      t('Show Markers in a Colorbox.')
    );
    $form['getlocations_colorbox']['marker_width'] = getlocations_element_map_tf(
      t('Marker Colorbox width'),
      $getlocations_colorbox['marker_width'],
      '',
      5,
      10,
      TRUE
    );
    // need this to get validation to work
    $form['getlocations_colorbox']['marker_width']['#parents'] = array('getlocations_colorbox', 'marker_width');
    $form['getlocations_colorbox']['marker_height'] = getlocations_element_map_tf(
      t('Marker Colorbox height'),
      $getlocations_colorbox['marker_height'],
      '',
      5,
      10,
      TRUE
    );
    // need this to get validation to work
    $form['getlocations_colorbox']['marker_height']['#parents'] = array('getlocations_colorbox', 'marker_height');
  }
*/

  $form['getlocations_ua'] = array(
    '#type' => 'fieldset',
    '#title' => t('User Agent detection'),
    '#description' => t('For advanced users who want to edit the User Agent detection string.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );

  $ua_string = getlocations_ua_get();
  $form['getlocations_ua']['ua_string'] = getlocations_element_map_tf(
    t('User Agent detection'),
    $ua_string,
    t('User Agent detection is used to determine wether the browser is on a mobile device. Edit this regular expression with care.'),
    60,
    255,
    TRUE
  );

  $aggr = getlocations_aggr_get();
  $form['getlocations_agg'] = array(
    '#type' => 'fieldset',
    '#title' => t('Javascript Aggregation'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    // This will store all the defaults in one variable.
    '#tree' => FALSE,
  );
  $form['getlocations_agg']['getlocations_aggr'] = getlocations_element_map_checkbox(
    t('Allow Getlocations Javascript to be aggregated'),
    $aggr
  );

  $form['getlocations_paths'] = array(
    '#type' => 'fieldset',
    '#title' => t('Javascript paths'),
    '#description' => t('For advanced users who want to supply their own javascript.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );

  $form['getlocations_paths']['infobubble_path'] = getlocations_element_path(
    t('Path to InfoBubble javascript file'),
    getlocations_paths_get('infobubble_path'),
    60,
    128,
    t('Where the InfoBubble javascript file is located.')
  );
  $form['getlocations_paths']['infobubble_extended_path'] = getlocations_element_path(
    t('Path to InfoBubble extended javascript file'),
    getlocations_paths_get('infobubble_extended_path'),
    60,
    128,
    t('Where the InfoBubble extended javascript file is located.')
  );

  $form['getlocations_paths']['infowindow_options_path'] = getlocations_element_path(
    t('Path to InfoWindow options javascript file'),
    getlocations_paths_get('infowindow_options_path'),
    60,
    128,
    t('Where the InfoWindow options javascript file is located. If this file does not exist the default settings will be used.')
  );
  $form['getlocations_paths']['infobubble_options_path'] = getlocations_element_path(
    t('Path to InfoBubble options javascript file'),
    getlocations_paths_get('infobubble_options_path'),
    60,
    128,
    t('Where the InfoBubble options javascript file is located. If this file does not exist the default settings will be used.')
  );
  $form['getlocations_paths']['markermanager_path'] = getlocations_element_path(
    t('Path to markermanager javascript file'),
    getlocations_paths_get('markermanager_path'),
    60,
    128,
    t('Where the markermanager javascript file is located.')
  );

  $form['getlocations_paths']['markerclusterer_path'] = getlocations_element_path(
    t('Path to markerclusterer javascript file'),
    getlocations_paths_get('markerclusterer_path'),
    60,
    128,
    t('Where the markerclusterer javascript file is located.')
  );
  $form['getlocations_paths']['getlocations_polygons_path'] = getlocations_element_path(
    t('Path to getlocations Polygons javascript file'),
    getlocations_paths_get('getlocations_polygons_path'),
    60,
    128,
    t('Where the getlocations polygons javascript file is located.')
  );
  $form['getlocations_paths']['getlocations_rectangles_path'] = getlocations_element_path(
    t('Path to getlocations Rectangles javascript file'),
    getlocations_paths_get('getlocations_rectangles_path'),
    60,
    128,
    t('Where the getlocations rectangles javascript file is located.')
  );
  $form['getlocations_paths']['getlocations_circles_path'] = getlocations_element_path(
    t('Path to getlocations Circles javascript file'),
    getlocations_paths_get('getlocations_circles_path'),
    60,
    128,
    t('Where the getlocations circles javascript file is located.')
  );
  $form['getlocations_paths']['getlocations_polylines_path'] = getlocations_element_path(
    t('Path to getlocations Polylines javascript file'),
    getlocations_paths_get('getlocations_polylines_path'),
    60,
    128,
    t('Where the getlocations polylines javascript file is located.')
  );

  // categories
  $form['getlocations_paths']['getlocations_categories_path'] = getlocations_element_path(
    t('Path to getlocations Categories javascript file'),
    getlocations_paths_get('getlocations_categories_path'),
    60,
    128,
    t('Where the getlocations categories javascript file is located.')
  );
  // search_places
  $form['getlocations_paths']['getlocations_search_places_path'] = getlocations_element_path(
    t('Path to getlocations Search Places javascript file'),
    getlocations_paths_get('getlocations_search_places_path'),
    60,
    128,
    t('Where the getlocations search places javascript file is located.')
  );
  // geo
  $form['getlocations_paths']['getlocations_geo_path'] = getlocations_element_path(
    t('Path to getlocations Geo javascript file'),
    getlocations_paths_get('getlocations_geo_path'),
    60,
    128,
    t('Where the getlocations geo javascript file is located.')
  );
  // preview
  $form['getlocations_paths']['getlocations_preview_path'] = getlocations_element_path(
    t('Path to getlocations Preview javascript file'),
    getlocations_paths_get('getlocations_preview_path'),
    60,
    128,
    t('Where the getlocations preview javascript file is located.')
  );
  // geojson
  $form['getlocations_paths']['getlocations_geojson_path'] = getlocations_element_path(
    t('Path to getlocations Geojson javascript file'),
    getlocations_paths_get('getlocations_geojson_path'),
    60,
    128,
    t('Where the getlocations geojson javascript file is located.')
  );
  // admin
  $form['getlocations_paths']['getlocations_admin_path'] = getlocations_element_path(
    t('Path to getlocations Admin javascript file'),
    getlocations_paths_get('getlocations_admin_path'),
    60,
    128,
    t('Where the getlocations admin javascript file is located.')
  );
  // box
  $form['getlocations_paths']['getlocations_box_path'] = getlocations_element_path(
    t('Path to getlocations Box javascript file'),
    getlocations_paths_get('getlocations_box_path'),
    60,
    128,
    t('Where the getlocations box javascript file is located.')
  );
  // colorbox
  $form['getlocations_paths']['getlocations_colorbox_path'] = getlocations_element_path(
    t('Path to getlocations Colorbox javascript file'),
    getlocations_paths_get('getlocations_colorbox_path'),
    60,
    128,
    t('Where the getlocations colorbox javascript file is located.')
  );
  // marker_box
  $form['getlocations_paths']['getlocations_marker_box_path'] = getlocations_element_path(
    t('Path to getlocations Markerbox javascript file'),
    getlocations_paths_get('getlocations_marker_box_path'),
    60,
    128,
    t('Where the getlocations markerbox javascript file is located.')
  );
  // views
  $form['getlocations_paths']['getlocations_views_path'] = getlocations_element_path(
    t('Path to getlocations Views javascript file'),
    getlocations_paths_get('getlocations_views_path'),
    60,
    128,
    t('Where the getlocations views javascript file is located.')
  );
  // icons
  $form['getlocations_paths']['getlocations_icons_path'] = getlocations_element_path(
    t('Path to getlocations Icons javascript file'),
    getlocations_paths_get('getlocations_icons_path'),
    60,
    128,
    t('Where the getlocations icons javascript file is located.')
  );
  // what3words
  $form['getlocations_paths']['getlocations_what3words_path'] = getlocations_element_path(
    t('Path to getlocations what3words javascript file'),
    getlocations_paths_get('getlocations_what3words_path'),
    60,
    128,
    t('Where the getlocations what3words javascript file is located.')
  );

  // graticule
  $form['getlocations_paths']['getlocations_graticule_path'] = getlocations_element_path(
    t('Path to getlocations graticule javascript file'),
    getlocations_paths_get('getlocations_graticule_path'),
    60,
    128,
    t('Where the getlocations graticule javascript file is located.')
  );

  $form['getlocations_paths']['getlocations_path'] = getlocations_element_path(
    t('Path to getlocations javascript file'),
    getlocations_paths_get('getlocations_path'),
    60,
    128,
    t('Where the getlocations javascript file is located.')
  );

  // Add a submit button
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  unset($form['#theme']);
  $form['#theme'] = 'getlocations_settings_form';

  return $form;
}

function getlocations_settings_form_validate($form, &$form_state) {

  if ($latlon = getlocations_latlon_check($form_state['values']['getlocations_default']['latlong'])) {
    $form_state['values']['getlocations_default']['latlong'] = $latlon;
  }
  else {
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

  if ( ! is_numeric($form_state['values']['getlocations_default']['getlocations_js_weight'])) {
    form_set_error('getlocations_default][getlocations_js_weight', t('Getlocations js weight must be a number'));
  }

/*
  if (module_exists('colorbox') && isset($form_state['values']['getlocations_colorbox']['enable']) && $form_state['values']['getlocations_colorbox']['enable']) {
    if (empty($form_state['values']['getlocations_colorbox']['width']) || ! is_numeric($form_state['values']['getlocations_colorbox']['width']) || $form_state['values']['getlocations_colorbox']['width'] < 1 ) {
      form_set_error('getlocations_colorbox][width', t('Colorbox width must be a number'));
    }
    if (empty($form_state['values']['getlocations_colorbox']['height']) || ! is_numeric($form_state['values']['getlocations_colorbox']['height']) || $form_state['values']['getlocations_colorbox']['height'] < 1 ) {
      form_set_error('getlocations_colorbox][height', t('Colorbox height must be a number'));
    }
  }

  if (module_exists('colorbox') && isset($form_state['values']['getlocations_colorbox']['marker_enable']) && $form_state['values']['getlocations_colorbox']['marker_enable']) {
    if (empty($form_state['values']['getlocations_colorbox']['marker_width']) || ! is_numeric($form_state['values']['getlocations_colorbox']['marker_width']) || $form_state['values']['getlocations_colorbox']['marker_width'] < 1 ) {
      form_set_error('getlocations_colorbox][marker_width', t('Colorbox width must be a number'));
    }
    if (empty($form_state['values']['getlocations_colorbox']['marker_height']) || ! is_numeric($form_state['values']['getlocations_colorbox']['marker_height']) || $form_state['values']['getlocations_colorbox']['marker_height'] < 1 ) {
      form_set_error('getlocations_colorbox][marker_height', t('Colorbox height must be a number'));
    }
  }

  $list = array('Map', 'Satellite', 'Hybrid', 'Physical', 'OpenStreetMap');
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
    $form_state['values']['getlocations_node_marker']['enable'] = 0;
  }
  if (isset($form_state['values']['getlocations_vocabulary_marker']) && ! $form_state['values']['getlocations_vocabulary_marker']['enable']) {
    unset($form_state['values']['getlocations_vocabulary_marker']);
    $form_state['values']['getlocations_vocabulary_marker']['enable'] = 0;
  }
  if (isset($form_state['values']['getlocations_term_marker']) && ! $form_state['values']['getlocations_term_marker']['enable']) {
    unset($form_state['values']['getlocations_term_marker']);
    $form_state['values']['getlocations_term_marker']['enable'] = 0;
    $form_state['values']['getlocations_term_marker']['vids'] = 0;
    $form_state['values']['getlocations_term_marker']['max_depth'] = '';
  }
*/
  // search_places
  if (isset($form_state['values']['getlocations_default']['search_places']) && $form_state['values']['getlocations_default']['search_places']) {
    $form_state['values']['getlocations_default']['places'] = 1;
  }

  // css check
  if (isset($form_state['values']['getlocations_default']['width'])) {
    if ($check = getlocations_dim_check($form_state['values']['getlocations_default']['width'])) {
      $form_state['values']['getlocations_default']['width'] = $check;
    }
    else {
      form_set_error('getlocations_default][width', t('Width must be valid css'));
    }
  }
  if (isset($form_state['values']['getlocations_default']['height'])) {
    if ($check = getlocations_dim_check($form_state['values']['getlocations_default']['height'])) {
      $form_state['values']['getlocations_default']['height'] = $check;
    }
    else {
      form_set_error('getlocations_default][height', t('Height must be valid css'));
    }
  }

}

function getlocations_settings_form_submit($form, &$form_state) {
#  $config = getlocations_defaults();
  $config = config('getlocations.settings');
  $settings = $config->get('settings');
  $keys = getlocations_get_keys();

  $values = $form_state['values'];
  // extract the paths as they are in a different storage
  $getlocations_paths = $values['getlocations_paths'];
  unset($values['getlocations_paths']);

  $getlocations_paths_config = config('getlocations.paths');
  $getlocations_paths_config->set('paths', $getlocations_paths);
  $getlocations_paths_config->save();

  $getlocations_default = $values['getlocations_default'];
  $values += $getlocations_default;
  unset($values['getlocations_default']);

  // trim up some entries
  $api3_key = $values['api3_group']['api3_key'];
  $values['api3_group']['api3_key'] = trim($api3_key);
  $api3_clientID = $values['api3_group']['api3_clientID'];
  $values['api3_group']['api3_clientID'] = trim($api3_clientID);
  $api3_signature = $values['api3_group']['api3_signature'];
  $values['api3_group']['api3_signature'] = trim($api3_signature);
  $api3_channel = $values['api3_group']['api3_channel'];
  $values['api3_group']['api3_channel'] = trim($api3_channel);


#  $markerclusterer_group = array("markerclusterer_style","markerclusterer_zoom","markerclusterer_size","markerclusterer_minsize","markerclusterer_title","markerclusterer_imgpath");
#  foreach ($markerclusterer_group AS $item) {
#    $values['markerclusterer_group'][$item] = $values[$item];
#    unset($values[$item]);
#  }


  $returnlink_group = array("returnlink_page_enable","returnlink_page_link","returnlink_user_enable","returnlink_user_link","returnlink_term_enable","returnlink_term_link","returnlink_comment_enable","returnlink_comment_link");
  foreach ($returnlink_group AS $item) {
    if (isset($values[$item])) {
      $values['returnlink_group'][$item] = $values[$item];
      unset($values[$item]);
    }
  }

  #$sv_group = array("sv_show","svcontrolposition","sv_showfirst","sv_heading","sv_zoom","sv_pitch","sv_enable","sv_addresscontrol","sv_addresscontrolposition","sv_pancontrol","sv_pancontrolposition","sv_zoomcontrol","sv_zoomcontrolposition","sv_linkscontrol","sv_imagedatecontrol","sv_scrollwheel","sv_clicktogo");
  $sv_group = array("sv_showfirst","sv_heading","sv_zoom","sv_pitch","sv_enable","sv_addresscontrol","sv_addresscontrolposition","sv_pancontrol","sv_pancontrolposition","sv_zoomcontrol","sv_zoomcontrolposition","sv_linkscontrol","sv_imagedatecontrol","sv_scrollwheel","sv_clicktogo");
  foreach ($sv_group AS $item) {
    if (isset($values[$item])) {
      $values['sv_group'][$item] = $values[$item];
      unset($values[$item]);
    }
  }

  // gps
  if (module_exists('getlocations_gps')) {
    $gps_keys = getlocations_gps_get_keys();
    foreach ($gps_keys AS $gk) {
      if (isset($values[$gk])) {
        $config->set('settings.' . $gk, $values[$gk] );
      }
    }
  }

#  $views_search_keys = array("views_search_center","views_search_marker_enable","views_search_marker","views_search_marker","views_search_marker_toggle","views_search_marker_toggle_active","views_search_radshape_enable","views_search_radshape_strokecolor","views_search_radshape_strokeopacity","views_search_radshape_strokeweight","views_search_radshape_fillcolor","views_search_radshape_fillopacity","views_search_radshape_toggle","views_search_radshape_toggle_active");
#  foreach ($views_search_keys AS $k) {
#    if (isset($values[$k])) {
#      $values['views_search_group'][$k] = $values[$k];
#      unset($values[$k]);
#    }
#  }

  foreach ($keys AS $key) {
    if ( isset($values[$key])) {
      $config->set('settings.' . $key, $values[$key]);
    }
  }
  $config->save();

  backdrop_set_message(t('Getlocations configuration options have been saved.'));

}

/**
 * Rebuild marker js.
 */
function _getlocations_rebuild_marker_js_submit($form, &$form_state) {
  if (getlocations_regenerate_markers()) {
    backdrop_set_message(t('Marker cache regenerated.'));
  }
}
