<?php
// NEEDS TESTING
/**
 * @file
 * Longitude field handler.
 */

class getlocations_fields_views_handler_field_longitude extends getlocations_fields_views_handler_field_latitude {

  function render($values) {
    if ($this->options['style'] == 'dms') {
      return theme('getlocations_fields_longitude_dms', array('longitude' => $values->{$this->field_alias}));
    }
    return parent::render($values);
  }
}
