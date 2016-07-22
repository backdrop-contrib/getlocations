<?php

/**
 * @file
 * getlocations_search.theme.inc
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * getlocations_search module administration functions.
 */

/**
 * @param array $variables
 *
 * @return
 *   Modifies $variables in situ
 *
 */
function template_preprocess_getlocations_search_box(&$variables) {

  $getlocations_search_defaults = getlocations_search_defaults();
  $variables['box_width'] = $getlocations_search_defaults['width'];
  $variables['box_height'] = $getlocations_search_defaults['height'];

  if (module_exists('admin_menu')) {
    admin_menu_suppress();
  }

  // Construct page title
  if (backdrop_get_title()) {
    $head_title = array(strip_tags(backdrop_get_title()), 'Backdrop');
  }
  else {
    $head_title = array('Backdrop');
    #if (variable_get('site_slogan', '')) {
    #  $head_title[] = variable_get('site_slogan', '');
    #}
  }
  $variables['head_title'] = implode(' | ', $head_title);
  $variables['base_path'] = base_path();
  $variables['head'] = backdrop_get_html_head();
  $variables['language'] = $GLOBALS['language'];
  $variables['language']->dir = $GLOBALS['language']->direction ? 'rtl' : 'ltr';
  $variables['css'] = backdrop_add_css();
  $variables['styles'] = backdrop_get_css();
  $variables['scripts'] = backdrop_get_js();
  $variables['title'] = backdrop_get_title();
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
 * Themes the search page.
 *
 * @param array $variables
 *
 * @return
 *   Returns $content
 *
 */
function theme_getlocations_search($variables) {
  $which = $variables['which'];
  $contents = '';
  $contents .= '<div id="getlocations_search_' . $which . '">';
  $getmap = getlocations_search_getmap($which);
  $map = $getmap['map'];
  $mapid = $getmap['mapid'];
  $form = backdrop_get_form('getlocations_search_form', $which, $mapid);
  $contents .= backdrop_render($form);
  $contents .= $map;
  $contents .= '</div>';
  return $contents;
}

/**
 * Themes the search form and results.
 *
 * @param array $variables
 *
 * @return
 *   Returns $output
 *
 */
function theme_getlocations_search_form($variables) {
  $form = $variables['form'];
  $which = $form['which']['#value'];
  unset($form['which']);
  $mapid = $form['mapid']['#value'];
  unset($form['mapid']);
  $display_latlon = $form['display_latlon']['#value'];
  unset($form['display_latlon']);
  $display_accuracy = $form['display_accuracy']['#value'];
  unset($form['display_accuracy']);
  $display_geo_microformat = $form['display_geo_microformat']['#value'];
  unset($form['display_geo_microformat']);
  $output = '';
$output .= "\n<!-- theme_getlocations_search_form -->\n";
  $form['getlocations_search_' . $mapid]['#prefix'] = '<div id="getlocations_search_wrapper">';
  $form['getlocations_search_submit']['#suffix'] = '</div>';

  // if the units dropdown is not exposed show the units after the distance box
  if ($form['getlocations_search_units_' . $mapid]['#type'] == 'hidden' && $form['getlocations_search_distance_' . $mapid]['#type'] !== 'hidden') {
    $form['getlocations_search_distance_' . $mapid]['#field_suffix'] = getlocations_get_unit_names($form['getlocations_search_units_' . $mapid]['#value'], 'plurals');
  }

  if (getlocations_is_mobile() && isset($form['getlocations_search_geolocation_button_' . $mapid])) {
    $geolocation_button = '<div id="getlocations_search_geolocation_button_wrapper_' . $mapid . '"><p>';
    $geolocation_button .= '<input type="button" value="' . t('Find current Location') . '" title="' . t('Get the latitude and longitude for this location from the browser') . '" id="getlocations_search_geolocation_button_' . $mapid . '" class="form-submit" />&nbsp;';
    $geolocation_button .= '<span id="getlocations_search_geolocation_status_ok_' . $mapid . '" class="js-hide" ><img src="' . base_path() . GETLOCATIONS_PATH . '/images/ok.png' . '" title="' . t('Geolocation OK') . '" /></span>';
    $geolocation_button .= '<span id="getlocations_search_geolocation_status_err_' . $mapid . '" class="js-hide" ><img src="' . base_path() . GETLOCATIONS_PATH . '/images/error.png' . '" title="' . t('Geolocation failed') . '" /></span>';
    $geolocation_button .= '<span id="getlocations_search_geolocation_status_load_' . $mapid . '" class="js-hide" ><img src="' . base_path() . GETLOCATIONS_PATH . '/images/loading_small.gif' . '" title="' . t('Geolocation loading') . '" /></span>';
    $geolocation_button .= '</p>';
    $geolocation_button .= '<p>' . t('Use the browser to find your current location') . '</p></div>';
    $form['getlocations_search_geolocation_button_' . $mapid]['#markup'] = $geolocation_button;
  }

  if (isset($form['getlocations_search_country_' . $mapid]['#markup'])) {
    $restrict_country = '<p>' . t('Restrict the search to %c', array('%c' => getlocations_get_country_name($form['getlocations_search_country_' . $mapid]['#markup']))) . '</p>';
    $form['getlocations_search_country_' . $mapid]['#markup'] = $restrict_country;
  }

  // geocode button
  if (isset($form['getlocations_search_geocode_button_' . $mapid]['#markup'])) {
    $geocode_button = '<div id="getlocations_search_geocode_button_wrapper_' . $mapid . '">';
    $geocode_button .= '<input type="button" value="' . t('Geocode') . '" title="' . t('Geocode this address') . '" id="getlocations_search_geocode_button_' . $mapid . '" class="form-submit" />';
    $geocode_button .= '</div>';
    $form['getlocations_search_geocode_button_' . $mapid]['#markup'] = $geocode_button;
  }

  // reset button
  if (isset($form['getlocations_search_reset_button_' . $mapid]['#markup'])) {
    $reset_button = '<div id="getlocations_search_reset_button_wrapper_' . $mapid . '">';
    $reset_button .= '<input type="button" value="' . t('Reset') . '" title="' . t('Reset this form') . '" id="getlocations_search_reset_button_' . $mapid . '" class="form-submit" />';
    $reset_button .= '</div>';
    $form['getlocations_search_reset_button_' . $mapid]['#markup'] = $reset_button;
  }

  $output .= backdrop_render_children($form);

  // $which can be page or block so we can change things accordingly
  $output .= "<!-- $which -->";
  $output .= '<div id="getlocations_search' . ($which == 'block' ? '_block' : '') . '_result">';

  $output .= '<h4>' . t('Results') . '</h4>';
  $output .= '<div id="getlocations_search_address_' . $mapid . '"></div>';
  $output .= '<div id="getlocations_search_distance_' . $mapid . '"></div>';
  $output .= '<div id="getlocations_search_count_' . $mapid . '"></div>';
  $output .= '<div id="getlocations_search_type_' . $mapid . '"></div>';
  if ($display_accuracy) {
    $output .= '<div id="getlocations_search_accuracy_' . $mapid . '"></div>';
  }
  if ($display_latlon) {
    $output .= '<div id="getlocations_search' . ($which == 'block' ? '_block' : '') . '_latlon_wrapper">';
    if ($display_geo_microformat) {
      $output .= '<div id="getlocations_search_latlon_' . $mapid . '" class="getlocations_search' . ($which == 'block' ? '_block' : '') . '_latlon"></div>';
    }
    else {
      $output .= '<div id="getlocations_search_lat_' . $mapid . '" class="getlocations_search' . ($which == 'block' ? '_block' : '') . '_lat"></div>';
      $output .= '<div id="getlocations_search_lon_' . $mapid . '" class="getlocations_search' . ($which == 'block' ? '_block' : '') . '_lon"></div>';
    }
    $output .= '</div>';
  }
  $output .= '</div>';
  // hidden
  $output .= '<div id="getlocations_search_data_' . $mapid . '" class="js-hide">';
  $output .= '<div id="getlocations_search_slat_' . $mapid . '"></div>';
  $output .= '<div id="getlocations_search_slon_' . $mapid . '"></div>';
  $output .= '<div id="getlocations_search_sunit_' . $mapid . '"></div>';
  $output .= '<div id="getlocations_search_markerdata_' . $mapid . '"></div>';
  $output .= '</div>';

$output .= "\n<!-- /theme_getlocations_search_form -->\n";
  return $output;
}

/**
 * Themes getlocations_search settings form
 *
 * @param array $variables
 *
 * @return
 *   Returns $output
 *
 */
function theme_getlocations_search_settings_form($variables) {
  $form = $variables['form'];
  $output = '';
$output .= "\n<!-- theme_getlocations_search_settings_form -->\n";
  $varname = $form['varname']['#value'];
  unset($form['varname']);
  if (isset($form[$varname]['vocab']) ) {
    $form[$varname]['vocab']['#prefix'] = '<div id="getlocations_search_defaults_vocab">';
    $form[$varname]['vocab_element']['#suffix'] = '</div>';
  }
  $form[$varname]['useclustermanager']['#prefix'] = '<div id="wrap-getlocations-clusteropts">';
  $form[$varname]['markerclusterer_minsize']['#suffix'] = '</div>';

  $form[$varname]['usemarkermanager']['#prefix'] = '<div id="wrap-getlocations-markeropts">';
  $form[$varname]['maxzoom']['#suffix'] = '</div>';

  $form[$varname]['do_search_marker']['#suffix'] = '<div id="wrap-getlocations-search-marker">';
  $form[$varname]['search_marker_toggle_active']['#suffix'] = '</div>';

  if (module_exists('colorbox')) {
    $getlocations_colorbox = getlocations_colorbox_settings();
    if ($getlocations_colorbox['marker_enable']) {
      $link = getlocations_markerpicker_link($form[$varname]['search_marker']['#id'], 's');
      $form[$varname]['search_marker']['#field_suffix'] = '&nbsp;' . $link;
      if (isset($form[$varname]['gps_marker'])) {
        $link = getlocations_markerpicker_link($form[$varname]['gps_marker']['#id'], 'g');
        $form[$varname]['gps_marker']['#field_suffix'] = '&nbsp;' . $link;
      }
      if (isset($form[$varname]['smartip_marker'])) {
        $link = getlocations_markerpicker_link($form[$varname]['smartip_marker']['#id'], 'm');
        $form[$varname]['smartip_marker']['#field_suffix'] = '&nbsp;' . $link;
      }
    }
  }

  if (module_exists('getlocations_gps')) {
    if (isset($form[$varname]['gps_button']) && $form[$varname]['gps_button']['#type'] !== 'value' ) {
      $form[$varname]['gps_button']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('GPS Button') . '</span></legend><div class="fieldset-wrapper">';
      $tsuf = $form[$varname]['gps_center']['#suffix'];
      $form[$varname]['gps_center']['#suffix'] = $tsuf . '</div></fieldset>';
    }
  }

  if (module_exists('getlocations_smartip')) {
    if (isset($form[$varname]['smartip_button']) && $form[$varname]['smartip_button']['#type'] !== 'value' ) {
    $form[$varname]['smartip_button']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Smartip Button') . '</span></legend><div class="fieldset-wrapper">';
      $tsuf = $form[$varname]['smartip_center']['#suffix'];
      $form[$varname]['smartip_center']['#suffix'] = $tsuf . '</div></fieldset>';
    }
  }

  if (isset($form[$varname]['highlight_enable']) && $form[$varname]['highlight_enable']['#type'] !== 'value' ) {
    $form[$varname]['highlight_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Marker Highlighting') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form[$varname]['highlight_radius']['#suffix'];
    $form[$varname]['highlight_radius']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // google search places
  if (isset($form[$varname]['search_places']) && $form[$varname]['search_places']['#type'] !== 'value' ) {
    $form[$varname]['search_places']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Google Search Places') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form[$varname]['search_places_dd']['#suffix'];
    $form[$varname]['search_places_dd']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // polygons
  if (isset($form[$varname]['polygons_enable']) && $form[$varname]['polygons_enable']['#type'] !== 'value' ) {
    $form[$varname]['polygons_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Polygons') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form[$varname]['polygons_coords']['#suffix'];
    $form[$varname]['polygons_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // rectangles
  if (isset($form[$varname]['rectangles_enable']) && $form[$varname]['rectangles_enable']['#type'] !== 'value' ) {
    $form[$varname]['rectangles_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Rectangles') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form[$varname]['rectangles_coords']['#suffix'];
    $form[$varname]['rectangles_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // circles
  if (isset($form[$varname]['circles_enable']) && $form[$varname]['circles_enable']['#type'] !== 'value' ) {
    $form[$varname]['circles_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Circles') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form[$varname]['circles_coords']['#suffix'];
    $form[$varname]['circles_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // polylines
  if (isset($form[$varname]['polylines_enable']) && $form[$varname]['polylines_enable']['#type'] !== 'value' ) {
    $form[$varname]['polylines_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Polylines') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form[$varname]['polylines_coords']['#suffix'];
    $form[$varname]['polylines_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // what3words
  if (isset($form[$varname]['what3words_enable']) && $form[$varname]['what3words_enable']['#type'] !== 'value' ) {
    $form[$varname]['what3words_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('What3words') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form[$varname]['what3words_show']['#suffix'];
    $form['getlocations_default']['what3words_show']['#suffix'] = $tsuf . '</div></fieldset>';
  }


  $output .= backdrop_render_children($form);

$output .= "\n<!-- /theme_getlocations_search_settings_form -->\n";

  return $output;

}

/**
 * Themes getlocations_search_block settings form
 *
 * @param array $variables
 *
 * @return
 *   Returns $output
 *
 */
function theme_getlocations_search_block_settings_form($variables) {
  $form = $variables['form'];
  $output = '';
  $varname = $form['varname']['#value'];
  unset($form['varname']);

  if (isset($form[$varname]['vocab']) ) {
    $form[$varname]['vocab']['#prefix'] = '<div id="getlocations_search_defaults_vocab">';
    $form[$varname]['vocab_element']['#suffix'] = '</div>';
  }
  $form[$varname]['useclustermanager']['#prefix'] = '<div id="wrap-getlocations-clusteropts">';
  $form[$varname]['markerclusterer_minsize']['#suffix'] = '</div>';

  $form[$varname]['usemarkermanager']['#prefix'] = '<div id="wrap-getlocations-markeropts">';
  $form[$varname]['maxzoom']['#suffix'] = '</div>';

  $form[$varname]['do_search_marker']['#suffix'] = '<div id="wrap-getlocations-search-marker">';
  $form[$varname]['search_marker_toggle_active']['#suffix'] = '</div>';

  if (module_exists('colorbox')) {
    $getlocations_colorbox = getlocations_colorbox_settings();
    if ($getlocations_colorbox['marker_enable']) {
      $link = getlocations_markerpicker_link($form[$varname]['search_marker']['#id'], 's');
      $form[$varname]['search_marker']['#field_suffix'] = '&nbsp;' . $link;
      if (isset($form[$varname]['gps_marker'])) {
        $link = getlocations_markerpicker_link($form[$varname]['gps_marker']['#id'], 'g');
        $form[$varname]['gps_marker']['#field_suffix'] = '&nbsp;' . $link;
      }
      if (isset($form[$varname]['smartip_marker'])) {
        $link = getlocations_markerpicker_link($form[$varname]['smartip_marker']['#id'], 'm');
        $form[$varname]['smartip_marker']['#field_suffix'] = '&nbsp;' . $link;
      }
    }
  }

  if (module_exists('getlocations_gps')) {
    if (isset($form[$varname]['gps_button']) && $form[$varname]['gps_button']['#type'] !== 'value' ) {
      $form[$varname]['gps_button']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('GPS Button') . '</span></legend><div class="fieldset-wrapper">';
      $tsuf = $form[$varname]['gps_center']['#suffix'];
      $form[$varname]['gps_center']['#suffix'] = $tsuf . '</div></fieldset>';
    }
  }

  if (module_exists('getlocations_smartip')) {
    if (isset($form[$varname]['smartip_button']) && $form[$varname]['smartip_button']['#type'] !== 'value' ) {
    $form[$varname]['smartip_button']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Smartip Button') . '</span></legend><div class="fieldset-wrapper">';
      $tsuf = $form[$varname]['smartip_center']['#suffix'];
      $form[$varname]['smartip_center']['#suffix'] = $tsuf . '</div></fieldset>';
    }
  }

  $output .= backdrop_render_children($form);
  return $output;

}
