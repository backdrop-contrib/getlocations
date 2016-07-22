<?php

/**
 * @file
 * getlocations_gps.theme.inc
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * Provides support for smartip module.
 * for Backdrop
 */

function theme_getlocations_smartip_button($variables) {
  $defaults = $variables['defaults'];
  $mapid = $variables['mapid'];
  $output = '';

  if (isset($defaults['smartip_button']) && $defaults['smartip_button']) {
    $smartipbtn = '<input type="button" value="' . $defaults['smartip_button_label'] . '" id="getlocations_smartip_show_' . $mapid . '" class="form-submit"  />';
    $smartipbtn .= '<div class="getlocations_smartip_throbber getlocations_smartip_throbber_inactive" id="getlocations_smartip_throbber_' . $mapid . '">&nbsp;&nbsp;&nbsp;&nbsp;</div>';
    $output .= $smartipbtn;
  }
  return $output;
}
