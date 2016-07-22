<?php

/**
 * @file
 * getlocations_gps.theme.inc
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * Provides a gps facility.
 * for Backdrop
 */

 function theme_getlocations_gps_button($variables) {
  $defaults = $variables['defaults'];
  $mapid = $variables['mapid'];
  $output = '';

  $geolocation_mobile_check = ($defaults['geolocation_mobile_check'] ? FALSE : TRUE);
  if (getlocations_is_mobile($geolocation_mobile_check) && isset($defaults['gps_button']) && $defaults['gps_button']) {
    $gpsbtn = '<input type="button" value="' . $defaults['gps_button_label'] . '" id="getlocations_gps_show_' . $mapid . '" class="form-submit"  />';
    $gpsbtn .= '<div class="getlocations_gps_throbber getlocations_gps_throbber_inactive" id="getlocations_gps_throbber_' . $mapid . '">&nbsp;&nbsp;&nbsp;&nbsp;</div>';
    $output .= $gpsbtn;
  }
  return $output;
}
