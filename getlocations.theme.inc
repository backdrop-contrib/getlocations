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
    'getlocations_box' => array(
      'arguments' => array(
        'content' => null,
      ),
      'template' => 'getlocations_box',
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
    // if you are using a colorbox to display getlocations you might want to make this a plain heading
    $output .= '<h4>' . l($location['name'], 'node/'. $location['nid'], array('attributes' => array('class' => 'getlocations_infolink'))) . '</h4>';
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

function template_preprocess_getlocations_box(&$variables) {

  if(module_exists('admin_menu')) {
    admin_menu_suppress();
  }
  drupal_add_js(GETLOCATIONS_PATH .'/js/getlocations_box.js');

  // Construct page title
  if (drupal_get_title()) {
    $head_title = array(strip_tags(drupal_get_title()), variable_get('site_name', 'Drupal'));
  }
  else {
    $head_title = array(variable_get('site_name', 'Drupal'));
    if (variable_get('site_slogan', '')) {
      $head_title[] = variable_get('site_slogan', '');
    }
  }
  $variables['head_title']        = implode(' | ', $head_title);
  $variables['base_path']         = base_path();
  $variables['head']              = drupal_get_html_head();
  $variables['language']          = $GLOBALS['language'];
  $variables['language']->dir     = $GLOBALS['language']->direction ? 'rtl' : 'ltr';
  $variables['css']               = drupal_add_css();
  $variables['styles']            = drupal_get_css();
  $variables['scripts']           = drupal_get_js();
  if (module_exists('jquery_update')) {
    jquery_update_preprocess_page($variables);
  }
  $variables['title'] = drupal_get_title();
  // Closure should be filled last.
  $variables['closure'] = theme('closure');
  // Compile a list of classes that are going to be applied to the body element.
  // This allows advanced theming based on context (home page, node of certain type, etc.).
  $body_classes = array();
  // Add a class that tells us whether we're on the front page or not.
  $body_classes[] = $variables['is_front'] ? 'front' : 'not-front';
  // Add a class that tells us whether the page is viewed by an authenticated user or not.
  $body_classes[] = $variables['logged_in'] ? 'logged-in' : 'not-logged-in';
  $body_classes[] = 'no-sidebars';
  // Implode with spaces.
  $variables['body_classes'] = implode(' ', $body_classes);

}


