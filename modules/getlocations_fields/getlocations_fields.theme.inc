<?php

/**
 * @file
 * getlocations_field module theming functions.
 * using version 3 googlemaps API
 */


/**
 * Implements hook_theme().
 *
 * This lets us tell Drupal about our theme functions and their arguments.
 */
function getlocations_fields_theme() {

  return array(
    'getlocations_fields_show' => array(
      'variables' => array(
        'locations' => '',
        'settings' => '',
      ),
    ),
    'getlocations_fields_latitude_dms' => array(
      'variables' => array(
        'latitude' => '',
      ),
    ),
    'getlocations_fields_longitude_dms' => array(
      'variables' => array(
        'longitude' => '',
      ),
    ),
    'getlocations_fields_field_settings_form' => array(
      'render element' => 'form',
    ),
    'getlocations_fields_field_formatter_settings_form' => array(
      'render element' => 'form',
    ),
    'getlocations_fields_field_widget_form' => array(
      'render element' => 'form',
    ),
    'getlocations_fields_settings_form' => array(
      'render element' => 'form',
    ),
  );

}

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
  $output = '';
  foreach ($locations AS $location) {
    $output .= '<div class="location vcard">';
    if (! empty($location['name']) && $settings['display_name']) {
      $output .= '<h4>' . $location['name'] . '</h4>';
    }
    $output .= '<div class="adr">';
    if (! empty($location['street']) && $settings['display_street'] ) {
      $output .= '<div class="street-address">' . $location['street'];
      if (! empty($location['additional']) && $settings['display_additional']) {
        $output .= ' ' . $location['additional'];
      }
      $output .= '</div>';
    }
    if (! empty($location['city']) && $settings['display_city']) {
      $output .= '<span class="locality">' . $location['city'] . ' </span>';
      if (! empty($location['province']) && $settings['display_province']) {
        $output .= ",&nbsp;";
      }
    }
    if (! empty($location['province']) && $settings['display_province']) {
      $output .= '<span class="region">' . $location['province'] . ' </span>';
    }
    if (! empty($location['postal_code']) && $settings['display_postal_code']) {
      $output .= '<span class="postal-code">' . drupal_strtoupper($location['postal_code']) . ' </span>';
    }
    if (! empty($location['country']) && $settings['display_country']) {
      if ($settings['country_full'] && strlen($location['country']) == 2 ) {
        // this is a 2 letter code, we want the full name
        $countries = getlocations_fields_get_countries_list();
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
    $output .= '</div>';

    if ($settings['display_latlong']) {
      $lat = $location['latitude'];
      $lng = $location['longitude'];
      if ($settings['display_dms']) {
        $lat = theme('getlocations_fields_latitude_dms', array('latitude' => $lat));
        $lng = theme('getlocations_fields_longitude_dms', array('longitude' => $lng));
      }
      $output .= '<div id="getlocations_fields_latlon_wrapper_themed">';
      $output .= '<div id="getlocations_fields_lat_wrapper_themed">';
      $output .= t('Latitude') . ': ' . $lat . '</div>';
      $output .= '<div id="getlocations_fields_lon_wrapper_themed">';
      $output .= t('Longitude') . ': ' . $lng . '</div>';
      $output .= '</div>';
      $output .= '<br />';
    }

    if ($settings['display_showmap'] && $location['longitude'] && $location['latitude']) {
      $a = $location['latitude'] . "," . $location['longitude'] . "," . $location['glid'] . "," . $location['name'] . ',' . $settings['map_marker'];
      $map = getlocations_fields_getmap_show($settings, $a);
      $output .= $map;
    }
    else {
      if ($location['nid']) {
        $output .= '<p>' . l(t('Show on a map'), 'getlocations/node/' . $location['nid']) . '</p>';
      }
      elseif ($location['uid']) {
        $output .= '<p>' . l(t('Show on a map'), 'getlocations/user/' . $location['uid']) . '</p>';
      }
    }
  }

  return $output;

}

/**
 * Display a coordinate.
 * from location module
 */
/**
 * @param array $variables
 *
 * @return
 *   Returns $output
 *
 */
function theme_getlocations_fields_latitude_dms($variables) {
  $latitude = $variables['latitude'];
  $output = '';
  list($degrees, $minutes, $seconds, $negative) = getlocations_fields_dd_to_dms($latitude);
  $output .= "${degrees}° ${minutes}' ${seconds}\" ";
  if (!$negative) {
    $output .= 'N';
  }
  else {
    $output .= 'S';
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
function theme_getlocations_fields_longitude_dms($variables) {
  $longitude = $variables['longitude'];
  $output = '';
  list($degrees, $minutes, $seconds, $negative) = getlocations_fields_dd_to_dms($longitude);
  $output .= "${degrees}° ${minutes}' ${seconds}\" ";
  if (!$negative) {
    $output .= 'E';
  }
  else {
    $output .= 'W';
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
  $prefix = '<fieldset class="form-wrapper">';
  $prefix .= '<legend><span class="fieldset-legend">' . t('Enable map types') . '</span></legend>';
  $prefix .= '<div class="fieldset-wrapper">';
  $prefix .= '<div class="fieldset-description">' . t( 'Select which maps you want to be available.') . '</div>';
  $form['baselayers']['Map']['#prefix'] = $prefix;
  $form['baselayers']['Physical']['#suffix'] = '</div></fieldset>';

  $prefix = '<fieldset class="form-wrapper">';
  $prefix .= '<legend><span class="fieldset-legend">' . t('Input form settings') . '</span></legend>';
  $prefix .= '<div class="fieldset-wrapper">';
  $prefix .= '<div class="fieldset-description">' . t('Configure the input form.') . '</div>';
  $form['use_address']['#prefix'] = $prefix;
  $form['use_country_dropdown']['#suffix'] = '</div></fieldset>';

  $prefix = '<fieldset class="form-wrapper">';
  $prefix .= '<legend><span class="fieldset-legend">' . t('Input map settings') . '</span></legend>';
  $prefix .= '<div class="fieldset-wrapper">';
  $prefix .= '<div class="fieldset-description">' . t('Configure the input map.') . '</div>';
  $form['mapwidth']['#prefix'] = $prefix;
  $form['draggable']['#suffix'] = '</div></fieldset>';

  $output .= drupal_render_children($form);
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
  $prefix = '<fieldset class="form-wrapper">';
  $prefix .= '<legend><span class="fieldset-legend">' . t('Enable map types') . '</span></legend>';
  $prefix .= '<div class="fieldset-wrapper">';
  $prefix .= '<div class="fieldset-description">Select which maps you want to be available.</div>';
  $form['baselayers']['Map']['#prefix'] = $prefix;
  $form['baselayers']['Physical']['#suffix'] = '</div></fieldset>';

  $form['display_showmap']['#prefix'] = '<fieldset class="getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Address display settings') . '</span></legend><div class="fieldset-wrapper">';
  $form['country_full']['#suffix'] = '</div></fieldset>';

  $output .= drupal_render_children($form);

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
  if (isset($form['geobutton']) ) {
    $mapid = $form['mapid']['#value'];
    unset($form['mapid']);
    $form['geobutton']['#markup'] = '<p><input type="submit" value="' . t('Geocode this address') . '" title="' . t('Get the latitude and longitude for this address') . '" id="getlocations_geocodebutton_' . $mapid . '" class="form-submit" /></p>';
  }
  $form['latitude']['#prefix'] = '<div class="getlocations_fields_latlon_wrapper"><div class="getlocations_fields_lat_wrapper">';
  $form['latitude']['#suffix'] = '</div>';
  $form['longitude']['#prefix'] = '<div class="getlocations_fields_lon_wrapper">';
  $form['longitude']['#suffix'] = '</div></div>';

  $output .= drupal_render_children($form);
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

  $prefix = '<fieldset class="form-wrapper">';
  $prefix .= '<legend><span class="fieldset-legend">' . t('Default Input form settings') . '</span></legend>';
  $prefix .= '<div class="fieldset-wrapper">';
  $prefix .= '<div class="fieldset-description">' . t('Configure the default input form.') . '</div>';
  $form['getlocations_fields_defaults']['use_address']['#prefix'] = $prefix;
  $form['getlocations_fields_defaults']['use_country_dropdown']['#suffix'] = '</div></fieldset>';

  $prefix = '<fieldset class="form-wrapper">';
  $prefix .= '<legend><span class="fieldset-legend">' . t('Default Address display settings') . '</span></legend>';
  $prefix .= '<div class="fieldset-wrapper">';
  $prefix .= '<div class="fieldset-description">' . t('Configure the default address display.') . '</div>';
  $form['getlocations_fields_defaults']['display_showmap']['#prefix'] = $prefix;
  $form['getlocations_fields_defaults']['country_full']['#suffix'] = '</div></fieldset>';

  $output .= drupal_render_children($form);
  return $output;

}
