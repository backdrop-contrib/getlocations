<?php

/**
 * @file
 * getlocations module theming functions.
 * using version 3 googlemaps API
 */

/**
 * Implementation of hook_theme().
 *
 * This lets us tell Drupal about our theme functions and their arguments.
 */
function getlocations_theme() {
  return array(
    'getlocations_show' => array(
      'arguments' => array(
        'width' => '',
        'height' => '',
        'defaults' => '',
        'type' => '',
        'node' => '',
      ),
    ),
    'getlocations_info' => array(
      'arguments' => array(
        'location' => null,
      ),
    ),
  );
}

/**
 * All the map displays pass through here.
 */
function theme_getlocations_show($width, $height, $defaults, $type = '', $node = '') {

  $output = '';
  // return link
  if ($type == 'node' && $defaults['returnlink_page_enable']) {
    if (is_object($node)) {
      $linktext = $defaults['returnlink_page_link'];
      if ( preg_match("/%t/", $linktext)) {
        $linktext = preg_replace("/%t/", $node->title, $linktext);
      }
      $l = l($linktext, 'node/' . $node->nid);
      $output .= '<div class="getlocations_returnlink">' . $l . '</div>';
    }
  }
  elseif ($type == 'user' && $defaults['returnlink_user_enable']) {
    if (is_object($node)) {
      $linktext = $defaults['returnlink_user_link'];
      if ( preg_match("/%n/", $linktext)) {
        $linktext = preg_replace("/%n/", $node->name, $linktext);
      }
      $l = l($linktext, 'user/' . $node->uid);
      $output .= '<div class="getlocations_returnlink">' . $l . '</div>';
    }
  }
  // do map
  $output .= '<div id="getlocations_map_canvas" style="width: '. $width .'; height: '. $height .'" ></div>';
  // buttons
  $form = array();
  if ($defaults['trafficinfo']) {
    $form['trafficinfo'] = array(
      '#type' => 'button',
      '#value' => t('Toggle traffic info'),
      '#weight' => 10,
      '#attributes' => array( 'onClick' => 'Drupal.getlocations.toggleTraffic(); return false;', 'title' => t('Limited Availability')),
    );
  }
  if ($defaults['bicycleinfo']) {
    $form['bicycleinfo'] = array(
      '#type' => 'button',
      '#value' => t('Toggle bicycling info'),
      '#weight' => 12,
      '#attributes' => array( 'onClick' => 'Drupal.getlocations.toggleBicycle(); return false;', 'title' => t('Limited Availability')),
    );
  }
  if ($defaults['panoramio_show']) {
    $form['panoramio'] = array(
      '#type' => 'button',
      '#value' => t('Toggle Panoramio'),
      '#weight' => 14,
      '#attributes' => array( 'onClick' => 'Drupal.getlocations.togglePanoramio(); return false;'),
    );
  }
  if (count($form)) {
    $output .= '<div id="getlocations_map_buttons" class="container-inline">';
    $output .= drupal_render($form);
    $output .= '</div>';
  }

  return $output;
}

/**
 * returns a location's vcard, requested by ajax
 *
 */
function theme_getlocations_info($location) {

  $output = '';

  $output .= '<div class="location vcard">';
  $output .= '<br />';
  if (! empty($location['name'])) {
    $output .= '<h4>' . l($location['name'], 'node/'. $location['nid']) . '</h4>';
  }
  $output .= '<div class="adr">';
  if (! empty($location['street'])) {
    $output .= '<div class="street-address">' . $location['street'];
    if (! empty($location['additional'])) {
      $output .= ' ' . $location['additional'];
    }
    $output .= '</div>';
  }
  if (! empty($location['city'])) {
    $output .= '<span class="locality">' . $location['city'] . ' </span>';
    if (! empty($location['province_name'])) {
      $output .= ",&nbsp;";
    }
  }
  if (! empty($location['province_name'])) {
    $output .= '<span class="region">' . $location['province_name'] . ' </span>';
  }
  if (! empty($location['postal_code'])) {
    $output .= '<span class="postal-code">' . strtoupper($location['postal_code']) . ' </span>';
  }
  if (! empty($location['country_name'])) {
    $output .= '<div class="country-name">' . $location['country_name'] . '</div>';
  }
  $output .= '</div>';
  $output .= '</div>';

  return $output;
}
