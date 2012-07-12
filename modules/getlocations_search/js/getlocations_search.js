
/**
 * @file
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations_search module
*/
(function ($) {
  var batchr = [];
  var do_lookup = 0;
  Drupal.getlocations.doSearch = function(map, gs, mkey) {
    var searchsettings = Drupal.settings.getlocations_search;
    var method = '';
    var autocomplete_bias = 0;
    jQuery.each(searchsettings, function (searchkey, ssettings) {
      method = ssettings.method;
      do_lookup = ssettings.do_lookup;
      autocomplete_bias = ssettings.autocomplete_bias;
    }); // end each search loop

    if (gs.markermanagertype == 1) {
      gs.usemarkermanager = true;
      mgr = new MarkerManager(map, {
        borderPadding: 50,
        maxZoom: ssettings.maxzoom,
        trackMarkers: false
      });
    }
    else if (gs.markermanagertype == 2) {
      gs.useclustermanager = true;
      cmgr = new MarkerClusterer(
        map,
        [],
        {
          gridSize: gs.cmgr_gridSize,
          maxZoom: gs.cmgr_maxZoom,
          styles: gs.cmgr_styles[gs.cmgr_style],
          minimumClusterSize: gs.cmgr_minClusterSize,
          title: gs.cmgr_title
        }
      );
    }
    if (method == 'google_ac') {
      var input_adrs = document.getElementById("edit-getlocations-search");
      var fm_adrs = '';
      var ac_adrs = new google.maps.places.Autocomplete(input_adrs);
      if (autocomplete_bias) {
        ac_adrs.bindTo('bounds', map);
      }
      google.maps.event.addListener(ac_adrs, 'place_changed', function () {
        var place_adrs = ac_adrs.getPlace();
        fm_adrs = {'address': place_adrs.formatted_address};
        // Create a Client Geocoder
        do_Geocode(map, gs, fm_adrs, mkey);
      });
    }
    else {
      $("#edit-getlocations-search-submit").click( function() {
        // collect the search string
        input_adrs = $("#edit-getlocations-search").val();
        fm_adrs = {'address': input_adrs};
        // Create a Client Geocoder
        do_Geocode(map, gs, fm_adrs, mkey);
        return false;
      });
    }

    if (gs.is_mobile) {
      if (navigator && navigator.geolocation) {
        $("#getlocations_search_geolocation_button").click( function () {
          do_Geolocationbutton(map, gs, mkey);
          return false;
        });
      }
      else {
        $("#getlocations_search_geolocation_button").hide();
      }
    }
  }

  // cleans out any existing markers, sets up a new geocoder and runs it, filling in the results.
  function do_Geocode(map, gs, adrs, mkey) {
    // are there any markers already?
    if (batchr.length > 1) {
      // clear out markers
      for($i=0; $i <= batchr.length; $i++) {
        marker = batchr.pop();
        marker.setMap();
      }
      // clear out manager
      if (gs.usemarkermanager) {
        mgr.clearMarkers();
      }
      else if (gs.useclustermanager) {
        cmgr.clearMarkers();
      }
      batchr = [];
    }
    // clear the results box
    $("#getlocations_search_address").html();
    $("#getlocations_search_count").html();
    $("#getlocations_search_distance").html();
    $("#getlocations_search_type").html();
    $("#getlocations_search_lat").html();
    $("#getlocations_search_lon").html();
    // set up some display vars
    var unitsdisplay = {'km': Drupal.t('Kilometer'), 'm': Drupal.t('Meter'), 'mi': Drupal.t('Mile'), 'yd': Drupal.t('Yard'), 'nmi': Drupal.t('Nautical mile')};
    var unitsdisplaypl = {'km': Drupal.t('Kilometers'), 'm': Drupal.t('Meters'), 'mi': Drupal.t('Miles'), 'yd': Drupal.t('Yards'), 'nmi': Drupal.t('Nautical miles')};
    var typesdisplay = {'all': Drupal.t('All'), 'node': Drupal.t('Nodes'), 'user': Drupal.t('Users'), 'term': Drupal.t('Terms'), 'comment': Drupal.t('Comments')};
    // get settings from the DOM
    var distance = $("#edit-getlocations-search-distance").val();
    var units = $("#edit-getlocations-search-units").val();
    var type = $("#edit-getlocations-search-type").val();
    var limits = $("#edit-getlocations-search-limits").val();
    // start geocoder
    var geocoder = new google.maps.Geocoder();
    geocoder.geocode(adrs, function (results, status) {
      if (status == google.maps.GeocoderStatus.OK) {
        var address = results[0].formatted_address;
        // go get the data
        $.get(Drupal.settings.basePath + "getlocations_search/info", {'lat':results[0].geometry.location.lat(),'lon':results[0].geometry.location.lng(),'distance':distance,'units':units,'type':type,'limits':limits}, function(data) {
          // in data, an array of locations, minmaxes and info
          var locations = data['locations'];
          var minmaxes = data['minmaxes'];
          var minlat = ''; var minlon = ''; var maxlat = ''; var maxlon = ''; var cenlat = ''; var cenlon = '';
          if (minmaxes) {
            mmarr = minmaxes.split(',');
            minlat = parseFloat(mmarr[0]);
            minlon = parseFloat(mmarr[1]);
            maxlat = parseFloat(mmarr[2]);
            maxlon = parseFloat(mmarr[3]);
            cenlat = parseFloat((minlat + maxlat)/2);
            cenlon = parseFloat((minlon + maxlon)/2);
          }
          var info = data['info'];
          distance = 0;
          units = '';
          infoarr = info.split(',');
          distance = infoarr[0];
          units = infoarr[1];
          type = infoarr[2];
          latout = infoarr[3];
          lonout = infoarr[4];
          locationct = 0;
          for (var i = 0; i < locations.length; i++) {
            lidkey = 'nid';
            if (locations[i].nid > 0) { lidkey = 'nid'; }
            else if (locations[i].uid > 0) { lidkey = 'uid'; }
            else if (locations[i].tid > 0) { lidkey = 'tid'; }
            else if (locations[i].cid > 0) { lidkey = 'cid'; }
            gs.markdone = Drupal.getlocations.getIcon(locations[i].marker);
            title = (locations[i].title ? locations[i].title : (locations[i].name ? locations[i].name : ''));
            marker = Drupal.getlocations.makeMarker(map, gs, locations[i].latitude, locations[i].longitude, locations[i].glid, title, lidkey, '', mkey);
            batchr.push(marker);
            locationct++;
          }
          // display results
          $("#getlocations_search_address").html('<span class="results-label">' + Drupal.t('Search') + ':</span><span class="results-value">' +  address + '</span>');
          $("#getlocations_search_distance").html('<span class="results-label">' + Drupal.t('Distance') + ':</span><span class="results-value">' + distance + ' ' + (distance == 1 ? unitsdisplay[units] : unitsdisplaypl[units] ) + '</span>');
          if (do_lookup) {
            $("#getlocations_search_count").html('<span class="results-label">' + Drupal.t('Locations found') + ':</span><span class="results-value">' + locationct + '</span>');
            $("#getlocations_search_type").html('<span class="results-label">' + Drupal.t('Search Type') + ':</span><span class="results-value">' + typesdisplay[type] + '</span>');
          }
          $("#getlocations_search_lat").html('<span class="results-label">' + Drupal.t('Latitude') + ':</span><span class="results-value">' + latout + '</span>');
          $("#getlocations_search_lon").html('<span class="results-label">' + Drupal.t('Longitude') + ':</span><span class="results-value">' + lonout + '</span>');
          // markermanagers add batchr
          if (gs.usemarkermanager) {
            mgr.addMarkers(batchr, gs.minzoom, gs.maxzoom);
          }
          else if (gs.useclustermanager) {
            cmgr.addMarkers(batchr, 0);
          }
          if (minlat !== '' && minlon !== '' && maxlat !== '' && maxlon !== '') {
            if (gs.pansetting == 1) {
              Drupal.getlocations.doBounds(map, minlat, minlon, maxlat, maxlon, true);
            }
            else if (gs.pansetting == 2) {
              Drupal.getlocations.doBounds(map, minlat, minlon, maxlat, maxlon, false);
            }
            else if (gs.pansetting == 3) {
              if (cenlat && cenlon) {
                c = new google.maps.LatLng(cenlat, cenlon);
                map.setCenter(c);
              }
            }
          }
          if (gs.usemarkermanager) {
            mgr.refresh();
          }
          else if (gs.useclustermanager) {
             cmgr.repaint();
          }
        });
      }
      else {
        var prm = {'!a': place_adrs, '!b': Drupal.getlocations.getGeoErrCode(status) };
        var msg = Drupal.t('Geocode for (!a) was not successful for the following reason: !b', prm);
        alert(msg);
      }
    });
  }

  function do_Geolocationbutton(map, gs, mkey) {
    var statusdiv = '#getlocations_search_geolocation_status';
    var statusmsg = '';
    $(statusdiv).html(statusmsg);
    navigator.geolocation.getCurrentPosition(
      function(position) {
        lat = position.coords.latitude;
        lng = position.coords.longitude;
        var p = new google.maps.LatLng(parseFloat(lat), parseFloat(lng));
        var fm_adrs = {'latLng': p};
        do_Geocode(map, gs, fm_adrs, mkey);
        //statusmsg = Drupal.t('Browser OK');
        //$(statusdiv).html(statusmsg);
      },
      function(error) {
        statusmsg = Drupal.t("Sorry, I couldn't find your location using the browser") + ' ' + Drupal.getlocations.geolocationErrorMessages(error.code) + ".";
        $(statusdiv).html(statusmsg);
      }, {maximumAge:10000}
    );
  }

})(jQuery);
