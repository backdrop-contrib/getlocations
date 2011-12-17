<?php

/**
 * @file
 * Contains the getlocations style plugin.
 */

/**
 * Getlocations style plugin to render rows as icons on a map.
 *
 * @ingroup views_style_plugins
 */
class getlocations_plugin_style_map extends views_plugin_style {
  /**
   * Set default options
   */
  function options(&$options) {
    parent::options($options);
    $options['empty_result'] = FALSE;
  }

  function option_definition() {
    $options = parent::option_definition();

    $getlocations_defaults = getlocations_defaults();

    $options['width']                 = array('default' => $getlocations_defaults['width']);
    $options['height']                = array('default' => $getlocations_defaults['height']);
    $options['node_map_marker']       = array('default' => $getlocations_defaults['node_map_marker']);
    $options['user_map_marker']       = array('default' => $getlocations_defaults['user_map_marker']);
    $options['vocabulary_map_marker'] = array('default' => $getlocations_defaults['vocabulary_map_marker']);
    $options['comment_map_marker']    = array('default' => $getlocations_defaults['comment_map_marker']);
    $options['latlong']               = array('default' => $getlocations_defaults['latlong']);
    $options['zoom']                  = array('default' => $getlocations_defaults['zoom']);
    $options['controltype']           = array('default' => $getlocations_defaults['controltype']);
    $options['pancontrol']            = array('default' => $getlocations_defaults['pancontrol']);
    $options['mtc']                   = array('default' => $getlocations_defaults['mtc']);
    $options['maptype']               = array('default' => $getlocations_defaults['maptype']);
    $options['baselayers']            = array('default' => $getlocations_defaults['baselayers']);
    $options['behavior']              = array('default' => $getlocations_defaults['behavior']);
    $options['streetview_show']       = array('default' => $getlocations_defaults['streetview_show']);
    $options['trafficinfo']           = array('default' => $getlocations_defaults['trafficinfo']);
    $options['bicycleinfo']           = array('default' => $getlocations_defaults['bicycleinfo']);
    $options['panoramio_use']         = array('default' => $getlocations_defaults['panoramio_use']);
    $options['panoramio_show']        = array('default' => $getlocations_defaults['panoramio_show']);
    $options['places']                = array('default' => $getlocations_defaults['places']);
    $options['poi_show']              = array('default' => $getlocations_defaults['poi_show']);
    $options['transit_show']          = array('default' => $getlocations_defaults['transit_show']);
    $options['minzoom']               = array('default' => $getlocations_defaults['minzoom']);
    $options['maxzoom']               = array('default' => $getlocations_defaults['maxzoom']);
    $options['nodezoom']              = array('default' => $getlocations_defaults['nodezoom']);
    $options['markeraction']          = array('default' => $getlocations_defaults['markeraction']);
    $options['usemarkermanager']      = array('default' => $getlocations_defaults['usemarkermanager']);
    $options['pansetting']            = array('default' => $getlocations_defaults['pansetting']);
    $options['draggable']             = array('default' => $getlocations_defaults['draggable']);
    $options['styles']                = array('default' => $getlocations_defaults['styles']);

    // node markers
    $getlocations_node_marker = variable_get('getlocations_node_marker', array('enable' => 0));
    if ($getlocations_node_marker['enable']) {
      if ($types = getlocations_get_types()) {
        foreach ($types AS $type => $name) {
          $field_name = getlocations_get_fieldname($type);
          $mkey = 'node_marker_' . $field_name;
          $mmarker = (isset($getlocations_node_marker['content_type'][$type]['map_marker']) ? $getlocations_node_marker['content_type'][$type]['map_marker'] : $getlocations_defaults['node_map_marker']);
          $options[$mkey] = array('default' => $mmarker);
        }
      }
    }

    if (module_exists('getlocations_fields')) {
      // vocabulary markers
      $getlocations_vocabulary_marker = variable_get('getlocations_vocabulary_marker', array('enable' => 0));
      if ($getlocations_vocabulary_marker['enable']) {
        if ($types = getlocations_get_vocabularies()) {
          foreach ($types AS $type => $name) {
            $mkey = 'vocabulary_marker_' . $type;
            $mmarker = (isset($getlocations_vocabulary_marker['vocabulary'][$type]['map_marker']) ? $getlocations_vocabulary_marker['vocabulary'][$type]['map_marker'] : $getlocations_defaults['vocabulary_map_marker']);
            $options[$mkey] = array('default' => $mmarker);
          }
        }
      }
    }

    return $options;

  } // end option_definition

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['width'] = getlocations_element_map_tf(
      t('Map width'),
      $this->options['width'],
      10,
      10,
      t('The width of a Google map, as a CSS length or percentage. Examples: <em>50px</em>, <em>5em</em>, <em>2.5in</em>, <em>95%</em>')
    );

    $form['height'] = getlocations_element_map_tf(
      t('Map height'),
      $this->options['height'],
      10,
      10,
      t('The height of a Google map, as a CSS length or percentage. Examples: <em>50px</em>, <em>5em</em>, <em>2.5in</em>, <em>95%</em>')
    );

    $form['styles'] = array(
      '#type' => 'textarea',
      '#title' => t('Default styles'),
      '#default_value' => $this->options['styles'],
      '#description' => t('The default styles of a Google map. Use !link for generating your styles', array('!link' => l('http://gmaps-samples-v3.googlecode.com/svn/trunk/styledmaps/wizard/', 'http://gmaps-samples-v3.googlecode.com/svn/trunk/styledmaps/wizard/', array('external' => TRUE)))),
    );

    $form['latlong'] = getlocations_element_map_tf(
      t('Map center'),
      $this->options['latlong'],
      30,
      30,
      t('The center coordinates of a Google map, expressed as a decimal latitude and longitude, separated by a comma.')
    );

    $form['zoom'] = getlocations_element_map_zoom(
      t('Zoom'),
      $this->options['zoom'],
      t('The zoom level of a Google map.')
    );

    $form += getlocations_map_display_options_form($this->options, FALSE);

    // markers
    $markers = getlocations_get_marker_titles();
    $form['node_map_marker'] = getlocations_element_map_marker(
      t('Content Map marker'),
      $markers,
      $this->options['node_map_marker']
    );
    $getlocations_node_marker = variable_get('getlocations_node_marker', array('enable' => 0));
    if ($getlocations_node_marker['enable']) {
      if ($types = getlocations_get_types()) {
        foreach ($types AS $type => $name) {
          $field_name = getlocations_get_fieldname($type);
          $mkey = 'node_marker_' . $field_name;
          $form[$mkey] = getlocations_element_map_marker(
            t('%name Content Map Marker', array('%name' => $name)),
            $markers,
            $this->options[$mkey]
          );
        }
      }
    }
    // user markers
    if (getlocations_check_user()) {
      $form['user_map_marker'] = getlocations_element_map_marker(
        t('User Map Marker'),
        $markers,
        $this->options['user_map_marker']
      );
    }
    // vocabulary markers
    if ($types = getlocations_get_vocabularies()) {
      $form['vocabulary_map_marker'] = getlocations_element_map_marker(
        t('Vocabulary Map Marker'),
        $markers,
        $this->options['vocabulary_map_marker']
      );
      $getlocations_vocabulary_marker = variable_get('getlocations_vocabulary_marker', array('enable' => 0));
      if ($getlocations_vocabulary_marker['enable']) {
        foreach ($types AS $type => $name) {
          $field_name = getlocations_get_fieldname($type, 'taxonomy_term');
          $mkey = 'vocabulary_marker_' . $field_name;
          $form[$mkey] = getlocations_element_map_marker(
            t('%name Vocabulary Marker', array('%name' => $name)),
            $markers,
            $this->options[$mkey]
          );
        }
      }
    }
    if (getlocations_check_comment()) {
      // default comment marker
      $form['comment_map_marker'] = getlocations_element_map_marker(
        t('Comment Map marker'),
        $markers,
        $this->options['comment_map_marker']
      );
    }

    $form['markeraction'] = getlocations_element_map_markeraction(
      $this->options['markeraction']
    );

    $form['minzoom'] = getlocations_element_map_zoom(
      t('Minimum Zoom'),
      $this->options['minzoom'],
      t('The Minimum zoom level at which markers will be visible.')
    );
    $form['maxzoom'] = getlocations_element_map_zoom(
      t('Maximum Zoom'),
      $this->options['maxzoom'],
      t('The Maximum zoom level at which markers will be visible.')
    );
    $form['nodezoom'] = getlocations_element_map_zoom(
      t('Default Zoom for Single location'),
      $this->options['nodezoom'],
      t('The Default zoom level for a single marker.')
    );
    $form['pansetting'] = getlocations_element_map_pansetting(
      $this->options['pansetting']
    );

    $form['empty_result'] = getlocations_element_map_checkbox(
      t('Show map even if view has no results'),
      $this->options['empty_result']
    );
    $getlocations_defaults = getlocations_defaults();
    $form['usemarkermanager'] = array(
      '#type' => 'hidden',
      '#value' => $getlocations_defaults['usemarkermanager']
    );

  } // end options_form

  /**
   * Validate the options form.
   */

  function options_validate(&$form, &$form_state) {

    $list = array('Map', 'Satellite', 'Hybrid', 'Physical');
    $found = FALSE;
    foreach ($list AS $maptype) {
      if ($form_state['values']['maptype'] == $maptype && $form_state['values']['baselayers'][$maptype] ) {
        $found = TRUE;
        break;
      }
    }
    if (! $found) {
      // force a setting
      $form_state['values']['maptype'] = 'Map';
      $form_state['values']['baselayers']['Map'] = 1;
    }
  }

  function even_empty() {
    return parent::even_empty() || !empty($this->options['empty_result']);
  }

  function render() {
    if (isset($this->view->live_preview) && $this->view->live_preview) {
      return t('Getlocations Map views are not compatible with live preview.');
    }
    return parent::render();
  }

}
