<?php

/**
 * @file
 * getlocations_leaflet.theme.inc
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * Displays locations on a map, themes
 * for Backdrop 1
 */

/**
 * Function
 *
 * @param
 *
 * @return
 *   Returns
 *
 */
function theme_getlocations_leaflet_link($variables) {
  $link_text   = $variables['link_text'];
  $entity_type = $variables['entity_type'];
  $entity_id   = $variables['entity_id'];

  $output = '';
  $path = 'getlocations_leaflet/' . $entity_type . '/' . $entity_id;
  $link = t('!l on a map', array('!l' => l($link_text, $path)));

  $output .= '<div class="getlocations_link">' . $link . '</div>';
  return $output;

}

/**
 * Function
 *
 * @param
 *
 * @return
 *   Returns
 *
 */
function theme_getlocations_leaflet_map($variables) {

  backdrop_add_library('getlocations_leaflet', 'getlocations-leaflet');
  backdrop_add_css(GETLOCATIONS_LEAFLET_PATH . '/getlocations_leaflet.css');
  $width = $variables['width'];
  $height = $variables['height'];
  $map_settings = $variables['map_settings'];
  $mapid = $variables['mapid'];
  $links = $variables['links'];

  $datanum = $map_settings['datanum'];
  $latlons = $map_settings['latlons'];
  $icons = $map_settings['icons'];
  $minmaxes = $map_settings['map_settings']['minmaxes'];
  $show_maplinks = $map_settings['map_settings']['show_maplinks'];
  unset($map_settings['datanum']);
  unset($map_settings['latlons']);
  unset($map_settings['icons']);
  unset($map_settings['map_settings']['minmaxes']);

  getlocations_leaflet_js_settings_do($map_settings, $mapid);

  $output = '';

  // links
  if (isset($links['returnlink'])) {
    $output .= '<div class="getlocations_returnlink">' . $links['returnlink'] . '</div>';
  }

  // wrap the map
  $output .= '<div class="getlocations_leaflet_map_wrapper_inner">';
  $output .= '<div id="getlocations_leaflet_wrapper_' . $mapid . '"  style="width: ' . $width . '; height: ' . $height . '" >';
  $output .= '<div class="getlocations_leaflet_canvas" id="getlocations_leaflet_canvas_' . $mapid . '" style="width: 100%; height: 100%" ></div>';
  $output .= '</div>';
  $output .= '</div>';

  // give each map its own data
  $localdata = json_encode(array(
    'datanum'  => $datanum,
    'latlons'  => $latlons,
    'icons'    => $icons,
    'minmaxes' => $minmaxes
  ));
  $output .= "\n" . '<script type="text/javascript">' . "\n" . '<!--//--><![CDATA[//><!--' . "\n";
  $output .= 'Backdrop.getlocations_leaflet_data["' . $mapid . '"] = ' . $localdata . ';' . "\n";
  $output .= '//--><!]]>' . "\n" . '</script>' . "\n";

  // show_search_distance etc
  if (module_exists('getlocations_fields') && isset($map_settings['search_dist_info'])) {
    $output .= '<div id="getlocations_fields_search_views_search_wrapper_' . $mapid . '" class="js-hide">';
    $output .= '<div id="getlocations_fields_search_views_search_units_' . $mapid . '">' . $map_settings['search_dist_info']['search_units'] . '</div>';
    $output .= '<div id="getlocations_fields_search_views_search_latitude_' . $mapid . '">' . $map_settings['search_dist_info']['latitude'] . '</div>';
    $output .= '<div id="getlocations_fields_search_views_search_longitude_' . $mapid . '">' . $map_settings['search_dist_info']['longitude'] . '</div>';
    $output .= '<div id="getlocations_fields_search_views_search_distance_meters_' . $mapid . '">' . getlocations_convert_distance_to_meters($map_settings['search_dist_info']['search_distance'], $map_settings['search_dist_info']['search_units']) . '</div>';
    $output .= '</div>';
  }

  // show maplinks if enabled
  if ($show_maplinks) {
    $output .= '<div class="getlocations_leaflet_map_links" id="getlocations_leaflet_map_links_' . $mapid . '" ><ul></ul></div>';
  }

  // buttons
  $buttons = array();

  // usermarker
  $geolocation_mobile_check = ($map_settings['map_settings']['geolocation_mobile_check'] ? FALSE : TRUE);
  if (getlocations_is_mobile($geolocation_mobile_check) && $map_settings['map_settings']['usermarker']) {
    $buttons[] = '<input type="button" value="' . $map_settings['map_settings']['usermarker_button_label'] . '" id="getlocations_leaflet_gps_show_' . $mapid . '" class="form-submit"  /><div class="getlocations_leaflet_gps_throbber getlocations_leaflet_gps_throbber_inactive" id="getlocations_leaflet_gps_throbber_' . $mapid . '">&nbsp;&nbsp;&nbsp;&nbsp;</div>';
  }
  // views_search_marker
  if (module_exists('getlocations_fields') && isset($map_settings['search_dist_info'])) {
    if ($map_settings['map_settings']['views_search_marker_enable'] && $map_settings['map_settings']['views_search_marker_toggle']) {
      $buttons[] = '<input type="button" value="' . t('Search marker !t', array('!t' => ($map_settings['map_settings']['views_search_marker_toggle_active'] ? t('Off') : t('On')))) . '" id="getlocations_leaflet_toggleSearchMarker_' . $mapid . '" class="form-submit" />';
    }
    if ($map_settings['map_settings']['views_search_radshape_enable'] && $map_settings['map_settings']['views_search_radshape_toggle']) {
      $buttons[] = '<input type="button" value="' . t('Search area !t', array('!t' => ($map_settings['map_settings']['views_search_radshape_toggle_active'] ? t('Off') : t('On')))) . '" id="getlocations_leaflet_toggleSearchArea_' . $mapid . '" class="form-submit" />';
    }
  }

  if (count($buttons)) {
    $output .= '<div class="getlocations_leaflet_map_buttons container-inline">';
    $output .= implode('&nbsp;', $buttons);
    $output .= '</div>';
  }

  // what3words
  $what3words_lic = getlocations_w3w_get_lic();
  if ($what3words_lic['key'] && $map_settings['map_settings']['what3words_enable']) {
    $output .= '<div class="getlocations_leaflet_what3words container-inline">';
    if ($map_settings['map_settings']['what3words_search']) {
      // textbox
      $output .= t('what3words') . '&nbsp;&nbsp;<input type="text" id="edit-getlocations-leaflet-what3words-search" name="edit-getlocations-leaflet-what3words-search" value="" size="' . $map_settings['map_settings']['what3words_size'] . '" class="form-text" />';
      $output .= '&nbsp;&nbsp;<input type="button" value="' . t('Search') . '" id="edit-getlocations-leaflet-what3words-search-submit" class="form-submit" />';
      $output .= '<div class="getlocations_w3w_throbber getlocations_w3w_throbber_inactive" id="getlocations_w3w_throbber_' . $mapid . '">&nbsp;&nbsp;&nbsp;&nbsp;</div>';
      $output .= '<br />';
    }
    if ($map_settings['map_settings']['what3words_show']) {
      $output .= '<div id="edit-getlocations-leaflet-what3words-show"></div>';
    }
    $output .= '</div>';
  }

  return $output;

}

/**
 * Function
 *
 * @param
 *
 * @return
 *   Returns
 *
 */
function theme_getlocations_leaflet_plugin_style_options_form($variables) {
  $form = $variables['form'];
  $form = getlocations_leaflet_display_options_fieldsets($form);
  $output = '';
  $output .= backdrop_render_children($form);
  return $output;
}

/**
 * Function
 *
 * @param
 *
 * @return
 *   Returns
 *
 */
function theme_getlocations_leaflet_settings_form($variables) {
  $form = $variables['form'];
  $output = '';
  $form['getlocations_leaflet_defaults']['returnlink_page_link']['#prefix'] = '<div id="wrap-page-link">';
  $form['getlocations_leaflet_defaults']['returnlink_page_link']['#suffix'] = '</div>';
  if (isset($form['getlocations_leaflet_defaults']['returnlink_user_link'])) {
    $form['getlocations_leaflet_defaults']['returnlink_user_link']['#prefix'] = '<div id="wrap-user-link">';
    $form['getlocations_leaflet_defaults']['returnlink_user_link']['#suffix'] = '</div>';
  }
  if (isset($form['getlocations_leaflet_defaults']['returnlink_term_link'])) {
    $form['getlocations_leaflet_defaults']['returnlink_term_link']['#prefix'] = '<div id="wrap-term-link">';
    $form['getlocations_leaflet_defaults']['returnlink_term_link']['#suffix'] = '</div>';
  }
  if (isset($form['getlocations_leaflet_defaults']['returnlink_comment_link'])) {
    $form['getlocations_leaflet_defaults']['returnlink_comment_link']['#prefix'] = '<div id="wrap-comment-link">';
    $form['getlocations_leaflet_defaults']['returnlink_comment_link']['#suffix'] = '</div>';
  }

  // polygons
  if (isset($form['getlocations_leaflet_defaults']['polygons_group']['polygons_enable']) && $form['getlocations_leaflet_defaults']['polygons_group']['polygons_enable']['#type'] !== 'value' ) {
    $form['getlocations_leaflet_defaults']['polygons_group']['polygons_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Polygons') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_leaflet_defaults']['polygons_group']['polygons_coords']['#suffix'];
    $form['getlocations_leaflet_defaults']['polygons_group']['polygons_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }


  // rectangles
  if (isset($form['getlocations_leaflet_defaults']['rectangles_group']['rectangles_enable']) && $form['getlocations_leaflet_defaults']['rectangles_group']['rectangles_enable']['#type'] !== 'value' ) {
    $form['getlocations_leaflet_defaults']['rectangles_group']['rectangles_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Rectangles') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_leaflet_defaults']['rectangles_group']['rectangles_coords']['#suffix'];
    $form['getlocations_leaflet_defaults']['rectangles_group']['rectangles_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // circles
  if (isset($form['getlocations_leaflet_defaults']['circles_group']['circles_enable']) && $form['getlocations_leaflet_defaults']['circles_group']['circles_enable']['#type'] !== 'value' ) {
    $form['getlocations_leaflet_defaults']['circles_group']['circles_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Circles') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_leaflet_defaults']['circles_group']['circles_coords']['#suffix'];
    $form['getlocations_leaflet_defaults']['circles_group']['circles_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // polylines
  if (isset($form['getlocations_leaflet_defaults']['polylines_group']['polylines_enable']) && $form['getlocations_leaflet_defaults']['polylines_group']['polylines_enable']['#type'] !== 'value' ) {
    $form['getlocations_leaflet_defaults']['polylines_group']['polylines_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Polylines') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_leaflet_defaults']['polylines_group']['polylines_coords']['#suffix'];
    $form['getlocations_leaflet_defaults']['polylines_group']['polylines_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['getlocations_leaflet_defaults']['views_search_group']['views_search_marker_enable']) && $form['getlocations_leaflet_defaults']['views_search_group']['views_search_marker_enable']['#type'] !== 'value' ) {
    $form['getlocations_leaflet_defaults']['views_search_group']['views_search_marker_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Views Search') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_leaflet_defaults']['views_search_group']['views_search_radshape_toggle_active']['#suffix'];
    $form['getlocations_leaflet_defaults']['views_search_group']['views_search_radshape_toggle_active']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // mapbox
  if (module_exists('getlocations_mapbox')) {
    $mapnum = $form['getlocations_leaflet_mapbox']['mapnum']['#value'];
    unset($form['getlocations_leaflet_mapbox']['mapnum']);
    for ($ct = 0; $ct < $mapnum; $ct++) {
      $form['getlocations_leaflet_mapbox']['mapbox_info'][$ct]['label']['#prefix'] = '<fieldset class="getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('MapBox map @n', array('@n' => $ct + 1)) . '</span></legend><div class="fieldset-wrapper">';
      $form['getlocations_leaflet_mapbox']['mapbox_info'][$ct]['type']['#suffix'] = '</div></fieldset>';
    }
  }

  // preview leaflet
  if (isset($form['getlocations_leaflet_preview']['preview_map']['#markup'])) {
    $links = array();
    $nodezoom = FALSE;
    $iconlist = array();

    $getlocations_leaflet_defaults = getlocations_leaflet_defaults();
    $map_settings = getlocations_leaflet_map_get_info('Getlocations OSM');
    $map_settings = getlocations_leaflet_get_map_layers($map_settings);
    if (! empty($getlocations_leaflet_defaults['baselayers'])) {
      $map_layers = array();
      foreach ($getlocations_leaflet_defaults['baselayers'] AS $k => $v) {
        if (isset($map_settings['map_layers'][$k]) && $getlocations_leaflet_defaults['baselayers'][$k]) {
          $map_layers[$k] = $map_settings['map_layers'][$k];
        }
      }
      if (! empty($map_layers)) {
        $map_settings['map_layers'] = $map_layers;
      }
    }
    $ll = explode(',', $getlocations_leaflet_defaults['latlong']);
    $map_settings['map_opts']['center'] = array($ll[0], $ll[1]);
    $map_settings['map_opts']['zoom'] = $getlocations_leaflet_defaults['zoom'];
    $mapid = getlocations_setup_map('', FALSE, FALSE, TRUE);
    $latlons = array();
    $minmaxes = array();
    $map_settings['map_settings']['dragging'] = TRUE;
    // add in some more
    $map_settings = getlocations_leaflet_map_settings_do($map_settings, $getlocations_leaflet_defaults, $latlons, $mapid);
    $map_settings['map_settings']['nodezoom'] = ($nodezoom ? $nodezoom : $getlocations_leaflet_defaults['nodezoom']);
    $map_settings['map_settings']['minmaxes'] = (empty($minmaxes) ? FALSE : implode(',', $minmaxes));
    $map_settings['icons'] = $iconlist;
    $map_settings['datanum'] = 0;
    $map_settings['latlons'] = $latlons;
    $map_settings['extcontrol'] = 'preview_map';

    $preview_map = theme('getlocations_leaflet_map', array(
        'width' => $getlocations_leaflet_defaults['width'],
        'height' => $getlocations_leaflet_defaults['height'],
        'map_settings' => $map_settings,
        'mapid' => $mapid,
        'links' => $links
      )
    );

    $form['getlocations_leaflet_preview']['preview_map']['#markup'] = '<div id="getlocations_leaflet_preview_map">' . $preview_map . '</div>';
  }

  $output .= backdrop_render_children($form);
  return $output;
}

function theme_getlocations_leaflet_display_options_form($variables) {
  $form = $variables['form'];
  $form = getlocations_leaflet_display_options_fieldsets($form);
  $output = '';
  $output .= backdrop_render_children($form);
  return $output;
}

function getlocations_leaflet_display_options_fieldsets($form) {

  if (isset($form['zoomControl']) && $form['zoomControl']['#type'] !== 'value') {
    $form['zoomControl']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Zoom Control') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['zoomcontrolposition']['#suffix'];
    $form['zoomcontrolposition']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['scaleControl']) && $form['scaleControl']['#type'] !== 'value') {
    $form['scaleControl']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Scale Control') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['scalecontrolposition']['#suffix'];
    $form['scalecontrolposition']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['attributionControl']) && $form['attributionControl']['#type'] !== 'value') {
    $form['attributionControl']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Attribution Control') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['attributioncontrolposition']['#suffix'];
    $form['attributioncontrolposition']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['geocoder']) && $form['geocoder']['#type'] !== 'value') {
    $form['geocoder']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Geocoder') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['geocodercollapsed']['#suffix'];
    $form['geocodercollapsed']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['usermarker']) && $form['usermarker']['#type'] !== 'value') {
    $form['usermarker']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('User marker') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['usermarker_circle_fillopacity']['#suffix'];
    $form['usermarker_circle_fillopacity']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['bouncemarker']) && $form['bouncemarker']['#type'] !== 'value') {
    $form['bouncemarker']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Bounce marker') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['bouncemarker_height']['#suffix'];
    $form['bouncemarker_height']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['magnifyingglass']) && $form['magnifyingglass']['#type'] !== 'value') {
    $form['magnifyingglass']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Magnifying Glass') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['magnifyingglasszoomoffset']['#suffix'];
    $form['magnifyingglasszoomoffset']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['terminator']) && $form['terminator']['#type'] !== 'value' ) {
    $form['terminator']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Day/Night Layer') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['terminator_label']['#suffix'];
    $form['terminator_label']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['layerControl']) && $form['layerControl']['#type'] !== 'value' ) {
    $form['layerControl']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Layer Control') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['layercontrolposition']['#suffix'];
    $form['layercontrolposition']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['fullscreen']) && $form['fullscreen']['#type'] !== 'value' ) {
    $form['fullscreen']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Fullscreen Control') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['fullscreenposition']['#suffix'];
    $form['fullscreenposition']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['graticule']) && $form['graticule']['#type'] !== 'value' ) {
    $form['graticule']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Graticule Control') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['graticule_ov_label']['#suffix'];
    $form['graticule_ov_label']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['mouseposition']) && $form['mouseposition']['#type'] !== 'value' ) {
    $form['mouseposition']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Mouse position Control') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['mouseposition_display_dms']['#suffix'];
    $form['mouseposition_display_dms']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['pancontrol']) && $form['pancontrol']['#type'] !== 'value' ) {
    $form['pancontrol']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Pan Control') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['pancontrolposition']['#suffix'];
    $form['pancontrolposition']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['zoomslider']) && $form['zoomslider']['#type'] !== 'value' ) {
    $form['zoomslider']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Zoom Slider Control') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['zoomsliderposition']['#suffix'];
    $form['zoomsliderposition']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['mapquest_maps_use']) && $form['mapquest_maps_use']['#type'] !== 'value' ) {
    $form['mapquest_maps_use']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Mapquest Maps') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['mapquest_traffic_incident_on']['#suffix'];
    $form['mapquest_traffic_incident_on']['#suffix'] = $tsuf . '</div></fieldset>';
  }
########
  // polygons
  if (isset($form['polygons_enable']) && $form['polygons_enable']['#type'] !== 'value' ) {
    $form['polygons_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Polygons') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['polygons_coords']['#suffix'];
    $form['polygons_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // rectangles
  if (isset($form['rectangles_enable']) && $form['rectangles_enable']['#type'] !== 'value' ) {
    $form['rectangles_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Rectangles') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['rectangles_coords']['#suffix'];
    $form['rectangles_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // circles
  if (isset($form['circles_enable']) && $form['circles_enable']['#type'] !== 'value' ) {
    $form['circles_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Circles') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['circles_coords']['#suffix'];
    $form['circles_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // polylines
  if (isset($form['polylines_enable']) && $form['polylines_enable']['#type'] !== 'value' ) {
    $form['polylines_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Polylines') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['polylines_coords']['#suffix'];
    $form['polylines_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // what3words
  if (isset($form['what3words_enable']) && $form['what3words_enable']['#type'] !== 'value' ) {
    $form['what3words_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('What3words') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['what3words_show']['#suffix'];
    $form['what3words_show']['#suffix'] = $tsuf . '</div></fieldset>';
  }

########

  return $form;
}
