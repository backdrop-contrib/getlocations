/**
 * @file
 * Javascript functions for getlocations module for Drupal 7
 *
 * @author Bob Hutchinson http://drupal.org/user/52366
 * this is for googlemaps API version 3
 */

(function ($) {

  Drupal.behaviors.getlocations_fields = {
    attach: function() {

      var adrsfield = 'getlocations_address';
      var namefield = 'getlocations_name';
      var streetfield = 'getlocations_street';
      var additionalfield = 'getlocations_additional';
      var cityfield = 'getlocations_city';
      var provincefield = 'getlocations_province';
      var postal_codefield = 'getlocations_postal_code';
      var countryfield = 'getlocations_country';
      var latfield = 'getlocations_latitude';
      var lonfield = 'getlocations_longitude';
      var mark = '';
      var point = '';

      var settings = Drupal.settings.getlocations_fields;
      var nodezoom = parseInt(settings.nodezoom);
      var use_address = settings.use_address;

     // we need to see if this is an update
      var lat = $("#" + latfield).val();
      var lng = $("#" + lonfield).val();
      if (lat && lng) {
        point = new google.maps.LatLng(parseFloat(lat), parseFloat(lng));
        inputmap.panTo(point);
        inputmap.setZoom(nodezoom);
        makeMoveMarker(point);
      }

      if (use_address) {
        var input_adrs = document.getElementById(adrsfield);
        var fm_adrs = '';
        var ac_adrs = new google.maps.places.Autocomplete(input_adrs);
        google.maps.event.addListener(ac_adrs, 'place_changed', function() {
          var place_adrs = ac_adrs.getPlace();
          fm_adrs = {'address': place_adrs.formatted_address};
          // Create a Client Geocoder
          var geocoder = new google.maps.Geocoder();
          geocoder.geocode(fm_adrs, function (results, status) {
            if (status == google.maps.GeocoderStatus.OK) {
              point = results[0].geometry.location;
              lat = results[0].geometry.location.lat();
              lng = results[0].geometry.location.lng();
              $("#" + latfield).val(lat);
              $("#" + lonfield).val(lng);
              $("#" + adrsfield).val(place_adrs.formatted_address);

// NEEDS WORK //////////////////////////

              address_components = place_adrs.address_components;
              streetfield_value = '';
              streetnumber_value = '';
              additionalfield_value = '';
              cityfield_value = '';
              provincefield_value = '';
              countryfield_value = '';
              postal_codefield_value = '';
              postal_code_prefix_field_value = '';
              admin_area_level_1 = '';
              admin_area_level_2 = '';
              admin_area_level_3 = '';
              for (var i = 0; i < address_components.length; i++) {
                type = address_components[i].types[0];
                //if (type == 'street_address') {
                //  streetfield_value = address_components[i].long_name;
                //}
                if (type == 'street_number') {
                  streetnumber_value = address_components[i].long_name;
                }
                else if (type == 'route') {
                  streetfield_value = address_components[i].long_name;
                }
                else if (type == 'locality') {
                  cityfield_value = address_components[i].long_name;
                }
                else if (type == 'sublocality') {
                  additionalfield_value = address_components[i].long_name;
                }
                else if (type == 'administrative_area_level_3') {
                  admin_area_level_3 = address_components[i].long_name;
                }
                else if (type == 'administrative_area_level_2') {
                  admin_area_level_2 = address_components[i].long_name;
                }
                else if (type == 'administrative_area_level_1') {
                  admin_area_level_1 = address_components[i].long_name;
                }
                else if (type == 'country') {
                  countryfield_value = address_components[i].long_name;
                }
                else if (type == 'postal_code_prefix') {
                  postal_code_prefix_field_value = address_components[i].long_name;
                }
                else if (type == 'postal_code') {
                  postal_codefield_value = address_components[i].long_name;
                }

              }
              $("#" + streetfield).val( (streetnumber_value ? streetnumber_value + ' ' : '') + streetfield_value);
              if (admin_area_level_3 ) {
                provincefield_value = admin_area_level_3;
              }
              if (admin_area_level_2 && ! provincefield_value) {
                provincefield_value = admin_area_level_2;
              }
              if (admin_area_level_1 && ! provincefield_value) {
                provincefield_value = admin_area_level_1;
              }
              $("#" + provincefield).val(provincefield_value);
              $("#" + additionalfield).val(additionalfield_value);
              $("#" + cityfield).val(cityfield_value);
              if (postal_codefield_value) {
                $("#" + postal_codefield).val(postal_codefield_value);
              }
              else {
                $("#" + postal_codefield).val(postal_code_prefix_field_value);
              }

              // input or select box
              if ($("#" + countryfield).is("input")) {
                $("#" + countryfield).val(countryfield_value);
              }
              else if ($("#" + countryfield).is("select")) {
                // country list is keyed on two letter codes so we need to get
                // the code from the server in order to set the selectbox correctly
                $.get("/getlocations_fields/countryinfo", {'country': countryfield_value}, function(data) {
                  if (data) {
                    $("#" + countryfield).val(data).attr('selected', 'selected');
                  }
                });
              }

////////////////////////////

              inputmap.panTo(point);
              inputmap.setZoom(nodezoom);
              makeMoveMarker(point);
            }
            else {
              var prm = {'!a': place_adrs, '!b': getGeoErrCode(status) };
              var msg = Drupal.t('Geocode for (!a) was not successful for the following reason: !b', prm);
              alert(msg);
            }
          });

        });

      }
      else {
        // no autocomplete
        $("#getlocations_geocodebutton").click( function() { manageGeobutton(); return false; });
      }

      function manageGeobutton() {
        var input_adrs_arr = [];
        var streetfield_value = $("#" + streetfield).val();
        if (streetfield_value) {
          input_adrs_arr.push(streetfield_value);
        }
        var additionalfield_value = $("#" + additionalfield).val();
        if (additionalfield_value) {
          input_adrs_arr.push(additionalfield_value);
        }
        var cityfield_value = $("#" + cityfield).val();
        if (cityfield_value) {
          input_adrs_arr.push(cityfield_value);
        }
        var provincefield_value = $("#" + provincefield).val();
        if (provincefield_value) {
          input_adrs_arr.push(provincefield_value);
        }
        var postal_codefield_value = $("#" + postal_codefield).val();
        if (postal_codefield_value) {
          input_adrs_arr.push(postal_codefield_value);
        }
        var countryfield_value = $("#" + countryfield).val();
        if (countryfield_value) {
          if (countryfield_value == 'GB' ) {
            countryfield_value = 'UK';
          }
          input_adrs_arr.push(countryfield_value);
        }

        var input_adrstmp = input_adrs_arr.join(", ");
        if (input_adrstmp) {
          var input_adrs = {address: input_adrstmp};
          // Create a Client Geocoder
          var geocoder = new google.maps.Geocoder();
          geocoder.geocode(input_adrs, function (results, status) {
            if (status == google.maps.GeocoderStatus.OK) {
              point = results[0].geometry.location;
              lat = results[0].geometry.location.lat();
              lng = results[0].geometry.location.lng();
              $("#" + latfield).val(lat);
              $("#" + lonfield).val(lng);
              inputmap.panTo(point);
              inputmap.setZoom(nodezoom);
              makeMoveMarker(point);
            }
            else {
              var prm = {'!a': input_adrstmp , '!b': getGeoErrCode(status) };
              var msg = Drupal.t('Geocode for (!a) was not successful for the following reason: !b', prm);
              alert(msg);
            }
          });
        }
        else {
          var msg = Drupal.t('You have not entered an address.');
          alert(msg);
        }
      }

      google.maps.event.addListener(inputmap, 'click', function(event) {
        if (! mark) {
          // make an icon
          if (! point) {
            point = inputmap.getCenter();
          }
          makeMoveMarker(point);
        }
      });

      function makeMoveMarker(ppoint) {
        // remove existing marker
        if (mark) {
          mark.setMap();
        }
        marker = Drupal.getlocations.getIcon(settings.map_marker);
        mark = new google.maps.Marker({
          icon: marker.image,
          shadow: marker.shadow,
          shape: marker.shape,
          map: inputmap,
          position: ppoint,
          draggable: true,
          title: Drupal.t('Drag me to change position')
        });
        google.maps.event.addListener(mark, "dragend", function() {
          p = mark.getPosition();
          inputmap.panTo(p);
          //map.setZoom(nodezoom);
          lat = p.lat();
          lng = p.lng();
          $("#" + latfield).val(lat);
          $("#" + lonfield).val(lng);
        });
      }

      function getGeoErrCode(errcode) {
        var errstr;
        if (errcode == google.maps.GeocoderStatus.ERROR) {
          errstr = Drupal.t("There was a problem contacting the Google servers.");
        }
        else if (errcode == google.maps.GeocoderStatus.INVALID_REQUEST) {
          errstr = Drupal.t("This GeocoderRequest was invalid.");
        }
        else if (errcode == google.maps.GeocoderStatus.OVER_QUERY_LIMIT) {
          errstr = Drupal.t("The webpage has gone over the requests limit in too short a period of time.");
        }
        else if (errcode == google.maps.GeocoderStatus.REQUEST_DENIED) {
          errstr = Drupal.t("The webpage is not allowed to use the geocoder.");
        }
        else if (errcode == google.maps.GeocoderStatus.UNKNOWN_ERROR) {
          errstr = Drupal.t("A geocoding request could not be processed due to a server error. The request may succeed if you try again.");
        }
        else if (errcode == google.maps.GeocoderStatus.ZERO_RESULTS) {
          errstr = Drupal.t("No result was found for this GeocoderRequest.");
        }
        return errstr;
      }

    }
  }
})(jQuery);
