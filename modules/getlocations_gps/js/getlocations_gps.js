
/**
 * @file
 * getlocations_gps.js
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations_gps module for Backdrop
 */

(function ($) {
  Backdrop.getlocations_gps = {};
  var watchID = '';
  Backdrop.getlocations_gps.dolocation = function(key, settings) {

    $("#getlocations_gps_lat_" + key).html('');
    $("#getlocations_gps_lon_" + key).html('');
    var gps_marker = Backdrop.getlocations.getIcon(settings.gps_marker);
    var gps_marker_title = settings.gps_marker_title;
    var gps_bubble = settings.gps_bubble;
    var gps_geocode = settings.gps_geocode;
    var gps_center = settings.gps_center;
    var gps_type = settings.gps_type;
    var gps_zoom = settings.gps_zoom;
    var gps_latlon_path = settings.gps_latlon_path;
    var gs = Backdrop.getlocations_settings[key];
    gs.show_maplinks = false;
    var accuracies = [];
    accuracies['APPROXIMATE'] = Backdrop.t('Approximate');
    accuracies['GEOMETRIC_CENTER'] = Backdrop.t('Center');
    accuracies['RANGE_INTERPOLATED'] = Backdrop.t('Interpolated');
    accuracies['ROOFTOP'] = Backdrop.t('Exact');
    gs.markdone = gps_marker;
    var result = [];
    result['lat'] = '';
    result['lon'] = '';
    gps_in_dom(key, '', '');
    result['formatted_address'] = '';
    Backdrop.getlocations_gps.marker = Backdrop.getlocations_gps.marker || [];
    gps_marker_kill();

    if (navigator && navigator.geolocation) {
      active_throbber();
      if (gps_type) {
        if (watchID !== '') {
          navigator.geolocation.clearWatch(watchID);
          gps_marker_kill();
          watchID = '';
          deactive_throbber();
        }
        else {
          watchID = navigator.geolocation.watchPosition(gps_getpos, gps_poserror );
        }
      }
      else {
        navigator.geolocation.getCurrentPosition(gps_getpos, gps_poserror );
      }
    } // end if navigator
    else {
      msg = Backdrop.t('Sorry, no browser navigator available.');
      alert(msg);
    }

    // functions
    function gps_getpos(position) {

      // remove any old markers
      gps_marker_kill();

      if (position.coords.latitude && position.coords.longitude) {
        result['lat'] = parseFloat(position.coords.latitude);
        result['lon'] = parseFloat(position.coords.longitude);
        var p = new google.maps.LatLng(result['lat'], result['lon']);
        // send this data back to the server
        var gps_latlon = {gps_lat: result['lat'], gps_lon: result['lon']};
        $.get(gps_latlon_path, gps_latlon);
        if (gps_geocode) {
          // start geocoder
          var geocoder = new google.maps.Geocoder();
          geocoder.geocode({'latLng': p}, function (results, status) {
            if (status == google.maps.GeocoderStatus.OK) {
              result['formatted_address'] = results[0].formatted_address;
              result['lat'] = parseFloat(results[0].geometry.location.lat());
              result['lon'] = parseFloat(results[0].geometry.location.lng());
              gps_in_dom(key, result['lat'], result['lon']);
              var customContent = '';

              if (gps_bubble && result['formatted_address']) {
                customContent = '<div class="location vcard">';
                customContent += '<h4>' + gps_marker_title + '</h4>';
                customContent += '<div class="adr">' + result['formatted_address'].replace(/[,]/g, ',<br />');
                if (results[0].geometry.location_type) {
                  customContent += '<br />' + Backdrop.t('Accuracy') + ' : ' + accuracies[results[0].geometry.location_type];
                }
                customContent += '</div></div>';
                gs.useCustomContent = true;
                gs.useInfoBubble = (Backdrop.settings.getlocations[key].markeraction == 2 ? true : false);
                gs.markeraction = (Backdrop.settings.getlocations[key].markeraction == 2 ? 2 : 1);
              }
              else {
                gs.useCustomContent = false;
                gs.markeraction = 0;
                gs.useInfoBubble = false;
              }

              var ll = new google.maps.LatLng(result['lat'], result['lon']);
              var m = Backdrop.getlocations.makeMarker(Backdrop.getlocations_map[key], gs, result['lat'], result['lon'], 0, gps_marker_title, '', customContent, '', key);
              Backdrop.getlocations_gps.marker[key].push(m);

              // is this a distance View using gps as the origin
              if ( $("input[name='distance[gps]']").is('input')) {
                gps_dobounds(result);
              }

              if (gps_center) {
                Backdrop.getlocations_map[key].setCenter(ll);
              }

              if (gps_zoom > -1) {
                Backdrop.getlocations_map[key].setZoom(parseInt(gps_zoom));
              }

              // getlocations_search
              if (typeof(Backdrop.getlocations_search) !== 'undefined') {
                var mapid2 = key.replace("_", "-");
                var distance = $("#edit-getlocations-search-distance-" + mapid2).val();
                var units = $("#edit-getlocations-search-units-" + mapid2).val();
                var type = $("#edit-getlocations-search-type-" + mapid2).val();
                var limits = $("#edit-getlocations-search-limits-" + mapid2).val();
                var accuracy = accuracies[results[0].geometry.location_type];
                var address = result['formatted_address'];
                Backdrop.getlocations_search.getlocations_search_clear_results(key, gs);
                Backdrop.getlocations_search.getlocations_search_get_data(result['lat'], result['lon'], distance, units, type, limits, accuracy, address, gs, Backdrop.getlocations_map[key], key);
              }
              deactive_throbber();
            }
            else {
              // remove any old markers
              gps_marker_kill();
              deactive_throbber();
              var prm = {'!b': Backdrop.getlocations.getGeoErrCode(status) };
              var msg = Backdrop.t('Geocode was not successful for the following reason: !b', prm);
              alert(msg);
            }
          });
        }
        else {
          gps_in_dom(key, result['lat'], result['lon']);
          gps_marker_kill();
          // no geocode done
          gs.useCustomContent = false;
          gs.markeraction = 0;
          gs.useInfoBubble = false;
          var m = Backdrop.getlocations.makeMarker(Backdrop.getlocations_map[key], gs, result['lat'], result['lon'], 0, gps_marker_title, '', '', '', key);
          Backdrop.getlocations_gps.marker[key].push(m);

          // is this a distance View using gps as the origin
          if ( $("input[name='distance[gps]']").is('input')) {
            gps_dobounds(result);
          }

          if (gps_center) {
            Backdrop.getlocations_map[key].setCenter(p);
          }
          if (gps_zoom > -1) {
            Backdrop.getlocations_map[key].setZoom(parseInt(gps_zoom));
          }
          deactive_throbber();
        }
      }
      else {
        // remove any old markers
        gps_marker_kill();
        deactive_throbber();
      }

    }

    function gps_poserror(error) {
      // remove any old markers
      gps_marker_kill();
      deactive_throbber();
      msg = Backdrop.t("Sorry, I couldn't find your location using the browser") + ' ' + Backdrop.getlocations.geolocationErrorMessages(error) + ".";
      alert(msg);
    }

    function deactive_throbber() {
      $("#getlocations_gps_throbber_" + key).removeClass('getlocations_gps_throbber_active').addClass('getlocations_gps_throbber_inactive');
    }

    function active_throbber() {
      $("#getlocations_gps_throbber_" + key).removeClass('getlocations_gps_throbber_inactive').addClass('getlocations_gps_throbber_active');
    }

    function gps_in_dom(k, lat, lon) {
      if (! $("#getlocations_gps_lat_" + k).is('div')) {
        var lladd = '<div class="js-hide" id="getlocations_gps_lat_' + k + '"></div><div class="js-hide" id="getlocations_gps_lon_' + k + '"></div>';
        $("#getlocations_map_wrapper_" + k).append(lladd);
      }
      if (lat && lon) {
        $("#getlocations_gps_lat_" + k).html(lat);
        $("#getlocations_gps_lon_" + k).html(lon);
        if ($("#edit-distance-latitude").is('input')) {
          $("#edit-distance-latitude").val(lat);
          $("#edit-distance-longitude").val(lon);
        }
      }
    }

    function gps_marker_kill() {
      // remove any old markers
      if (Backdrop.getlocations_gps.marker[key] !== undefined ) {
        for (var mct = 0; mct < Backdrop.getlocations_gps.marker[key].length; mct++) {
          Backdrop.getlocations_gps.marker[key][mct].setMap();
        }
      }
      else {
        Backdrop.getlocations_gps.marker[key] = [];
      }
    }

    function gps_dobounds(r) {
      // a View with exposed filter distance form with gps selected as origin
      if ( $("input[name='distance[gps]']").is('input')) {
        var data = Backdrop.getlocations_data[key];
        if (data.datanum > 0) {
          // add the origin to minmaxes
          var minmaxes = data.minmaxes;
          if ( r['lat'] < minmaxes.minlat ) {
            minmaxes.minlat = r['lat'];
          }
          if ( r['lon'] < minmaxes.minlon ) {
            minmaxes.minlon = r['lon'];
          }
          if ( r['lat'] > minmaxes.maxlat ) {
            minmaxes.maxlat = r['lat'];
          }
          if ( r['lon'] > minmaxes.maxlon ) {
            minmaxes.maxlon = r['lon'];
          }
          Backdrop.getlocations.doBounds(Backdrop.getlocations_map[key], minmaxes.minlat, minmaxes.minlon, minmaxes.maxlat, minmaxes.maxlon, false);
        }
      }
    }
    // end functions
  };

  Backdrop.behaviors.getlocations_gps = {
    attach: function (context, settings) {

      // doh
      if (settings.getlocations_gps == undefined) {
        return;
      }

      $(".getlocations_map_canvas", context).once('getlocations-gps-map-processed', function(index, element) {
        var elemID = $(element).attr('id');
        var key = elemID.replace(/^getlocations_map_canvas_/, '');
        // is there really a map?
        if ($("#getlocations_map_canvas_" + key).is('div') && settings.getlocations_gps[key] !== undefined ) {
          var lladd = '<div class="js-hide" id="getlocations_gps_lat_' + key + '"></div><div class="js-hide" id="getlocations_gps_lon_' + key + '"></div>';
          $("#getlocations_map_wrapper_" + key).append(lladd);
          // gps button
          $("#getlocations_gps_show_" + key).click( function() {
            Backdrop.getlocations_gps.dolocation(key, settings.getlocations_gps[key]);
          }); // end button click
        } //  end is there really a map?
      }); // end once
    } // end attach
  }; // end behaviors
})(jQuery);
