<?php

/**
 * @file
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
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
      // default marker
      $marker = $options['node_map_marker'];
      // per type markers
      $getlocations_node_marker = variable_get('getlocations_node_marker', array('enable' => 0));
      if ($getlocations_node_marker['enable']) {
        if (isset($location['type'])) {
          if ($types = getlocations_get_types()) {
            foreach ($types AS $type => $name) {
              if ($type == $location['type']) {
                $mkey = 'node_marker__' . $type;
                if (isset($options[$mkey])) {
                  $marker = $options[$mkey];
                }
              }
            }
          }
        }
      }

      if (isset($location['uid'])) {
        $marker = $getlocations_defaults['user_map_marker'];
      }
      if (isset($location['marker']) && ! empty($location['marker'])) {
        $marker = $location['marker'];
      }
      if (getlocations_latlon_check($location['latitude'] . ',' . $location['longitude']) ) {
        $minmaxes = getlocations_do_minmaxes($ct, $location, $minmaxes);
        $ct++;
        $name = htmlspecialchars_decode(isset($location['name']) && $location['name'] ? strip_tags($location['name']) : (isset($location['title']) && $location['title'] ? strip_tags($location['title']) : ''), ENT_QUOTES);
        $latlons[] = array($location['latitude'], $location['longitude'], $location['lid'], $name, $marker, $base_field, $custom_content);
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

  $variables['map']  = theme('getlocations_show', $newdefaults['width'], $newdefaults['height'], $newdefaults, $mapid, '', '');

}


