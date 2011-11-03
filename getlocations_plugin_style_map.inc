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
#  function options(&$options) {
#    parent::options($options);
#  }

  function option_definition() {
    $options = parent::option_definition();

    $getlocations_defaults = getlocations_defaults();

    $options['width']            = array('default' => $getlocations_defaults['width']);
    $options['height']           = array('default' => $getlocations_defaults['height']);
    $options['map_marker']       = array('default' => $getlocations_defaults['map_marker']);
    $options['latlong']          = array('default' => $getlocations_defaults['latlong']);
    $options['zoom']             = array('default' => $getlocations_defaults['zoom']);
    $options['controltype']      = array('default' => $getlocations_defaults['controltype']);
    $options['pancontrol']       = array('default' => $getlocations_defaults['pancontrol']);
    $options['mtc']              = array('default' => $getlocations_defaults['mtc']);
    $options['maptype']          = array('default' => $getlocations_defaults['maptype']);
    $options['baselayers']       = array('default' => $getlocations_defaults['baselayers']);
    $options['behavior']         = array('default' => $getlocations_defaults['behavior']);
    $options['streetview_show']  = array('default' => $getlocations_defaults['streetview_show']);
    $options['trafficinfo']      = array('default' => $getlocations_defaults['trafficinfo']);
    $options['bicycleinfo']      = array('default' => $getlocations_defaults['bicycleinfo']);
    $options['panoramio_show']   = array('default' => $getlocations_defaults['panoramio_show']);
    $options['places']           = array('default' => $getlocations_defaults['places']);
    $options['poi_show']         = array('default' => $getlocations_defaults['poi_show']);
    $options['transit_show']     = array('default' => $getlocations_defaults['transit_show']);
    $options['minzoom']          = array('default' => $getlocations_defaults['minzoom']);
    $options['maxzoom']          = array('default' => $getlocations_defaults['maxzoom']);
    $options['nodezoom']         = array('default' => $getlocations_defaults['nodezoom']);
    $options['markeraction']     = array('default' => $getlocations_defaults['markeraction']);
    $options['usemarkermanager'] = array('default' => $getlocations_defaults['usemarkermanager']);
    $options['pansetting']       = array('default' => $getlocations_defaults['pansetting']);
    $options['draggable']        = array('default' => $getlocations_defaults['draggable']);
    $options['styles']           = array('default' => $getlocations_defaults['styles']);

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

    $form['controltype'] = getlocations_element_map_zoom_controltype(
      $this->options['controltype']
    );

    $form['pancontrol'] = getlocations_element_map_checkbox(
      t('Show Pan control'),
      $this->options['pancontrol']
    );

    $form['mtc'] = getlocations_element_map_mtc($this->options['mtc']);

    $baselayers = array();
    foreach ($this->options['baselayers'] AS $key => $value) {
      $baselayers[$key] = $value;
    }
    $form['maptype'] = getlocations_element_map_maptype($this->options['maptype'], $baselayers);

    $form['baselayers']['Map'] = getlocations_element_map_baselayers_map($this->options['baselayers']['Map']);
    $form['baselayers']['Satellite'] = getlocations_element_map_baselayers_satellite($this->options['baselayers']['Satellite']);
    $form['baselayers']['Hybrid'] = getlocations_element_map_baselayers_hybrid($this->options['baselayers']['Hybrid']);
    $form['baselayers']['Physical'] = getlocations_element_map_baselayers_physical($this->options['baselayers']['Physical']);

    $form['behavior']['scale'] = getlocations_element_map_checkbox(
      t('Scale'),
      $this->options['behavior']['scale'],
      t('Show scale')
    );
    $form['behavior']['overview'] = getlocations_element_map_checkbox(
      t('Overview map'),
      $this->options['behavior']['overview'],
      t('Show overview map')
    );
    $form['behavior']['overview_opened'] = getlocations_element_map_checkbox(
      t('Overview map state'),
      $this->options['behavior']['overview_opened'],
      t('Show overview map as open by default')
    );
    $form['behavior']['scrollwheel'] = getlocations_element_map_checkbox(
      t('Scrollwheel'),
      $this->options['behavior']['scrollwheel'],
      t('Enable scrollwheel zooming')
    );

    $form['draggable'] = getlocations_element_map_checkbox(
      t('Draggable'),
      $this->options['draggable'],
      t('Enable dragging the map.')
    );

    $form['streetview_show'] = getlocations_element_map_checkbox(
      t('Show streetview button'),
      $this->options['streetview_show']
    );
    $form['trafficinfo'] = getlocations_element_map_checkbox(
      t('Enable Traffic information'),
      $this->options['trafficinfo'],
      t('Google trafficinfo layer, limited availability.')
    );
    $form['bicycleinfo'] = getlocations_element_map_checkbox(
      t('Enable Bicycling information'),
      $this->options['bicycleinfo'],
      t('Google bicycling layer, limited availability.')
    );
    $form['panoramio_show'] = getlocations_element_map_checkbox(
      t('Enable Panoramio'),
      $this->options['panoramio_show'],
      t('Google panoramio picture links.')
    );
    $form['poi_show'] = getlocations_element_map_checkbox(
      t('Show Points of Interest'),
      $this->options['poi_show'],
      t('Show Google points of interest icons.')
    );
    $form['transit_show'] = getlocations_element_map_checkbox(
      t('Show Transit Points'),
      $this->options['transit_show'],
      t('Show Google transit points icons.')
    );

    $markers = getlocations_get_marker_titles();
    $form['map_marker'] = getlocations_element_map_marker(
      t('Marker / fallback marker to use'),
      $markers,
      $this->options['map_marker']
    );

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
    $getlocations_defaults = getlocations_defaults();
    $form['usemarkermanager'] = array(
      '#type' => 'hidden',
      '#value' => $getlocations_defaults['usemarkermanager']
    );
    $form['pansetting'] = getlocations_element_map_pansetting(
      $this->options['pansetting']
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

}
