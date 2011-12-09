<?php

/**
 * @file
 * Getlocations Map Views support.
 */

/**
 * Implementation of hook_views_plugins().
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
        'uses grouping' => TRUE,
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

  $latlons = array();
  $minmaxes = array('minlat' => 0, 'minlon' => 0, 'maxlat' => 0, 'maxlon' => 0);
  $ct = 0;
  if (count($locations)) {
    // we should loop over them and dump bummers with no lat/lon
    foreach ($locations AS $key => $location) {

      $lid = 0;
      if (module_exists('getlocations_fields')) {
        $lid = $location['glid'];
      }
      elseif (module_exists('location')) {
        $lid = $location['lid'];
      }
      // marker
      if ($type = getlocations_get_type_from_lid($lid)) {
        $marker = $options[$type . '_map_marker'];
      }
      else {
        $marker = $options['node_map_marker'];
      }
      if (isset($location['field_name']) && isset($options['node_marker_' . $location['field_name']])) {
        $marker = $options['node_marker_' . $location['field_name']];
      }
      if (getlocations_latlon_check($location['latitude'] . ',' . $location['longitude']) ) {
        $minmaxes = getlocations_do_minmaxes($ct, $location, $minmaxes);
        $ct++;
        $latlons[] = $location['latitude'] . ',' . $location['longitude'] . ',' . $lid . ',' . (isset($location['name']) && $location['name'] ? $location['name'] : (isset($location['title']) && $location['title'] ?  : '')    ) . ',' . $marker;
      }
    }
  }
  if ($ct < 2 ) {
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
