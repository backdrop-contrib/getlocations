<?php

/**
 * @file
 * @author Bob Hutchinson http://backdrop.org/user/52366
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
        'uses row plugin' => FALSE,
        'uses grouping' => FALSE,
        'uses options' => TRUE,
        'type' => 'normal',
        'uses fields' => TRUE,
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
  $thiskey = FALSE;

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
      if ($lid > 0) {
        if ($entity_type == 'node') {
          $marker = $options['node_map_marker'];
          #if (isset($location['type']) && isset($location['field_name']) ) {
          #  if (isset($options['node_marker__' . backdrop_strtolower($location['type']) . '__' . $location['field_name']])) {
          #    $marker = $options['node_marker__' . backdrop_strtolower($location['type']) . '__' . $location['field_name']];
          #  }
          #}
          // term marker
          #$getlocations_term_marker = config_get('getlocations_term_marker', array('enable' => 0, 'vids' => 0, 'max_depth' => ''));
          #if ($getlocations_term_marker['enable'] && $getlocations_term_marker['vids']) {
          #  $vids = $getlocations_term_marker['vids'];
          #  foreach ($vids AS $vid) {
          #    if ($nid = getlocations_get_nid_from_lid($lid)) {
          #      $query = db_select('taxonomy_index', 't');
          #      $query->fields('t', array('tid'));
          #      $query->join('taxonomy_term_data', 'd', 't.tid=d.tid');
          #      $query->condition('t.nid', $nid);
          #      $query->condition('d.vid', $vid);
          #      $result = $query->execute()->fetchObject();
          #      if (isset($result->tid) && $result->tid > 0 && isset($options['term_marker_' . $result->tid])) {
          #        $marker = $options['term_marker_' . $result->tid];
          #      }
          #    }
          #  }
          #}
        }
        elseif ($entity_type == 'taxonomy_term') {
          $marker = $options['vocabulary_map_marker'];
          if (isset($location['field_name']) && ! empty($location['field_name']) ) {
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
                $config_type = config("config_type." . $cat);
                $cats[$cat] = $config_type->get('name');
              }
            }
            elseif ($options['category_method'] == 2) {
              // term_reference_field
              if (isset($location[$options['category_term_reference_field']])) {
                $label = $location[$options['category_term_reference_field']];
                $cat = preg_replace("/\s+/", "_", $label);
                $cat = preg_replace("/'/", "", $cat);
                $cat = backdrop_strtolower($cat);
                $cats[$cat] = $label;
              }
            }
            if ($cat) {
              $options['categories'] = $cats;
            }
          }
          $latlons[$ct] = array($location['latitude'], $location['longitude'], $lid, $name, $marker, $base_field, $custom_content, $cat);
          // special case for ajax, a custom content field containing the key of the map associated with an exposed form
          $thiskey = FALSE;
          if (isset($location['nothing']) && preg_match("/^key_/", $location['nothing'])) {
            $thiskey = trim($location['nothing']);
          }

          $ct++;
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

#  if (! isset($newdefaults['polygons_group']) ) {
#    $shapes = config_get("getlocations_fields.shapes", "shapes");
#    $newdefaults += $shapes;
#  }

  if (! isset($newdefaults['sv_showfirst'])) {

    $getlocations_fields_defaults = getlocations_fields_defaults();
    $newdefaults['sv_showfirst'] = $getlocations_fields_defaults['sv_showfirst'];
    $newdefaults['sv_heading'] = $getlocations_fields_defaults['sv_heading'];
    $newdefaults['sv_zoom'] = $getlocations_fields_defaults['sv_zoom'];
    $newdefaults['sv_pitch'] = $getlocations_fields_defaults['sv_pitch'];
  }

#  if (! isset($newdefaults['sv_group'])) {
#    $sv = config_get("getlocations_fields.sv", "settings");
#    $newdefaults += $sv;
#  }

  $mapid = getlocations_setup_map($newdefaults);
  if ($thiskey) {
    $mapid = $thiskey;
  }

  getlocations_js_settings_do($newdefaults, $latlons, $minmaxes, $mapid);

  // show_search_distance
  if (isset($variables['view']->exposed_data['distance']) && isset($variables['view']->exposed_data['distance']['latitude']) && $variables['view']->exposed_data['distance']['latitude'] && isset($variables['view']->exposed_data['distance']['longitude']) && $variables['view']->exposed_data['distance']['longitude'] && $variables['view']->exposed_data['distance']['search_distance']) {
    $newdefaults['search_dist_info'] = $variables['view']->exposed_data['distance'];
  }

  $variables['map']  = theme('getlocations_show', array('width' => $newdefaults['width'], 'height' => $newdefaults['height'], 'defaults' => $newdefaults, 'mapid' => $mapid, 'latlons' => $latlons, 'minmaxes' => $minmaxes, 'type' => '', 'node' => ''));

}
