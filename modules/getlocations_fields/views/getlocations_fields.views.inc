<?php

/**
 * @file
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
 * Views 3 support for getlocations_fields.
 */

/**
 * Implements hook_views_handlers().
 */
function getlocations_fields_views_handlers() {

  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'getlocations_fields') . '/handlers',
    ),
    'handlers' => array(

#      'getlocations_fields_handler_argument_distance' => array(
#        'parent' => 'views_handler_argument',
#      ),

      'getlocations_fields_handler_field_coordinates' => array(
        'parent' => 'getlocations_fields_handler_field_latitude',
      ),
      'getlocations_fields_handler_field_country' => array(
        'parent' => 'views_handler_field',
      ),

#      'getlocations_fields_handler_field_distance' => array(
#        'parent' => 'views_handler_field',
#      ),

      'getlocations_fields_handler_field_latitude' => array(
        'parent' => 'views_handler_field',
      ),
      'getlocations_fields_handler_field_longitude' => array(
        'parent' => 'getlocations_fields_handler_field_latitude',
      ),

      'getlocations_fields_handler_filter_country' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
      'getlocations_fields_handler_filter_distance' => array(
        'parent' => 'views_handler_filter',
      ),

      'getlocations_fields_handler_sort_distance' => array(
        'parent' => 'views_handler_sort',
      ),
    ),
  );
}

/**
 * Implements hook_views_data().
 */
function getlocations_fields_views_data() {

  // ----------------------------------------------------------------
  // getlocations_fields table -- basic table information.

  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.

  $data['getlocations_fields']['table']['group'] = t('Getlocations Fields');

  // Advertise this table as a possible base table
  $data['getlocations_fields']['table']['base'] = array(
    'field' => 'glid',
    'title' => t('Getlocations'),
    'help' => t('Locations are addresses and map coordinates.'),
    'weight' => -10,
  );

  $data['getlocations_fields']['table']['join'] = array(
    // getlocations_fields links to node through getlocations_fields_entities via glid.
    'node' => array(
      'left_table' => 'getlocations_fields_entities',
      'left_field' => 'glid',
      'field' => 'glid',
    ),
    // getlocations_fields links to node_revision through getlocations_fields_entities via glid.
    'node_revision' => array(
      'left_table' => 'getlocations_fields_entities',
      'left_field' => 'glid',
      'field' => 'glid',
    ),
    // getlocations_fields links to users through getlocations_fields_entities via glid.
    'users' => array(
      'left_table' => 'getlocations_fields_entities',
      'left_field' => 'glid',
      'field' => 'glid',
    ),
    // getlocations_fields links to taxonomy terms through getlocations_fields_entities via glid.
    'taxonomy_term_data' => array(
      'left_table' => 'getlocations_fields_entities',
      'left_field' => 'glid',
      'field' => 'glid',
    ),
    // getlocations_fields links to comment through getlocations_fields_entities via glid.
    'comment' => array(
      'left_table' => 'getlocations_fields_entities',
      'left_field' => 'glid',
      'field' => 'glid',
    ),

  );

  // ----------------------------------------------------------------
  // getlocations_fields table -- fields


  // glid
  $data['getlocations_fields']['glid'] = array(
    'title' => t('Glid'),
    'help' => t('The getlocations ID of the location.'), // The help that appears on the UI,
    // Information for displaying the glid
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    // Information for accepting a lid as an argument
    /*
    'argument' => array(
      'handler' => 'views_handler_argument_node_nid',
      'name field' => 'title', // the field to display in the summary.
      'numeric' => TRUE,
      'validate type' => 'nid',
    ),
    */
    // Information for accepting a glid as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    // Information for sorting on a glid.
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // name
  $data['getlocations_fields']['name'] = array(
    'title' => t('Name'),
    'help' => t('The name of the selected location.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // street
  $data['getlocations_fields']['street'] = array(
    'title' => t('Street'),
    'help' => t('The street address of the selected location.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // city
  $data['getlocations_fields']['city'] = array(
    'title' => t('City'),
    'help' => t('The city of the selected location.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'empty field name' => t('Unknown'),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // province
  $data['getlocations_fields']['province'] = array(
    'title' => t('Province'),
    'help' => t('The province of the selected location.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
#    'argument' => array(
#      'handler' => 'getlocations_fields_handler_argument_province',
#      //'name field' => 'name',
#    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // postal_code
  $data['getlocations_fields']['postal_code'] = array(
    'title' => t('Postal Code'),
    'help' => t('The postal code of the selected location.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // country
  $data['getlocations_fields']['country'] = array(
    'title' => t('Country'),
    'help' => t('The country of the selected location.'),
    'field' => array(
      'handler' => 'getlocations_fields_handler_field_country',
      'click sortable' => TRUE,
    ),
#    'argument' => array(
#      'handler' => 'getlocations_fields_handler_argument_country',
#      //'name field' => 'name',
#    ),
    'filter' => array(
      'handler' => 'getlocations_fields_handler_filter_country',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
      // TODO: needs handler to sort by name, not code
    ),
  );

  // latitude
  $data['getlocations_fields']['latitude'] = array(
    'title' => t('Latitude'),
    'help' => t('The latitude of the selected location.'),
    'field' => array(
      'handler' => 'getlocations_fields_handler_field_latitude',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // longitude
  $data['getlocations_fields']['longitude'] = array(
    'title' => t('Longitude'),
    'help' => t('The longitude of the selected location.'),
    'field' => array(
      'handler' => 'getlocations_fields_handler_field_longitude',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // coordinates
  $data['getlocations_fields']['coordinates'] = array(
    'title' => t('Coordinates'),
    'help' => t("The coordinates of the selected location in 'lat,long' format."),
    'field' => array(
      'field' => 'latitude', // The handler adds the longitude.
      'handler' => 'getlocations_fields_handler_field_coordinates',
      'click sortable' => FALSE,
    ),
  );
  // TODO handlers

  $data['getlocations_fields']['distance'] = array(
    'title' => t('Distance'),
    'help' => t("The distance from the selected location and either the current user or a specific location."),
    'field' => array(
#      'handler' => 'getlocations_fields_handler_field_distance',  // not working yet
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'getlocations_fields_handler_sort_distance',
    ),
#    'argument' => array(
#      'handler' => 'getlocations_fields_handler_argument_distance',  // not working yet
#    ),
    'filter' => array(
      'handler' => 'getlocations_fields_handler_filter_distance',
    ),
//    'relationship' => array(
//      'handler' => 'getlocations_fields_handler_relationship_distance',
//    ),

  );
/*
  // address
  $data['getlocations_fields']['address'] = array(
    'title' => t('Address'),
    'help' => t('The entire address block for the location.'),
    'field' => array(
      'field' => 'glid',
#      'handler' => 'getlocations_fields_handler_field_address',
      'element type' => 'div',
    ),
  );
*/
  // ----------------------------------------------------------------
  // END getlocations_fields table -- fields



  $data['getlocations_fields_entities']['table']['group']  = t('Getlocations Fields');

  $data['getlocations_fields_entities']['table']['join'] = array(
    'getlocations_fields' => array(
      'left_field' => 'glid',
      'field' => 'glid',
    ),
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
    'node' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
    'node_revision' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
    'taxonomy_term_data' => array(
      'left_field' => 'tid',
      'field' => 'tid',
    ),
  );

  $data['getlocations_fields_entities']['field_name'] = array(
    'title' => t('Field name'),
    'help' => t('The field name used in the Content type definition.'),
    'field' => array(
      'handler' => 'views_handler_field', // @@@
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),

  );
  $data['getlocations_fields_entities']['nid'] = array(
    'title' => t('Node Id'),
    'help' => t('The Node Identifier.'),
    'field' => array(
      'handler' => 'views_handler_field', // @@@
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['getlocations_fields_entities']['uid'] = array(
    'title' => t('User Id'),
    'help' => t('The User Identifier.'),
    'field' => array(
      'handler' => 'views_handler_field', // @@@
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['getlocations_fields_entities']['tid'] = array(
    'title' => t('Taxonomy Term Id'),
    'help' => t('The Taxonomy Term Identifier.'),
    'field' => array(
      'handler' => 'views_handler_field', // @@@
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['getlocations_fields_entities']['cid'] = array(
    'title' => t('comment Id'),
    'help' => t('The Comment Identifier.'),
    'field' => array(
      'handler' => 'views_handler_field', // @@@
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Tell the base tables about us.
  $data['node']['table']['join']['getlocations_fields'] = array(
    'left_table' => 'getlocations_fields_entities',
    'left_field' => 'vid',
    'field' => 'vid',
  );
  $data['node_revision']['table']['join']['getlocations_fields'] = array(
    'left_table' => 'getlocations_fields_entities',
    'left_field' => 'vid',
    'field' => 'vid',
  );
  $data['users']['table']['join']['getlocations_fields'] = array(
    'left_table' => 'getlocations_fields_entities',
    'left_field' => 'uid',
    'field' => 'uid',
  );
  $data['taxonomy_term_data']['table']['join']['getlocations_fields'] = array(
    'left_table' => 'getlocations_fields_entities',
    'left_field' => 'tid',
    'field' => 'tid',
  );
  $data['comment']['table']['join']['getlocations_fields'] = array(
    'left_table' => 'getlocations_fields_entities',
    'left_field' => 'cid',
    'field' => 'cid',
  );

  return $data;

}


/**
 * Theme preprocess function for location_distance.
 */
function template_preprocess_getlocations_fields_distance(&$variables) {
  // from getlocations_fields_handler_field_nearby.inc
  $units = $variables['units'];
  unset($variables['units']);
  if ($units == 'km') {
    $variables['shortunit'] = 'km';
    $variables['longunit'] = 'kilometer(s)';
  }
  elseif ($units == 'mi') {
    $variables['shortunit'] = 'mi';
    $variables['longunit'] = 'mile(s)';
  }
  elseif ($units == 'm') {
    $variables['shortunit'] = 'm';
    $variables['longunit'] = 'meter(s)';
  }
  $variables['distance'] = (float)$variables['distance'];
}


/**
 * Helper function for proximity handlers.
 * Retrieves the coordinates of the location that this field measures distances against.
 *
 * @param $view
 *   The view object.
 * @param $options
 *   An array of the options (or values in the case of the filter) of the handler.
 *
 * @return
 *   An array with keys 'latitude' and 'longitude' or an empty array.
 */
function getlocations_fields_views_proximity_get_reference_location($view, $options) {
  $coordinates = array();
  switch ($options['origin']) {
#    case 'user':
#    case 'hybrid':
#      global $user;
#      $user_locations = isset($user->locations) ? $user->locations : location_load_locations($user->uid, 'uid');
#      // This user_location_delta will only possibly be set if we are dealing with the filter.
#      $i = (isset($options['user_location_delta']) && !empty($options['user_location_delta'])) ? $options['user_location_delta'] : 0;
#      if (isset($user_locations[$i]['latitude']) || !empty($user_locations[$i]['latitude'])) {
#        $coordinates['latitude'] = (float) $user_locations[$i]['latitude'];
#        $coordinates['longitude'] = (float) $user_locations[$i]['longitude'];
#      }
#      elseif ($options['origin'] == 'hybrid') {
#        $coordinates['latitude'] = (float) $options['latitude'];
#        $coordinates['longitude'] = (float) $options['longitude'];
#      }
#      break;
    case 'static':
      // not tested
      $coordinates['latitude'] = (float) $options['latitude'];
      $coordinates['longitude'] = (float) $options['longitude'];
      break;
#    case 'tied':
#      if (!empty($view->filter)) {
#        foreach ($view->filter as $filter) {
#          if ($filter->table == 'location' && $filter->field == 'distance' && $filter->options['relationship'] == $options['relationship']) {
#            $filter_options = array_merge($filter->options, $filter->options['value'], $filter->value);
#            if ($coords = location_views_proximity_get_reference_location($view, $filter_options)) {
#              $coordinates['latitude'] = (float) $coords['latitude'];
#              $coordinates['longitude'] = (float) $coords['longitude'];
#            }
#          }
#        }
#      }
#      break;
#    case 'postal':
#    case 'postal_default':
#      // Force default for country.
#      if ($options['origin'] == 'postal_default') {
#        $options['country'] = variable_get('location_default_country', 'us');
#      }
#      // Zip code lookup.
#      if (!empty($options['postal_code']) && !empty($options['country'])) {
#        $coords = location_latlon_rough($options);
#        if ($coords) {
#          $coordinates['latitude'] = (float) $coords['lat'];
#          $coordinates['longitude'] = (float) $coords['lon'];
#        }
#      }
#      break;
    case 'php':
      // not tested
      ob_start();
      $result = eval($options['php_code']);
      ob_end_clean();
      if ($result && $result['latitude'] && $result['longitude']) {
        $coordinates['latitude'] = (float) $result['latitude'];
        $coordinates['longitude'] = (float) $result['longitude'];
      }
      break;
    case 'nid_arg':
      // tested OK
      if ($nodehandler = $view->display_handler->get_handler('argument', $options['nid_arg'])) {
        $nid = $nodehandler->get_value();
        if ($nid && is_numeric($nid) && $tempnode = node_load($nid)) {
          $field_name = $options['nid_loc_field'];
          if ($field_name == 'node') {
            $coordinates['latitude'] = (float) $tempnode->location['latitude'];
            $coordinates['longitude'] = (float) $tempnode->location['longitude'];
          }
          else {
            if (isset($tempnode->$field_name)) {
              $lang = $tempnode->language;
              if (empty($lang)) {
                $lang = 'und';
              }
              $location = $tempnode->$field_name;
              if (isset($location[$lang][0]['longitude']) && isset($location[$lang][0]['latitude'])) {
                $coordinates['latitude'] = (float) $location[$lang][0]['latitude'];
                $coordinates['longitude'] = (float) $location[$lang][0]['longitude'];
              }
            }
          }
        }
      }
      break;
    case 'uid_arg':
      // tested OK
      if ($userhandler = $view->display_handler->get_handler('argument', $options['uid_arg'])) {
        $uid = $userhandler->get_value();
        if ($uid && is_numeric($uid) && $tempuser = user_load($uid)) {
          $field_name = $options['uid_loc_field'];
          if ($field_name == 'user') {
            $coordinates['latitude'] = (float) $tempuser->location['latitude'];
            $coordinates['longitude'] = (float) $tempuser->location['longitude'];
          }
          else {
            if (isset($tempuser->$field_name)) {
              $lang = $tempuser->language;
              if (empty($lang)) {
                $lang = 'und';
              }
              $location = $tempuser->$field_name;
              if (isset($location[$lang][0]['longitude']) && isset($location[$lang][0]['latitude'])) {
                $coordinates['latitude'] = (float) $location[$lang][0]['latitude'];
                $coordinates['longitude'] = (float) $location[$lang][0]['longitude'];
              }
            }
          }
        }
      }
      break;
    case 'distance_arg':
      // not tested
      foreach ($view->argument as $argument) {
        if ($argument->field == 'distance') {
          list($coords, $search_distance) = explode('_', $view->args[$argument->position]);
          list($lat, $lon) = explode(',', $coords);
          break;
        }
      }
      $coordinates['latitude'] = (float) $lat;
      $coordinates['longitude'] = (float) $lon;
      break;

  }

  return $coordinates;
}

function getlocations_fields_views_proximity_get_argument_options($view) {
  // Get the arguments for this view so we can use nid, uid or Global: Null arguments.
  $uid_argument_options = array();
  $nid_argument_options = array();
  $tid_argument_options = array();
  $arguments = $view->display_handler->get_handlers('argument');
  foreach ($arguments as $id => $handler) {
    if ($handler->field == 'null') {
      $uid_argument_options[$id] = $handler->ui_name();
      $nid_argument_options[$id] = $handler->ui_name();
      $tid_argument_options[$id] = $handler->ui_name();
    }
    elseif ($handler->field == 'nid') {
      $nid_argument_options[$id] = $handler->ui_name();
    }
    elseif ($handler->field == 'uid') {
      $uid_argument_options[$id] = $handler->ui_name();
    }
    elseif ($handler->field == 'tid') {
      $tid_argument_options[$id] = $handler->ui_name();
    }
  }
  return array($nid_argument_options, $uid_argument_options, $tid_argument_options);

}

function getlocations_fields_views_proximity_get_location_field_options() {
  $field_options = array();

  $fields = field_info_fields();
  foreach ($fields as $field) {
    if ($field['module'] == 'getlocations_fields') {
      $field_options[$field['field_name']] = t('Getlocations: @name', array('@name' => $field['field_name']));
    }
  }

  return $field_options;
}