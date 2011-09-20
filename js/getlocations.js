
/**
 * @file
 * Javascript functions for getlocations module for Drupal 6
 *
 * @author Bob Hutchinson http://drupal.org/user/52366
 * this is for googlemaps API version 3
*/
(function ($) {

  // global vars
  var map;
  var maxzoom = 16;
  var minzoom = 7;
  var nodezoom = 12;
  var mgr;
  var latlons;
  var defaultIcon;
  var usemarkermanager = true;
  var useInfoBubble = false;
  var useInfoWindow = false;
  var useLink = false;
  var markeraction = 0;
  var infoBubbles = [];
  var datanum = 0;
  var trafficInfo;
  var bicycleInfo;
  var traffictoggleState = 0;
  var bicycletoggleState = 0;
  var panoramioLayer;
  var panoramiotoggleState = 0;

  function initialize() {
    var lat = parseFloat(Drupal.settings.getlocations.lat);
    var lng = parseFloat(Drupal.settings.getlocations.lng);
    var selzoom = parseInt(Drupal.settings.getlocations.zoom);
    var controltype = Drupal.settings.getlocations.controltype;
    var pancontrol = Drupal.settings.getlocations.pancontrol;
    var scale = Drupal.settings.getlocations.scale;
    var overview = Drupal.settings.getlocations.overview;
    var overview_opened = Drupal.settings.getlocations.overview_opened;
    var streetview_show = Drupal.settings.getlocations.streetview_show;
    var scrollw = Drupal.settings.getlocations.scrollwheel;
    var maptype = (Drupal.settings.getlocations.maptype ? Drupal.settings.getlocations.maptype : '');
    var baselayers = (Drupal.settings.getlocations.baselayers ? Drupal.settings.getlocations.baselayers : '');
    var map_marker = Drupal.settings.getlocations.map_marker;
    var poi_show = Drupal.settings.getlocations.poi_show;
    var transit_show = Drupal.settings.getlocations.transit_show;
    var pansetting = Drupal.settings.getlocations.pansetting;
    var draggable = Drupal.settings.getlocations.draggable;
    minzoom = parseInt(Drupal.settings.getlocations.minzoom);
    maxzoom = parseInt(Drupal.settings.getlocations.maxzoom);
    nodezoom = parseInt(Drupal.settings.getlocations.nodezoom);
    datanum = Drupal.settings.getlocations.datanum;
    usemarkermanager = Drupal.settings.getlocations.usemarkermanager;

    markeraction = Drupal.settings.getlocations.markeraction;

    if (markeraction == 2) {
      useInfoBubble = true;
    }
    else if (markeraction == 3) {
      useLink = true;
    }

    // in icons.js
    Drupal.getlocations.iconSetup();

    defaultIcon = Drupal.getlocations.getIcon(map_marker);

    // pipe delim
    latlons = (Drupal.settings.getlocations.latlons ? Drupal.settings.getlocations.latlons : '');
    var minmaxes = (Drupal.settings.getlocations.minmaxes ? Drupal.settings.getlocations.minmaxes : '');
    var minlat = '';
    var minlon = '';
    var maxlat = '';
    var maxlon = '';
    var cenlat = '';
    var cenlon = '';

    if (minmaxes !== '') {
      mmarr = minmaxes.split(',');
      minlat = mmarr[0];
      minlon = mmarr[1];
      maxlat = mmarr[2];
      maxlon = mmarr[3];
      cenlat = (parseFloat(minlat) + parseFloat(maxlat))/2;
      cenlon = (parseFloat(minlon) + parseFloat(maxlon))/2;
    }

    // menu type
    var mtc = Drupal.settings.getlocations.mtc;
    if (mtc == 'standard') { mtc = google.maps.MapTypeControlStyle.HORIZONTAL_BAR; }
    else if (mtc == 'menu' ) { mtc = google.maps.MapTypeControlStyle.DROPDOWN_MENU; }
    else { mtc = false; }

    // nav control type
    if (controltype == 'default') { controltype = google.maps.ZoomControlStyle.DEFAULT; }
    else if (controltype == 'small') { controltype = google.maps.ZoomControlStyle.SMALL; }
    else if (controltype == 'large') { controltype = google.maps.ZoomControlStyle.LARGE; }
    else { controltype = false; }

    // map type
    if (maptype) {
      if (maptype == 'Map' && baselayers.Map) { maptype = google.maps.MapTypeId.ROADMAP; }
      if (maptype == 'Satellite' && baselayers.Satellite) { maptype = google.maps.MapTypeId.SATELLITE; }
      if (maptype == 'Hybrid' && baselayers.Hybrid) { maptype = google.maps.MapTypeId.HYBRID; }
      if (maptype == 'Physical' && baselayers.Physical) { maptype = google.maps.MapTypeId.TERRAIN; }
    }
    else { maptype = google.maps.MapTypeId.ROADMAP; }

    var mapOpts = {
      zoom: selzoom,
      center: new google.maps.LatLng(lat, lng),
      mapTypeControl: (mtc ? true : false),
      mapTypeControlOptions: {style: mtc},
      zoomControl: (controltype ? true : false),
      zoomControlOptions: {style: controltype},
      panControl: (pancontrol ? true : false),
      mapTypeId: maptype,
      scrollwheel: (scrollw ? true : false),
      draggable: (draggable ? true : false),
      styles: [
        { featureType: "poi", elementType: "labels", stylers: [{ visibility: (poi_show ? 'on' : 'off') }] },
        { featureType: "transit", elementType: "labels", stylers: [{ visibility: (transit_show ? 'on' : 'off') }] }
      ],
      overviewMapControl: (overview ? true : false),
      overviewMapControlOptions: {opened: (overview_opened ? true : false)},
      streetViewControl: (streetview_show ? true : false),
      scaleControl: (scale ? true : false),
      scaleControlOptions: {style: google.maps.ScaleControlStyle.DEFAULT}
    };
    map = new google.maps.Map(document.getElementById("getlocations_map_canvas"), mapOpts);

    // set up markermanager
    if (usemarkermanager) {
      mgr = new MarkerManager(map, {
        borderPadding: 50,
        maxZoom: maxzoom,
        trackMarkers: false
      });
    }

    if (Drupal.settings.getlocations.trafficinfo) {
      trafficInfo = new google.maps.TrafficLayer();
    }
    if (Drupal.settings.getlocations.bicycleinfo) {
      bicycleInfo = new google.maps.BicyclingLayer();
    }
    if (Drupal.settings.getlocations.panoramio_show) {
      panoramioLayer = new google.maps.panoramio.PanoramioLayer();
    }

    setTimeout(doAllMarkers, 1000);

    if (pansetting == 1) {
      doBounds(minlat, minlon, maxlat, maxlon, true);
    }
    else if (pansetting == 2) {
      doBounds(minlat, minlon, maxlat, maxlon, false);
    }
    else if (pansetting == 3) {
      if (cenlat && cenlon) {
        c = new google.maps.LatLng(cenlat, cenlon);
        map.setCenter(c);
      }
    }

  } // end initialize

  function makeMarker(ico, lat, lon, lid, title) {

    var p = new google.maps.LatLng(lat, lon);
    var m = new google.maps.Marker({
      icon: ico.image,
      shadow: ico.shadow,
      shape: ico.shape,
      map: map,
      position: p,
      title: title
    });

    if (markeraction > 0) {
      google.maps.event.addListener(m, 'click', function() {
        if (useLink) {
          // fetch link and relocate
          $.get("/getlocations/lidinfo", {lid: lid}, function(data) {
            if (data) {
              window.location = data;
            }
          });
        }
        else {
          // fetch bubble content
          $.get("/getlocations/info", {lid: lid}, function(data) {

            // close any previous instances
            for (var i in infoBubbles) {
              infoBubbles[i].close();
            }
            if (useInfoBubble) {
              var infoBubble = new InfoBubble({
                content: data,
                shadowStyle: 1
              });
              infoBubble.open(map, m);
              // add to the array
              infoBubbles.push(infoBubble);
            }
            else {
              var infowindow = new google.maps.InfoWindow({
                content: data
              });
              infowindow.open(map, m);
              // add to the array
              infoBubbles.push(infowindow);
            }
          });
        }
      });
    }

    // we only have one marker
    if (datanum == 1) {
      map.setCenter(p);
      map.setZoom(nodezoom);
    }
    return m;
  }

  function doAllMarkers () {

    // using markermanager
    if (usemarkermanager) {
      var batchr = [];
    }

    var arr = latlons.split('|');
    for (var i = 0; i < arr.length; i++) {
      arr2 = arr[i].split(',');
      lat = arr2[0];
      lon = arr2[1];
      lid = arr2[2];
      name = arr2[3];
      mark = arr2[4];
      if (mark === '') {
        markdone = defaultIcon;
      }
      else {
        markdone = Drupal.getlocations.getIcon(mark);
      }
      m = makeMarker(markdone, lat, lon, lid, name);
      if (usemarkermanager) {
        batchr.push(m);
      }
    }
    // add batchr
    if (usemarkermanager) {
      mgr.addMarkers(batchr, minzoom, maxzoom);
      mgr.refresh();
    }
  }

  function doBounds(minlat, minlon, maxlat, maxlon, dopan) {
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

  Drupal.getlocations.toggleTraffic = function() {
    if (traffictoggleState == 1) {
      trafficInfo.setMap();
      traffictoggleState = 0;
    }
    else {
      trafficInfo.setMap(map);
      traffictoggleState = 1;
    }
  }

  Drupal.getlocations.toggleBicycle = function() {
    if (bicycletoggleState == 1) {
      bicycleInfo.setMap();
      bicycletoggleState = 0;
    }
    else {
      bicycleInfo.setMap(map);
      bicycletoggleState = 1;
    }
  }

  Drupal.getlocations.togglePanoramio = function() {
    if (panoramiotoggleState == 1) {
      panoramioLayer.setMap();
      panoramiotoggleState = 0;
    }
    else {
      panoramioLayer.setMap(map);
      panoramiotoggleState = 1;
    }
  }

  // gogogo
  Drupal.behaviors.getlocations = function() {
    initialize();
  };


})(jQuery);
