/**
 * @file
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations module for Drupal 7
 * this is for googlemaps API version 3
*/

var getlocations_inputmap = [];
var getlocations_map = [];
(function ($) {
  // global vars
  var settings = [];

  function initialize() {

    // in icons.js
    Drupal.getlocations.iconSetup();

    settings = Drupal.settings.getlocations;

    // each map has its own settings
    jQuery.each(settings, function (key, settings) {

      var global_settings = {
        maxzoom: 16,
        minzoom: 7,
        nodezoom: 12,
        mgr: '',
        cmgr: '',
        cmgr_gridSize: null,
        cmgr_maxZoom: null,
        cmgr_minClusterSize: null,
        cmgr_styles: '',
        cmgr_style: null,
        defaultIcon: '',
        usemarkermanager: true,
        useInfoBubble: false,
        useInfoWindow: false,
        useCustomContent: false,
        useLink: false,
        markeraction: 0,
        markeractiontype: 1,
        infoBubbles: [],
        datanum: 0,
        trafficInfo: {},
        bicycleInfo: {},
        traffictoggleState: [],
        bicycletoggleState: [],
        panoramioLayer: {},
        panoramiotoggleState: []
      };

      var lat = parseFloat(settings.lat);
      var lng = parseFloat(settings.lng);
      var selzoom = parseInt(settings.zoom);
      var controltype = settings.controltype;
      var pancontrol = settings.pancontrol;
      var scale = settings.scale;
      var overview = settings.overview;
      var overview_opened = settings.overview_opened;
      var streetview_show = settings.streetview_show;
      var scrollw = settings.scrollwheel;
      var maptype = (settings.maptype ? settings.maptype : '');
      var baselayers = (settings.baselayers ? settings.baselayers : '');
      var map_marker = settings.map_marker;
      var poi_show = settings.poi_show;
      var transit_show = settings.transit_show;
      var pansetting = settings.pansetting;
      var draggable = settings.draggable;
      var map_styles = settings.styles;

      global_settings.minzoom = parseInt(settings.minzoom);
      global_settings.maxzoom = parseInt(settings.maxzoom);
      global_settings.nodezoom = parseInt(settings.nodezoom);
      global_settings.datanum = settings.datanum;
      global_settings.markermanagertype = settings.markermanagertype;
      global_settings.pansetting = settings.pansetting;

      if (settings.markermanagertype == 2) {
        global_settings.cmgr_styles = Drupal.settings.getlocations_markerclusterer;
        global_settings.cmgr_style = (settings.markerclusterer_style == -1 ? null : settings.markerclusterer_style);
        global_settings.cmgr_gridSize = (settings.markerclusterer_size == -1 ? null : parseInt(settings.markerclusterer_size));
        global_settings.cmgr_maxZoom = (settings.markerclusterer_zoom == -1 ? null : parseInt(settings.markerclusterer_zoom));
        global_settings.cmgr_minClusterSize = (settings.markerclusterer_minsize == -1 ? null : parseInt(settings.markerclusterer_minsize));
      }

      if (settings.markermanagertype == 1 && settings.usemarkermanager) {
        global_settings.usemarkermanager = true;
        global_settings.useclustermanager = false;
      }
      else if (settings.markermanagertype == 2 && settings.useclustermanager) {
        global_settings.useclustermanager = true;
        global_settings.usemarkermanager = false;
      }
      else {
        global_settings.usemarkermanager = false;
        global_settings.useclustermanager = false;
      }

      global_settings.markeraction = settings.markeraction;
      global_settings.markeractiontype = 'click';
      if (settings.markeractiontype == 2) {
        global_settings.markeractiontype = 'mouseover';
      }

      if (global_settings.markeraction == 1) {
        global_settings.useInfoWindow = true;
      }

      else if (global_settings.markeraction == 2) {
        global_settings.useInfoBubble = true;
      }
      else if (global_settings.markeraction == 3) {
        global_settings.useLink = true;
      }

      if((global_settings.useInfoWindow || global_settings.useInfoBubble) && settings.custom_content_enable == 1) {
        global_settings.useCustomContent = true;
      }
      global_settings.defaultIcon = Drupal.getlocations.getIcon(map_marker);

      // pipe delim
      global_settings.latlons = (settings.latlons ? settings.latlons : '');
      var minmaxes = (settings.minmaxes ? settings.minmaxes : '');
      var minlat = '';
      var minlon = '';
      var maxlat = '';
      var maxlon = '';
      var cenlat = '';
      var cenlon = '';

      if (minmaxes) {
        mmarr = minmaxes.split(',');
        minlat = mmarr[0];
        minlon = mmarr[1];
        maxlat = mmarr[2];
        maxlon = mmarr[3];
        cenlat = parseFloat((minlat + maxlat)/2);
        cenlon = parseFloat((minlon + maxlon)/2);
      }

      // menu type
      var mtc = settings.mtc;
      if (mtc == 'standard') { mtc = google.maps.MapTypeControlStyle.HORIZONTAL_BAR; }
      else if (mtc == 'menu' ) { mtc = google.maps.MapTypeControlStyle.DROPDOWN_MENU; }
      else { mtc = false; }

      // nav control type
      if (controltype == 'default') { controltype = google.maps.ZoomControlStyle.DEFAULT; }
      else if (controltype == 'small') { controltype = google.maps.ZoomControlStyle.SMALL; }
      else if (controltype == 'large') { controltype = google.maps.ZoomControlStyle.LARGE; }
      else { controltype = false; }

      // map type
      maptypes = [];
      if (maptype) {
        if (maptype == 'Map' && baselayers.Map) { maptype = google.maps.MapTypeId.ROADMAP; }
          if (maptype == 'Satellite' && baselayers.Satellite) { maptype = google.maps.MapTypeId.SATELLITE; }
          if (maptype == 'Hybrid' && baselayers.Hybrid) { maptype = google.maps.MapTypeId.HYBRID; }
          if (maptype == 'Physical' && baselayers.Physical) { maptype = google.maps.MapTypeId.TERRAIN; }
          if (baselayers.Map) { maptypes.push(google.maps.MapTypeId.ROADMAP); }
          if (baselayers.Satellite) { maptypes.push(google.maps.MapTypeId.SATELLITE); }
          if (baselayers.Hybrid) { maptypes.push(google.maps.MapTypeId.HYBRID); }
          if (baselayers.Physical) { maptypes.push(google.maps.MapTypeId.TERRAIN); }
      }
      else {
        maptype = google.maps.MapTypeId.ROADMAP;
        maptypes.push(google.maps.MapTypeId.ROADMAP);
        maptypes.push(google.maps.MapTypeId.SATELLITE);
        maptypes.push(google.maps.MapTypeId.HYBRID);
        maptypes.push(google.maps.MapTypeId.TERRAIN);
      }

      // map styling
      var styles_array = [];
      if (map_styles) {
        try {
          styles_array = eval(map_styles);
        } catch (e) {
          if (e instanceof SyntaxError) {
            console.log(e.message);
            // Error on parsing string. Using default.
            styles_array = [];
          }
        }
      }

      // Merge styles with our settings.
      var styles = styles_array.concat([
        { featureType: "poi", elementType: "labels", stylers: [{ visibility: (poi_show ? 'on' : 'off') }] },
        { featureType: "transit", elementType: "labels", stylers: [{ visibility: (transit_show ? 'on' : 'off') }] }
      ]);

      var mapOpts = {
        zoom: selzoom,
        center: new google.maps.LatLng(lat, lng),
        mapTypeControl: (mtc ? true : false),
        mapTypeControlOptions: {style: mtc,  mapTypeIds: maptypes},
        zoomControl: (controltype ? true : false),
        zoomControlOptions: {style: controltype},
        panControl: (pancontrol ? true : false),
        mapTypeId: maptype,
        scrollwheel: (scrollw ? true : false),
        draggable: (draggable ? true : false),
        styles: styles,
        overviewMapControl: (overview ? true : false),
        overviewMapControlOptions: {opened: (overview_opened ? true : false)},
        streetViewControl: (streetview_show ? true : false),
        scaleControl: (scale ? true : false),
        scaleControlOptions: {style: google.maps.ScaleControlStyle.DEFAULT}
      };

      getlocations_map[key] = new google.maps.Map(document.getElementById("getlocations_map_canvas_" + key), mapOpts);

      if (settings.inputmap) {
        getlocations_inputmap[key] = getlocations_map[key];
      }

      // set up markermanager
      if (global_settings.usemarkermanager == 1) {
        global_settings.mgr = new MarkerManager(getlocations_map[key], {
          borderPadding: 50,
          maxZoom: global_settings.maxzoom,
          trackMarkers: false
        });
      }
      else if (global_settings.useclustermanager == 1) {
        global_settings.cmgr = new MarkerClusterer(
          getlocations_map[key],
          [],
          {
            gridSize: global_settings.cmgr_gridSize,
            maxZoom: global_settings.cmgr_maxZoom,
            styles: global_settings.cmgr_styles[global_settings.cmgr_style],
            minimumClusterSize: global_settings.cmgr_minClusterSize
          }
        );
      }

      if (settings.trafficinfo) {
        global_settings.trafficInfo[key] = new google.maps.TrafficLayer();
        global_settings.trafficInfo[key].setMap(getlocations_map[key]);
        global_settings.traffictoggleState[key] = 1;
        $("#getlocations_toggleTraffic_" + key).click( function() { manageTrafficButton(getlocations_map[key], global_settings.trafficInfo[key], key) });
      }
      if (settings.bicycleinfo) {
        global_settings.bicycleInfo[key] = new google.maps.BicyclingLayer();
        global_settings.bicycleInfo[key].setMap(getlocations_map[key]);
        global_settings.bicycletoggleState[key] = 1;
        $("#getlocations_toggleBicycle_" + key).click( function() { manageBicycleButton(getlocations_map[key], global_settings.bicycleInfo[key], key) });

      }
      if (settings.panoramio_use && settings.panoramio_show) {
        global_settings.panoramioLayer[key] = new google.maps.panoramio.PanoramioLayer();
        global_settings.panoramioLayer[key].setMap(getlocations_map[key]);
        global_settings.panoramiotoggleState[key] = 1;
        $("#getlocations_togglePanoramio_" + key).click( function() { managePanoramioButton(getlocations_map[key], global_settings.panoramioLayer[key], key) });
      }

      if (! settings.inputmap && ! settings.searchmap) {
        setTimeout(function() { doAllMarkers(getlocations_map[key], global_settings) }, 300);

        if (pansetting == 1) {
          Drupal.getlocations.doBounds(getlocations_map[key], minlat, minlon, maxlat, maxlon, true);
        }
        else if (pansetting == 2) {
          Drupal.getlocations.doBounds(getlocations_map[key], minlat, minlon, maxlat, maxlon, false);
        }
        else if (pansetting == 3) {
          if (cenlat && cenlon) {
            c = new google.maps.LatLng(cenlat, cenlon);
            getlocations_map[key].setCenter(c);
          }
        }
      }

      // searchmap
      if (settings.searchmap) {
        setTimeout(function() { Drupal.getlocations.doSearch(getlocations_map[key], global_settings) }, 300);
      } // end searchmap

      function manageTrafficButton(map, trafficInfo, key) {
        if ( global_settings.traffictoggleState[key] == 1) {
          trafficInfo.setMap();
          global_settings.traffictoggleState[key] = 0;
        }
        else {
          trafficInfo.setMap(map);
          global_settings.traffictoggleState[key] = 1;
        }
      }

      function manageBicycleButton(map, bicycleInfo, key) {
        if ( global_settings.bicycletoggleState[key] == 1) {
          bicycleInfo.setMap();
          global_settings.bicycletoggleState[key] = 0;
        }
        else {
          bicycleInfo.setMap(map);
          global_settings.bicycletoggleState[key] = 1;
        }
      }

      function managePanoramioButton(map, panoramioLayer, key) {
        if ( global_settings.panoramiotoggleState[key] == 1) {
          panoramioLayer.setMap();
          global_settings.panoramiotoggleState[key] = 0;
        }
        else {
          panoramioLayer.setMap(map);
          global_settings.panoramiotoggleState[key] = 1;
        }
      }

    }); // end each setting loop


    function doAllMarkers (map, gs) {

      // using markermanager
      if (gs.usemarkermanager || gs.useclustermanager) {
        var batchr = [];
      }

      var arr = gs.latlons;
      for (var i = 0; i < arr.length; i++) {
        arr2 = arr[i];
        if (arr2.length < 2) {
          return;
        }
        lat = arr2[0];
        lon = arr2[1];
        lid = arr2[2];
        name = arr2[3];
        mark = arr2[4];
        lidkey = arr2[5];
        customContent = arr2[6];
        if (mark === '') {
          gs.markdone = gs.defaultIcon;
        }
        else {
          gs.markdone = Drupal.getlocations.getIcon(mark);
        }
        m = Drupal.getlocations.makeMarker(map, gs, lat, lon, lid, name, lidkey, customContent);
        if (gs.usemarkermanager || gs.useclustermanager) {
          batchr.push(m);
        }
      }
      // add batchr
      if (gs.usemarkermanager) {
       gs.mgr.addMarkers(batchr, gs.minzoom, gs.maxzoom);
        gs.mgr.refresh();
      }
      else if (gs.useclustermanager) {
        gs.cmgr.addMarkers(batchr, 0);
      }
    }

  } // end initialize

  Drupal.getlocations.makeMarker = function(map, gs, lat, lon, lid, title, lidkey, customContent) {

    //if (! gs.markdone) {
    //  return;
    //}

    var mouseoverTimeoutId = null;
    var mouseoverTimeout = (gs.markeractiontype == 'mouseover' ? 300 : 0);
    var p = new google.maps.LatLng(lat, lon);
    var m = new google.maps.Marker({
      icon: gs.markdone.image,
      shadow: gs.markdone.shadow,
      shape: gs.markdone.shape,
      map: map,
      position: p,
      title: title,
      optimized: false
    });

    if (gs.markeraction > 0) {
      google.maps.event.addListener(m, gs.markeractiontype, function() {
        mouseoverTimeoutId = setTimeout(function() {
          if (gs.useLink) {
            // fetch link and relocate
            var path = Drupal.settings.basePath + "getlocations/lidinfo";
            $.get(path, {'lid': lid, 'key': lidkey}, function(data) {
              if (data) {
                window.location = data.content;
              }
            });
          }
          else {
            if(gs.useCustomContent) {
              var cc = [];
              cc.content = customContent;
              Drupal.getlocations.showPopup(map, m, gs, cc);
            }
            else {
              // fetch bubble content
              var path = Drupal.settings.basePath + "getlocations/info";
              $.get(path, {'lid': lid, 'key': lidkey}, function(data) {
                Drupal.getlocations.showPopup(map, m, gs, data);
              });
            }
          }
        }, mouseoverTimeout);
      });
      google.maps.event.addListener(m,'mouseout', function() {
        if(mouseoverTimeoutId) {
          clearTimeout(mouseoverTimeoutId);
          mouseoverTimeoutId = null;
        }
      });

    }
    // we only have one marker
    if (gs.datanum == 1) {
      map.setCenter(p);
      map.setZoom(gs.nodezoom);
    }
    return m;

  }

  Drupal.getlocations.showPopup = function(map, m, gs, data) {
    var ver = Drupal.getlocations.msiedetect();
    var pushit = false;
    if ( (ver == '') || (ver && ver > 8)) {
      pushit = true;
    }

    if (pushit) {
      // close any previous instances
      for (var i in gs.infoBubbles) {
        gs.infoBubbles[i].close();
      }
    }

    if (gs.useInfoBubble) {
      if (typeof(infoBubbleOptions) == 'object') {
        var infoBubbleOpts = infoBubbleOptions;
      }
      else {
        var infoBubbleOpts = {};
      }
      infoBubbleOpts.content = data.content;
      var infoBubble = new InfoBubble(infoBubbleOpts);
      infoBubble.open(map, m);
      if (pushit) {
        // add to the array
        gs.infoBubbles.push(infoBubble);
      }
    }
    else {
      if (typeof(infoWindowOptions) == 'object') {
        var infoWindowOpts = infoWindowOptions;
      }
      else {
        var infoWindowOpts = {};
      }
      infoWindowOpts.content = data.content;
      var infowindow = new google.maps.InfoWindow(infoWindowOpts);
      infowindow.open(map, m);
      if (pushit) {
        // add to the array
        gs.infoBubbles.push(infowindow);
      }
    }

  }

  Drupal.getlocations.doBounds = function(map, minlat, minlon, maxlat, maxlon, dopan) {
    if (minlat !== '' && minlon !== '' && maxlat !== '' && maxlon !== '') {
      // Bounding
      var minpoint = new google.maps.LatLng(parseFloat(minlat), parseFloat(minlon));
      var maxpoint = new google.maps.LatLng(parseFloat(maxlat), parseFloat(maxlon));
      var bounds = new google.maps.LatLngBounds(minpoint, maxpoint);
      if (dopan) {
        map.panToBounds(bounds);
      }
      else {
        map.fitBounds(bounds);
      }
    }
  }

  Drupal.getlocations.msiedetect = function() {
    var ieversion = '';
    if (/MSIE (\d+\.\d+);/.test(navigator.userAgent)){ //test for MSIE x.x;
     ieversion = new Number(RegExp.$1) // capture x.x portion and store as a number
    }
    return ieversion;
  }

  Drupal.getlocations.getGeoErrCode = function(errcode) {
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

  // gogogo
  Drupal.behaviors.getlocations = {
    attach: function() {
      initialize();
    }
  };

})(jQuery);
