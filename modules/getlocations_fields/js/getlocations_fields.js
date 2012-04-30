/**
 * @file
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations_fields module for Drupal 7
 * this is for googlemaps API version 3
 */

(function ($) {

  Drupal.behaviors.getlocations_fields = {
    attach: function () {

      var settings = Drupal.settings.getlocations_fields;

      // each map has its own settings
      jQuery.each(settings, function (key, sett) {

        var point = [];
        var adrsfield = 'getlocations_address_';
        var namefield = 'getlocations_name_';
        var streetfield = 'getlocations_street_';
        var additionalfield = 'getlocations_additional_';
        var cityfield = 'getlocations_city_';
        var provincefield = 'getlocations_province_';
        var postal_codefield = 'getlocations_postal_code_';
        var countryfield = 'getlocations_country_';
        var latfield = 'getlocations_latitude_';
        var lonfield = 'getlocations_longitude_';
        var nodezoom = '';
        var use_address = '';
        var map_marker = 'drupal';
        var mark = [];
        var gkey = key;
        nodezoom = parseInt(sett.nodezoom);
        use_address = sett.use_address;
        map_marker = sett.map_marker;

       // we need to see if this is an update
        lat = $("#" + latfield + key).val();
        lng = $("#" + lonfield + key).val();
        if (lat && lng) {
          point[key] = new google.maps.LatLng(parseFloat(lat), parseFloat(lng));
          updateMap(getlocations_inputmap[key], point[key], key);
        }

        if (use_address) {
          var input_adrs = document.getElementById(adrsfield + key);
          var fm_adrs = '';
          var ac_adrs = new google.maps.places.Autocomplete(input_adrs);
          google.maps.event.addListener(ac_adrs, 'place_changed', function () {
            var place_adrs = ac_adrs.getPlace();
            fm_adrs = {'address': place_adrs.formatted_address};
            // Create a Client Geocoder
            var geocoder = new google.maps.Geocoder();
            geocoder.geocode(fm_adrs, function (results, status) {
              if (status == google.maps.GeocoderStatus.OK) {
                point[gkey] = results[0].geometry.location;
                lat = results[0].geometry.location.lat();
                lng = results[0].geometry.location.lng();
                $("#" + latfield + gkey).val(lat);
                $("#" + lonfield + gkey).val(lng);
                $("#" + adrsfield + gkey).val(place_adrs.formatted_address);
                updateMap(getlocations_inputmap[gkey], point[gkey], gkey);
                set_address_components(gkey, place_adrs.address_components);
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
          $("#" + 'getlocations_geocodebutton_' + key).click( function () {
            manageGeobutton(key);
            return false;
          });
        }

        function manageGeobutton(k) {
          var mmap = getlocations_inputmap[k];
          var kk = k;
          var input_adrs_arr = [];
          var streetfield_value = $("#" + streetfield + k).val();
          if (streetfield_value) {
            input_adrs_arr.push(streetfield_value);
          }
          var additionalfield_value = $("#" + additionalfield + k).val();
          if (additionalfield_value) {
            input_adrs_arr.push(additionalfield_value);
          }
          var cityfield_value = $("#" + cityfield + k).val();
          if (cityfield_value) {
            input_adrs_arr.push(cityfield_value);
          }
          var provincefield_value = $("#" + provincefield + k).val();
          if (provincefield_value) {
            input_adrs_arr.push(provincefield_value);
          }
          var postal_codefield_value = $("#" + postal_codefield + k).val();
          if (postal_codefield_value) {
            input_adrs_arr.push(postal_codefield_value);
          }
          var countryfield_value = $("#" + countryfield + k).val();
          if (countryfield_value && streetfield_value) {
            if (countryfield_value == 'GB' ) {
              countryfield_value = 'UK';
            }
            input_adrs_arr.push(countryfield_value);
          }
          var input_adrstmp = input_adrs_arr.join(", ");
          if (input_adrstmp) {
            var input_adrs = {'address': input_adrstmp};
            // Create a Client Geocoder
            var geocoder = new google.maps.Geocoder();
            geocoder.geocode(input_adrs, function (results, status) {
              if (status == google.maps.GeocoderStatus.OK) {
                point[kk] = results[0].geometry.location;
                lat = results[0].geometry.location.lat();
                lng = results[0].geometry.location.lng();
                $("#" + latfield + kk).val(lat);
                $("#" + lonfield + kk).val(lng);
                updateMap(mmap, point[kk], kk);
              }
              else {
                var prm = {'!a': input_adrstmp, '!b': getGeoErrCode(status) };
                var msg = Drupal.t('Geocode for (!a) was not successful for the following reason: !b', prm);
                alert(msg);
              }
            });
          }
          else if ( ($("#" + latfield + k).val() !== '') && ($("#" + lonfield + k).val() !== '')  ) {
            lat = $("#" + latfield + k).val();
            lng = $("#" + lonfield + k).val();
            point[k] = new google.maps.LatLng(parseFloat(lat), parseFloat(lng));
            var input_ll = {'latLng': point[k]};
            // Create a Client Geocoder
            var geocoder = new google.maps.Geocoder();
            geocoder.geocode(input_ll, function (results, status) {
              if (status == google.maps.GeocoderStatus.OK) {
                //
                if (results[0]) {
                  //results[0].formatted_address
                  if ($("#" + namefield + kk).val() == '') {
                    $("#" + namefield + kk).val(results[0].formatted_address);
                  }
                  set_address_components(kk, results[0].address_components);
                }
              }
              else {
                var prm = {'!b': Drupal.getlocations.getGeoErrCode(status) };
                var msg = Drupal.t('Geocode was not successful for the following reason: !b', prm);
                alert(msg);
              }
            });
          }
          else {
            var msg = Drupal.t('You have not entered an address.');
            alert(msg);
          }
        }

        // distribute the results to the various textfields
        function set_address_components(k, address_components) {
          streetfield_value = '';
          streetnumber_value = '';
          additionalfield_value = '';
          neighborhood_value = '';
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
            else if (type == 'neighborhood') {
              neighborhood_value = address_components[i].long_name;
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
          $("#" + streetfield + k).val( (streetnumber_value ? streetnumber_value + ' ' : '') + streetfield_value);

          if (admin_area_level_1) {
            provincefield_value = admin_area_level_1;
          }
          if (admin_area_level_1 && admin_area_level_2) {
            provincefield_value = admin_area_level_2 + ', ' + admin_area_level_1;
          }
          if (admin_area_level_1 && admin_area_level_2 && admin_area_level_3) {
            provincefield_value = admin_area_level_3 + ', ' + admin_area_level_2 + ', ' + admin_area_level_1;
          }
          if (admin_area_level_2 && admin_area_level_3) {
            provincefield_value = admin_area_level_3 + ', ' + admin_area_level_2;
          }
          if (admin_area_level_2 && ! provincefield_value) {
            provincefield_value = admin_area_level_2;
          }
          if (admin_area_level_3  && ! provincefield_value) {
            provincefield_value = admin_area_level_3;
          }

          $("#" + provincefield + k).val(provincefield_value);
          $("#" + additionalfield + k).val((additionalfield_value ? additionalfield_value : neighborhood_value));
          $("#" + cityfield + k).val(cityfield_value);
          if (postal_codefield_value) {
            $("#" + postal_codefield + k).val(postal_codefield_value);
          }
          else {
            $("#" + postal_codefield + k).val(postal_code_prefix_field_value);
          }

          // input or select box
          if ($("#" + countryfield + k).is("input")) {
            $("#" + countryfield + k).val(countryfield_value);
          }
          else if ($("#" + countryfield + k).is("select")) {
            // country list is keyed on two letter codes so we need to get
            // the code from the server in order to set the selectbox correctly
            var path = Drupal.settings.basePath + "getlocations_fields/countryinfo";
            var kk = k;
            $.get(path, {'country': countryfield_value}, function (data) {
              if (data) {
                $("#" + countryfield + kk).val(data).attr('selected', 'selected');
              }
            });
          }
        } // set_address_components

        google.maps.event.addListener(getlocations_inputmap[gkey], 'click', function (event) {
          if (! mark[gkey]) {
            // make an icon
            if (! point[gkey]) {
              point[gkey] = event.latLng;
              getlocations_inputmap[gkey].setCenter(point[gkey]);
            }
            makeMoveMarker(getlocations_inputmap[gkey], point[gkey], gkey);
          }
        });

        function makeMoveMarker(mmap, ppoint, mkey) {
          // remove existing marker
          if (mark[mkey]) {
            mark[mkey].setMap();
          }
          marker = Drupal.getlocations.getIcon(map_marker);
          mark[mkey] = new google.maps.Marker({
            icon: marker.image,
            shadow: marker.shadow,
            shape: marker.shape,
            map: mmap,
            position: ppoint,
            draggable: true,
            title: Drupal.t('Drag me to change position')
          });
          var mmmap = mmap;
          var mmkey = mkey;
          google.maps.event.addListener(mark[mkey], "dragend", function () {
            p = mark[mmkey].getPosition();
            mmmap.panTo(p);
            lat = p.lat();
            lng = p.lng();
            $("#" + latfield + mmkey).val(lat);
            $("#" + lonfield + mmkey).val(lng);
          });
        }

        function updateMap(umap, pt, ukey) {
          umap.panTo(pt);
          umap.setZoom(nodezoom);
          makeMoveMarker(umap, pt, ukey);
        }

        $("#" + 'getlocations_smart_ip_button_' + key).click( function () {
          manageSmartIpbutton(key);
          return false;
        });

        function manageSmartIpbutton(k) {
          var kk = k;
          $.get(Drupal.settings.basePath + "getlocations_fields/smart_ip", {}, function (loc) {
            if (loc) {
              lat = loc.latitude;
              lng = loc.longitude;
              if (lat && lng) {
                $("#" + latfield + kk).val(lat);
                $("#" + lonfield + kk).val(lng);
                if (loc.city) {
                  $("#" + cityfield + kk).val(loc.city);
                }
                if (loc.region) {
                  $("#" + provincefield + kk).val(loc.region);
                }
                if (loc.zip && loc.zip != '-') {
                  $("#" + postal_codefield + kk).val(loc.zip);
                }

                if ($("#" + countryfield + kk).is("input")) {
                  if (loc.country) {
                    $("#" + countryfield + kk).val(loc.country);
                  }
                }
                else if ($("#" + countryfield + kk).is("select")) {
                  // do we already have countrycode?
                  cc = '';
                  if (loc.country_code) {
                    if (loc.country_code == 'UK') {
                      cc = 'GB';
                    }
                    else {
                      cc = loc.country_code;
                    }
                  }
                  if (cc) {
                    $("#" + countryfield + kk).val(cc).attr('selected', 'selected');
                  }
                  else if (loc.country) {
                    // country list is keyed on two letter codes so we need to get
                    // the code from the server in order to set the selectbox correctly
                    var kkk = kk;
                    $.get(Drupal.settings.basePath + "getlocations_fields/countryinfo", {'country': loc.country}, function (data) {
                      if (data) {
                        $("#" + countryfield + kkk).val(data).attr('selected', 'selected');
                      }
                    });
                  }
                }
                point[kk] = new google.maps.LatLng(parseFloat(lat), parseFloat(lng));
                updateMap(getlocations_inputmap[kk], point[kk], kk);
              }
            }
          });
        }

        // do 'fake' required fields
        var requireds = ['name', 'street', 'additional', 'city', 'province', 'postal_code'];
        $.each(requireds, function(k, v) {
          if ($(".getlocations_required_" + v + '_' + key).is("div")) {
            $("div.getlocations_required_" + v + "_" + key + " label").append(' <span class="form-required" title="' + Drupal.t("This field is required.") + '">*</span>');
          }
        });

      }); // end each setting loop


    }
  };
})(jQuery);
