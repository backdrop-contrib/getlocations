<?php

/**
 * @file
 * getlocations_fields.admin.inc
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * getlocations_fields module administration functions.
 *
 */

/**
 * @param array $variables
 *
 * @return
 *   Returns $output
 *
 */
function theme_getlocations_fields_show($variables) {
  $locations = $variables['locations'];
  $settings = $variables['settings'];

  if ($settings['display_onemap']) {
    $minmaxes = array('minlat' => 0, 'minlon' => 0, 'maxlat' => 0, 'maxlon' => 0);
  }
  else {
    $minmaxes = '';
  }

  $output = '';
  $location_ct = 0;
  foreach ($locations AS $location) {
    $output .= '<div class="location vcard">';
    if (! empty($location['name']) && $settings['display_name']) {
      $output .= '<h4>' . $location['name'] . '</h4>';
    }
    $output .= '<div class="adr">';
    if (! empty($location['street']) && $settings['display_street'] ) {
      $output .= '<div class="street-address">' . $location['street'];
      if (! empty($location['additional']) && $settings['display_additional']) {
        $output .= ' ' . '<span class="extended-address">' . $location['additional'] . '</span>';
      }
      $output .= '</div>';
    }
    if (! empty($location['city']) && $settings['display_city']) {
      $output .= '<span class="locality">' . $location['city'] . '</span>';
      if (! empty($location['province']) && $settings['display_province']) {
        $output .= ",&nbsp;";
      }
      else {
        $output .= "&nbsp;";
      }
    }
    if (! empty($location['province']) && $settings['display_province']) {
      $output .= '<span class="region">' . $location['province'] . '</span>';
      if (! empty($location['postal_code']) && $settings['display_postal_code']) {
        $output .= "&nbsp;";
      }
    }
    if (! empty($location['postal_code']) && $settings['display_postal_code']) {
      $output .= '<span class="postal-code">' . backdrop_strtoupper($location['postal_code']) . '</span>';
    }
    if (! empty($location['country']) && $settings['display_country']) {
      if ($settings['country_full'] && backdrop_strlen($location['country']) == 2 ) {
        // this is a 2 letter code, we want the full name
        $countries = getlocations_get_countries_list();
        $country = $countries[$location['country']];
        if (empty($country)) {
          $country = $location['country'];
        }
      }
      else {
        $country = $location['country'];
      }
      $output .= '<div class="country-name">' . $country . '</div>';
    }
    $output .= '</div>';

    if (($location['phone'] && $settings['display_phone']) || ($location['mobile'] && $settings['display_mobile']) || ($location['fax'] && $settings['display_fax'])) {
      $output .= '<div class="phones">';
      if ($location['phone'] && $settings['display_phone']) {
        $output .= '<div class="phone"><span class="phone_label">' . t('Phone') . '</span>' . $location['phone'] . '</div>';
      }
      if ($location['mobile'] && $settings['display_mobile']) {
        $output .= '<div class="mobile"><span class="mobile_label">' . t('Mobile') . '</span>' . $location['mobile'] . '</div>';
      }
      if ($location['fax'] && $settings['display_fax']) {
        $output .= '<div class="fax"><span class="fax_label">' . t('Fax') . '</span>' . $location['fax'] . '</div>';
      }
      $output .= '</div>';
    }


    $output .= '</div>';

    // what3words
    $what3words_lic = getlocations_w3w_get_lic();
    if ($what3words_lic['key'] && isset($location['what3words']) && $location['what3words'] && $settings['what3words_display'] ) {
      $output .= '<div class="w3w"><span class="w3w_label">' . t('what3words') . ':</span>' . $location['what3words'] . '</div>';
    }

    if ($settings['display_latlong']) {
      $lat = $location['latitude'];
      $lng = $location['longitude'];
      if ($settings['display_geo_microformat'] > 0) {
        $lat_dms = theme('getlocations_latitude_dms', array('latitude' => $lat));
        $lng_dms = theme('getlocations_longitude_dms', array('longitude' => $lng));
        if ($settings['display_geo_microformat'] == 1) {
          $output .= '<div class="geo">';
          $output .= '<abbr class="latitude" title="' . $lat . '">' . $lat_dms . '</abbr> ';
          $output .= '<abbr class="longitude" title="' . $lng . '">' . $lng_dms . '</abbr>';
          $output .= '</div>';
        }
        else {
          $output .= '<div itemprop="geo" itemscope itemtype="http://schema.org/GeoCoordinates">';
          $output .= t('Latitude') . '&nbsp;' . $lat_dms . '<br />';
          $output .= t('Longitude') . '&nbsp;' . $lng_dms;
          $output .= '<meta itemprop="latitude" content="' . $lat . '" />';
          $output .= '<meta itemprop="longitude" content="' . $lng . '" />';
          $output .= '</div>';
        }
        $output .= '<br />';
      }
      else {
        if ($settings['display_dms']) {
          $lat = theme('getlocations_latitude_dms', array('latitude' => $lat));
          $lng = theme('getlocations_longitude_dms', array('longitude' => $lng));
        }
        $nomap = '';
        if (! $settings['display_showmap']) {
          $nomap = '_nomap';
        }
        $output .= '<div class="getlocations_fields_latlon_wrapper_themed' . $nomap . '">';
        $output .= '<div class="getlocations_fields_lat_wrapper_themed' . $nomap . '">';
        $output .= t('Latitude') . ":&nbsp;" . $lat . '</div>';
        $output .= '<div class="getlocations_fields_lon_wrapper_themed' . $nomap . '">';
        $output .= t('Longitude') . ":&nbsp;" . $lng . '</div>';
        $output .= '</div>';
        $output .= '<br />';

      }
    }

    // smuggle these in from location data
    // map_settings_allow
    if (isset($location['map_settings_allow'])) {
      $map_settings_allow = $location['map_settings_allow'];
    }
    else {
      $map_settings_allow = getlocations_fields_map_settings_allow();
    }
    if ($map_settings_allow) {
      if (isset($location['mapzoom']) && is_numeric($location['mapzoom'])) {
        $settings['nodezoom'] = $location['mapzoom'];
      }
      if (isset($location['map_maptype']) && $location['map_maptype']) {
        $settings['maptype'] = $location['map_maptype'];
      }
    }

    // streetview
    if (isset($location['streetview_settings_allow'])) {
      $streetview_settings_allow = $location['streetview_settings_allow'];
    }
    else {
      $streetview_settings_allow = getlocations_fields_streetview_settings_allow();
    }
    if ($streetview_settings_allow) {
      if (isset($location['sv_enable'])) {
        $settings['sv_enable'] = ($location['sv_enable'] == 1 ? 1 : 0);
      }
      if (isset($location['sv_showfirst'])) {
        $settings['sv_showfirst'] = ($location['sv_showfirst'] == 1 ? 1 : 0);
      }
      if (isset($location['sv_heading']) && is_numeric($location['sv_heading'])) {
        $settings['sv_heading'] = $location['sv_heading'];
      }
      if (isset($location['sv_zoom']) && is_numeric($location['sv_zoom'])) {
        $settings['sv_zoom'] = $location['sv_zoom'];
      }
      if (isset($location['sv_pitch']) && is_numeric($location['sv_pitch'])) {
        $settings['sv_pitch'] = $location['sv_pitch'];
      }
      $settings += getlocations_fields_get_display_settings($location);

    }
    else {
      $settings['sv_enable'] = 0;
      $settings['sv_showfirst'] = 0;
    }

    if ($location['longitude'] && $location['latitude']) {
      if ($settings['display_showmap']) {
        $name = htmlspecialchars_decode(isset($location['name']) && $location['name'] ? strip_tags($location['name']) : (isset($location['title']) && $location['title'] ? strip_tags($location['title']) : ''), ENT_QUOTES);
        $base = '';
        if ($location['nid']) {
          $base = 'nid';
        }
        elseif ($location['uid']) {
          $base = 'uid';
        }
        elseif ($location['tid']) {
          $base = 'tid';
        }
        elseif ($location['cid']) {
          $base = 'cid';
        }

        $marker = $settings['map_marker'];
        if ($base == 'nid') {
          // term markers, nodes only
          $marker = getlocations_get_term_marker($location['nid'], $marker);
        }

        // per location marker
        if (isset($location['marker']) && ! empty($location['marker'])) {
          $marker = $location['marker'];
        }
        // onemap
        if ($settings['display_onemap']) {
          $latlons[] = array($location['latitude'], $location['longitude'], $location['glid'], $name, $marker, $base, '', '');
          $minmaxes = getlocations_do_minmaxes($location_ct, $location, $minmaxes);
        }
        else {
          $latlons = array($location['latitude'], $location['longitude'], $location['glid'], $name, $marker, $base, '', '');
          $map = getlocations_fields_getmap_show($settings, $latlons);
          $output .= $map;
        }
      }
      else {
        if ($settings['display_maplink']) {
          if (count($locations) > 1 ) {
            $output .= '<p>' . l(t('Show on a map'), 'getlocations/lids/' . $location['glid']) . '</p>';
          }
          else {
            if ($location['nid']) {
              $output .= '<p>' . l(t('Show on a map'), 'getlocations/node/' . $location['nid']) . '</p>';
            }
            elseif ($location['uid']) {
              $output .= '<p>' . l(t('Show on a map'), 'getlocations/user/' . $location['uid']) . '</p>';
            }
            elseif ($location['tid']) {
              $output .= '<p>' . l(t('Show on a map'), 'getlocations/term/' . $location['tid']) . '</p>';
            }
            elseif ($location['cid']) {
              $output .= '<p>' . l(t('Show on a map'), 'getlocations/comment/' . $location['cid']) . '</p>';
            }
          }
        }
      }
      $location_ct++;
    }
  }
  // onemap
  if ($settings['display_showmap'] && $settings['display_onemap'] && isset($latlons)) {
    if ($location_ct < 2 ) {
      unset($minmaxes);
      $minmaxes = '';
    }
    $map = getlocations_fields_getmap_show($settings, $latlons, $minmaxes);
    $output .= $map;
  }

  return $output;

}


/**
 * @param array $variables
 *
 * @return
 *   Returns $output
 *
 */
function theme_getlocations_fields_field_settings_form($variables) {
  $form = $variables['form'];

  $output = '';

  // try table
  $header = array();
  $no_striping = TRUE;
  $rows = array(
    array('data' =>
      array(
        array('data' => $form['input_name_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['input_name_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['input_name_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['input_street_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['input_street_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['input_street_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),

    array('data' =>
      array(
        array('data' => $form['input_additional_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['input_additional_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['input_additional_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),

    array('data' =>
      array(
        array('data' => $form['input_city_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['input_city_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['input_city_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['input_province_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['input_province_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['input_province_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['input_postal_code_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['input_postal_code_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['input_postal_code_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['input_country_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['input_country_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['input_country_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),

    array('data' =>
      array(
        array('data' => $form['input_phone_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['input_phone_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['input_phone_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['input_mobile_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['input_mobile_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['input_mobile_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['input_fax_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['input_fax_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['input_fax_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['input_latitude_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['input_latitude_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => '', 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['input_longitude_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['input_longitude_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => '', 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),

  );
  $attributes = array('class' => array('getlocations_fields_input_table'));
  $table = theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => $attributes,
    )
  );
  $form['input_name_width'] = array('#markup' => $table);
  unset($form['input_name_required']);
  unset($form['input_name_weight']);
  unset($form['input_street_width']);
  unset($form['input_street_required']);
  unset($form['input_street_weight']);
  unset($form['input_additional_width']);
  unset($form['input_additional_required']);
  unset($form['input_additional_weight']);
  unset($form['input_city_width']);
  unset($form['input_city_required']);
  unset($form['input_city_weight']);
  unset($form['input_province_width']);
  unset($form['input_province_required']);
  unset($form['input_province_weight']);
  unset($form['input_postal_code_width']);
  unset($form['input_postal_code_required']);
  unset($form['input_postal_code_weight']);
  unset($form['input_country_width']);
  unset($form['input_country_required']);
  unset($form['input_country_weight']);
  unset($form['input_latitude_width']);
  unset($form['input_latitude_weight']);
  unset($form['input_longitude_width']);
  unset($form['input_longitude_weight']);
  unset($form['input_phone_width']);
  unset($form['input_phone_required']);
  unset($form['input_phone_weight']);
  unset($form['input_mobile_width']);
  unset($form['input_mobile_required']);
  unset($form['input_mobile_weight']);
  unset($form['input_fax_width']);
  unset($form['input_fax_required']);
  unset($form['input_fax_weight']);

  $prefix = '<fieldset class="form-wrapper">';
  $prefix .= '<legend><span class="fieldset-legend">' . t('Input form settings') . '</span></legend>';
  $prefix .= '<div class="fieldset-wrapper">';
  $prefix .= '<div class="fieldset-description">' . t('Configure the input form.') . '</div>';
  $form['use_address']['#prefix'] = $prefix;
  if (module_exists('countries')) {
    $form['only_countries']['#suffix'] = '</div></fieldset>';
  }
  else {
    $form['use_country_dropdown']['#suffix'] = '</div></fieldset>';
  }

  $prefix = '<fieldset class="form-wrapper">';
  $prefix .= '<legend><span class="fieldset-legend">' . t('Input map settings') . '</span></legend>';
  $prefix .= '<div class="fieldset-wrapper">';
  $prefix .= '<div class="fieldset-description">' . t('Configure the input map.') . '</div>';
  $form['input_map_show']['#prefix'] = $prefix;
  $form['draggable']['#suffix'] = '</div></fieldset>';

  if (isset($form['input_map_marker'])) {
    $link = getlocations_markerpicker_link($form['input_map_marker']['#id'], 'i');
    $form['input_map_marker']['#field_suffix'] = '&nbsp;' . $link;
  }

  $output .= backdrop_render_children($form);
  return $output;

}

/**
 * The display settings form
 *
 * @param array $variables
 *
 * @return
 *   Returns $output
 *
 */
function theme_getlocations_fields_field_formatter_settings_form($variables) {
  $form = $variables['form'];
  $output = '';
  $form['display_showmap']['#prefix'] = '<fieldset class="getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Address display settings') . '</span></legend><div class="fieldset-wrapper">';
  $form['display_fax']['#suffix'] = '</div></fieldset>';

  $form['sv_addresscontrol']['#prefix'] = '<fieldset class="getlocations_fieldset collapsible ' . (getlocations_fields_streetview_settings_allow() ? '' : 'collapsed') . ' form-wrapper"><legend><span class="fieldset-legend">' . t('Streetview overlay settings') . '</span></legend><div class="fieldset-wrapper">';
  $form['sv_clicktogo']['#suffix'] = '</div></fieldset>';

  $fieldsets = getlocations_settings_fieldsets($form);
  $form = array_merge($form, $fieldsets );

  $output .= backdrop_render_children($form);
  return $output;
}

/**
 * The input form
 *
 * @param array $variables
 *
 * @return
 *   Returns $output
 *
 */
function theme_getlocations_fields_field_widget_form($variables) {

  $form = $variables['form'];
  $output = '';

  $settings = $form['settings']['#value'];
  unset($form['settings']);
  $active = $form['active']['#value'];

  list($map, $mapid) = getlocations_fields_getmap($settings, $active);

  // attributes
  $fieldlist = array(
    'name', 'street', 'additional', 'city', 'province', 'postal_code', 'country', 'latitude', 'longitude',
    'mapzoom', 'sv_heading', 'sv_zoom', 'sv_pitch', 'map_maptype', 'sv_enable', 'sv_showfirst'
  );
  foreach ($fieldlist AS $field) {
    if (isset($form[$field])) {
      $form[$field]['#attributes'] = array('class' => array('getlocations_' . $field . '_' . $mapid));
    }
  }
  if (isset($form['address'])) {
    $form['address']['#attributes'] = array('id' => ($active ? 'getlocations_address_' . $mapid : 'getlocations_default_address'), 'placeholder' => t('Enter an address'));
  }

  if ($mapid !== NULL && isset($form['geobutton']) ) {
    $geobutton = '<p><input type="button" value="' . t('Geocode this address') . '" title="' . t('Get the latitude and longitude for this address') . '" id="getlocations_geocodebutton_' . $mapid . '" class="form-submit" /></p>';
    $form['geobutton']['#markup'] = $geobutton;
  }

  if ($mapid !== NULL && isset($form['smart_ip_button']) && module_exists('smart_ip')) {
    $smart_ip_button = '<p><input type="button" value="' . t('Use current user position') . '" title="' . t('Get the latitude and longitude for this address from the user IP') . '" id="getlocations_smart_ip_button_' . $mapid . '" class="form-submit" /></p>';
    $form['smart_ip_button']['#markup'] = $smart_ip_button;
  }
  // html5 and google
  if (getlocations_is_mobile() && $mapid !== NULL && isset($form['geolocation_button'])) {
    $geolocation_button = '<p><input type="button" value="' . t('Find Location') . '" title="' . t('Get the latitude and longitude for this address from the browser') . '" id="getlocations_geolocation_button_' . $mapid . '" class="form-submit" />&nbsp;<span id="getlocations_geolocation_status_' . $mapid . '" ></span></p>';
    $geolocation_button .= '<p>Use the browser to find your current location</p>';
    $form['geolocation_button']['#markup'] = $geolocation_button;
  }

  // Clear button
  if (isset($form['clear_button'])) {
    $clear_button = '<p><input type="button" value="' . t('Clear') . '" title="' . t('Clear the address on the form') . '" id="getlocations_clear_button_' . $mapid . '" class="form-submit" /></p>';
    $form['clear_button']['#markup'] = $clear_button;
  }

  $form['latitude']['#prefix'] = '<div class="getlocations_fields_latlon_wrapper clearfix"><div class="getlocations_fields_lat_wrapper">';
  $form['latitude']['#suffix'] = '</div>';
  $form['longitude']['#prefix'] = '<div class="getlocations_fields_lon_wrapper">';
  $form['longitude']['#suffix'] = '</div></div>';

  if (isset($form['marker']) && $form['marker']['#type'] != 'value') {
    // colorbox marker
    $link = getlocations_markerpicker_link($form['marker']['#id'], 'i');
    $form['marker']['#field_suffix'] = '&nbsp;' . $link;
    $form['marker']['#prefix'] = '<div class="getlocations_fields_marker_wrapper">';
    $form['marker']['#suffix'] = '</div>';
  }

  $form['city']['#prefix'] = '<div class="getlocations_fields_city_wrapper">';
  $form['city']['#suffix'] = '</div>';
  $form['province']['#prefix'] = '<div class="getlocations_fields_province_wrapper">';
  $form['province']['#suffix'] = '</div>';
  $form['country']['#prefix'] = '<div class="getlocations_fields_country_wrapper">';
  if (isset($form['country_display'])) {
    $form['country_display']['#suffix'] = '</div>';
  }
  else {
    $form['country']['#suffix'] = '</div>';
  }


  $msg = t('To use the map to find a location, drag the marker or click on the map.');
  if (isset($settings['map_settings_allow'])) {
    $map_settings_allow = $settings['map_settings_allow'];
  }
  else {
    $map_settings_allow = getlocations_fields_map_settings_allow();
  }
  if ($map_settings_allow) {
    $msg .= '<br />' . t('You can also set the map type and zoom');
  }
  if (! $active) {
    $msg =  t('A preview of the current map settings.') . '<br />' . t('You can adjust the Map center, Zoom and map type by changing the map.') . '<br />' . t('For all other changes use the form. Remember to Save when you are done.');
  }
  $form['map']['#prefix'] = '<div class="getlocations_fields_map_wrapper">';
  $form['map']['#suffix'] = '</div>';
  if ($settings['use_address'] < 1) {
    $form['map']['#markup'] = '<p>' . t('If you leave the address empty you can Geocode by moving the marker on the map') . '</p>';
  }
  else {
    $form['map']['#markup'] = '';
  }
  $form['map']['#markup'] .= '<p>' . $msg . '</p><div class="getlocations_fields_map">' . $map . '</div>';

  if (isset($settings['streetview_settings_allow'])) {
    $streetview_settings_allow = $settings['streetview_settings_allow'];
  }
  else {
    $streetview_settings_allow = getlocations_fields_streetview_settings_allow();
  }

  if ($active && $streetview_settings_allow) {
    $form['map']['#markup'] .= '<div id="getlocations_streetview_setup_' . $mapid . '">';
    $form['map']['#markup'] .= '<input type="button" value="' . t('Streetview Setup') . '" title="' . t('Configure streetview heading, zoom and pitch for this map.') . '" id="getlocations_streetview_setupbutton_' . $mapid . '" class="form-submit" />';
    $form['map']['#markup'] .= '</div>';
  }

  // wrap 'fake' required in a div
  if ($mapid !== NULL && isset($form['getlocations_required'])) {
    $requireds = explode(',', $form['getlocations_required']['#value']);
    foreach ($requireds AS $id) {
      $form[$id]['#prefix'] = '<div class="getlocations_required_' . $id . '_' . $mapid . '">';
      $form[$id]['#suffix'] = '</div>';
    }
    unset($form['getlocations_required']);
  }

  $output .= backdrop_render_children($form);
  return $output;

}

/**
 * The settings form
 *
 * @param array $variables
 *
 * @return
 *   Returns $output
 *
 */
function theme_getlocations_fields_settings_form($variables) {
  $form = $variables['form'];

  $output = '';

  // try table
  $header = array();
  $no_striping = TRUE;
  $rows = array(
    array('data' =>
      array(
        array('data' => $form['getlocations_fields_defaults']['input_name_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['getlocations_fields_defaults']['input_name_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['getlocations_fields_defaults']['input_name_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['getlocations_fields_defaults']['input_street_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['getlocations_fields_defaults']['input_street_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['getlocations_fields_defaults']['input_street_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['getlocations_fields_defaults']['input_additional_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['getlocations_fields_defaults']['input_additional_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['getlocations_fields_defaults']['input_additional_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['getlocations_fields_defaults']['input_city_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['getlocations_fields_defaults']['input_city_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['getlocations_fields_defaults']['input_city_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['getlocations_fields_defaults']['input_province_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['getlocations_fields_defaults']['input_province_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['getlocations_fields_defaults']['input_province_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['getlocations_fields_defaults']['input_postal_code_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['getlocations_fields_defaults']['input_postal_code_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['getlocations_fields_defaults']['input_postal_code_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['getlocations_fields_defaults']['input_country_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['getlocations_fields_defaults']['input_country_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['getlocations_fields_defaults']['input_country_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),

    array('data' =>
      array(
        array('data' => $form['getlocations_fields_defaults']['input_phone_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['getlocations_fields_defaults']['input_phone_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['getlocations_fields_defaults']['input_phone_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['getlocations_fields_defaults']['input_mobile_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['getlocations_fields_defaults']['input_mobile_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['getlocations_fields_defaults']['input_mobile_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['getlocations_fields_defaults']['input_fax_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['getlocations_fields_defaults']['input_fax_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => $form['getlocations_fields_defaults']['input_fax_required'], 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['getlocations_fields_defaults']['input_latitude_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['getlocations_fields_defaults']['input_latitude_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => '', 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),
    array('data' =>
      array(
        array('data' => $form['getlocations_fields_defaults']['input_longitude_width'], 'class' => array('getlocations_fields_input_cell1')),
        array('data' => $form['getlocations_fields_defaults']['input_longitude_weight'], 'class' => array('getlocations_fields_input_cell2')),
        array('data' => '', 'class' => array('getlocations_fields_input_cell3')),
      ),
      'no_striping' => $no_striping,
    ),

  );
  $attributes = array('class' => array('getlocations_fields_input_table'));
  $table = theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => $attributes,
    )
  );
  $form['getlocations_fields_defaults']['input_name_width'] = array('#markup' => $table);
  unset($form['getlocations_fields_defaults']['input_name_required']);
  unset($form['getlocations_fields_defaults']['input_name_weight']);
  unset($form['getlocations_fields_defaults']['input_street_width']);
  unset($form['getlocations_fields_defaults']['input_street_required']);
  unset($form['getlocations_fields_defaults']['input_street_weight']);
  unset($form['getlocations_fields_defaults']['input_additional_width']);
  unset($form['getlocations_fields_defaults']['input_additional_required']);
  unset($form['getlocations_fields_defaults']['input_additional_weight']);
  unset($form['getlocations_fields_defaults']['input_city_width']);
  unset($form['getlocations_fields_defaults']['input_city_required']);
  unset($form['getlocations_fields_defaults']['input_city_weight']);
  unset($form['getlocations_fields_defaults']['input_province_width']);
  unset($form['getlocations_fields_defaults']['input_province_required']);
  unset($form['getlocations_fields_defaults']['input_province_weight']);
  unset($form['getlocations_fields_defaults']['input_postal_code_width']);
  unset($form['getlocations_fields_defaults']['input_postal_code_required']);
  unset($form['getlocations_fields_defaults']['input_postal_code_weight']);
  unset($form['getlocations_fields_defaults']['input_country_width']);
  unset($form['getlocations_fields_defaults']['input_country_required']);
  unset($form['getlocations_fields_defaults']['input_country_weight']);
  unset($form['getlocations_fields_defaults']['input_latitude_width']);
  unset($form['getlocations_fields_defaults']['input_latitude_weight']);
  unset($form['getlocations_fields_defaults']['input_longitude_width']);
  unset($form['getlocations_fields_defaults']['input_longitude_weight']);
  unset($form['getlocations_fields_defaults']['input_phone_width']);
  unset($form['getlocations_fields_defaults']['input_phone_required']);
  unset($form['getlocations_fields_defaults']['input_phone_weight']);
  unset($form['getlocations_fields_defaults']['input_mobile_width']);
  unset($form['getlocations_fields_defaults']['input_mobile_required']);
  unset($form['getlocations_fields_defaults']['input_mobile_weight']);
  unset($form['getlocations_fields_defaults']['input_fax_width']);
  unset($form['getlocations_fields_defaults']['input_fax_required']);
  unset($form['getlocations_fields_defaults']['input_fax_weight']);

  $prefix = '<fieldset class="collapsible form-wrapper">';
  $prefix .= '<legend><span class="fieldset-legend">' . t('Default Input form settings') . '</span></legend>';
  $prefix .= '<div class="fieldset-wrapper">';
  $prefix .= '<div class="fieldset-description">' . t('Configure the default input form.') . '</div>';
  $form['getlocations_fields_defaults']['use_address']['#prefix'] = $prefix;
  $form['getlocations_fields_defaults']['use_country_dropdown']['#suffix'] = '</div></fieldset>';

  $prefix = '<fieldset class="collapsible form-wrapper">';
  $prefix .= '<legend><span class="fieldset-legend">' . t('Default Address display settings') . '</span></legend>';
  $prefix .= '<div class="fieldset-wrapper">';
  $prefix .= '<div class="fieldset-description">' . t('Configure the default address display.') . '</div>';
  $form['getlocations_fields_defaults']['display_showmap']['#prefix'] = $prefix;
  $form['getlocations_fields_defaults']['display_fax']['#suffix'] = '</div></fieldset>';

  $output .= backdrop_render_children($form);
  return $output;

}

function theme_getlocations_fields_distance($variables) {
  $distance = $variables['distance'];
  $shortunit = $variables['shortunit'];
  // also available
  // $longunit = $variables['longunit'];
  $output = '';
  $output .= number_format($distance, 2) . ' ' . $shortunit;
  return $output;
}

/**
 * Theme preprocess function for getlocations_fields_distance.
 */
function template_preprocess_getlocations_fields_distance(&$variables) {
  $units = $variables['units'];
  unset($variables['units']);
  $variables['shortunit'] = $units;
  $variables['longunit'] = getlocations_get_unit_names($units, 'plurals');
  $variables['distance'] = (float)$variables['distance'];
}
