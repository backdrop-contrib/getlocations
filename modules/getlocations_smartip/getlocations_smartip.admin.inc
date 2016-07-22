<?php

/**
 * @file
 * getlocations_gps.admin.inc
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * Provides support for smartip module.
 * for Backdrop
 */

/**
 * Function to display the getlocations_smartip admin settings form
 * @return
 *   Returns the form.
 */
function getlocations_smartip_settings_form() {

  $getlocations_smartip_defaults = getlocations_smartip_defaults();

  $getlocations_smartip_paths = getlocations_smartip_paths_get();

  $form = array();

  $form['getlocations_smartip_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Getlocations Smartip Default settings'),
    '#description' => t('The settings here will provide the defaults for Getlocations Smartip.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );

  $form['getlocations_smartip_defaults'] += getlocations_smartip_map_display_options_form($getlocations_smartip_defaults);

  $form['getlocations_smartip_paths'] = array(
    '#type' => 'fieldset',
    '#title' => t('Javascript paths'),
    '#description' => t('For advanced users who want to supply their own javascript.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );

  $form['getlocations_smartip_paths']['getlocations_smartip_path'] = getlocations_element_path(
    t('Path to getlocations_smartip javascript file'),
    $getlocations_smartip_paths['getlocations_smartip_path'],
    70,
    128,
    t('Where the getlocations_smartip javascript file is located.')
  );
  $form['getlocations_smartip_paths']['getlocations_smartip_admin_path'] = getlocations_element_path(
    t('Path to getlocations_smartip_admin javascript file'),
    $getlocations_smartip_paths['getlocations_smartip_admin_path'],
    70,
    128,
    t('Where the getlocations_smartip_admin javascript file is located.')
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
function getlocations_smartip_settings_form_validate($form, &$form_state) {

  if ( empty($form_state['values']['getlocations_smartip_paths']['getlocations_smartip_path'])) {
    form_set_error('getlocations_smartip_paths][getlocations_smartip_path', t('The path to the javascript must not be empty.'));
  }

  if ( empty($form_state['values']['getlocations_smartip_paths']['getlocations_smartip_admin_path'])) {
    form_set_error('getlocations_smartip_paths][getlocations_smartip_admin_path', t('The path to the javascript must not be empty.'));
  }

  if ( empty($form_state['values']['getlocations_smartip_defaults']['smartip_button_label'])) {
    form_set_error('getlocations_smartip_defaults][smartip_button_label', t('The button label must not be empty.'));
  }

  if ( empty($form_state['values']['getlocations_smartip_defaults']['smartip_marker_title'])) {
    form_set_error('getlocations_smartip_defaults][smartip_marker_title', t('The marker title must not be empty.'));
  }

}

/**
 * Admin settings form validation.
 *
 */
function getlocations_smartip_settings_form_submit($form, &$form_state) {

  $getlocations_smartip_paths = $form_state['values']['getlocations_smartip_paths'];
  $getlocations_smartip_paths_settings = config('getlocations_smartip.paths');
  $keys = array("getlocations_smartip_path", "getlocations_smartip_admin_path");
  foreach ($keys AS $key) {
    $getlocations_smartip_paths_settings->set('paths.' . $keys, $getlocations_smartip_paths[$key]);
  }
  $getlocations_smartip_paths_settings->save();

  $values = $form_state['values']['getlocations_smartip_defaults'];
  $settings = config('getlocations_smartip.settings');
  $keys = getlocations_smartip_get_keys();
  foreach ($keys AS $key) {
    $settings->set('settings.' . $keys, $values[$key]);
  }
  $settings->save();
  backdrop_set_message(t('Getlocations smartip configuration options have been saved.'));
}
