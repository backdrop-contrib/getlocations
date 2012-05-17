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
    ),
  );
}

/**
 * Preprocess function for theme_getlocations_view_map().
 */
function template_preprocess_getlocations_view_map(&$variables) {
  global $language;

  $locations = $variables['view']->style_plugin->rendered_fields;
  $options = $variables['view']->style_plugin->options;
  $base_field = $variables['view']->style_plugin->view->base_field;
  $latlons = array();
  $minmaxes = array('minlat' => 0, 'minlon' => 0, 'maxlat' => 0, 'maxlon' => 0);
  $ct = 0;

  if ($options['custom_content_enable'] and !empty($options['custom_content_source'])) {
    $custom_content_source = $options['custom_content_source'];
  }
  else {
    $custom_content_source = NULL;
  }
  if (count($locations)) {
    // we should loop over them and dump bummers with no lat/lon
    foreach ($locations AS $key => $location) {
      $custom_content = $custom_content_source ? $location[$custom_content_source] : '';
      $lid = 0;
      if (module_exists('getlocations_fields') && isset($location['glid']) && $location['glid'] > 0) {
        $lid = $location['glid'];
      }
      elseif (module_exists('location') && isset($location['lid']) && $location['lid'] > 0) {
        $lid = $location['lid'];
      }
      elseif (module_exists('geofield') && isset($location[$base_field]) && $location[$base_field] > 0 ) {
        $lid = $location[$base_field];
        $location['field_name'] = getlocations_get_fieldname($location['type']);
        $location['latitude'] = $location[$location['field_name']];
        $location['longitude'] = $location[$location['field_name'] . '_1'];
      }
      elseif (module_exists('geolocation') && isset($location[$base_field]) && $location[$base_field] > 0 ) {
        $lid = $location[$base_field];
        $location['field_name'] = getlocations_get_fieldname($location['type']);
        $location['latitude'] = $location[$location['field_name']];
        $location['longitude'] = $location[$location['field_name'] . '_1'];
      }
      if ($lid > 0) {
        // marker
        $marker = $options['node_map_marker'];
        if ($type = getlocations_get_type_from_lid($lid)) {
          if (isset($options[$type . '_map_marker'])) {
            $marker = $options[$type . '_map_marker'];
          }
        }
        if (isset($location['field_name']) && isset($options['node_marker_' . $location['field_name']])) {
          $marker = $options['node_marker_' . $location['field_name']];
        }
        if (isset($location['marker']) && ! empty($location['marker'])) {
          $marker = $location['marker'];
        }
        if ($nid = getlocations_get_nid_from_lid($lid)) {
          $results = db_query('SELECT tid FROM {taxonomy_index} WHERE nid = :nid', array(':nid' => $nid));
          foreach ($results as $result) {
            if (isset($options['term_marker_' . $result->tid])) {
              $marker = $options['term_marker_' . $result->tid];
            }
          }
        }
        if (getlocations_latlon_check($location['latitude'] . ',' . $location['longitude']) ) {
          $minmaxes = getlocations_do_minmaxes($ct, $location, $minmaxes);
          $ct++;
          $name = htmlspecialchars_decode(isset($location['name']) && $location['name'] ? strip_tags($location['name']) : (isset($location['title']) && $location['title'] ? strip_tags($location['title']) : ''), ENT_QUOTES);
          $latlons[] = array($location['latitude'], $location['longitude'], $lid, $name, $marker, $base_field, $custom_content);
        }
      }
    }
  }
  if ($ct < 2 || $lid == 0) {
    unset($minmaxes);
    $minmaxes = '';
  }

  // get the defaults and override with the style plugin options
  $newdefaults = array();
  $getlocations_defaults = getlocations_defaults();
  foreach ($getlocations_defaults AS $k => $v) {
    if (isset($options[$k])) {
      $newdefaults[$k] = $options[$k];
    }
    else {
      $newdefaults[$k] = $getlocations_defaults[$k];
    }
  }

  $mapid = getlocations_setup_map($newdefaults);
  getlocations_js_settings_do($newdefaults, $latlons, $minmaxes, $mapid);

  $variables['map']  = theme('getlocations_show', array('width' => $newdefaults['width'], 'height' => $newdefaults['height'], 'defaults' => $newdefaults, 'mapid' => $mapid, 'type' => '', 'node' => ''));

}
