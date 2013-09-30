<?php

/**
 * @file
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
 * Getlocations Map Views support.
 */

/**
 * Implements hook_views_plugins().
 */
function getlocations_views_plugins() {

  return array(
    'module' => 'getlocations',
    'style' => array(
      'getlocations' => array(
        'title' => t('GetLocations'),
        'help' => t('Displays rows as a map.'),
        'handler' => 'getlocations_plugin_style_map',
        'theme' => 'getlocations_view_map',
        'theme path' => GETLOCATIONS_PATH . '/views',
        'uses row plugin' => TRUE,
        'uses grouping' => FALSE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
      'getlocations_streetview' => array(
        'title' => t('GetLocations Streetview'),
        'help' => t('Displays a location in Streetview.'),
        'handler' => 'getlocations_plugin_style_streetview',
        'theme' => 'getlocations_view_streetview',
        'theme path' => GETLOCATIONS_PATH . '/views',
        'uses row plugin' => TRUE,
        'uses grouping' => FALSE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}

/**
 * Preprocess function for getlocations_view_map.tpl
 */
function template_preprocess_getlocations_view_map(&$variables) {
  global $language;

  $locations = $variables['view']->style_plugin->rendered_fields;
  $options = $variables['view']->style_plugin->options;
  $base_field = $variables['view']->style_plugin->view->base_field;

  $latlons = array();
  $minmaxes = array('minlat' => 0, 'minlon' => 0, 'maxlat' => 0, 'maxlon' => 0);
  $ct = 0;
  $entity_type = 'node';
  if ($base_field == 'uid') {
    $entity_type = 'user';
  }
  elseif ($base_field == 'tid') {
    $entity_type = 'taxonomy_term';
  }
  elseif ($base_field == 'cid') {
    $entity_type = 'comment';
  }

  if ($options['custom_content_enable'] and !empty($options['custom_content_source'])) {
    $custom_content_source = $options['custom_content_source'];
  }
  else {
    $custom_content_source = NULL;
  }
  if (count($locations)) {
    $cats = array();
    // we should loop over them and dump bummers with no lat/lon
    foreach ($locations AS $key => $location) {

      $custom_content = $custom_content_source ? $location[$custom_content_source] : '';
      $lid = 0;
      if (module_exists('getlocations_fields') && isset($location['glid']) && $location['glid'] > 0) {
        $lid = $location['glid'];
      }
      elseif (module_exists('location') && isset($location['lid']) && $location['lid'] > 0) {
        $lid = $location['lid'];
        if (isset($location['type'])) {
          $location['field_name'] = getlocations_get_fieldname($location['type'], $entity_type);
        }
      }
      elseif (module_exists('geofield') && isset($location[$base_field]) && $location[$base_field] > 0 ) {
        $lid = $location[$base_field];
        $location['field_name'] = getlocations_get_fieldname($location['type'], $entity_type);
        $location['latitude'] = $location[$location['field_name']];
        $location['longitude'] = $location[$location['field_name'] . '_1'];
      }
      elseif (module_exists('geolocation') && isset($location[$base_field]) && $location[$base_field] > 0 ) {
        $lid = $location[$base_field];
        $location['field_name'] = getlocations_get_fieldname($location['type'], $entity_type);
        $location['latitude'] = $location[$location['field_name']];
        $location['longitude'] = $location[$location['field_name'] . '_1'];
      }
      if ($lid > 0) {
        if ($entity_type == 'node') {
          $marker = $options['node_map_marker'];
          if (isset($location['type']) && isset($location['field_name']) ) {
            if (isset($options['node_marker__' . strtolower($location['type']) . '__' . $location['field_name']])) {
              $marker = $options['node_marker__' . strtolower($location['type']) . '__' . $location['field_name']];
            }
          }
          // term marker
          $getlocations_term_marker = variable_get('getlocations_term_marker', array('enable' => 0, 'vids' => 0, 'max_depth' => ''));
          if ($getlocations_term_marker['enable'] && $getlocations_term_marker['vids']) {
            $vids = $getlocations_term_marker['vids'];
            foreach ($vids AS $vid) {
              if ($nid = getlocations_get_nid_from_lid($lid)) {
                $query = db_select('taxonomy_index', 't');
                $query->fields('t', array('tid'));
                $query->join('taxonomy_term_data', 'd', 't.tid=d.tid');
                $query->condition('t.nid', $nid);
                $query->condition('d.vid', $vid);
                $result = $query->execute()->fetchObject();
                if (isset($result->tid) && $result->tid > 0 && isset($options['term_marker_' . $result->tid])) {
                  $marker = $options['term_marker_' . $result->tid];
                }
              }
            }
          }
        }
        elseif ($entity_type == 'taxonomy_term') {
          $marker = $options['vocabulary_map_marker'];
          if (isset($location['field_name'])) {
            if (isset($options['vocabulary_marker_' . $location['field_name']])) {
              $marker = $options['vocabulary_marker_' . $location['field_name']];
            }
          }
        }
        elseif ($entity_type == 'user') {
          $marker = $options['user_map_marker'];
        }
        elseif ($entity_type == 'comment') {
          $marker = $options['comment_map_marker'];
        }
        // per item marker
        if (isset($location['marker']) && ! empty($location['marker'])) {
          $marker = $location['marker'];
        }
        // dump bummers with no lat/lon
        if ($latlon = getlocations_latlon_check($location['latitude'] . ',' . $location['longitude'])) {
          $ll = explode(',', $latlon);
          $location['latitude'] = $ll[0];
          $location['longitude'] = $ll[1];
          $minmaxes = getlocations_do_minmaxes($ct, $location, $minmaxes);
          $ct++;
          $name = htmlspecialchars_decode(isset($location['name']) && $location['name'] ? strip_tags($location['name']) : (isset($location['title']) && $location['title'] ? strip_tags($location['title']) : ''), ENT_QUOTES);

          // categories
          $cat = '';
          if ($options['category_method']) {
            if ($options['category_method'] == 1) {
              // content type
              if (! isset($location['type']) && isset($location['machine_name'])) {
                $location['type'] = $location['machine_name'];
              }
              if (isset($location['type'])) {
                $cat = $location['type'];
                // lookup label
                $query = db_select('node_type', 't');
                $query->fields('t', array('name'));
                $query->condition('t.type', $cat);
                $label = $query->execute()->fetchField();
                $cats[$cat] = $label;
              }
            }
            elseif ($options['category_method'] == 2) {
              // term_reference_field
              if (isset($location[$options['category_term_reference_field']])) {
                $label = $location[$options['category_term_reference_field']];
                $cat = preg_replace("/\s+/", "_", $label);
                $cat = preg_replace("/'/", "", $cat);
                $cat = drupal_strtolower($cat);
                $cats[$cat] = $label;
              }
            }
            if ($cat) {
              $options['categories'] = $cats;
            }
          }
          $latlons[] = array($location['latitude'], $location['longitude'], $lid, $name, $marker, $base_field, $custom_content, $cat);
        }
      }
    }
  }
  if ($ct < 2 || $lid == 0) {
    unset($minmaxes);
    $minmaxes = '';
  }

  // get the defaults and override with the style plugin options
  $getlocations_defaults = getlocations_defaults();
  $newdefaults = getlocations_adjust_vars($getlocations_defaults, $options);

  $mapid = getlocations_setup_map($newdefaults);
  getlocations_js_settings_do($newdefaults, $latlons, $minmaxes, $mapid);

  $variables['map']  = theme('getlocations_show', array('width' => $newdefaults['width'], 'height' => $newdefaults['height'], 'defaults' => $newdefaults, 'mapid' => $mapid, 'type' => '', 'node' => ''));

}

/**
 * Preprocess function for getlocations_view_streetview.tpl
 */
function template_preprocess_getlocations_view_streetview(&$variables) {
  global $language;

  // just in case
  if (! getlocations_sv_global()) {
    $variables['mapid'] = FALSE;
    return;
  }

  $locations = $variables['view']->style_plugin->rendered_fields;
  $options = $variables['view']->style_plugin->options;
  $base_field = $variables['view']->style_plugin->view->base_field;

  $latlons = array();
  $entity_type = 'node';
  if ($base_field == 'uid') {
    $entity_type = 'user';
  }
  elseif ($base_field == 'tid') {
    $entity_type = 'taxonomy_term';
  }
  elseif ($base_field == 'cid') {
    $entity_type = 'comment';
  }

  if (count($locations) == 1) {
    $location = $locations[0];

    $lid = 0;
    if (module_exists('getlocations_fields')) {
      if (isset($location['glid']) && $location['glid'] > 0 && isset($location['latitude']) && isset($location['longitude'])) {
        $lid = $location['glid'];
      }
    }
    elseif (module_exists('location')) {
      // TODO test this
      if (isset($location['lid']) && $location['lid'] > 0 && isset($location['latitude']) && isset($location['longitude'])) {
        $lid = $location['lid'];
        if (isset($location['type'])) {
          $location['field_name'] = getlocations_get_fieldname($location['type'], $entity_type);
        }
      }
    }
    elseif (module_exists('geofield')) {
      // TODO test this
      if (isset($location[$base_field]) && $location[$base_field] > 0 ) {
        $lid = $location[$base_field];
        $location['field_name'] = getlocations_get_fieldname($location['type'], $entity_type);
        $location['latitude'] = $location[$location['field_name']];
        $location['longitude'] = $location[$location['field_name'] . '_1'];
      }
    }
    elseif (module_exists('geolocation')) {
      // TODO test this
      if (isset($location[$base_field]) && $location[$base_field] > 0) {
        $lid = $location[$base_field];
        $location['field_name'] = getlocations_get_fieldname($location['type'], $entity_type);
        $location['latitude'] = $location[$location['field_name']];
        $location['longitude'] = $location[$location['field_name'] . '_1'];
      }
    }

    if ($lid > 0) {
      // dump bummers with no lat/lon
      if ($latlon = getlocations_latlon_check($location['latitude'] . ',' . $location['longitude'])) {
        $ll = explode(',', $latlon);
        $location['latitude'] = $ll[0];
        $location['longitude'] = $ll[1];

        $options['sv_heading'] = (isset($location['data']) && is_numeric($location['data']) ? $location['data'] : 0);
        $options['sv_zoom']    = (isset($location['data_1']) && is_numeric($location['data_1']) ? $location['data_1'] : 1);
        $options['sv_pitch']   = (isset($location['data_2']) && is_numeric($location['data_2']) ? $location['data_2'] : 0);
        $options['sv_enable']  = (isset($location['data_3']) && is_numeric($location['data_3']) ? $location['data_3'] : 1);

        $getlocations_defaults = getlocations_defaults();
        $newdefaults = getlocations_adjust_vars($getlocations_defaults, $options);
        $mapid = getlocations_setup_map($newdefaults, FALSE, TRUE);
        $options['latitude'] = $location['latitude'];
        $options['longitude'] = $location['longitude'];

        getlocations_streetview_js_settings_do($options, $mapid);
        $variables['mapid'] = $mapid;
        $variables['width'] = $options['width'];
        $variables['height'] = $options['height'];
      }
    }
  }
}

function getlocations_streetview_js_settings_do($defaults, $mapid) {

  $settings = array(
    $mapid => array(
      'width'                     => $defaults['width'],
      'height'                    => $defaults['height'],
      'sv_addresscontrol'         => $defaults['sv_addresscontrol'],
      'sv_addresscontrolposition' => $defaults['sv_addresscontrolposition'],
      'sv_pancontrol'             => $defaults['sv_pancontrol'],
      'sv_pancontrolposition'     => $defaults['sv_pancontrolposition'],
      'sv_zoomcontrol'            => $defaults['sv_zoomcontrol'],
      'sv_zoomcontrolposition'    => $defaults['sv_zoomcontrolposition'],
      'sv_linkscontrol'           => $defaults['sv_linkscontrol'],
      'sv_imagedatecontrol'       => $defaults['sv_imagedatecontrol'],
      'sv_scrollwheel'            => $defaults['sv_scrollwheel'],
      'sv_clicktogo'              => $defaults['sv_clicktogo'],
      'latitude'                  => $defaults['latitude'],
      'longitude'                 => $defaults['longitude'],
      'sv_heading'                => $defaults['sv_heading'],
      'sv_zoom'                   => $defaults['sv_zoom'],
      'sv_pitch'                  => $defaults['sv_pitch'],
      'sv_enable'                 => $defaults['sv_enable'],
      'js_path'                   => base_path() . GETLOCATIONS_PATH . '/js/',
      'sv_fullscreen'             => $defaults['sv_fullscreen'],
    ),
  );

  drupal_add_js(array('getlocations_streetview' => $settings), 'setting');

}

/**
 * Implements hook_views_pre_render().
 *
 * This hook is called right before the render process. The query has been
 * executed, and the pre_render() phase has already happened for handlers, so
 * all data should be available.
 *
 * Adding output to the view can be accomplished by placing text on
 * $view->attachment_before and $view->attachment_after. Altering the content
 * can be achieved by editing the items of $view->result.
 *
 * This hook can be utilized by themes.
 * @param $view
 *   The view object about to be processed.
 */
function getlocations_views_pre_render(&$view) {

  // look for the right view, machine name must end in getlocations_streetview
  if (preg_match('/getlocations_streetview$/i', $view->name)) {

    // streetview killswitch
    if (getlocations_sv_global()) {
      if (count($view->result) == 1) {
        if (isset($view->result[0]->getlocations_fields_data)) {
          // OK, now get the data, unserialize and get sv_enable
          $value = unserialize($view->result[0]->getlocations_fields_data);
          $enable = (isset($value['data']['sv_enable']) ? $value['data']['sv_enable'] : 1);
          if (! $enable) {
            // scrub the result
            unset($view->result[0]);
          }
        }
      }
      else {
        // scrub the result
        $c = count($view->result);
        for ($i = 0; $i < $c; $i++) {
          unset($view->result[$i]);
        }
      }
    }
    else {
      // scrub the result
      $c = count($view->result);
      for ($i = 0; $i < $c; $i++) {
        unset($view->result[$i]);
      }
    }
  }

}
