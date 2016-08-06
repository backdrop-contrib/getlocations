<?php

/**
 * @file
 * getlocations.theme.inc
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * Displays locations on a map, themes
 * for Backdrop 1
 * using version 3 googlemaps API
 */

/**
 * Returns HTML for a map.
 *
 * All the map displays pass through here.
 *
 * @param array $variables
 *   An associative array containing:
 *   - width: The width of the map.
 *   - height: The height of the map.
 *   - defaults: The settings to be applied to the map, links, buttons and form elements.
 *   - mapid: The unique identifier for the map.
 *   - type: The entity type, eg node, user, term or comment.
 *   - node: The entity object.
 *
 * @return string $output
 *
 * @ingroup themeable
 *
 */
function theme_getlocations_show($variables) {
  $width = $variables['width'];
  $height = $variables['height'];
  $defaults = $variables['defaults'];
  $mapid = $variables['mapid'];
  $type = $variables['type'];
  $node = $variables['node'];

  $latlons = $variables['latlons'];
  $minmaxes = $variables['minmaxes'];
  $datanum = count($latlons);

  $output = '';
  $output .= "\n" . '<!-- theme_getlocations_show -->' . "\n";
  $returnlink = FALSE;
  // return link
  $returnlink_group = $defaults['returnlink_group'];
  if ($type == 'node' && $returnlink_group['returnlink_page_enable']) {
    if (is_object($node)) {
      $linktext = $returnlink_group['returnlink_page_link'];
      if ( preg_match("/%t/", $linktext)) {
        $linktext = preg_replace("/%t/", $node->title, $linktext);
      }
      $l = l($linktext, 'node/' . $node->nid);
      $returnlink = '<div class="getlocations_returnlink">' . $l . '</div>';
    }
  }
  elseif ($type == 'user' && $returnlink_group['returnlink_user_enable']) {
    if (is_object($node)) {
      $linktext = $returnlink_group['returnlink_user_link'];
      if ( preg_match("/%n/", $linktext)) {
        $linktext = preg_replace("/%n/", $node->name, $linktext);
      }
      $l = l($linktext, 'user/' . $node->uid);
      $returnlink = '<div class="getlocations_returnlink">' . $l . '</div>';
    }
  }
  elseif ($type == 'term' && $returnlink_group['returnlink_term_enable'] && module_exists('taxonomy')) {
    if (is_object($node)) {
      $linktext = $returnlink_group['returnlink_term_link'];
      if ( preg_match("/%n/", $linktext)) {
        $linktext = preg_replace("/%n/", $node->name, $linktext);
      }
      $l = l($linktext, 'taxonomy/term/' . $node->tid);
      $returnlink = '<div class="getlocations_returnlink">' . $l . '</div>';
    }
  }
  elseif ($type == 'comment' && $returnlink_group['returnlink_comment_enable'] && module_exists('comment')) {
    if (is_object($node)) {
      $linktext = $returnlink_group['returnlink_comment_link'];
      if ( preg_match("/%n/", $linktext)) {
        $linktext = preg_replace("/%n/", $node->subject, $linktext);
      }
      $l = l($linktext, 'comment/' . $node->cid);
      $returnlink = '<div class="getlocations_returnlink">' . $l . '</div>';
    }
  }
  if ($returnlink) {
    $output .= $returnlink;
  }

  if ($defaults['map_resize'] && getlocations_is_mobile()) {
    $width = '100%';
    #$height = '100%';
  }

  // show maplinks if enabled
  if ($defaults['show_maplinks']) {
    $output .= '<a id="maptop_' . $mapid . '" name="maptop_' . $mapid . '"></a>';
  }
  // search_places
  $sp = '';
  $search_places_group = $defaults['search_places_group'];
  if ($search_places_group['search_places']) {

    $sp .= '<div class="search_places_input_wrapper">';
    if ($search_places_group['search_places_label']) {
      $sp .= '<label for="search_places_select_' . $mapid . '">' . $search_places_group['search_places_label'] . '</label>';
    }

    if ($search_places_group['search_places_dd']) {
      // alternative dropdown
      #$sp_config = config('getlocations.search_places_opts');
      #$sp_opts = $sp_config->get('opts');
      $sp_opts = config_get('getlocations.search_places_opts', 'opts');

      $sp .= '<select id="search_places_select_' . $mapid . '" class="form-select" >';
      foreach ($sp_opts AS $k_opt => $opt) {
        $sel = '';
        if ($k_opt == 'establishment') {
          $sel = 'selected';
        }
        $sp .= '<option value="' . $k_opt . '" ' . $sel . '>' . $opt . '</option>';
      }
      $sp .= '</select>';
      $sp .= '&nbsp;&nbsp;<input type="button" value="' . t('Go') . '" id="search_places_go_btn_' . $mapid . '" class="form-submit" />';
      $sp .= '&nbsp;&nbsp;<input type="button" value="' . t('Reset') . '" onClick="Backdrop.getlocations_search_places_clearmarkers(\'' . $mapid . '\', true)"  class="form-submit" />';
      $sp .= '</div>';
    }
    else {
      $placeholder = '';
      if ($search_places_group['search_places_placeholder']) {
        $placeholder = 'placeholder="' . $search_places_group['search_places_placeholder'] . '"';
      }
      $sp .= '<input type="text" id="search_places_input_' . $mapid . '" size="' . $search_places_group['search_places_size'] . '" class="form-text" ' . $placeholder . ' />';
      $sp .= '&nbsp;&nbsp;<input type="button" value="' . t('Reset') . '" onClick="Backdrop.getlocations_search_places_clearmarkers(\'' . $mapid . '\', true)"  class="form-submit" />';
      $sp .= '</div>';
    }
    if ($search_places_group['search_places_list']) {
      $sp .= '<div class="sp_listing_wrapper"><h4>' . t('Google Places search results') . '</h4><div class="sp_listing"><ul class="sp_ul" id="search_places_results_' . $mapid . '"></ul></div></div>';
    }
  }
  if ($search_places_group['search_places'] && $search_places_group['search_places_position'] == 'outside_above') {
    $output .= $sp;
  }

  // type class
  $class = '';
  if ($type) {
    $class = ' getlocations_' . $type;
  }

  // wrap the map
  $output .= '<div class="getlocations_map_wrapper_inner' . $class . '">';
  $output .= '<div id="getlocations_map_wrapper_' . $mapid . '"  style="width: ' . $width . '; height: ' . $height . '" >';
  $output .= '<div class="getlocations_map_canvas" id="getlocations_map_canvas_' . $mapid . '" style="width: 100%; height: 100%" ></div>';
  $output .= '</div>';
  $output .= '</div>'; // getlocations_map_wrapper_inner


  // give each map its own data
  $localdata = json_encode(array(
    'datanum'  => $datanum,
    'latlons'  => $latlons,
    'minmaxes' => $minmaxes
  ));
  $output .= "\n" . '<script type="text/javascript">' . "\n" . '<!--//--><![CDATA[//><!--' . "\n";
  $output .= 'Backdrop.getlocations_data["' . $mapid . '"] = ' . $localdata . ';' . "\n";
  $output .= '//--><!]]>' . "\n" . '</script>' . "\n";

  // show_search_distance
  if (module_exists('getlocations_fields')) {
    $search_dist_info = $defaults['search_dist_info'];
    $output .= '<div id="getlocations_fields_search_views_search_wrapper_' . $mapid . '" class="js-hide">';
    $output .= '<div id="getlocations_fields_search_views_search_units_' . $mapid . '">' . $search_dist_info['search_units'] . '</div>';
    $output .= '<div id="getlocations_fields_search_views_search_latitude_' . $mapid . '">' . $search_dist_info['latitude'] . '</div>';
    $output .= '<div id="getlocations_fields_search_views_search_longitude_' . $mapid . '">' . $search_dist_info['longitude'] . '</div>';
    $output .= '<div id="getlocations_fields_search_views_search_distance_meters_' . $mapid . '">' . getlocations_convert_distance_to_meters($search_dist_info['search_distance'], $search_dist_info['search_units']) . '</div>';
    $output .= '</div>';
  }

  // show maplinks if enabled
  if ($defaults['show_maplinks']) {
    $output .= '<div class="getlocations_map_links" id="getlocations_map_links_' . $mapid . '" ><ul></ul></div>';
  }
  // buttons
  $buttons = array();
  if ($defaults['trafficinfo']) {
    $buttons[] = '<input type="button" value="' . t('Traffic Info !t', array('!t' => ($defaults['trafficinfo_state'] ? t('Off') : t('On')))) . '" title="' . t('Limited Availability') . '" id="getlocations_toggleTraffic_' . $mapid . '" class="form-submit" />';
  }
  if ($defaults['bicycleinfo']) {
    $buttons[] = '<input type="button" value="' . t('Bicycle Info !t', array('!t' => ($defaults['bicycleinfo_state'] ? t('Off') : t('On')))) . '" title="' . t('Limited Availability') . '" id="getlocations_toggleBicycle_' . $mapid . '" class="form-submit" />';
  }
  if ($defaults['transitinfo']) {
    $buttons[] = '<input type="button" value="' . t('Transit Info !t', array('!t' => ($defaults['transitinfo_state'] ? t('Off') : t('On')))) . '" title="' . t('Limited Availability') . '" id="getlocations_toggleTransit_' . $mapid . '" class="form-submit" />';
  }

#  // views_search_marker
  if (module_exists('getlocations_fields') ) {
    $views_search_group = $defaults['views_search_group'];
    if ($views_search_group['views_search_marker_enable'] && $views_search_group['views_search_marker_toggle']) {
      $buttons[] = '<input type="button" value="' . t('Search marker !t', array('!t' => ($views_search_group['views_search_marker_toggle_active'] ? t('Off') : t('On')))) . '" id="getlocations_toggleSearchMarker_' . $mapid . '" class="form-submit" />';
    }
    if ($views_search_group['views_search_radshape_enable'] && $views_search_group['views_search_radshape_toggle']) {
      $buttons[] = '<input type="button" value="' . t('Search area !t', array('!t' => ($views_search_group['views_search_radshape_toggle_active'] ? t('Off') : t('On')))) . '" id="getlocations_toggleSearchArea_' . $mapid . '" class="form-submit" />';
    }
  }

  // categories
  if ($defaults['category_showhide_buttons']) {
    if ($defaults['categories']) {
      foreach ($defaults['categories'] AS $cat => $label) {
        $buttons[] = '<input type="button" value="' . t('!cat Off', array('!cat' => $label)) . '" id="getlocations_toggle_' . $cat . '_' . $mapid . '" class="form-submit" />';
      }
    }
  }

  // KML
  $kml_group = $defaults['kml_group'];
  if ($kml_group['kml_url'] && $kml_group['kml_url_button']) {
    $kmlbuttonlabel = t('Kml Layer');
    if ($kml_group['kml_url_button_label']) {
      $kmlbuttonlabel = $kml_group['kml_url_button_label'];
    }
    $kmlbuttonlabel .= ' ' . ($kml_group['kml_url_button_state'] ? t('Off') : t('On'));
    $buttons[] = '<input type="button" value="' . $kmlbuttonlabel . '" id="getlocations_toggleKmlLayer_' . $mapid . '" class="form-submit"  />';
  }

  if (module_exists('getlocations_search')) {
    // search area shape
    if (isset($defaults['search_radshape_toggle']) && $defaults['search_radshape_toggle'] && $defaults['search_radshape_enable']) {
      $buttons[] = '<input type="button" value="' . t('Search area !t', array('!t' => ($defaults['search_radshape_toggle_active'] ? t('Off') : t('On')))) . '" id="getlocations_search_toggleShape_' . $mapid . '" class="form-submit" />';
    }
    // search marker toggle button
    if (isset($defaults['do_search_marker']) && $defaults['do_search_marker'] && $defaults['search_marker_toggle']) {
      $buttons[] = '<input type="button" value="' . t('Marker !t', array('!t' => ($defaults['search_marker_toggle_active'] ? t('Off') : t('On')))) . '" id="getlocations_search_toggleMarker_' . $mapid . '" class="form-submit" />';
    }
  }

  // getlocations_gps
  if (module_exists('getlocations_gps')) {
    $getlocations_gps_defaults = getlocations_gps_defaults();
    if ($getlocations_gps_defaults['gps_button']) {
      $buttons[] = theme('getlocations_gps_button', array('defaults' => $getlocations_gps_defaults, 'mapid' => $mapid));
    }
  }

  // getlocations_smartip
  if (module_exists('getlocations_smartip')) {
    $getlocations_smartip_defaults = getlocations_smartip_defaults();
    if ($getlocations_smartip_defaults['smartip_button']) {
      $buttons[] = theme('getlocations_smartip_button', array('defaults' => $getlocations_smartip_defaults, 'mapid' => $mapid));
    }
  }

  if (count($buttons)) {
    $output .= '<div class="getlocations_map_buttons container-inline">';
    $output .= implode('&nbsp;', $buttons);
    $output .= '</div>';
  }

  // search_places

  if ($search_places_group['search_places'] && $search_places_group['search_places_position'] == 'outside_below') {
    $output .= $sp;
  }

  // what3words
  $what3words_lic = $defaults['what3words_lic'];
  $what3words_group = getlocations_w3w_get_group();
  if ($what3words_lic['key'] && $what3words_group['what3words_enable']) {
    $output .= '<div class="getlocations_what3words container-inline">';
    if ($what3words_group['what3words_search']) {
      // textbox
      $output .= t('what3words') . '&nbsp;&nbsp;<input type="text" id="edit-getlocations-what3words-search" name="edit-getlocations-what3words-search" value="" size="' . $defaults['what3words_size'] . '" class="form-text" />';
      $output .= '&nbsp;&nbsp;<input type="button" value="' . t('Search') . '" id="edit-getlocations-what3words-search-submit" class="form-submit" />';
      $output .= '<div class="getlocations_w3w_throbber getlocations_w3w_throbber_inactive" id="getlocations_w3w_throbber_' . $mapid . '">&nbsp;&nbsp;&nbsp;&nbsp;</div>';
      $output .= '<br />';
    }
    if ($what3words_group['what3words_show']) {
      $output .= '<div id="edit-getlocations-what3words-show"></div>';
    }
    $output .= '</div>';
  }
  $output .= "\n" . '<!-- /theme_getlocations_show -->' . "\n";

  return $output;
}

/**
 * Returns HTML of a location's vcard, requested by ajax.
 *
 * @param array $variables
 *   An associative array containing:
 *   - location: The information pertaining to the address to be formatted.
 *
 * @return string $output
 *
 * @ingroup themeable
 *
 */
function theme_getlocations_adinfo($variables) {
  $location = $variables['location'];
  $output = '';

  $output .= '<div class="location vcard">';

  // this logic gives the location name field precedence over the node title
  // similarly for users, terms and comments
  $link = FALSE;
  $l =  FALSE;
  if (isset($location['nid']) && $location['nid'] > 0) {
    if (! empty($location['name'])) {
      $link = $location['name'];
    }
    else {
      $node = node_load($location['nid']);
      $link = $node->title;
    }
    $l = l($link, 'node/' . $location['nid'], array('attributes' => array('class' => array('getlocations_infolink'), 'target' => '_parent')));
  }
  elseif (isset($location['uid']) && $location['uid'] > 0) {
    if (! empty($location['name'])) {
      $link = $location['name'];
    }
    else {
      $account = user_load($location['uid']);
      $link = $account->name;
    }
    $l = l($link, 'user/' . $location['uid'], array('attributes' => array('class' => array('getlocations_infolink'), 'target' => '_parent')));
  }
  elseif (isset($location['tid']) && $location['tid'] > 0 && module_exists('taxonomy')) {
    if (! empty($location['name'])) {
      $link = $location['name'];
    }
    else {
      $term = taxonomy_term_load($location['tid']);
      $link = $term->name;
    }
    $l = l($link, 'taxonomy/term/' . $location['tid'], array('attributes' => array('class' => array('getlocations_infolink'), 'target' => '_parent')));
  }
  elseif (isset($location['cid']) && $location['cid'] > 0 && module_exists('comment')) {
    if (! empty($location['name'])) {
      $link = $location['name'];
    }
    else {
      $comment = comment_load($location['cid']);
      $link = $comment->subject;
    }
    $l = l($link, 'comment/' . $location['cid'], array('attributes' => array('class' => array('getlocations_infolink'), 'target' => '_parent')));
  }
  if ($l) {
    $output .= '<h4>' . $l . '</h4>';
  }

  $output .= '<div class="adr">';
  if (! empty($location['street'])) {
    $output .= '<div class="street-address">' . $location['street'];
    if (! empty($location['additional'])) {
      $output .= "&nbsp;" . '<span class="extended-address">' . $location['additional'] . '</span>';
    }
    $output .= '</div>';
  }
  if (! empty($location['city'])) {
    $output .= '<span class="locality">' . $location['city'] . '</span>';
    if (! empty($location['province_name'])) {
      $output .= ",&nbsp;";
    }
    elseif (! empty($location['province'])) {
      $output .= ",&nbsp;";
    }
    else {
      $output .= "&nbsp;";
    }
  }
  if (isset($location['province_name']) && ! empty($location['province_name'])) {
    $output .= '<span class="region">' . $location['province_name'] . '</span>';
    if (! empty($location['postal_code'])) {
      $output .= "&nbsp;";
    }
  }
  elseif (isset($location['province']) && ! empty($location['province'])) {
    $output .= '<span class="region">' . $location['province'] . '</span>';
    if (! empty($location['postal_code'])) {
      $output .= "&nbsp;";
    }
  }
  if (! empty($location['postal_code'])) {
    $output .= '<span class="postal-code">' . backdrop_strtoupper($location['postal_code']) . '</span>';
  }
  if (isset($location['country_name']) && ! empty($location['country_name'])) {
    $output .= '<div class="country-name">' . $location['country_name'] . '</div>';
  }
  elseif (isset($location['country']) && ! empty($location['country'])) {
    $output .= '<div class="country-name">' . $location['country'] . '</div>';
  }
  $output .= '</div>';
  if (isset($location['sdist'])) {
    if ($location['sdist'] <> 1) {
      $unit_disp = getlocations_get_unit_names($location['sunit']);
    }
    else {
      $unit_disp = getlocations_get_unit_names($location['sunit'], 'single');
    }
    $output .= '<div class="search-distance">' . number_format(floatval($location['sdist']), 2) . "&nbsp;" . $unit_disp . '</div>';
  }

  if (module_exists('getdirections') && isset($location['getdirections_link']) && $location['getdirections_link']) {
    $gdlink = '';
    if (isset($location['nid']) && $location['nid']) {
      $gdlink = l(t('Directions'), 'getdirections/location/to/' . $location['nid'], array('attributes' => array('class' => array('getlocations_infolink'), 'target' => '_parent')));
    }
    elseif (isset($location['uid']) && $location['uid']) {
      $gdlink = l(t('Directions'), 'getdirections/location_user/to/' . $location['uid'], array('attributes' => array('class' => array('getlocations_infolink'), 'target' => '_parent')));
    }
    elseif (isset($location['cid']) && $location['cid'] && getdirections_check_entity_type('comment')) {
      $gdlink = l(t('Directions'), 'getdirections/location_comment/to/' . $location['cid'], array('attributes' => array('class' => array('getlocations_infolink'), 'target' => '_parent')));
    }
    elseif (isset($location['tid']) && $location['tid'] && getdirections_get_vocabularies()) {
      $gdlink = l(t('Directions'), 'getdirections/location_term/to/' . $location['tid'], array('attributes' => array('class' => array('getlocations_infolink'), 'target' => '_parent')));
    }
    if ($gdlink) {
      $output .= '<div class="getdirections-link">' . $gdlink . '</div>';
    }
  }


  $output .= '</div>';

  return $output;
}

/**
 * Returns HTML of the getlocations plugin_style_map_options form.
 *
 * @param array $variables
 *   An associative array containing:
 *   - form: The form array.
 *
 * @return string The rendered form
 *
 * @ingroup themeable
 *
 */
/*
 *
 * name: theme_getlocations_plugin_style_map_options_form
 * @param
 * @return
 *
 */
function theme_getlocations_plugin_style_map_options_form($variables) {
  $form = $variables['form'];

  if (module_exists('colorbox')) {
    $getlocations_colorbox = getlocations_colorbox_settings();
    if ($getlocations_colorbox['marker_enable']) {
      if (isset($form['node_map_marker'])) {
        $link = getlocations_markerpicker_link($form['node_map_marker']['#id'], 'n');
        $form['node_map_marker']['#field_suffix'] = '&nbsp;' . $link;
      }
      $getlocations_node_marker = config_get('getlocations_node_marker', array('enable' => 0));
      if ($getlocations_node_marker['enable']) {
        if ($types = getlocations_get_types()) {
          foreach ($types AS $type => $name) {
            $field_names = getlocations_get_fieldname2($type, 'node');
            foreach ($field_names AS $field_name) {
              $mkey = 'node_marker__' . backdrop_strtolower($type) . '__' . $field_name;
              $link = getlocations_markerpicker_link($form[$mkey]['#id'], 'n');
              $form[$mkey]['#field_suffix'] = '&nbsp;' . $link;
            }
          }
        }
      }
      if (isset($form['user_map_marker'])) {
        $link = getlocations_markerpicker_link($form['user_map_marker']['#id'], 'u');
        $form['user_map_marker']['#field_suffix'] = '&nbsp;' . $link;
      }

      if (module_exists('taxonomy')) {
        if (isset($form['vocabulary_map_marker'])) {
          $link = getlocations_markerpicker_link($form['vocabulary_map_marker']['#id'], 'v');
          $form['vocabulary_map_marker']['#field_suffix'] = '&nbsp;' . $link;
        }
        $getlocations_vocabulary_marker = config_get('getlocations_vocabulary_marker', array('enable' => 0));
        if ($getlocations_vocabulary_marker['enable']) {
          foreach ($types AS $type => $name) {
            $field_name = getlocations_get_fieldname($type, 'taxonomy_term');
            $mkey = 'vocabulary_marker_' . $field_name;
            $link = getlocations_markerpicker_link($form[$mkey]['#id'], 'v');
            $form[$mkey]['#field_suffix'] = '&nbsp;' . $link;
          }
        }
        if (isset($form['term_map_marker'])) {
          $link = getlocations_markerpicker_link($form['term_map_marker']['#id'], 't');
          $form['term_map_marker']['#field_suffix'] = '&nbsp;' . $link;
        }
        $getlocations_term_marker = config_get('getlocations_term_marker', array('enable' => 0, 'vids' => 0, 'max_depth' => ''));
        if ($getlocations_term_marker['enable'] && $getlocations_term_marker['vids']) {
          $depth = is_numeric($getlocations_term_marker['max_depth']) && $getlocations_term_marker['max_depth'] > 0 ? $getlocations_term_marker['max_depth'] : NULL;
          $vids = $getlocations_term_marker['vids'];
          foreach ($vids AS $vid) {
            $terms = taxonomy_get_tree($vid, 0, $depth);
            foreach ($terms AS $term) {
              $name = $term->name;
              $tid = $term->tid;
              $mkey = 'term_marker_' . $tid;
              $link = getlocations_markerpicker_link($form[$mkey]['#id'], 't');
              $form[$mkey]['#field_suffix'] = '&nbsp;' . $link;
            }
          }
        }
      }

      if (isset($form['comment_map_marker'])) {
        $link = getlocations_markerpicker_link($form['comment_map_marker']['#id'], 'c');
        $form['comment_map_marker']['#field_suffix'] = '&nbsp;' . $link;
      }

      if (isset($form['gps_marker'])) {
        $link = getlocations_markerpicker_link($form['gps_marker']['#id'], 'g');
        $form['gps_marker']['#field_suffix'] = '&nbsp;' . $link;
      }

      if (isset($form['smartip_marker'])) {
        $link = getlocations_markerpicker_link($form['smartip_marker']['#id'], 'm');
        $form['smartip_marker']['#field_suffix'] = '&nbsp;' . $link;
      }

    }
  }

  if (isset($form['gps_button']) && $form['gps_button']['#type'] !== 'value' ) {
    $form['gps_button']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('GPS Button') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['gps_center']['#suffix'];
    $form['gps_center']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['smartip_button']) && $form['smartip_button']['#type'] !== 'value' ) {
    $form['smartip_button']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Smartip Button') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['smartip_center']['#suffix'];
    $form['smartip_center']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // geojson
  if (isset($form['geojson_enable']) && $form['geojson_enable']['#type'] !== 'value' ) {
    $form['geojson_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Geojson') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['geojson_options']['#suffix'];
    $form['geojson_options']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['highlight_group']['highlight_enable']) && $form['highlight_group']['highlight_enable']['#type'] !== 'value' ) {
    $form['highlight_group']['highlight_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Marker Highlighting') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['highlight_group']['highlight_radius']['#suffix'];
    $form['highlight_group']['highlight_radius']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // google search places
  if (isset($form['search_places_group']['search_places']) && $form['search_places_group']['search_places']['#type'] !== 'value' ) {
    $form['search_places_group']['search_places']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Google Search Places') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['search_places_group']['search_places_dd']['#suffix'];
    $form['search_places_group']['search_places_dd']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // polygons
  if (isset($form['polygons_group']['polygons_enable']) && $form['polygons_group']['polygons_enable']['#type'] !== 'value' ) {
    $form['polygons_group']['polygons_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Polygons') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['polygons_group']['polygons_coords']['#suffix'];
    $form['polygons_group']['polygons_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // rectangles
  if (isset($form['rectangles_group']['rectangles_enable']) && $form['rectangles_group']['rectangles_enable']['#type'] !== 'value' ) {
    $form['rectangles_group']['rectangles_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Rectangles') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['rectangles_group']['rectangles_coords']['#suffix'];
    $form['rectangles_group']['rectangles_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // circles
  if (isset($form['circles_group']['circles_enable']) && $form['circles_group']['circles_enable']['#type'] !== 'value' ) {
    $form['circles_group']['circles_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Circles') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['circles_group']['circles_coords']['#suffix'];
    $form['circles_group']['circles_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // polylines
  if (isset($form['polylines_group']['polylines_enable']) && $form['polylines_group']['polylines_enable']['#type'] !== 'value' ) {
    $form['polylines_group']['polylines_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Polylines') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['polylines_group']['polylines_coords']['#suffix'];
    $form['polylines_group']['polylines_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // what3words
  if (isset($form['what3words_enable']) && $form['what3words_enable']['#type'] !== 'value' ) {
    $form['what3words_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('What3words') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['what3words_show']['#suffix'];
    $form['what3words_show']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['markerclusterer_group']['useclustermanager']) && $form['markerclusterer_group']['useclustermanager']['#type'] !== 'value' ) {
    $form['markerclusterer_group']['useclustermanager']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('MarkerClusterer') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['markerclusterer_group']['markerclusterer_minsize']['#suffix'];
    $form['markerclusterer_group']['markerclusterer_minsize']['#suffix'] = $tsuf . '</div></fieldset>';
  }

    if (isset($form['views_search_group']['views_search_marker_enable']) && $form['views_search_group']['views_search_marker_enable']['#type'] !== 'value' ) {
      $form['views_search_group']['views_search_marker_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Views Search') . '</span></legend><div class="fieldset-wrapper">';
      $tsuf = $form['views_search_group']['views_search_radshape_toggle_active']['#suffix'];
      $form['views_search_group']['views_search_radshape_toggle_active']['#suffix'] = $tsuf . '</div></fieldset>';
    }

  $output = backdrop_render_children($form);
  return $output;

}

function theme_getlocations_settings_form($variables) {
  $form = $variables['form'];

  if (module_exists('getlocations_gps')) {
    if (isset($form['getlocations_default']['gps_button']) && $form['getlocations_default']['gps_button']['#type'] !== 'value' ) {
      $form['getlocations_default']['gps_button']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('GPS Button') . '</span></legend><div class="fieldset-wrapper">';
      $tsuf = $form['getlocations_default']['gps_center']['#suffix'];
      $form['getlocations_default']['gps_center']['#suffix'] = $tsuf . '</div></fieldset>';
    }

  }

  if (isset($form['getlocations_default']['smartip_button']) && $form['getlocations_default']['smartip_button']['#type'] !== 'value' ) {
    $form['getlocations_default']['smartip_button']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Smartip Button') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_default']['smartip_center']['#suffix'];
    $form['getlocations_default']['smartip_center']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // geojson
  if (isset($form['getlocations_default']['geojson_enable']) && $form['getlocations_default']['geojson_enable']['#type'] !== 'value' ) {
    $form['getlocations_default']['geojson_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Geojson') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_default']['geojson_options']['#suffix'];
    $form['getlocations_default']['geojson_options']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['getlocations_default']['highlight_group']['highlight_enable']) && $form['getlocations_default']['highlight_group']['highlight_enable']['#type'] !== 'value' ) {
    $form['getlocations_default']['highlight_group']['highlight_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Marker Highlighting') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_default']['highlight_group']['highlight_radius']['#suffix'];
    $form['getlocations_default']['highlight_group']['highlight_radius']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // google search places
  if (isset($form['getlocations_default']['search_places_group']['search_places']) && $form['getlocations_default']['search_places_group']['search_places']['#type'] !== 'value' ) {
    $form['getlocations_default']['search_places_group']['search_places']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Google Search Places') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_default']['search_places_group']['search_places_dd']['#suffix'];
    $form['getlocations_default']['search_places_group']['search_places_dd']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // polygons
  if (isset($form['getlocations_default']['polygons_group']['polygons_enable']) && $form['getlocations_default']['polygons_group']['polygons_enable']['#type'] !== 'value' ) {
    $form['getlocations_default']['polygons_group']['polygons_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Polygons') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_default']['polygons_group']['polygons_coords']['#suffix'];
    $form['getlocations_default']['polygons_group']['polygons_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // rectangles
  if (isset($form['getlocations_default']['rectangles_group']['rectangles_enable']) && $form['getlocations_default']['rectangles_group']['rectangles_enable']['#type'] !== 'value' ) {
    $form['getlocations_default']['rectangles_group']['rectangles_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Rectangles') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_default']['rectangles_group']['rectangles_coords']['#suffix'];
    $form['getlocations_default']['rectangles_group']['rectangles_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // circles
  if (isset($form['getlocations_default']['circles_group']['circles_enable']) && $form['getlocations_default']['circles_group']['circles_enable']['#type'] !== 'value' ) {
    $form['getlocations_default']['circles_group']['circles_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Circles') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_default']['circles_group']['circles_coords']['#suffix'];
    $form['getlocations_default']['circles_group']['circles_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // polylines
  if (isset($form['getlocations_default']['polylines_group']['polylines_enable']) && $form['getlocations_default']['polylines_group']['polylines_enable']['#type'] !== 'value' ) {
    $form['getlocations_default']['polylines_group']['polylines_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Polylines') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_default']['polylines_group']['polylines_coords']['#suffix'];
    $form['getlocations_default']['polylines_group']['polylines_coords']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  // what3words
  if (isset($form['getlocations_default']['what3words_enable']) && $form['getlocations_default']['what3words_enable']['#type'] !== 'value' ) {
    $form['getlocations_default']['what3words_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('What3words') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_default']['what3words_show']['#suffix'];
    $form['getlocations_default']['what3words_show']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['getlocations_default']['markerclusterer_group']['useclustermanager']) && $form['getlocations_default']['markerclusterer_group']['useclustermanager']['#type'] !== 'value' ) {
    $form['getlocations_default']['markerclusterer_group']['useclustermanager']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('MarkerClusterer') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_default']['markerclusterer_group']['markerclusterer_minsize']['#suffix'];
    $form['getlocations_default']['markerclusterer_group']['markerclusterer_minsize']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  if (isset($form['getlocations_default']['views_search_group']['views_search_marker_enable']) && $form['getlocations_default']['views_search_group']['views_search_marker_enable']['#type'] !== 'value' ) {
    $form['getlocations_default']['views_search_group']['views_search_marker_enable']['#prefix'] = '<fieldset class="collapsible getlocations_fieldset form-wrapper"><legend><span class="fieldset-legend">' . t('Views Search') . '</span></legend><div class="fieldset-wrapper">';
    $tsuf = $form['getlocations_default']['views_search_group']['views_search_radshape_toggle_active']['#suffix'];
    $form['getlocations_default']['views_search_group']['views_search_radshape_toggle_active']['#suffix'] = $tsuf . '</div></fieldset>';
  }

  $output = '<!-- theme_getlocations_settings_form -->';
  $output .= backdrop_render_children($form);
  $output .= '<!-- /theme_getlocations_settings_form -->';
  return $output;
}

/**
 * Returns HTML of the getlocations plugin_style_streetview_options form.
 *
 * @param array $variables
 *   An associative array containing:
 *   - form: The form array.
 *
 * @return string The rendered form
 *
 * @ingroup themeable
 *
 */
function theme_getlocations_plugin_style_streetview_options_form($variables) {
  $form = $variables['form'];


  $output = backdrop_render_children($form);
  return $output;
}

/**
 * Returns HTML of a latitude in decimal degress expressed in degrees, minutes and seconds.
 *
 * from location module
 *
 * @param array $variables
 *   An associative array containing:
 *   - latitude: A latitude in decimal degrees.
 *
 * @ingroup themeable
 *
 */
function theme_getlocations_latitude_dms($variables) {
  $latitude = $variables['latitude'];
  $output = '';
  list($degrees, $minutes, $seconds, $negative) = getlocations_dd_to_dms($latitude);
  $output .= $degrees . "&deg; " . $minutes . "&#39; " . $seconds . "&#34; ";
  if (!$negative) {
    $output .= 'N';
  }
  else {
    $output .= 'S';
  }
  return $output;
}

/**
 * Returns HTML of a longitude in decimal degress expressed in degrees, minutes and seconds.
 *
 * from location module
 *
 * @param array $variables
 *   An associative array containing:
 *   - longitude: A longitude in decimal degrees.
 *
 * @ingroup themeable
 *
 */
function theme_getlocations_longitude_dms($variables) {
  $longitude = $variables['longitude'];
  $output = '';
  list($degrees, $minutes, $seconds, $negative) = getlocations_dd_to_dms($longitude);
  $output .= $degrees . "&deg; " . $minutes . "&#39; " . $seconds . "&#34; ";
  if (!$negative) {
    $output .= 'E';
  }
  else {
    $output .= 'W';
  }
  return $output;
}

/**
 * Returns an array of an address from the addressfield module converted for use in getlocations.
 *
 * from location module
 *
 * @param array $variables
 *   An associative array containing:
 *   - address: an array of address components.
 *
 * @ingroup themeable
 *
 */
function theme_getlocations_addressfield_convert($variables) {
  $address = $variables['address'];
  $location = array();
  if (is_array($address) && ! empty($address)) {
    $name = array();
    if (isset($address['name_line']) && $address['name_line']) {
      $name[] = $address['name_line'];
    }
    if (isset($address['first_name']) && $address['first_name']) {
      if (isset($address['last_name']) && $address['last_name']) {
        $name[] = $address['first_name'] . ' ' . $address['last_name'];
      }
      else {
        $name[] = $address['first_name'];
      }
    }
    elseif (isset($address['last_name']) && $address['last_name']) {
      $name[] = $address['last_name'];
    }
    if (isset($address['organisation_name']) && $address['organisation_name']) {
      $name[] = $address['organisation_name'];
    }
    $location['name'] = (count($name) ? implode(", ", $name) : '');

    $location['street'] = (isset($address['thoroughfare']) ? $address['thoroughfare'] : '');
    $additional = array();
    if (isset($address['premise']) && $address['premise']) {
      $additional[] = $address['premise'];
    }
    if (isset($address['sub_premise']) && $address['sub_premise']) {
      $additional[] = $address['sub_premise'];
    }
    $location['additional'] = (count($additional) ? implode(", ", $additional) : '');
    $city = array();
    if (isset($address['dependent_locality']) && $address['dependent_locality']) {
      $city[] = $address['dependent_locality'];
    }
    if (isset($address['locality']) && $address['locality']) {
      $city[] = $address['locality'];
    }
    $location['city'] = (count($city) ? implode(", ", $city) : '');
    $admin_area = array();
    if (isset($address['sub_administrative_area']) && $address['sub_administrative_area']) {
      $admin_area[] = $address['sub_administrative_area'];
    }
    if (isset($address['administrative_area']) && $address['administrative_area']) {
      $admin_area[] = $address['administrative_area'];
    }
    $location['province_name'] = (count($admin_area) ? implode(", ", $admin_area) :'');
    $location['postal_code'] = (isset($address['postal_code']) ? backdrop_strtoupper($address['postal_code']) : '');
    $location['country_name'] = (isset($address['country_name']) ? $address['country_name'] : $address['country']);
    $location['country'] = $address['country'];
  }
  return $location;

}

/**
 * Returns HTML of a url, requested by ajax.
 *
 * @param array $variables
 *   An associative array containing:
 *   - lid: The location identifier or glid.
 *   - lidkey: The entity identifier type
 *
 * @return string $output
 *
 * @ingroup themeable
 *
 */
function theme_getlocations_lidinfo($variables) {
  $lid = $variables['lid'];
  $lidkey = $variables['lidkey'];

  $output = FALSE;
  if ($lid > 0) {
    if (module_exists('getlocations_fields') || module_exists('location')) {
      $path = getlocations_get_path_from_lid($lid);
      if ($path) {
        $output = $path;
      }
    }
    elseif (module_exists('geofield') || module_exists('geolocation') ) {
      if ($lidkey == 'nid') {
        $path = url('node/' . $lid);
      }
      elseif ($lidkey == 'vid') {
        $nid = getlocations_get_nid($lid);
        $path = url('node/' . $nid);
      }
      elseif ($lidkey == 'uid') {
        $path = url('user/' . $lid);
      }
      elseif ($lidkey == 'tid' && module_exists('taxonomy')) {
        $path = url('taxonomy/term/' . $lid);
      }
      elseif ($lidkey == 'cid' && module_exists('comment')) {
        $path = url('comment/' . $lid);
      }
      if ($path) {
        $output = $path;
      }
    }
  }
  return $output;

}

/**
 * Prepares variables for getlocations_box.tpl.php
 *
 * @param array $variables
 *   An associative array containing all the elements to construct an HTML document
 *   suitable for use in a colorbox.
 *
 */
function template_preprocess_getlocations_box(&$variables) {

  if (module_exists('admin_menu')) {
    admin_menu_suppress();
  }
  $getlocations_paths = getlocations_paths_get();
  backdrop_add_js($getlocations_paths['getlocations_box_path']);

  // Construct page title
  if (backdrop_get_title()) {
    $head_title = array(strip_tags(backdrop_get_title()), config_get('site_name', 'Backdrop'));
  }
  else {
    $head_title = array(config_get('site_name', 'Backdrop'));
    if (config_get('site_slogan', '')) {
      $head_title[] = config_get('site_slogan', '');
    }
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
 * Prepares variables for getlocations_marker_box.tpl.php
 *
 * @param array $variables
 *   An associative array containing all the elements to construct an HTML document
 *   suitable for use in a colorbox.
 *
 */
function template_preprocess_getlocations_marker_box(&$variables) {

  if (module_exists('admin_menu')) {
    admin_menu_suppress();
  }
  $getlocations_paths = getlocations_paths_get();
  backdrop_add_js($getlocations_paths['getlocations_marker_box_path']);

  $head_title = t('Getlocations markers');
  $variables['head_title'] = $head_title;
  $variables['base_path'] = base_path();
  $variables['head'] = backdrop_get_html_head();
  $variables['language'] = $GLOBALS['language'];
  $variables['language']->dir = $GLOBALS['language']->direction ? 'rtl' : 'ltr';
  $variables['css'] = backdrop_add_css();
  $variables['styles'] = backdrop_get_css();
  $variables['scripts'] = backdrop_get_js();
  $variables['title'] = $head_title;

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
