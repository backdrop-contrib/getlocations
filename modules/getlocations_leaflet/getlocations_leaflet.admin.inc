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
 * Function
 *
 * @param
 *
 * @return
 *   Returns
 *
 */
function getlocations_leaflet_settings_form() {

  $getlocations_leaflet_defaults = getlocations_leaflet_defaults();
  $getlocations_defaults = getlocations_defaults();

  $form = array();
  $pagetitle = '<div><h4>' . t('Getlocations Leaflet') . '</h4><p>' . t('The settings selected here will be used as the starting point for all other Leaflet maps.') . '</p></div>';
  $form['pagetitle'] = array('#markup' => $pagetitle);

  $form['rebuild'] = array(
    '#type' => 'fieldset',
    '#title' => t('Regenerate Getlocations leaflet marker cache'),
    '#description' => t('If you are having problems with markers, or have changed anything in the markers library, click on the Regenerate button.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );
  $c = count(getlocations_get_marker_titles());
  if ($c) {
    $rebuildmsg = '<p>' . format_plural($c, 'You have 1 marker installed.', 'You have @count markers installed.') . '</p>';
  }
  else {
    $rebuildmsg = '<p class="error">' . t('WARNING! NO markers found.') . '</p>';
  }
  $form['rebuild']['msg'] = array('#markup' => $rebuildmsg);

  $form['rebuild']['rebuild_marker_js'] = array(
    '#type' => 'submit',
    '#value' => t('Regenerate'),
    '#submit' => array('_getlocations_leaflet_rebuild_marker_js_submit'),
  );
  $form['rebuild']['getlocations_leaflet_flush'] = getlocations_element_map_checkbox(
    t('Flush marker cache'),
     $getlocations_leaflet_defaults['flush_marker_cache'],
    t('Include the marker cache when the Backdrop cache is flushed.')
  );

  // getlocations_leaflet_cdn
  $getlocations_leaflet_cdn = config_get("getlocations_leaflet.cdn", "settings");

  $leaflet_libraries_installed = (libraries_get_path('leaflet') ? TRUE : FALSE);
  $leaflet_version = '';
  if ($leaflet_libraries_installed) {
    $desc = t('The Leaflet Library is installed at !p.', array('!p' => libraries_get_path('leaflet')));
    $leaflet_version = getlocations_leaflet_library_version();
    if ($leaflet_version) {
      $desc .= '&nbsp;' . t('Using version !v', array('!v' => $leaflet_version));
    }
  }
  elseif ( $getlocations_leaflet_cdn['enable']) {
    $desc = t('The Leaflet library is being hosted on CDN.');
  }
  else {
    $desc = '<span class="error">' . t('The Leaflet library is NOT installed.') . '</span>';
  }
  $desc .= '<br />' . t('For details on the Leaflet library please see !u', array('!u' => l(t('leafletjs.com'), 'http://leafletjs.com/', array('attributes' => array('target' => '_blank')))));
  $desc .= '<br />' . t('Please read the README.txt included with getlocations_leaflet.');
  $form['getlocations_leaflet_cdn'] = array(
    '#type' => 'fieldset',
    '#title' => t('Leaflet Library'),
    '#description' => $desc,
    '#collapsible' => TRUE,
    '#collapsed' => ($leaflet_libraries_installed || ($getlocations_leaflet_cdn['enable'] && $getlocations_leaflet_cdn['js'] && $getlocations_leaflet_cdn['css']) ? TRUE : FALSE),
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );
  $form['getlocations_leaflet_cdn']['enable'] = getlocations_element_map_checkbox(
    t('Enable CDN'),
    $getlocations_leaflet_cdn['enable'],
    t('Supply the URLs for CDN below.')
  );
  $form['getlocations_leaflet_cdn']['js'] = getlocations_element_map_tf(
    t('Leaflet library javascript URL'),
    $getlocations_leaflet_cdn['js'],
    t('The full URL to the Leaflet javascript library.'),
    80,
    128
  );
  $form['getlocations_leaflet_cdn']['css'] = getlocations_element_map_tf(
    t('Leaflet library CSS URL'),
    $getlocations_leaflet_cdn['css'],
    t('The full URL to the Leaflet css library.'),
    80,
    128
  );

  if ($leaflet_libraries_installed || ($getlocations_leaflet_cdn['enable'] && $getlocations_leaflet_cdn['js'] && $getlocations_leaflet_cdn['css'])) {
    // preview
    $form['getlocations_leaflet_preview'] = array(
      '#type' => 'fieldset',
      '#title' => t('Getlocations Leaflet Preview'),
      '#description' => t('A preview of the current map settings.') . '<br />' . t('You can adjust the default Map center and Zoom by changing the map.') . '<br />' . t('For all other changes use the form. Remember to Save configuration when you are done.'),
      // This will store all the defaults in one variable.
      '#tree' => FALSE,
    );
    $form['getlocations_leaflet_preview']['preview_map'] = array('#markup' => '');
  }

  // plugins
  $getlocations_leaflet_plugins = getlocations_leaflet_plugins();
  $form['getlocations_leaflet_plugins'] = array(
    '#type' => 'fieldset',
    '#title' => t('Leaflet plugins'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['getlocations_leaflet_plugins']['markercluster_enable'] = getlocations_element_map_checkbox(
    t('Enable Markercluster plugin'),
    $getlocations_leaflet_plugins['markercluster_enable']
  );
  $form['getlocations_leaflet_plugins']['fullscreen_enable'] = getlocations_element_map_checkbox(
    t('Enable Fullscreen plugin'),
    $getlocations_leaflet_plugins['fullscreen_enable']
  );
  $form['getlocations_leaflet_plugins']['graticule_enable'] = getlocations_element_map_checkbox(
    t('Enable Graticule plugin'),
    $getlocations_leaflet_plugins['graticule_enable']
  );
  $form['getlocations_leaflet_plugins']['pancontrol_enable'] = getlocations_element_map_checkbox(
    t('Enable Pancontrol plugin'),
    $getlocations_leaflet_plugins['pancontrol_enable']
  );
  $form['getlocations_leaflet_plugins']['zoomslider_enable'] = getlocations_element_map_checkbox(
    t('Enable Zoomslider plugin'),
    $getlocations_leaflet_plugins['zoomslider_enable']
  );
  $form['getlocations_leaflet_plugins']['awesome_enable'] = getlocations_element_map_checkbox(
    t('Enable Awesome markers plugin'),
    $getlocations_leaflet_plugins['awesome_enable']
  );
  $form['getlocations_leaflet_plugins']['mouseposition_enable'] = getlocations_element_map_checkbox(
    t('Enable Mouseposition plugin'),
    $getlocations_leaflet_plugins['mouseposition_enable']
  );
  $form['getlocations_leaflet_plugins']['minimap_enable'] = getlocations_element_map_checkbox(
    t('Enable Minimap plugin'),
    $getlocations_leaflet_plugins['minimap_enable']
  );
  $form['getlocations_leaflet_plugins']['geocoder_enable'] = getlocations_element_map_checkbox(
    t('Enable Geocoder plugin'),
    $getlocations_leaflet_plugins['geocoder_enable']
  );
  $form['getlocations_leaflet_plugins']['usermarker_enable'] = getlocations_element_map_checkbox(
    t('Enable Usermarker plugin'),
    $getlocations_leaflet_plugins['usermarker_enable']
  );
  $form['getlocations_leaflet_plugins']['bouncemarker_enable'] = getlocations_element_map_checkbox(
    t('Enable Bouncemarker plugin'),
    $getlocations_leaflet_plugins['bouncemarker_enable']
  );
  $form['getlocations_leaflet_plugins']['magnifyingglass_enable'] = getlocations_element_map_checkbox(
    t('Enable Magnifying Glass plugin'),
    $getlocations_leaflet_plugins['magnifyingglass_enable']
  );
  $form['getlocations_leaflet_plugins']['terminator_enable'] = getlocations_element_map_checkbox(
    t('Enable Day/Night plugin'),
    $getlocations_leaflet_plugins['terminator_enable']
  );

  // leaflet-hash
  $leaflet_hash_file = getlocations_leaflet_hash_library_check();
  if ($leaflet_hash_file) {
    $form['getlocations_leaflet_plugins']['hash_enable'] = getlocations_element_map_checkbox(
      t('Enable Leaflet hash plugin'),
      $getlocations_leaflet_plugins['hash_enable']
    );
  }
  else {
    $form['getlocations_leaflet_plugins']['hash_enable'] = array('#type' => 'value', '#value' => 0);
  }

  // mapquest
  $mapquest_lic = getlocations_mapquest_get_lic();
  if ($mapquest_lic['key']) {

    if ($mapquest_lic['type'] == 'l') {
      $form['getlocations_leaflet_plugins']['mapquest_traffic_enable'] = getlocations_element_map_checkbox(
        t('Enable Mapquest Traffic plugin'),
        $getlocations_leaflet_plugins['mapquest_traffic_enable']
      );
    }
    else {
      $form['getlocations_leaflet_plugins']['mapquest_traffic_enable'] = array('#type' => 'value', '#value' => 0);
    }

    #$form['getlocations_leaflet_plugins']['mapquest_routing_enable'] = getlocations_element_map_checkbox(
    #  t('Enable Mapquest Routing plugin'),
    #  $getlocations_leaflet_plugins['mapquest_routing_enable']
    #);
    $form['getlocations_leaflet_plugins']['mapquest_routing_enable'] = array('#type' => 'value', '#value' => 0);

    if ($mapquest_lic['type'] == 'l') {
      $form['getlocations_leaflet_plugins']['mapquest_geocoder_enable'] = getlocations_element_map_checkbox(
        t('Enable Mapquest Geocoding plugin'),
        $getlocations_leaflet_plugins['mapquest_geocoder_enable']
      );
    }
    else {
      $form['getlocations_leaflet_plugins']['mapquest_geocoder_enable'] = array('#type' => 'value', '#value' => 0);
    }

    $form['getlocations_leaflet_plugins']['mapquest_maps_enable'] = getlocations_element_map_checkbox(
      t('Enable Mapquest Maps plugin'),
      $getlocations_leaflet_plugins['mapquest_maps_enable']
    );
    #$form['getlocations_leaflet_plugins']['mapquest_maps_enable'] = array('#type' => 'value', '#value' => 0);

  }
  else {
    $form['getlocations_leaflet_plugins']['mapquest_traffic_enable'] = array('#type' => 'value', '#value' => 0);
    $form['getlocations_leaflet_plugins']['mapquest_routing_enable'] = array('#type' => 'value', '#value' => 0);
    $form['getlocations_leaflet_plugins']['mapquest_geocoder_enable'] = array('#type' => 'value', '#value' => 0);
    $form['getlocations_leaflet_plugins']['mapquest_maps_enable'] = array('#type' => 'value', '#value' => 0);
  }

  // mapbox
  if (module_exists('getlocations_mapbox')) {
    $form += getlocations_mapbox_settings_form();
  }

  // cloudmade
  if (module_exists('getlocations_cloudmade')) {
    $form += getlocations_cloudmade_settings_form();
  }

  $settings = getlocations_leaflet_defaults();

  $form['getlocations_leaflet_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default Page settings'),
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $labels = array(
    'width' => t('Width'),
    'height' => t('Height'),
  );

  $form['getlocations_leaflet_defaults'] += getlocations_map_display_basics_form($settings, $labels);
  unset($form['getlocations_leaflet_defaults']['map_resize']);
  unset($form['getlocations_leaflet_defaults']['fullscreen_disable']);
  unset($form['getlocations_leaflet_defaults']['styles']);

  unset($form['getlocations_leaflet_defaults']['zoom']['#options']['21']);
  unset($form['getlocations_leaflet_defaults']['zoom']['#options']['20']);
  unset($form['getlocations_leaflet_defaults']['zoom']['#options']['19']);
  unset($form['getlocations_leaflet_defaults']['minzoom_map']['#options']['21']);
  unset($form['getlocations_leaflet_defaults']['minzoom_map']['#options']['20']);
  unset($form['getlocations_leaflet_defaults']['minzoom_map']['#options']['19']);

  unset($form['getlocations_leaflet_defaults']['maxzoom_map']['#options']['21']);
  unset($form['getlocations_leaflet_defaults']['maxzoom_map']['#options']['20']);
  unset($form['getlocations_leaflet_defaults']['maxzoom_map']['#options']['19']);

  $what3words_lic = getlocations_w3w_get_lic();
  $settings['what3words_lic'] = $what3words_lic;
  $form['getlocations_leaflet_defaults'] += getlocations_leaflet_display_options_form($settings, TRUE);
  unset($form['getlocations_leaflet_defaults']['nodezoom']['#options']['21']);
  unset($form['getlocations_leaflet_defaults']['nodezoom']['#options']['20']);
  unset($form['getlocations_leaflet_defaults']['nodezoom']['#options']['19']);

  // awesome
  if ($settings['awesome'] && $settings['marker_type'] == 'fa') {

    // default
    $form['getlocations_leaflet_defaults'] += getlocations_leaflet_awesome_markers_elements_get($settings);

    // nodes
    $labels = array(
      'awesome_icon' => t('Node Awesome icon'),
      'awesome_icon_color' => t('Node Awesome icon color'),
      'awesome_marker_color' => t('Node Awesome marker color'),
      'awesome_title' => t('Node Awesome Fonts icon settings'),
      'awesome_icon_spin' => t('Node Awesome icon spin'),
      'awesome_icon_size' => t('Node Awesome icon size'),
      'awesome_icon_type' => t('Node Awesome icon type'),
      'awesome_icon_flip' => t('Node Awesome icon flip and rotate'),
      'awesome_icon_html' => t('Node Awesome icon HTML'),
      'awesome_icon_class' => t('Node Awesome icon class'),
    );
    $form['getlocations_leaflet_defaults'] += getlocations_leaflet_awesome_markers_elements_get($settings, $labels, "node");

    // node type markers
    if ($types = getlocations_get_types()) {

      $getlocations_node_marker = $getlocations_leaflet_defaults['node_map_marker'];
      #if ($getlocations_node_marker['enable']) {
      #  $typect = 0;
      #  foreach ($types AS $type => $name) {
      #    $field_names = getlocations_get_fieldname2($type, 'node');
      #    foreach ($field_names AS $field_name) {
      #      $label = t('%name Map marker, field %field' , array('%name' => $name, '%field' => $field_name));
      #      $mkey = 'node_marker__' . backdrop_strtolower($type) . '__' . $field_name;
      #      $labels = array(
      #        'awesome_icon'         => t($label . ' Awesome icon'),
      #        'awesome_icon_color'   => t($label . ' Awesome icon color'),
      #        'awesome_marker_color' => t($label . ' Awesome marker color'),
      #        'awesome_title'        => t($label . ' Awesome Fonts icon settings'),
      #        'awesome_icon_spin'    => t($label . ' Awesome icon spin'),
      #        'awesome_icon_size'    => t($label . ' Awesome icon size'),
      #        'awesome_icon_type'    => t($label . ' Awesome icon type'),
      #        'awesome_icon_flip'    => t($label . ' Awesome icon flip and rotate'),
      #        'awesome_icon_html'    => t($label . ' Awesome icon HTML'),
      #        'awesome_icon_class'   => t($label . ' Awesome icon class'),
      #      );
      #      $form['getlocations_leaflet_defaults'] += getlocations_leaflet_awesome_markers_elements_get($settings, $labels, $mkey);
      #    }
      #  }
      #}
    }

    // users
    if (getlocations_check_entity_type('user')) {
      $labels = array(
        'awesome_icon' => t('User Awesome icon'),
        'awesome_icon_color' => t('User Awesome icon color'),
        'awesome_marker_color' => t('User Awesome marker color'),
        'awesome_title' => t('User Awesome Fonts icon settings'),
        'awesome_icon_spin' => t('User Awesome icon spin'),
        'awesome_icon_size' => t('User Awesome icon size'),
        'awesome_icon_type' => t('User Awesome icon type'),
        'awesome_icon_flip' => t('User Awesome icon flip and rotate'),
        'awesome_icon_html' => t('User Awesome icon HTML'),
        'awesome_icon_class' => t('User Awesome icon class'),
      );
      $form['getlocations_leaflet_defaults'] += getlocations_leaflet_awesome_markers_elements_get($settings, $labels, 'user');
    }

    if (module_exists('taxonomy')) {
      if ($types = getlocations_get_machine_vocabularies()) {
        // vocabulary
        // TODO per vocab
        $labels = array(
          'awesome_icon' => t('Vocabulary Awesome icon'),
          'awesome_icon_color' => t('Vocabulary Awesome icon color'),
          'awesome_marker_color' => t('Vocabulary Awesome marker color'),
          'awesome_title' => t('Vocabulary Awesome Fonts icon settings'),
          'awesome_icon_spin' => t('Vocabulary Awesome icon spin'),
          'awesome_icon_size' => t('Vocabulary Awesome icon size'),
          'awesome_icon_type' => t('Vocabulary Awesome icon type'),
          'awesome_icon_flip' => t('Vocabulary Awesome icon flip and rotate'),
          'awesome_icon_html' => t('Vocabulary Awesome icon HTML'),
          'awesome_icon_class' => t('Vocabulary Awesome icon class'),
        );
        $form['getlocations_leaflet_defaults'] += getlocations_leaflet_awesome_markers_elements_get($settings, $labels, 'vocabulary');

      }
      // terms
      // TODO per term
      $labels = array(
        'awesome_icon' => t('Term Awesome icon'),
        'awesome_icon_color' => t('Term Awesome icon color'),
        'awesome_marker_color' => t('Term Awesome marker color'),
        'awesome_title' => t('Term Awesome Fonts icon settings'),
        'awesome_icon_spin' => t('Term Awesome icon spin'),
        'awesome_icon_size' => t('Term Awesome icon size'),
        'awesome_icon_type' => t('Term Awesome icon type'),
        'awesome_icon_flip' => t('Term Awesome icon flip and rotate'),
        'awesome_icon_html' => t('Term Awesome icon HTML'),
        'awesome_icon_class' => t('Term Awesome icon class'),
      );
      $form['getlocations_leaflet_defaults'] += getlocations_leaflet_awesome_markers_elements_get($settings, $labels, 'term');
    }
    if (getlocations_check_entity_type('comment')) {
      // comment
      $labels = array(
        'awesome_icon' => t('Comment Awesome icon'),
        'awesome_icon_color' => t('Comment Awesome icon color'),
        'awesome_marker_color' => t('Comment Awesome marker color'),
        'awesome_title' => t('Comment Awesome Fonts icon settings'),
        'awesome_icon_spin' => t('Comment Awesome icon spin'),
        'awesome_icon_size' => t('Comment Awesome icon size'),
        'awesome_icon_type' => t('Comment Awesome icon type'),
        'awesome_icon_flip' => t('Comment Awesome icon flip and rotate'),
        'awesome_icon_html' => t('Comment Awesome icon HTML'),
        'awesome_icon_class' => t('Comment Awesome icon class'),
      );
      $form['getlocations_leaflet_defaults'] += getlocations_leaflet_awesome_markers_elements_get($settings, $labels, 'comment');

    }

  }
  elseif ($settings['marker_type'] == 'gg') {
    // getlocations markers
    // default node marker
    $markers = getlocations_get_marker_titles();
    $desc = '';
    if (getlocations_check_entity_type('node')) {
      $desc = t('In use');
    }
    $form['getlocations_leaflet_defaults']['node_map_marker'] = getlocations_element_map_marker(
      t('Default Content Map marker'),
      $markers,
      $getlocations_leaflet_defaults['node_map_marker'],
      $desc
    );

    // default user marker
    $desc = '';
    if (getlocations_check_entity_type('user')) {
      $desc = t('In use');
    }
    $form['getlocations_leaflet_defaults']['user_map_marker'] = getlocations_element_map_marker(
      t('Default User Map marker'),
      $markers,
      $getlocations_leaflet_defaults['user_map_marker'],
      $desc
    );
    if (module_exists('taxonomy')) {
      // default vocabulary marker
      $desc = '';
      if (getlocations_get_vocabularies()) {
        $desc = t('In use');
      }
      $form['getlocations_leaflet_defaults']['vocabulary_map_marker'] = getlocations_element_map_marker(
        t('Default Vocabulary Map marker'),
        $markers,
        $getlocations_leaflet_defaults['vocabulary_map_marker'],
        $desc
      );
      $form['getlocations_leaflet_defaults']['term_map_marker'] = getlocations_element_map_marker(
        t('Default Term Map marker'),
        $markers,
        $getlocations_leaflet_defaults['term_map_marker'],
        ''
      );
    }
    if (module_exists('comment')) {
      // default comment marker
      $desc = '';
      if (getlocations_check_entity_type('comment')) {
        $desc = t('In use');
      }
      $form['getlocations_leaflet_defaults']['comment_map_marker'] = getlocations_element_map_marker(
        t('Default Comment Map marker'),
        $markers,
        $getlocations_leaflet_defaults['comment_map_marker'],
        $desc
      );
    }
  }

  // returnlink_group
  $returnlink_group = $settings['returnlink_group'];
  $form['getlocations_leaflet_defaults']['returnlink_page_enable'] = getlocations_element_map_checkbox(
    t('Show link back to page'),
    $returnlink_group['returnlink_page_enable']
  );
  $form['getlocations_leaflet_defaults']['returnlink_page_link'] = getlocations_element_map_tf(
    t('Text of page return link'),
    $returnlink_group['returnlink_page_link'],
    t('Use %t to insert the page title'),
    30,
    64
  );

  if (module_exists('getlocations_fields')) {
    if (getlocations_check_entity_type('user')) {
      $form['getlocations_leaflet_defaults']['returnlink_user_enable'] = getlocations_element_map_checkbox(
        t('Show link back to user'),
        $returnlink_group['returnlink_user_enable']
      );
      $form['getlocations_leaflet_defaults']['returnlink_user_link'] = getlocations_element_map_tf(
        t('Text of user return link'),
        $returnlink_group['returnlink_user_link'],
        t('Use %n to insert the user name'),
        30,
        64
      );
    }

    if (module_exists('taxonomy')) {
      if (getlocations_get_vocabularies()) {
        $form['getlocations_leaflet_defaults']['returnlink_term_enable'] = getlocations_element_map_checkbox(
          t('Show link back to term'),
          $returnlink_group['returnlink_term_enable']
        );
        $form['getlocations_leaflet_defaults']['returnlink_term_link'] = getlocations_element_map_tf(
          t('Text of term return link'),
          $returnlink_group['returnlink_term_link'],
          t('Use %n to insert the term name'),
          30,
          64
        );
      }
    }

    if (getlocations_check_entity_type('comment')) {
      $form['getlocations_leaflet_defaults']['returnlink_comment_enable'] = getlocations_element_map_checkbox(
        t('Show link back to comment'),
        $returnlink_group['returnlink_comment_enable']
      );
      $form['getlocations_leaflet_defaults']['returnlink_comment_link'] = getlocations_element_map_tf(
        t('Text of comment return link'),
        $returnlink_group['returnlink_comment_link'],
        t('Use %n to insert the comment subject'),
        30,
        64
      );
    }

    // search markers
    if (module_exists('getlocations_fields') && module_exists('views')) {
      $form['getlocations_leaflet_defaults'] += getlocations_fields_views_search_form($settings, 'leaflet');
    }
  }

  // javascript paths
  $getlocations_leaflet_paths = getlocations_leaflet_paths_get_all();
  $form['getlocations_leaflet_paths'] = array(
    '#type' => 'fieldset',
    '#title' => t('Javascript paths'),
    '#description' => t('For advanced users who want to supply their own javascript.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );

  $form['getlocations_leaflet_paths']['getlocations_leaflet_path'] = getlocations_element_path(
    t('Path to Getlocations leaflet javascript file'),
    $getlocations_leaflet_paths['getlocations_leaflet_path'],
    80,
    128,
    t('Where the Getlocations leaflet javascript file is located.')
  );
  $form['getlocations_leaflet_paths']['getlocations_leaflet_circles_path'] = getlocations_element_path(
    t('Path to Getlocations leaflet circles javascript file'),
    $getlocations_leaflet_paths['getlocations_leaflet_circles_path'],
    80,
    128,
    t('Where the Getlocations leaflet circles javascript file is located.')
  );
  $form['getlocations_leaflet_paths']['getlocations_leaflet_formatter_path'] = getlocations_element_path(
    t('Path to Getlocations leaflet formatter javascript file'),
    $getlocations_leaflet_paths['getlocations_leaflet_formatter_path'],
    80,
    128,
    t('Where the Getlocations leaflet formatter javascript file is located.')
  );
  $form['getlocations_leaflet_paths']['getlocations_leaflet_polygons_path'] = getlocations_element_path(
    t('Path to Getlocations leaflet polygons javascript file'),
    $getlocations_leaflet_paths['getlocations_leaflet_polygons_path'],
    80,
    128,
    t('Where the Getlocations leaflet polygons javascript file is located.')
  );
  $form['getlocations_leaflet_paths']['getlocations_leaflet_polylines_path'] = getlocations_element_path(
    t('Path to Getlocations leaflet polylines javascript file'),
    $getlocations_leaflet_paths['getlocations_leaflet_polylines_path'],
    80,
    128,
    t('Where the Getlocations leaflet polylines javascript file is located.')
  );
  $form['getlocations_leaflet_paths']['getlocations_leaflet_rectangles_path'] = getlocations_element_path(
    t('Path to Getlocations leaflet rectangles javascript file'),
    $getlocations_leaflet_paths['getlocations_leaflet_rectangles_path'],
    80,
    128,
    t('Where the Getlocations leaflet rectangles javascript file is located.')
  );
  $form['getlocations_leaflet_paths']['getlocations_leaflet_geojson_path'] = getlocations_element_path(
    t('Path to Getlocations leaflet geojson javascript file'),
    $getlocations_leaflet_paths['getlocations_leaflet_geojson_path'],
    80,
    128,
    t('Where the Getlocations leaflet geojson javascript file is located.')
  );
  $form['getlocations_leaflet_paths']['getlocations_leaflet_providers_path'] = getlocations_element_path(
    t('Path to Getlocations leaflet providers javascript file'),
    $getlocations_leaflet_paths['getlocations_leaflet_providers_path'],
    80,
    128,
    t('Where the Getlocations leaflet providers javascript file is located.')
  );
  $form['getlocations_leaflet_paths']['getlocations_leaflet_preview_path'] = getlocations_element_path(
    t('Path to Getlocations leaflet preview javascript file'),
    $getlocations_leaflet_paths['getlocations_leaflet_preview_path'],
    80,
    128,
    t('Where the Getlocations leaflet preview javascript file is located.')
  );
  $form['getlocations_leaflet_paths']['getlocations_leaflet_field_group_path'] = getlocations_element_path(
    t('Path to Getlocations leaflet field group javascript file'),
    $getlocations_leaflet_paths['getlocations_leaflet_field_group_path'],
    80,
    128,
    t('Where the Getlocations leaflet field group javascript file is located.')
  );
  $form['getlocations_leaflet_paths']['getlocations_leaflet_what3words_path'] = getlocations_element_path(
    t('Path to Getlocations leaflet what3words javascript file'),
    $getlocations_leaflet_paths['getlocations_leaflet_what3words_path'],
    80,
    128,
    t('Where the Getlocations leaflet what3words javascript file is located.')
  );

#  $form['getlocations_leaflet_paths']['reset'] = getlocations_element_dd(
#    t('Reset'),
#    0,
#    array(0 => t('No'), 1 => t('Reset'), 2 => t('Reset to minified')),
#    t('Reset the paths to the defaults.')
#  );

  // Add a submit button
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  unset($form['#theme']);
  $form['#theme'] = 'getlocations_leaflet_settings_form';
#  $form['#validate'][] = 'getlocations_leaflet_settings_validate';
  $form['#attached']['js'] = array(
    $getlocations_leaflet_paths['getlocations_leaflet_formatter_path'],
    $getlocations_leaflet_paths['getlocations_leaflet_preview_path'],
  );
  return $form;

}

/**
 * Function
 *
 * @param
 *
 * @return
 *   Returns
 *
 */
function getlocations_leaflet_settings_form_validate($form, &$form_state) {
#  $reset = $form_state['values']['getlocations_leaflet_paths']['reset'];
#  unset($form_state['values']['getlocations_leaflet_paths']['reset']);
#  if ($reset == 1) {
#    $form_state['values']['getlocations_leaflet_paths'] = getlocations_leaflet_paths_get(TRUE);
#  }
#  elseif ($reset == 2) {
#    $form_state['values']['getlocations_leaflet_paths'] = getlocations_leaflet_paths_get(FALSE, TRUE);
#  }

  // getlocations_leaflet_cdn
  if ($form_state['values']['getlocations_leaflet_cdn']['enable']) {
    if (empty($form_state['values']['getlocations_leaflet_cdn']['js']) || empty($form_state['values']['getlocations_leaflet_cdn']['css'])) {
      form_set_error('getlocations_leaflet_cdn][enable', t('You must supply a valid css and js URL.'));
    }
  }

  // cloudmade
#  if (module_exists('getlocations_cloudmade')) {
#    $form_state = getlocations_cloudmade_settings_validate($form_state);
#  }

  // mapbox
#  if (module_exists('getlocations_mapbox')) {
#    $form_state = getlocations_mapbox_settings_form_validate($form_state);
#  }

  // css check
  if (isset($form_state['values']['getlocations_leaflet_defaults']['width'])) {
    if ($check = getlocations_dim_check($form_state['values']['getlocations_leaflet_defaults']['width'])) {
      $form_state['values']['getlocations_leaflet_defaults']['width'] = $check;
    }
    else {
      form_set_error('getlocations_leaflet_defaults][width', t('Width must be valid css'));
    }
  }
  if (isset($form_state['values']['getlocations_leaflet_defaults']['height'])) {
    if ($check = getlocations_dim_check($form_state['values']['getlocations_leaflet_defaults']['height'])) {
      $form_state['values']['getlocations_leaflet_defaults']['height'] = $check;
    }
    else {
      form_set_error('getlocations_leaflet_defaults][height', t('Height must be valid css'));
    }
  }

}

function getlocations_leaflet_settings_form_submit($form, &$form_state) {

  $config = config('getlocations_leaflet.settings');
  $settings = $config->get('settings');
  $keys = array_keys($settings);
  // extract the paths as they are in a different storage
  $getlocations_leaflet_paths_config = config("getlocations_leaflet.paths");
  $getlocations_leaflet_paths_config->set('paths', $form_state['values']['getlocations_leaflet_paths']);
  $getlocations_leaflet_paths_config->save();

  // getlocations_leaflet_cdn
  $config_cdn = config("getlocations_leaflet.cdn");
  $config_cdn->set('settings', $form_state['values']['getlocations_leaflet_cdn']);
  $config_cdn->save();

  // getlocations_leaflet_plugins
  $config_plugins = config("getlocations_leaflet.plugins");
  $config_plugins->set('settings', $form_state['values']['getlocations_leaflet_plugins']);
  $config_plugins->save();

  // mapbox
  if (module_exists('getlocations_mapbox')) {
    getlocations_mapbox_settings_save($form_state['values']);
  }

  // cloudmade
  if (module_exists('getlocations_cloudmade')) {
    getlocations_cloudmade_settings_save($form_state['values']);
  }

  if (isset($form_state['values']['getlocations_leaflet_defaults'])) {

    //getlocations_leaflet_defaults
    $values = $form_state['values']['getlocations_leaflet_defaults'];

    // what3words only if there is a license
    $lic = getlocations_w3w_get_lic();
    if ( ! empty($lic['key'])) {
      $w3warr = array('what3words_enable','what3words_search','what3words_size','what3words_marker_show','what3words_map_marker','what3words_center','what3words_zoom','what3words_click','what3words_show', 'what3words_path');
      foreach ($w3warr AS $a) {
        $values['what3words_group'][$a] = $form_state['values']['getlocations_leaflet_defaults'][$a];
      }
    }

    // cache flush $form['rebuild']['getlocations_leaflet_flush']
    $values['flush_marker_cache'] = $form_state['values']['rebuild']['getlocations_leaflet_flush'];

    $returnlink_group = array("returnlink_page_enable","returnlink_page_link","returnlink_user_enable","returnlink_user_link","returnlink_term_enable","returnlink_term_link","returnlink_comment_enable","returnlink_comment_link");
    foreach ($returnlink_group AS $item) {
      if (isset($values[$item])) {
        $values['returnlink_group'][$item] = $values[$item];
        unset($values[$item]);
      }
    }

    // gps
    #if (module_exists('getlocations_gps')) {
    #  $gps_keys = getlocations_gps_get_keys();
    #  foreach ($gps_keys AS $gk) {
    #    if (isset($values[$gk])) {
    #      $config->set('settings.' . $gk, $values[$gk] );
    #    }
    #  }
    #}
/*
    // now in its own file getlocations.shapes
    $shapes_values = array();

    // polygons_group
    $polygons_group = array("polygons_enable","polygons_strokecolor","polygons_strokeopacity","polygons_strokeweight","polygons_fillcolor","polygons_fillopacity","polygons_coords","polygons_clickable","polygons_message");
    foreach ($polygons_group AS $item) {
      $shapes_values['polygons_group'][$item] = $values[$item];
      unset($values[$item]);
    }

    $rectangles_group = array("rectangles_enable","rectangles_strokecolor","rectangles_strokeopacity","rectangles_strokeweight","rectangles_fillcolor","rectangles_fillopacity","rectangles_coords","rectangles_clickable","rectangles_message","rectangles_apply","rectangles_dist");
    foreach ($rectangles_group AS $item) {
      $shapes_values['rectangles_group'][$item] = $values[$item];
      unset($values[$item]);
    }

    $circles_group = array("circles_enable","circles_strokecolor","circles_strokeopacity","circles_strokeweight","circles_fillcolor","circles_fillopacity","circles_coords","circles_clickable","circles_message","circles_radius","circles_apply");
    foreach ($circles_group AS $item) {
      $shapes_values['circles_group'][$item] = $values[$item];
      unset($values[$item]);
    }

    $polylines_group = array("polylines_enable","polylines_strokecolor","polylines_strokeopacity","polylines_strokeweight","polylines_coords","polylines_clickable","polylines_message");
    foreach ($polylines_group AS $item) {
      $shapes_values['polylines_group'][$item] = $values[$item];
      unset($values[$item]);
    }


    $shapes = config('getlocations.shapes');
    foreach($shapes_values AS $k => $v) {
      $shapes->set('shapes.' . $k, $v);
    }
    $shapes->save();
  // now in its own file getlocations.shapes
  $shapes_groups = array("polygons_group","rectangles_group","circles_group","polylines_group");
  $shapes = config('getlocations_leaflet.shapes');
  foreach ($shapes_groups AS $group) {
    $shapes->set('shapes.' . $group, $values[$group]);
    unset($values[$group]);
  }
  $shapes->save();
*/

    foreach ($keys AS $key) {
      if ( isset($values[$key])) {
        $config->set('settings.' . $key, $values[$key]);
      }
    }
    $config->save();

  }


  backdrop_set_message(t('Getlocations configuration options have been saved.'));

}


/**
 * Rebuild marker js.
 */
function _getlocations_leaflet_rebuild_marker_js_submit($form, &$form_state) {
  if (getlocations_leaflet_regenerate_markers()) {
    backdrop_set_message(t('Marker cache regenerated.'));
  }
}
