<?php

/**
 * @file
 * getlocations_fields_handler_field_longitude.inc
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * Longitude field handler.
 */

class getlocations_fields_handler_field_longitude extends getlocations_fields_handler_field_latitude {

  function render($values) {
    if ($this->options['style'] == 'dms') {
      return theme('getlocations_longitude_dms', array('longitude' => $values->{$this->field_alias}));
    }
    return parent::render($values);
  }
}
