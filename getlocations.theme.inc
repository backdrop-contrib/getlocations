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
        'mapid' => '',
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
    'getlocations_view_map' => array(
      'arguments' => array(
        'content' => null,
      ),
      'template' => 'getlocations_view_map',
    ),

  );
}

/**
 * All the map displays pass through here.
 */
function theme_getlocations_show($width, $height, $defaults, $mapid, $type = '', $node = '') {

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
  $output .= '<div class="getlocations_map_canvas" id="getlocations_map_canvas_' . $mapid . '" style="width: '. $width .'; height: '. $height .'" ></div>';
  // buttons
  $buttons = array();
  if ($defaults['trafficinfo']) {
    $buttons[] = '<input type="submit" value="' . t('Toggle traffic info') . '" title="' . t('Limited Availability') . '" id="getlocations_toggleTraffic" class="form-submit" />';
  }
  if ($defaults['bicycleinfo']) {
    $buttons[] = '<input type="submit" value="' . t('Toggle bicycle info') . '" title="' . t('Limited Availability') . '" id="getlocations_toggleBicycle" class="form-submit" />';
  }
  if ($defaults['panoramio_use'] && $defaults['panoramio_show']) {
    $buttons[] = '<input type="submit" value="' . t('Toggle panoramio') . '" id="getlocations_togglePanoramio" class="form-submit" />';
  }
  if (count($buttons)) {
    $output .= '<div class="getlocations_map_buttons" class="container-inline">';
    $output .= implode('&nbsp;', $buttons);
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
    $l = $location['name'];
    if ($location['nid'] > 0) {
      $l = l($location['name'], 'node/'. $location['nid'], array('attributes' => array('class' => 'getlocations_infolink', 'target' => '_parent')));
    }
    elseif ($location['uid'] > 0) {
      // Use $l = $location['name'] if you don't want links to user
      $l = l($location['name'], 'user/'. $location['uid'], array('attributes' => array('class' => 'getlocations_infolink')));
    }

    // if you are using a colorbox to display getlocations you might want to make this a plain heading
    $output .= '<h4>' . $l . '</h4>';
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


/**
 * Preprocess function for theme_getlocations_view_map().
 */
function template_preprocess_getlocations_view_map(&$variables) {
  global $language;

  $locations = $variables['view']->style_plugin->rendered_fields;
  $options = $variables['view']->style_plugin->options;
  $getlocations_defaults = getlocations_defaults();

  $latlons = array();
  $minmaxes = array('minlat' => 0, 'minlon' => 0, 'maxlat' => 0, 'maxlon' => 0);
  $ct = 0;
  if (count($locations)) {
    // we should loop over them and dump bummers with no lat/lon
    foreach ($locations AS $key => $location) {
      if (getlocations_latlon_check($location['latitude'] . ',' . $location['longitude']) ) {
        $minmaxes = getlocations_do_minmaxes($ct, $location, $minmaxes);
        $ct++;
        $marker = '';
        if (isset($location['uid'])) {
          $marker = $getlocations_defaults['user_map_marker'];
        }
        elseif (isset($options['map_marker']) && ! empty($options['map_marker'])) {
          $marker = $options['map_marker'];
        }
        else {
          $marker = $getlocations_defaults['map_marker'];
        }
        $name = htmlspecialchars_decode($location['name'], ENT_QUOTES);
        $latlons[] = $location['latitude'] . ',' . $location['longitude'] . ',' . $location['lid'] . ',' . $name . ',' . $marker;
      }
    }
  }
  if ($ct < 2 ) {
    unset($minmaxes);
    $minmaxes = '';
  }

  // get the defaults and override with the style plugin options
  $newdefaults = array();
  foreach ($getlocations_defaults AS $k => $v) {
    if (isset($options[$k])) {
      $newdefaults[$k] = $options[$k];
    }
    else {
      $newdefaults[$k] = $getlocations_defaults[$k];
    }
  }

  $mapid = getlocations_setup_map($newdefaults);
  getlocations_js_settings_do($newdefaults, $latlons, $minmaxes, $mapid);
  $variables['map']  = theme('getlocations_show', $newdefaults['width'], $newdefaults['height'], $newdefaults, $mapid, '', '');

}

