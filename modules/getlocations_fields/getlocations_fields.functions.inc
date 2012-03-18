<?php

/**
 * @file
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
 * Supplies getlocations fields functions.
 */

/**
 * Fetch a list of the core Drupal list of countries.
 * from location module
 *
 * @param bool $upper Default uppercase
 *
 * @return array The countries array
 */
function getlocations_fields_get_countries_list($upper = TRUE) {
  include_once DRUPAL_ROOT . '/includes/locale.inc';

  // Statically cache a version of the core Drupal list of countries
  $countries = &drupal_static(__FUNCTION__);

  if (! isset($countries)) {
    if ($upper) {
      $countries = country_get_list();
    }
    else {
      $countries = array_change_key_case(country_get_list(), CASE_LOWER);
    }
  }
  return $countries;
}

/**
 * Get the full country name
 *
 * @param string $id The two letter iso code of a country
 *
 * @return string Full country name.
 *
 */
function getlocations_fields_get_country_name($id) {
  $countries = getlocations_fields_get_countries_list();
  $id = drupal_strtoupper($id);
  $country = FALSE;
  if (isset($countries[$id])) {
    $country = $countries[$id];
  }
  return $country;
}

/**
 * Get the two letter code for a country
 *
 * @param string $country Full country name.
 *
 * @return string The two letter iso code of a country
 */
function getlocations_fields_get_country_id($country) {
  $id = FALSE;
  $countries = getlocations_fields_get_countries_list();
  foreach ($countries AS $k => $v) {
    if (drupal_strtoupper($country) == drupal_strtoupper($v)) {
      $id = drupal_strtoupper($k);
      break;
    }
  }
  return $id;
}

/**
 * Convert decimal degrees to degrees,minutes,seconds.
 * from location module
 *
 * @param float Decimal degrees
 *
 * @return array degrees,minutes,seconds,sign
 */
function getlocations_fields_dd_to_dms($coord) {
  $negative = ($coord < 0) ? TRUE : FALSE;
  $coord = abs($coord);
  $degrees = floor($coord);
  $coord -= $degrees;
  $coord *= 60;
  $minutes = floor($coord);
  $coord -= $minutes;
  $coord *= 60;
  $seconds = round($coord, 6);
  return array($degrees, $minutes, $seconds, $negative);
}

/**
 * Convert dms string to decimal degrees.
 * Should be reasonably tolerant of sloppy input
 *
 * @param string
 *
 * @return string
 */
function getlocations_fields_dms_to_dd($dms) {
  // If it ends with a word starting with S or W, then it's a negative
  // case insensitive
  $direction = 1;
  preg_match("/\s(\w+)\b$/", $dms, $m);
  if (preg_match("/^s/i", $m[1]) || preg_match("/^w/i", $m[1]) ) {
    $direction = -1;
  }

  $dmsarr = explode(' ', $dms);
  $dmsarr2 = array();
  foreach ($dmsarr AS $v) {
    if ($v) {
      // strip out non-numbers found at the end of the string so we keep '.'
      $tmp = preg_replace("/\D+$/", '', $v);
      $tmp = trim($tmp);
      if ($tmp) {
        $dmsarr2[] = $tmp;
      }
    }
  }
  $dd = FALSE;
  if (count($dmsarr2) == 3) {
    list($degrees, $minutes, $seconds) = $dmsarr2;
    $dd = floatval($degrees + ((($minutes * 60) + ($seconds )) / 3600));
    if ($dd > 0) {
      $dd = $direction * $dd;
    }
  }
  return $dd;
}

/**
 * Calculations functions.
 * from location module
 */

/**
 * License clarification:
 *
 * On Feb 13, 2005, in message <Pine.LNX.4.58.0502131827510.5072@server1.LFW.org>,
 * the creator of these routines, Ka-Ping Yee, authorized these routines to be
 * distributed under the GPL.
 */

/**
 * @file
 * Trigonometry for calculating geographical distances.
 * All function arguments and return values measure distances in metres
 * and angles in degrees.  The ellipsoid model is from the WGS-84 datum.
 * Ka-Ping Yee, 2003-08-11
 */

// This library is an original implementation of UCB CS graduate student, Ka-Ping Yee (http://www.zesty.ca).

define('GETLOCATIONS_FIELDS_EARTH_RADIUS_SEMIMAJOR', 6378137.0);
define('GETLOCATIONS_FIELDS_EARTH_FLATTENING', (1/298.257223563));
define('GETLOCATIONS_FIELDS_EARTH_RADIUS_SEMIMINOR', (6378137.0*(1-(1/298.257223563))));
define('GETLOCATIONS_FIELDS_EARTH_ECCENTRICITY_SQ', (2*(1/298.257223563)-pow((1/298.257223563), 2)));


// Default latitude halfway between north pole and equator
function getlocations_fields_earth_radius($latitude=45) {
  // Estimate the Earth's radius at a given latitude.
  $lat = deg2rad($latitude);
  $x = (cos($lat) / GETLOCATIONS_FIELDS_EARTH_RADIUS_SEMIMAJOR);
  $y = (sin($lat) / GETLOCATIONS_FIELDS_EARTH_RADIUS_SEMIMINOR);
  $return = (1 / (sqrt($x * $x + $y * $y)));
  return $return;
}

/**
 * Returns the SQL fragment needed to add a column called 'distance' to a query. For use in Views distance/proximity calculations
 *
 * @param $latitude    The measurement point
 * @param $longitude   The measurement point
 * @param $tbl_alias   If necessary, the alias name. Used by SQL to clearly identify a field.
 */
function getlocations_fields_earth_distance_sql($latitude, $longitude, $tbl_alias = '') {
  // Make a SQL expression that estimates the distance to the given location.
  $radius = getlocations_fields_earth_radius($latitude);

  // If the table alias is specified, add on the separator.
  $tbl_alias = (empty($tbl_alias) ? '' : $tbl_alias . '.');

  $latfield = $tbl_alias . 'latitude';
  $lonfield = $tbl_alias . 'longitude';

  // all calcs in mysql
  #$sql = "(IFNULL(ACOS(COS(RADIANS($latitude)) * COS(RADIANS($latfield)) * (COS(RADIANS($longitude)) * COS(RADIANS($lonfield)) + SIN(RADIANS($longitude)) * SIN(RADIANS($lonfield))) + SIN(RADIANS($latitude)) * SIN(RADIANS($latfield))), 0.00000) * $radius)";
  // some calcs predone in php
  $long = deg2rad($longitude);
  $lat = deg2rad($latitude);
  $coslong = cos($long);
  $coslat = cos($lat);
  $sinlong = sin($long);
  $sinlat = sin($lat);
  $sql = "(IFNULL(ACOS($coslat * COS(RADIANS($latfield)) * ($coslong*COS(RADIANS($lonfield)) + $sinlong * SIN(RADIANS($lonfield))) + $sinlat * SIN(RADIANS($latfield))), 0.00000) * $radius)";

  return $sql;
}

/**
 * This function uses earth_asin_safe so is not accurate for all possible
 *   parameter combinations. This means this function doesn't work properly
 *   for high distance values. This function needs to be re-written to work properly for
 *   larger distance values. See http://drupal.org/node/821628
 */
function getlocations_fields_earth_longitude_range($latitude, $longitude, $distance) {
  // Estimate the min and max longitudes within $distance of a given location.
  $long = deg2rad($longitude);
  $lat = deg2rad($latitude);
  $radius = getlocations_fields_earth_radius($latitude);

  $angle = $distance / $radius;
  $diff = getlocations_fields_earth_asin_safe(sin($angle)/cos($lat));
  $minlong = $long - $diff;
  $maxlong = $long + $diff;
  if ($minlong < -pi()) {
    $minlong = $minlong + pi()*2;
  }
  if ($maxlong > pi()) {
    $maxlong = $maxlong - pi()*2;
  }
  return array(rad2deg($minlong), rad2deg($maxlong));
}

function getlocations_fields_earth_latitude_range($latitude, $longitude, $distance) {
  // Estimate the min and max latitudes within $distance of a given location.
  $long = deg2rad($longitude);
  $lat = deg2rad($latitude);
  $radius = getlocations_fields_earth_radius($latitude);

  $angle = $distance / $radius;
  $minlat = $lat - $angle;
  $maxlat = $lat + $angle;
  $rightangle = pi()/2;
  if ($minlat < -$rightangle) { // wrapped around the south pole
    $overshoot = -$minlat - $rightangle;
    $minlat = -$rightangle + $overshoot;
    if ($minlat > $maxlat) {
      $maxlat = $minlat;
    }
    $minlat = -$rightangle;
  }
  if ($maxlat > $rightangle) { // wrapped around the north pole
    $overshoot = $maxlat - $rightangle;
    $maxlat = $rightangle - $overshoot;
    if ($maxlat < $minlat) {
      $minlat = $maxlat;
    }
    $maxlat = $rightangle;
  }
  return array(rad2deg($minlat), rad2deg($maxlat));
}

/**
 * This is a helper function to avoid errors when using the asin() PHP function.
 * asin is only real for values between -1 and 1.
 * If a value outside that range is given it returns NAN (not a number), which
 * we don't want to happen.
 * So this just rounds values outside this range to -1 or 1 first.
 *
 * This means that calculations done using this function with $x outside the range
 * will not be accurate.  The alternative though is getting NAN, which is an error
 * and won't give accurate results anyway.
 */
function getlocations_fields_earth_asin_safe($x) {
  return asin(max(-1, min($x, 1)));
}

function getlocations_fields_get_search_distance_sql($latitude, $longitude, $searchdistance, $tbl_alias = '') {
  $radius = getlocations_fields_earth_radius($latitude);
  $tbl_alias = empty($tbl_alias) ? $tbl_alias : ($tbl_alias . '.');
  $latfield = $tbl_alias . 'latitude';
  $lonfield = $tbl_alias . 'longitude';

  // all calcs in mysql
  #$sql = "(IFNULL(ACOS((SIN(RADIANS($latitude)) * SIN(RADIANS($latfield)) + (COS(RADIANS($latitude)) * COS(RADIANS($latfield)) * COS(RADIANS($lonfield) - RADIANS($longitude))))), 0.00000) * $radius) BETWEEN 0 AND $searchdistance ";
  // some calcs predone in php
  $lat = deg2rad($latitude);
  $long = deg2rad($longitude);
  #$coslong = cos($long);
  $coslat = cos($lat);
  #$sinlong = sin($long);
  $sinlat = sin($lat);
  $sql = "(IFNULL(ACOS(($sinlat * SIN(RADIANS($latfield)) + ($coslat * COS(RADIANS($latfield)) * COS(RADIANS($lonfield) - $long )))), 0.00000) * $radius)";
  if ($searchdistance > 0) {
    $sql .= " BETWEEN 0 AND $searchdistance";
  }

  return $sql;
}


/**
 * @param $distance
 *   A number in either kilometers, meters, miles, yards or nautical miles.
 *
 * @param $distance_unit
 *   String (optional). in either kilometers (km), meters (m), miles (mi), yards (yd) or nautical miles (nmi).
 *
 * @return
 *   A floating point number where the number in meters after the initially passed scalar has been round()'d
 */
function getlocations_fields_convert_distance_to_meters($distance, $distance_unit = 'km') {
  if (!is_numeric($distance) || $distance == 0) {
    return NULL;
  }
  $units = array(
    'km'  => 1000.0,
    'm'   => 1.0,
    'mi'  => 1609.344,
    'yd'  => 0.9144,
    'nmi' => 1852.0
  );
  if (! in_array($distance_unit, array_keys($units))) {
    $distance_unit = 'km';
  }
  $conv = $units[$distance_unit];
  // Convert distance to meters
  $retval = round(floatval($distance) * $conv, 2);
  return $retval;
}

// form elements
/**
 * @param string $default
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_distance_unit($default) {

    $element = array(
    '#type' => 'select',
    '#title' => t('Units'),
    '#options' => array(
      'km'  => t('Kilometers'),
      'm'   => t('Meters'),
      'mi'  => t('Miles'),
      'yd'  => t('Yards'),
      'nmi' => t('Nautical miles'),
    ),
    '#default_value' => $default,
  );
  return $element;

}

/**
 * @param string $default
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_search_distance($default) {
  $element = array(
    '#type' => 'textfield',
    '#title' => t('Distance'),
    '#default_value' => $default,
    '#size' => 10,
  );
  return $element;
}

/**
 * @param string $default
 *
 * @param bool $distance
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_origin($default, $distance=FALSE) {
  $options = array(
    'nid_arg' => t("Node's Lat/Lon from views nid argument"),
    'uid_arg' => t("User's Lat/Lon from views uid argument"),
  );
  if (getlocations_get_vocabularies()) {
    $options += array('tid_arg' => t("Term's Lat/Lon from views tid argument"));
  }
  if (module_exists('comment')) {
    $options += array('cid_arg' => t("Comment's Lat/Lon from views cid argument"));
  }
  if ($distance) {
    $options += array('distance_arg' => t("Lat/Lon from views argument"));
  }
  $options += array(
    'user' => t("User's Lat/Lon (blank if unset)"),
    'hybrid' => t("User's Lat/Lon (fall back to Static if unset)"),
    'static' => t('Static Lat/Lon'),
#    'tied' => t("Use Distance / Proximity filter"),
#    'postal' => t('Postal Code / Country'),
#    'postal_default' => t('Postal Code (assume default country)'),
    'php' => t('Use PHP code to determine Lat/Lon'),
  );

  $element = array(
    '#type' => 'select',
    '#title' => t('Origin'),
    '#options' => $options,
    '#description' => t("The way the latitude/longitude is determined. If the origin has multiple locations the first will be used."),
    '#default_value' => $default,
  );
  return $element;
}

/**
 * @param string $default
 *
 * @param bool $ctools
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_latitude($default, $ctools=TRUE) {
  $element = array(
    '#type' => 'textfield',
    '#title' => t('Latitude'),
    '#default_value' => $default,
  );
  if ($ctools) {
    $element['#dependency'] = array('edit-options-origin' => array('hybrid', 'static'));
  }
  return $element;
}

/**
 * @param string $default
 *
 * @param bool $ctools
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_longitude($default, $ctools=TRUE) {
  $element = array(
    '#type' => 'textfield',
    '#title' => t('Longitude'),
    '#default_value' => $default,
  );
  if ($ctools) {
    $element['#dependency'] = array('edit-options-origin' => array('hybrid', 'static'));
  }
  return $element;
}

/**
 * @param string $default
 *
 * @param bool $ctools
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_postal_code($default, $ctools=TRUE) {
  $element = array(
    '#type' => 'textfield',
    '#title' => t('Postal code'),
    '#default_value' => $default,
  );
  if ($ctools) {
    $element['#dependency'] = array('edit-options-origin' => array('postal', 'postal_default'));
  }
  return $element;
}

/**
 * @param string $default
 *
 * @param bool $ctools
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_country($default, $title="", $ctools=TRUE) {
  if (empty($title)) {
    $title = t('Country');
  }
  $element = array(
    '#type' => 'select',
    '#title' => $title,
    '#options' => array('' => '') + getlocations_fields_get_countries_list(),
    '#default_value' => $default,
  );
  if ($ctools) {
    $element['#dependency'] = array('edit-options-origin' => array('postal'));
  }
  return $element;
}

/**
 * @param string $default
 *
 * @param string $title
 *
 * @param array $options
 *
 * @param string $description
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_dd($default, $title, $options, $description = '') {

  $element = array(
    '#type' => 'select',
    '#title' => $title,
    '#default_value' => $default,
    '#options' => $options,
  );
  if ($description) {
    $element['#description'] = $description;
  }
  return $element;
}


/**
 * @param string $default
 *
 * @param bool $ctools
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_php_code($default, $ctools=TRUE) {
  $element = array(
    '#type' => 'textarea',
    '#title' => t('PHP code for latitude, longitude'),
    '#default_value' => $default,
    '#description' => t("Enter PHP code that returns a latitude/longitude.  Do not use &lt;?php ?&gt;. You must return only an array with float values set for the 'latitude' and 'longitude' keys."),
  );
  if ($ctools) {
    $element['#dependency'] = array('edit-options-origin' => array('php'));
  }
  return $element;
}

/**
 * @param string $default
 *
 * @param bool $ctools
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_nid_arg($default, $options, $ctools=TRUE) {
  $element = array(
    '#type' => 'select',
    '#title' => t('Node ID argument to use'),
    '#options' => $options,
    '#default_value' => $default,
    '#description' => empty($options) ? t("Select which of the view's arguments to use as the node ID. The latitude / longitude of the first location of that node will be used as the origin. You must have added arguments to the view to use this option.") : t("Select which of the view's arguments to use as the node ID. The latitude / longitude of the first location of that node will be used as the origin."),
    );
  if ($ctools) {
    $element['#dependency'] = array('edit-options-origin' => array('nid_arg'));
  }
  return $element;
}

/**
 * @param string $default
 *
 * @param bool $ctools
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_nid_loc_field($default, $options, $ctools=TRUE) {
  $element = array(
    '#type' => 'select',
    '#title' => t('Location to use'),
    '#options' => $options,
    '#default_value' => $default,
    '#description' => t("Select which field to use as the origin. If the location supports multiple entries the first one will be used."),
    );
  if ($ctools) {
    $element['#dependency'] = array('edit-options-origin' => array('nid_arg'));
  }
  return $element;
}

/**
 * @param string $default
 *
 * @param bool $ctools
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_uid_arg($default, $options, $ctools=TRUE) {
  $element = array(
    '#type' => 'select',
    '#title' => t('User ID argument to use'),
    '#options' => $options,
    '#default_value' => $default,
    '#description' => empty($options) ? t("Select which of the view's arguments to use as the user ID. The latitude / longitude of the first location of that user will be used as the origin. You must have added arguments to the view to use this option.") : t("Select which of the view's arguments to use as the user ID. The latitude / longitude of the first location of that user will be used as the origin."),
    );
  if ($ctools) {
    $element['#dependency'] = array('edit-options-origin' => array('uid_arg'));
  }
  return $element;
}

/**
 * @param string $default
 *
 * @param bool $ctools
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_uid_loc_field($default, $options, $ctools=TRUE) {
  $element = array(
    '#type' => 'select',
    '#title' => t('Location to use'),
    '#options' => $options,
    '#default_value' => $default,
    '#description' => t("Select which field to use as the origin. If the location supports multiple entries the first one will be used."),
    );
  if ($ctools) {
    $element['#dependency'] = array('edit-options-origin' => array('uid_arg'));
  }
  return $element;
}

/**
 * @param string $default
 *
 * @param bool $ctools
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_tid_arg($default, $options, $ctools=TRUE) {
  $element = array(
    '#type' => 'select',
    '#title' => t('Term ID argument to use'),
    '#options' => $options,
    '#default_value' => $default,
    '#description' => empty($options) ? t("Select which of the view's arguments to use as the term ID. The latitude / longitude of the first location of that term will be used as the origin. You must have added arguments to the view to use this option.") : t("Select which of the view's arguments to use as the term ID. The latitude / longitude of the first location of that term will be used as the origin."),
    );
  if ($ctools) {
    $element['#dependency'] = array('edit-options-origin' => array('tid_arg'));
  }
  return $element;
}

/**
 * @param string $default
 *
 * @param bool $ctools
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_tid_loc_field($default, $options, $ctools=TRUE) {
  $element = array(
    '#type' => 'select',
    '#title' => t('Location to use'),
    '#options' => $options,
    '#default_value' => $default,
    '#description' => t("Select which field to use as the origin. If the location supports multiple entries the first one will be used."),
    );
  if ($ctools) {
    $element['#dependency'] = array('edit-options-origin' => array('tid_arg'));
  }
  return $element;
}

/**
 * @param string $default
 *
 * @param bool $ctools
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_cid_arg($default, $options, $ctools=TRUE) {
  $element = array(
    '#type' => 'select',
    '#title' => t('Comment ID argument to use'),
    '#options' => $options,
    '#default_value' => $default,
    '#description' => empty($options) ? t("Select which of the view's arguments to use as the comment ID. The latitude / longitude of the first location of that comment will be used as the origin. You must have added arguments to the view to use this option.") : t("Select which of the view's arguments to use as the comment ID. The latitude / longitude of the first location of that comment will be used as the origin."),
    );
  if ($ctools) {
    $element['#dependency'] = array('edit-options-origin' => array('cid_arg'));
  }
  return $element;
}

/**
 * @param string $default
 *
 * @param bool $ctools
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_cid_loc_field($default, $options, $ctools=TRUE) {
  $element = array(
    '#type' => 'select',
    '#title' => t('Location to use'),
    '#options' => $options,
    '#default_value' => $default,
    '#description' => t("Select which field to use as the origin. If the location supports multiple entries the first one will be used."),
    );
  if ($ctools) {
    $element['#dependency'] = array('edit-options-origin' => array('cid_arg'));
  }
  return $element;
}

/**
 * @param string $title
 *
 * @param string $default
 *
 * @param string $description
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_weight($title, $default, $description='') {
  $options = array('' => '');
  $options += drupal_map_assoc(range(-50, 50));
  $element = array(
    '#type' => 'select',
    '#title' => $title,
    '#default_value' => $default,
    '#options' => $options,
  );
  if (! empty($description)) {
    $element['#description'] = $description;
  }
  return $element;
}

/**
 * @param string $title
 *
 * @param string $default
 *
 * @param string $description
 *
 * @return
 *   Returns form element
 *
 */
function getlocations_fields_element_opts($title, $default, $description='') {

  $element = array(
    '#type' => 'select',
    '#title' => $title,
    '#default_value' => $default,
    '#options' => array(
      '0' => t('Normal'),
      '1' => t('Required'),
      '2' => t('Read only'),
      '3' => t('Display only'),
      '4' => t('Hidden'),
    ),
  );
  if (! empty($description)) {
    $element['#description'] = $description;
  }
  return $element;
}

/**
 * ajax callback
 *
 * @return
 *   Returns country code
 *
 */
function getlocations_fields_countryinfo() {
  $country = $_GET['country'];
  $content = FALSE;
  if (drupal_strlen($country) == 2 ) {
    $content = drupal_strtoupper($country);
  }
  else {
    $content = getlocations_fields_get_country_id($country);
  }
  // fix 'The Netherlands' which is what google returns
  if ($country == 'The Netherlands') {
    $content = 'NL';
  }
  print $content;
  exit();

}

/**
 * autocomplete for country
 *
 * @param string $string
 *
 * @return
 *   Returns country names
 *
 */
function getlocations_fields_country_autocomplete($string = '') {
    $matches = array();
  if ($string) {
    $countries = getlocations_fields_get_countries_list();
    foreach ($countries AS $country) {
      $s = drupal_strtolower($string);
      $c = drupal_strtolower($country);
      preg_match_all("/^$s/", $c, $m);
      if (count( $m[0])) {
        $matches[$country] = $country;
      }
    }
  }
  drupal_json_output($matches);
}

/**
 * autocomplete for province
 *
 * @param string $string
 *
 * @return
 *   Returns province names
 *
 */
function getlocations_fields_province_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    //
    $query = db_select('getlocations_fields', 'f');
    $query->fields('f', array('province'));
    $query->where("LOWER(province) LIKE LOWER(:st)", array(':st' => $string . '%'));
    $query->range(0, 15);
    $result = $query->execute();
    foreach ($result AS $row) {
      $matches[$row->province] = check_plain($row->province);
    }
  }
  drupal_json_output($matches);
}

/**
 * autocomplete for city
 *
 * @param string $string
 *
 * @return
 *   Returns city names
 *
 */
function getlocations_fields_city_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    //
    $query = db_select('getlocations_fields', 'f');
    $query->fields('f', array('city'));
    $query->where("LOWER(city) LIKE LOWER(:st)", array(':st' => $string . '%'));
    $query->range(0, 15);
    $result = $query->execute();
    foreach ($result AS $row) {
      $matches[$row->city] = check_plain($row->city);
    }
  }
  drupal_json_output($matches);
}

/**
 * @return
 *   Returns location array
 *
 */
function getlocations_fields_smart_ip() {
  if (module_exists('smart_ip')) {
    global $user;
    $location = FALSE;
    if ($user->uid > 0 && isset($user->data['geoip_location'])) {
      $location = $user->data['geoip_location'];
    }
    elseif (isset($_SESSION['smart_ip']['location'])) {
      $location = $_SESSION['smart_ip']['location'];
    }
    drupal_json_output($location);
  }
  exit;
}
