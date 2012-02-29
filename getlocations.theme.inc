<?php

/**
 * @file
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
 * getlocations module theming functions.
 * using version 3 googlemaps API
 */

/**
 * Implements hook_theme().
 *
 * This lets us tell Drupal about our theme functions and their arguments.
 */
function getlocations_theme() {
  return array(
    'getlocations_show' => array(
      'variables' => array(
        'width' => '',
        'height' => '',
        'defaults' => '',
        'mapid' => '',
        'type' => '',
        'node' => '',
      ),
    ),
    'getlocations_info' => array(
      'variables' => array(
        'location' => null,
      ),
    ),
    'getlocations_box' => array(
      'variables' => array(
        'content' => null,
      ),
      'template' => 'getlocations_box',
    ),
    'getlocations_settings_form' => array(
      'render element' => 'form',
    ),
#    'getlocations_view_map' => array(
#      'variables' => array(
#        'content' => null,
#      ),
#      'template' => 'getlocations_view_map',
#    ),
  );
}

/**
 * All the map displays pass through here.
 *
 * @param array $variables
 *
 * @return
 *   Returns $output
 *
 */
function theme_getlocations_show($variables) {
  $width = $variables['width'];
  $height = $variables['height'];
  $defaults = $variables['defaults'];
  $mapid = $variables['mapid'];
  $type = $variables['type'];
  $node = $variables['node'];

  $output = '';
  $returnlink = FALSE;
  // return link
  if ($type == 'node' && $defaults['returnlink_page_enable']) {
    if (is_object($node)) {
      $linktext = $defaults['returnlink_page_link'];
      if ( preg_match("/%t/", $linktext)) {
        $linktext = preg_replace("/%t/", $node->title, $linktext);
      }
      $l = l($linktext, 'node/' . $node->nid);
      $returnlink = '<div class="getlocations_returnlink">' . $l . '</div>';
    }
  }
  elseif ($type == 'user' && $defaults['returnlink_user_enable']) {
    if (is_object($node)) {
      $linktext = $defaults['returnlink_user_link'];
      if ( preg_match("/%n/", $linktext)) {
        $linktext = preg_replace("/%n/", $node->name, $linktext);
      }
      $l = l($linktext, 'user/' . $node->uid);
      $returnlink = '<div class="getlocations_returnlink">' . $l . '</div>';
    }
  }
  elseif ($type == 'term' && $defaults['returnlink_term_enable']) {
    if (is_object($node)) {
      $linktext = $defaults['returnlink_term_link'];
      if ( preg_match("/%n/", $linktext)) {
        $linktext = preg_replace("/%n/", $node->name, $linktext);
      }
      $l = l($linktext, 'taxonomy/term/' . $node->tid);
      $returnlink = '<div class="getlocations_returnlink">' . $l . '</div>';
    }
  }
  elseif ($type == 'comment' && $defaults['returnlink_comment_enable']) {
    if (is_object($node)) {
      $linktext = $defaults['returnlink_comment_link'];
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

  // do map
  $output .= '<div class="getlocations_map_canvas" id="getlocations_map_canvas_' . $mapid . '" style="width: '. $width .'; height: '. $height .'" ></div>';
  // buttons
  $buttons = array();
  if ($defaults['trafficinfo']) {
    $buttons[] = '<input type="submit" value="' . t('Toggle traffic info') . '" title="' . t('Limited Availability') . '" id="getlocations_toggleTraffic_' . $mapid . '" class="form-submit" />';
  }
  if ($defaults['bicycleinfo']) {
    $buttons[] = '<input type="submit" value="' . t('Toggle bicycle info') . '" title="' . t('Limited Availability') . '" id="getlocations_toggleBicycle_' . $mapid . '" class="form-submit" />';
  }
  if ($defaults['panoramio_use'] && $defaults['panoramio_show']) {
    $buttons[] = '<input type="submit" value="' . t('Toggle panoramio') . '" id="getlocations_togglePanoramio_' . $mapid . '" class="form-submit" />';
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
 * @param array $variables
 *
 * @return
 *   Returns $output
 *
 */
function theme_getlocations_info($variables) {
  $location = $variables['location'];
  $output = '';

  $output .= '<div class="location vcard">';
  $output .= '<br />';
  if (! empty($location['name'])) {
    $l = $location['name'];
    if (isset($location['nid']) && $location['nid'] > 0) {
      $l = l($location['name'], 'node/'. $location['nid'], array('attributes' => array('class' => 'getlocations_infolink', 'target' => '_parent')));
    }
    elseif (isset($location['uid']) && $location['uid'] > 0) {
      // Use $l = $location['name'] if you don't want links to user
      $l = l($location['name'], 'user/'. $location['uid'], array('attributes' => array('class' => 'getlocations_infolink', 'target' => '_parent')));
    }
    elseif (isset($location['tid']) && $location['tid'] > 0) {
      $l = l($location['name'], 'taxonomy/term/'. $location['tid'], array('attributes' => array('class' => 'getlocations_infolink', 'target' => '_parent')));
    }
    elseif (isset($location['cid']) && $location['cid'] > 0) {
      $l = l($location['name'], 'comment/'. $location['cid'], array('attributes' => array('class' => 'getlocations_infolink', 'target' => '_parent')));
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
    elseif (! empty($location['province'])) {
      $output .= ",&nbsp;";
    }
  }
  if (isset($location['province_name']) && ! empty($location['province_name'])) {
    $output .= '<span class="region">' . $location['province_name'] . ' </span>';
  }
  elseif (isset($location['province']) && ! empty($location['province'])) {
    $output .= '<span class="region">' . $location['province'] . ' </span>';
  }
  if (! empty($location['postal_code'])) {
    $output .= '<span class="postal-code">' . strtoupper($location['postal_code']) . ' </span>';
  }
  if (isset($location['country_name']) && ! empty($location['country_name'])) {
    $output .= '<div class="country-name">' . $location['country_name'] . '</div>';
  }
  elseif (isset($location['country']) && ! empty($location['country'])) {
    $output .= '<div class="country-name">' . $location['country'] . '</div>';
  }
  $output .= '</div>';
  $output .= '</div>';

  return $output;
}

/**
 * @param array $variables
 *
 * @return
 *   Modifies $variables in situ
 *
 */
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

function theme_getlocations_settings_form($variables) {

  $form = $variables['form'];

  $output = '';
  $prefix = '<fieldset class="form-wrapper">';
  $prefix .= '<legend><span class="fieldset-legend">' . t('Enable map types') . '</span></legend>';
  $prefix .= '<div class="fieldset-wrapper">';
  $prefix .= '<div class="fieldset-description">Select which maps you want to be available.</div>';
  $form['getlocations_default']['baselayers']['Map']['#prefix'] = $prefix;
  $form['getlocations_default']['baselayers']['Physical']['#suffix'] = '</div></fieldset>';
  $form['getlocations_default']['returnlink_page_link']['#prefix'] = '<div id="wrap-page-link">';
  $form['getlocations_default']['returnlink_page_link']['#suffix'] = '</div>';
  if (isset($form['getlocations_default']['returnlink_user_link'])) {
    $form['getlocations_default']['returnlink_user_link']['#prefix'] = '<div id="wrap-user-link">';
    $form['getlocations_default']['returnlink_user_link']['#suffix'] = '</div>';
  }
  if (isset($form['getlocations_default']['returnlink_term_link'])) {
    $form['getlocations_default']['returnlink_term_link']['#prefix'] = '<div id="wrap-term-link">';
    $form['getlocations_default']['returnlink_term_link']['#suffix'] = '</div>';
  }
  if (isset($form['getlocations_default']['returnlink_comment_link'])) {
    $form['getlocations_default']['returnlink_comment_link']['#prefix'] = '<div id="wrap-comment-link">';
    $form['getlocations_default']['returnlink_comment_link']['#suffix'] = '</div>';
  }
  if (isset($form['getlocations_colorbox']['width'])) {
    $form['getlocations_colorbox']['width']['#prefix'] = '<div id="wrap-getlocations-colorbox">';
  }
  if (isset($form['getlocations_colorbox']['height'])) {
    $form['getlocations_colorbox']['height']['#suffix'] = '</div>';
  }

  $form['getlocations_default']['useclustermanager']['#prefix'] = '<div id="wrap-getlocations-clusteropts">';
  $form['getlocations_default']['markerclusterer_minsize']['#suffix'] = '</div>';

  $output .= drupal_render_children($form);
  return $output;
}
