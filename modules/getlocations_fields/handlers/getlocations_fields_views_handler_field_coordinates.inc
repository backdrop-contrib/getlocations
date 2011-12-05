<?php
// NEEDS TESTING
/**
 * @file
 * Coordinates field handler.
 */

class getlocations_fields_views_handler_field_coordinates extends getlocations_fields_views_handler_field_latitude {

  function construct() {
    parent::construct();
    $this->additional_fields['longitude'] = 'longitude';
  }

  function render($values) {
    if ($this->options['style'] == 'dms') {
      return theme('getlocations_fields_latitude_dms', array('latitude' => $values->{$this->field_alias})) . ', ' . theme('getlocations_fields_longitude_dms', array('longitude' => $values->{$this->aliases['longitude']}));
    }
    else {
      return check_plain($values->{$this->field_alias}) . ', ' . check_plain($values->{$this->aliases['longitude']});
    }
  }
}
