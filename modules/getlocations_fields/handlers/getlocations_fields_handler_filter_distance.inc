<?php
/**
 * @file
 * Views 3 support for getlocations_fields.
 */

// TODO EXPOSED FORM, distance

/**
 * General proximity filter for location latitude/longitude.
 */
class getlocations_fields_handler_filter_distance extends views_handler_filter {
  // This is always multiple, because we can have distance, units etc.
  var $always_multiple = TRUE;

  function option_definition() {
    $options = parent::option_definition();
    $options['operator'] = array('default' => 'mbr');

    $options['identifier'] = array('default' => 'distance');

    $options['origin'] = array('default' => 'nid_arg');

    $options['value'] = array(
      'default' => array(
        'latitude' => '',
        'longitude' => '',
#        'postal_code' => '',
#        'country' => '',
        'php_code' => '',
        'nid_arg' => '',
        'nid_loc_field' => 'node',
        'uid_arg' => '',
        'uid_loc_field' => 'user',
        'search_distance' => 100,
        'search_units' => 'km',
      ),
    );

#    $options['expose']['contains']['gmap_macro'] = array('default' => '[gmap ]');
#    $options['expose']['contains']['user_location_choose'] = array('default' => FALSE);

    return $options;
  }

  function admin_summary() {
    return '';
  }

  function operator_options() {
    return array(
      'mbr' => t('Proximity (Rectangular)'),
      'dist' => t('Proximity (Circular)'),
    );
  }
  // TODO
  function expose_options() {
    parent::expose_options();
#    $this->options['expose']['gmap_macro'] = array('default' => '[gmap ]');
#    $this->options['expose']['user_location_choose'] = array('default' => FALSE);
    $this->options['expose']['search_units'] = array('default' => 'km');
    $this->options['expose']['search_distance'] = array('default' => 10);
  }

  function expose_form_left(&$form, &$form_state) {
    parent::expose_form_left($form, $form_state);
    // @@@ Todo: autohide this.
#    $form['expose']['gmap_macro'] = array(
#      '#parents' => array('options', 'gmap_macro'),
#      '#type' => 'textfield',
#      '#title' => t('GMap macro'),
#      '#description' => t('The macro to use for the Latitude / Longitude map, if applicable.'),
#      '#default_value' => $this->options['expose']['gmap_macro'],
#    );
#
#    $form['expose']['user_location_choose'] = array(
#      '#type' => 'checkbox',
#      '#title' => t("Allow choice of user location"),
#      '#default_value' => $this->options['expose']['user_location_choose'],
#      '#description' => t("If checked and using a user location origin, the user will be able to choose which of their locations to use.  Otherwise their first location will be used."),
#    );

    $form['expose']['search_units'] = getlocations_fields_element_distance_unit($this->options['expose']['search_units']);
    $form['expose']['search_distance'] = getlocations_fields_element_search_distance($this->options['expose']['search_distance']);

  }

  function value_form(&$form, &$form_state) {

    $form['origin'] = getlocations_fields_element_origin($this->options['origin']);

    if (!empty($form_state['exposed'])) {
      $identifier = $this->options['expose']['identifier'];
      if (! isset($form_state['input'][$identifier])) {
        // We need to pretend the user already inputted the defaults, because
        // fapi will malfunction otherwise.
        $form_state['input'][$identifier] = $this->value;
      }
    }

    $form['value'] = array(
      '#tree' => TRUE,
    );
    $form['value']['latitude'] = getlocations_fields_element_latitude($this->value['latitude']);
    $form['value']['longitude'] = getlocations_fields_element_longitude($this->value['longitude']);
    #$form['value']['postal_code'] = getlocations_fields_element_postal_code($this->value['postal_code']);
    #$form['value']['country'] = getlocations_fields_element_country($this->value['country']);
    $form['value']['php_code'] = getlocations_fields_element_php_code($this->value['php_code']);

    list($nid_argument_options, $uid_argument_options, $tid_argument_options) = getlocations_fields_views_proximity_get_argument_options($this->view);
    $loc_field_options = getlocations_fields_views_proximity_get_location_field_options();
    if ($nid_argument_options) {
      $form['value']['nid_arg'] = getlocations_fields_element_nid_arg($this->value['nid_arg'], $nid_argument_options);
      $form['value']['nid_loc_field'] = getlocations_fields_element_nid_loc_field($this->value['nid_loc_field'], $loc_field_options);
    }
    if ($uid_argument_options) {
      $form['value']['uid_arg'] = getlocations_fields_element_uid_arg($this->value['uid_arg'], $uid_argument_options);
      $form['value']['uid_loc_field'] = getlocations_fields_element_uid_loc_field($this->value['uid_loc_field'], $loc_field_options);
    }

    $form['value']['search_units'] = getlocations_fields_element_distance_unit($this->value['search_units']);
    $form['value']['search_distance'] = getlocations_fields_element_search_distance($this->value['search_distance']);

  }
  // TODO
  function exposed_form(&$form, &$form_state) {
    parent::exposed_form($form, $form_state);
    $key = $this->options['expose']['identifier'];
    $origin = $this->options['origin'];

    // Strip dependencies off on exposed form.
    foreach (element_children($form[$key]) as $el) {
      if (!empty($form[$key][$el]['#dependency'])) {
        $form[$key][$el]['#dependency'] = array();
      }
    }
      #    if ($origin == 'latlon_gmap' && module_exists('gmap')) {
      #      // Bad things happen if we try to show a gmap in the views live preview.
      #      if (!empty($form_state['view']->live_preview)) {
      #        $form[$key]['proximity_map'] = array(
      #          '#markup' => t('Gmap location selection is not available during live preview.'),
      #          '#weight' => 0,
      #        );
      #      }
      #      else {
      #        $form[$key]['proximity_map'] = array(
      #          '#markup' => gmap_set_location($this->options['expose']['gmap_macro'], $form[$key], array('latitude' => 'latitude', 'longitude' => 'longitude')),
      #          '#weight' => 0,
      #        );
      #      }
      #    }
      #    elseif (($origin == 'user' || $origin == 'hybrid') && $this->options['expose']['user_location_choose']) {
      #      global $user;
      #      $user_locations = isset($user->locations) ? $user->locations : getlocations_load_locations($user->uid, 'uid');
      #      $location_options = array();
      #      if (!empty($user_locations)) {
      #        foreach ($user_locations as $i => $location) {
      #          if (isset($location['latitude']) && isset($location['longitude'])) {
      #            if (!empty($location['name'])) {
      #              $location_options[$i] = t(check_plain($location['name']));
      #            }
      #            else {
      #              $location_options[$i] = t('Location #@num', array('@num' => $i + 1));
      #            }
      #          }
      #        }
      #      }

      #      $form[$key]['user_location_delta'] = array(
      #        '#type' => 'select',
      #        '#title' => t('Location'),
      #        '#options' => $location_options,
      #        '#description' => t('Select which of your locations to use.'),
      #        '#weight' => 0,
      #      );
      #    }
      #
      #    // Remove unneeded fields when exposing the form.
      #    // It's shorter than redefining value_form.
      #    if ($origin != 'static' && $origin != 'latlon_gmap') {
    unset($form[$key]['latitude']);
    unset($form[$key]['longitude']);
      #    }
      #    if ($origin != 'postal' && $origin != 'postal_default') {
      #      unset($form[$key]['postal_code']);
      #    }
      #    if ($origin != 'postal') {
      #      unset($form[$key]['country']);
      #    }
      #

    // And we definitely do not want to expose the php code option when exposing the filter
    unset($form[$key]['php_code']);
    // The nid/uid arg options are not useful on an exposed form.
    unset($form[$key]['nid_arg']);
    unset($form[$key]['nid_loc_field']);
    unset($form[$key]['uid_arg']);
    unset($form[$key]['uid_loc_field']);
    unset($form['origin']);
  }

  function query() {

    if (empty($this->value)) {
      return;
    }

    // We need to merge with $this->options['value'] for filter values
    // and $this->value for exposed filter values.
    $options = array_merge($this->options, $this->options['value'], $this->value);
    $coordinates = getlocations_fields_views_proximity_get_reference_location($this->view, $options);
    // If we don't have any coordinates or distance, there's nothing to filter
    // by, so don't modify the query at all.
    if (empty($coordinates) || empty($this->value['search_distance'])) {
      return;
    }

    $this->ensure_my_table();

    $lat = $coordinates['latitude'];
    $lon = $coordinates['longitude'];

    $distance_meters = getlocations_fields_convert_distance_to_meters($this->value['search_distance'], $this->value['search_units']);
    $latrange = getlocations_fields_earth_latitude_range($lon, $lat, $distance_meters);
    $lonrange = getlocations_fields_earth_longitude_range($lon, $lat, $distance_meters);

    // Add MBR check (always).
    // In case we go past the 180/-180 mark for longitude.
    if ($lonrange[0] > $lonrange[1]) {
      #$where = "$this->table_alias.latitude > :minlat AND $this->table_alias.latitude < :maxlat AND (($this->table_alias.longitude < 180 AND $this->table_alias.longitude > :minlon) OR ($this->table_alias.longitude < :maxlon AND $this->table_alias.longitude > -180))";
      $where = $this->table_alias . ".latitude > :minlat
      AND " . $this->table_alias . ".latitude < :maxlat
      AND ((" . $this->table_alias . ".longitude < 180
      AND " . $this->table_alias . ".longitude > :minlon)
      OR (" . $this->table_alias . ".longitude < :maxlon
      AND " . $this->table_alias . ".longitude > -180))";
    }
    else {
      #$where = "$this->table_alias.latitude > :minlat AND $this->table_alias.latitude < :maxlat AND $this->table_alias.longitude > :minlon AND $this->table_alias.longitude < :maxlon";
      $where = $this->table_alias . ".latitude > :minlat
      AND " . $this->table_alias . ".latitude < :maxlat
      AND " . $this->table_alias . ".longitude > :minlon
      AND " . $this->table_alias . ".longitude < :maxlon";
    }
    $this->query->add_where_expression($this->options['group'], $where, array(':minlat' => $latrange[0], ':maxlat' => $latrange[1], ':minlon' => $lonrange[0], ':maxlon' => $lonrange[1]));
    if ($this->operator == 'dist') {
      // Add radius check.
      $this->query->add_where_expression($this->options['group'], getlocations_fields_earth_distance_sql($lat, $lon, $this->table_alias) . ' < :distance', array(':distance' => $distance_meters));
    }
  }
}
