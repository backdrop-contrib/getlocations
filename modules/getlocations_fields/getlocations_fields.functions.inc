<?php

/**
 * @file
 * Supplies getlocations fields functions.
 */

/**
 * Fetch a list of the core Drupal list of countries.
 * from location module
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

function getlocations_fields_get_country_name($id) {
  $countries = getlocations_fields_get_countries_list();
  return $countries[$id];
}

/**
 * Convert decimal degrees to degrees,minutes,seconds.
 * from location module
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
 * @param float $longitude1
 *
 * @param float $latitude1
 *
 * @param float $longitude2
 *
 * @param float $latitude2
 *
 * @return
 *   Returns distance in meters
 *
 */
function getlocations_fields_earth_distance($longitude1, $latitude1, $longitude2, $latitude2) {
  // Estimate the earth-surface distance between two locations.
  $long1 = deg2rad($longitude1);
  $lat1 = deg2rad($latitude1);
  $long2 = deg2rad($longitude2);
  $lat2 = deg2rad($latitude2);
  $radius = getlocations_fields_earth_radius(($latitude1 + $latitude2) / 2);

  $cosangle = cos($lat1)*cos($lat2) *
    (cos($long1)*cos($long2) + sin($long1)*sin($long2)) +
    sin($lat1)*sin($lat2);
  return acos($cosangle) * $radius;
}

/**
 * Returns the SQL fragment needed to add a column called 'distance'
 * to a query that includes the location table
 *
 * @param $latitude    The measurement point
 * @param $longitude   The measurement point
 * @param $tbl_alias   If necessary, the alias name. Used by SQL to clearly identify a field.
 */
function getlocations_fields_earth_distance_sql($latitude, $longitude, $tbl_alias = '') {
  // Make a SQL expression that estimates the distance to the given location.
  $radius = getlocations_fields_earth_radius($latitude);

  // If the table alias is specified, add on the separator.
  $tbl_alias = empty($tbl_alias) ? $tbl_alias : ($tbl_alias . '.');

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
 * @todo This function uses earth_asin_safe so is not accurate for all possible
 *   parameter combinations. This means this function doesn't work properly
 *   for high distance values. This function needs to be re-written to work properly for
 *   larger distance values. See http://drupal.org/node/821628
 */
function getlocations_fields_earth_longitude_range($longitude, $latitude, $distance) {
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

function getlocations_fields_earth_latitude_range($longitude, $latitude, $distance) {
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
 *   A number in either miles or km.
 *
 * @param $distance_unit
 *   String (optional). Either 'mile' or 'km' (default)
 *
 * @return
 *   A floating point number where the number in meters after the initially passed scalar has been ceil()'d
 *   This is done after the $distance_unit parmeter is forced to be 'km' or 'mile'
 */
function getlocations_fields_convert_distance_to_meters($distance, $distance_unit = 'km') {
  if (!is_numeric($distance)) {
    return NULL;
  }

  if ($distance == 0) {
    return NULL;
  }

  if ($distance_unit != 'km' && $distance_unit != 'mile') {
    $distance_unit = 'km';
  }

  // Convert distance to meters
  $retval = round(floatval($distance) * (($distance_unit == 'km') ? 1000.0 : 1609.347), 2);
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
      'km' => t('Kilometers'),
      'mi' => t('Miles'),
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
    'nid_arg' => t("Node's Latitude / Longitude from views nid argument"),
    'uid_arg' => t("User's Latitude / Longitude from views uid argument"),
  );
  if ($distance) {
    $options += array('distance_arg' => t("Latitude / Longitude from views argument"));
  }
  $options += array(
    'user' => t("User's Latitude / Longitude (blank if unset)"),
    'hybrid' => t("User's Latitude / Longitude (fall back to static if unset)"),
    'static' => t('Static  Latitude / Longitude'),
    'tied' => t("Use Distance / Proximity filter"),
#    'postal' => t('Postal Code / Country'),
#    'postal_default' => t('Postal Code (assume default country)'),
    'php' => t('Use PHP code to determine latitude/longitude'),
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
    $element['#process'] = array('ctools_dependent_process');
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
    $element['#process'] = array('ctools_dependent_process');
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
    $element['#process'] = array('ctools_dependent_process');
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
    $element['#process'] = array('ctools_dependent_process');
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
    $element['#process'] = array('ctools_dependent_process');
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
    '#description' => empty($options) ? t("Select which of the view's arguments to use as the node ID.  The latitude / longitude of the first location of that node will be used as the origin. You must have added arguments to the view to use this option.") : t("Select which of the view's arguments to use as the node ID.  The latitude / longitude of the first location of that node will be used as the origin."),
    );
  if ($ctools) {
    $element['#process'] = array('ctools_dependent_process');
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
    $element['#process'] = array('ctools_dependent_process');
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
    '#description' => empty($options) ? t("Select which of the view's arguments to use as the user ID. The latitude / longitude of the first location of that user will be used as the origin. You must have added arguments to the view to use this option.") : t("Select which of the view's arguments to use as the user ID.  The latitude / longitude of the first location of that user will be used as the origin."),
    );
  if ($ctools) {
    $element['#process'] = array('ctools_dependent_process');
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
    $element['#process'] = array('ctools_dependent_process');
    $element['#dependency'] = array('edit-options-origin' => array('uid_arg'));
  }
  return $element;
}

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

// ajax callback
function getlocations_fields_countryinfo() {
  $country = $_GET['country'];
  $content = FALSE;
  if (drupal_strlen($country) == 2 ) {
    $content = drupal_strtoupper($country);
  }
  else {
    $countries = getlocations_fields_get_countries_list();
    foreach ($countries AS $k => $v) {
      if ( drupal_strtolower($country) == drupal_strtolower($v) ) {
        $content = drupal_strtoupper($k);
        break;
      }
    }
  }
  print $content;
  exit();

}

// autocomplete for country
function getlocations_fields_country_autocomplete($string = '') {
    $matches = array();
  if ($string) {
    $countries = getlocations_fields_get_countries_list();
    foreach ($countries AS $country) {
      $s = strtolower($string);
      $c = strtolower($country);
      preg_match_all("/^$s/", $c, $m);
      if (count( $m[0])) {
        $matches[$country] = $country;
      }
    }
  }
  drupal_json_output($matches);
}

// autocomplete for province
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

// autocomplete for city
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

/***********************************************************/
// these functions currently not in use
function getlocations_fields_earth_xyz($longitude, $latitude, $height = 0) {
  // Convert longitude and latitude to earth-centered earth-fixed coordinates.
  // X axis is 0 long, 0 lat; Y axis is 90 deg E; Z axis is north pole.

  $long = deg2rad($longitude);
  $lat = deg2rad($latitude);

  $coslong = cos($long);
  $coslat = cos($lat);
  $sinlong = sin($long);
  $sinlat = sin($lat);
  $radius = (GETLOCATIONS_FIELDS_EARTH_RADIUS_SEMIMAJOR / sqrt(1 - GETLOCATIONS_FIELDS_EARTH_ECCENTRICITY_SQ * $sinlat * $sinlat));
  $x = ($radius + $height) * $coslat * $coslong;
  $y = ($radius + $height) * $coslat * $sinlong;
  $z = (($radius * (1 - GETLOCATIONS_FIELDS_EARTH_ECCENTRICITY_SQ ) + $height) * $sinlat);
  return array($x, $y, $z);
}

function getlocations_fields_earth_arclength($angle, $latitude=37.9) {
  // Convert a given angle to earth-surface distance.
  return deg2rad($angle) * getlocations_fields_earth_radius($latitude);
}

function getlocations_fields_get_exact_distance_sql($latitude, $longitude, $tbl_alias = '') {
  $radius = getlocations_fields_earth_radius($latitude);
  $tbl_alias = empty($tbl_alias) ? $tbl_alias : ($tbl_alias . '.');
  $latfield = $tbl_alias . 'latitude';
  $lonfield = $tbl_alias . 'longitude';

  // all calcs in mysql
  #$sql = "(IFNULL(ACOS((SIN(RADIANS($latitude)) * SIN(RADIANS($latfield))) + (COS(RADIANS($latitude)) * COS(RADIANS($latfield)) * COS(RADIANS($longitude - $lonfield)))), 0.00000) * $radius)";
  // some calcs predone in php
  $lat = deg2rad($latitude);
  $long = deg2rad($longitude);
  #$coslong = cos($long);
  $coslat = cos($lat);
  #$sinlong = sin($long);
  $sinlat = sin($lat);
  $sql = "(IFNULL(ACOS(($sinlat * SIN(RADIANS($latfield))) + ($coslat * COS(RADIANS($latfield)) * COS(RADIANS($longitude - $lonfield)))), 0.00000) * $radius)";
  return $sql;
}

/**
 * Given two points in lat/lon form, returns the distance between them.
 * @param $latlon_a
 *   An associative array where
 *      'lon' => is a floating point of the longitude coordinate for the point given by latlonA
 *      'lat' => is a floating point of the latitude coordinate for the point given by latlonB
 * @param $latlon_b
 *      Another point formatted like $latlon_b
 * @param $distance_unit
 *      A string that is either 'km' or 'mile'.
 *      If neither 'km' or 'mile' is passed, the parameter is forced to 'km'
 * @return
 *    NULL if sense can't be made of the parameters.
 *    An associative array where
 *      'scalar' => Is the distance between the two lat/lon parameter points
 *      'distance_unit' => Is the unit of distance being represented by 'scalar'.
 *                         This will be 'km' unless 'mile' is passed for the $distance_unit param
 */
function getlocations_fields_distance_between($latlon_a = array(), $latlon_b = array(), $distance_unit = 'km') {
  if (!isset($latlon_a['lon']) || !isset($latlon_a['lat']) || !isset($latlon_b['lon']) || !isset($latlon_b['lat'])) {
    return NULL;
  }

  if ($distance_unit != 'km' && $distance_unit != 'mile') {
    return NULL;
  }

  // $conversion_factor = number to divide by to convert meters to $distance_unit
  // At this point, $distance_unit == 'km' or 'mile' and nothing else
  //$conversion_factor = ($distance_unit == 'km') ? 1000.0 : 1609.347;

  $meters = getlocations_fields_earth_distance($latlon_a['lon'], $latlon_a['lat'], $latlon_b['lon'], $latlon_b['lat']);
  return array('scalar' => round($meters/(($distance_unit == 'km') ? 1000.0 : 1609.347), 1), 'distance_unit' => $distance_unit);
}