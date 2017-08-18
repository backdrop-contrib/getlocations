<?php

/**
 * @file
 * getlocations_gps.admin.inc
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * Provides a gps facility.
 * for Backdrop
 */

/**
 * Function to display the getlocations_gps admin settings form
 * @return
 *   Returns the form.
 */
function getlocations_gps_settings_form() {

  $getlocations_gps_defaults = getlocations_gps_defaults();
  $getlocations_gps_paths = getlocations_gps_paths_get();
  $form = array();

  global $is_https;
  $desc = t('The settings here will provide the defaults for Getlocations GPS.');
  if (! $is_https) {
    $desc .= '</br>' . t('Modern browsers may refuse to geolocate unless the site is running under https.');
  }

  $form['getlocations_gps_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Getlocations GPS Default settings'),
    '#description' => $desc,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );
  $form['getlocations_gps_defaults'] += getlocations_gps_map_display_options_form($getlocations_gps_defaults);
  $form['getlocations_gps_paths'] = array(
    '#type' => 'fieldset',
    '#title' => t('Javascript paths'),
    '#description' => t('For advanced users who want to supply their own javascript.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );
  $form['getlocations_gps_paths']['getlocations_gps_path'] = getlocations_element_path(
    t('Path to getlocations_gps javascript file'),
    $getlocations_gps_paths['getlocations_gps_path'],
    70,
    128,
    t('Where the getlocations_gps javascript file is located.')
  );
  $form['getlocations_gps_paths']['getlocations_gps_admin_path'] = getlocations_element_path(
    t('Path to getlocations_gps_admin javascript file'),
    $getlocations_gps_paths['getlocations_gps_admin_path'],
    70,
    128,
    t('Where the getlocations_gps_admin javascript file is located.')
  );

  // Add a submit button
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Admin settings form validation.
 *
 */
function getlocations_gps_settings_form_validate($form, &$form_state) {

  if ( empty($form_state['values']['getlocations_gps_paths']['getlocations_gps_path'])) {
    form_set_error('getlocations_gps_paths][getlocations_gps_path', t('The path to the javascript must not be empty.'));
  }

  if ( empty($form_state['values']['getlocations_gps_paths']['getlocations_gps_admin_path'])) {
    form_set_error('getlocations_gps_paths][getlocations_gps_admin_path', t('The path to the javascript must not be empty.'));
  }

  if ( empty($form_state['values']['getlocations_gps_defaults']['gps_button_label'])) {
    form_set_error('getlocations_gps_defaults][gps_button_label', t('The button label must not be empty.'));
  }

  if ( empty($form_state['values']['getlocations_gps_defaults']['gps_marker_title'])) {
    form_set_error('getlocations_gps_defaults][gps_marker_title', t('The marker title must not be empty.'));
  }

}

function getlocations_gps_settings_form_submit($form, &$form_state) {

  $getlocations_gps_paths = $form_state['values']['getlocations_gps_paths'];
  $getlocations_gps_paths_settings = config('getlocations_gps.paths');
  $keys = array("getlocations_gps_path", "getlocations_gps_admin_path");
  foreach ($keys AS $key) {
    $getlocations_gps_paths_settings->set('paths.' . $key, $getlocations_gps_paths[$key]);
  }
  $getlocations_gps_paths_settings->save();

  $values = $form_state['values']['getlocations_gps_defaults'];
  getlocations_gps_defaults_set($values);
  #$settings = config('getlocations_gps.settings');
  #$keys = getlocations_gps_get_keys();
#
  #foreach ($keys AS $key) {
  #  if (isset($values[$key])) {
  #    $settings->set('settings.' . $key, $values[$key]);
  #  }
  #}
  #$settings-> save();
  backdrop_set_message(t('Getlocations GPS configuration options have been saved.'));
}
