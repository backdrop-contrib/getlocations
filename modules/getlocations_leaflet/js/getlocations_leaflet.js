
/**
 * @file
 * getlocations_leaflet.js
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations_leaflet module for Backdrop
 * this is for leaflet maps http://leafletjs.com/
 */

(function ($) {
  Backdrop.getlocations_leaflet = {};
  Backdrop.getlocations_leaflet_map = [];
  Backdrop.getlocations_leaflet_markers = [];
  Backdrop.getlocations_leaflet_settings = [];
  Backdrop.getlocations_leaflet_overlays = [];
  Backdrop.getlocations_leaflet_layerscontrol = [];
  Backdrop.getlocations_leaflet_data = [];
  Backdrop.getlocations_leaflet_geocoder = [];

  Backdrop.behaviors.getlocations_leaflet = {
    attach: function (context, settings) {

      // functions

      function getlocations_leaflet_do_link(m, l) {
        m.on('click', function() {
          window.location = l;
        });
      }

      // show_maplinks
      function getlocations_leaflet_show_maplinks(key, glid, m, a) {
        $("div#getlocations_leaflet_map_links_" + key + " ul").append('<li><a href="#maptop_' + key + '" class="glid-' + glid + '">' + m.options.title + '</a></li>');
        $("div#getlocations_leaflet_map_links_" + key + " a.glid-" + glid).click(function() {
          $("div#getlocations_leaflet_map_links_" + key + " a").removeClass('active');
          $("div#getlocations_leaflet_map_links_" + key + " a.glid-" + glid).addClass('active');
          if (a.type == 'link') {
            // relocate
            window.location = a.data;
          }
          else if (a.type == 'popup') {
            m.fire('click');
          }
        });
      }

      function getlocations_leaflet_deactive_throbber(k) {
        $("#getlocations_leaflet_gps_throbber_" + k).removeClass('getlocations_leaflet_gps_throbber_active');
        $("#getlocations_leaflet_gps_throbber_" + k).addClass('getlocations_leaflet_gps_throbber_inactive');
      }

      // end functions

      // work over all class 'getlocations_leaflet_canvas'
      $(".getlocations_leaflet_canvas", context).once('getlocations-leaflet-processed', function(index, element) {
        var elemID = $(element).prop('id');
        var key = elemID.replace(/^getlocations_leaflet_canvas_/, '');
        // is there really a map?
        if ( $("#getlocations_leaflet_canvas_" + key).is('div') ) {
          var map_settings = settings.getlocations_leaflet[key].map_settings;
          var map_opts = settings.getlocations_leaflet[key].map_opts;
          var map_layers = settings.getlocations_leaflet[key].map_layers;

          var icons = Backdrop.getlocations_leaflet_data[key].icons;
          var datanum = Backdrop.getlocations_leaflet_data[key].datanum;
          var latlons = Backdrop.getlocations_leaflet_data[key].latlons;

          Backdrop.getlocations_leaflet_markers[key] = {};
          Backdrop.getlocations_leaflet_markers[key].coords = {};
          Backdrop.getlocations_leaflet_markers[key].lids = {};
          Backdrop.getlocations_leaflet_markers[key].cat = {};
          Backdrop.getlocations_leaflet_settings[key] = settings.getlocations_leaflet[key];
          Backdrop.getlocations_leaflet_overlays[key] = {};
          Backdrop.getlocations_leaflet_layerscontrol[key] = {};

          // get the map
          //Backdrop.getlocations_leaflet_map[key] = L.map('getlocations_leaflet_canvas_' + key, map_opts);
          Backdrop.getlocations_leaflet_map[key] = L.map($(element).get(0), map_opts);

          // layers
          var layers = {};
          var gotmap = false;

          // mapquest
          if (map_settings.mapquest_key && typeof(MQ) !== 'undefined') {

            if (map_settings.mapquest_traffic_enable) {
              if (map_settings.mapquest_traffic_flow) {
                var label_flow = Backdrop.t('Traffic Flow');
                Backdrop.getlocations_leaflet_overlays[key][label_flow] = MQ.trafficLayer({layers: ['flow']});
                if (map_settings.mapquest_traffic_flow_on == 1) {
                  Backdrop.getlocations_leaflet_overlays[key][label_flow].addTo(Backdrop.getlocations_leaflet_map[key]);
                }
              }
              if (map_settings.mapquest_traffic_incident) {
                var label_incident = Backdrop.t('Traffic Incidents');
                Backdrop.getlocations_leaflet_overlays[key][label_incident] = MQ.trafficLayer({layers: ['incidents']});
                if (map_settings.mapquest_traffic_incident_on == 1) {
                  Backdrop.getlocations_leaflet_overlays[key][label_incident].addTo(Backdrop.getlocations_leaflet_map[key]);
                }
              }
            }

            if (map_settings.mapquest_routing_enable) {
            }

            if (map_settings.mapquest_geocoder_enable) {
              //if ($("#edit-getlocations-leaflet-mapquest-geocoder-search").is('input') && $("#edit-getlocations-leaflet-mapquest-geocoder-search").val() ) {
              if ($("#edit-getlocations-leaflet-mapquest-geocoder-search").is('input')) {
                  $("#edit-getlocations-leaflet-mapquest-geocoder-search-submit").click( function() {
                  $("#getlocations_mapquest_search_throbber_" + key).removeClass('getlocations_mapquest_search_throbber_inactive').addClass('getlocations_mapquest_search_throbber_active');
                  var ss = $("#edit-getlocations-leaflet-mapquest-geocoder-search").val();
                  var gc = {map: Backdrop.getlocations_leaflet_map[key]};
                  // mapquest_geocoder_map_marker mapquest_geocoder_marker_show
                  //if (map_settings.mapquest_geocoder_marker && map_settings.mapquest_geocoder_marker_show) {
                  if (map_settings.mapquest_geocoder_marker_show ) {
                    var ic = map_settings.mapquest_geocoder_map_marker;
                    //var ic = Backdrop.getlocations_leaflet_data[key].icons[map_settings.mapquest_geocoder_map_marker];
                    var thisIcon = L.icon({
                      iconUrl: ic.iconUrl,
                      iconSize: ic.iconSize,
                      iconAnchor: ic.iconAnchor
                    });
                    gc.icon = thisIcon;
                  }
                  MQ.geocode(gc).search(ss);
                  $("#getlocations_mapquest_search_throbber_" + key).removeClass('getlocations_mapquest_search_throbber_active').addClass('getlocations_mapquest_search_throbber_inactive');
                });
              }
            }

            if (map_settings.mapquest_maps_enable && map_settings.mapquest_maps_use) {
              var default_layer_name = MQ.mapLayer();
              var default_layer_label = Backdrop.t('Map layer');
              if (map_settings.mapquest_maps_default == 's') {
                default_layer_name = MQ.satelliteLayer();
                default_layer_label = Backdrop.t('Satellite layer');
              }
              else if (map_settings.mapquest_maps_default == 'h') {
                default_layer_name = MQ.hybridLayer();
                default_layer_label = Backdrop.t('Hybrid layer');
              }
              layers[default_layer_label] = default_layer_name.addTo(Backdrop.getlocations_leaflet_map[key]);
              if (map_settings.mapquest_maps_default != 'm' && map_settings.mapquest_maps_maplayer) {
                layers[Backdrop.t('Map layer')] = MQ.mapLayer();
              }
              if (map_settings.mapquest_maps_default != 's' && map_settings.mapquest_maps_satellitelayer) {
                layers[Backdrop.t('Satellite layer')] = MQ.satelliteLayer();
              }
              if (map_settings.mapquest_maps_default != 'h' && map_settings.mapquest_maps_hybridlayer) {
                layers[Backdrop.t('Hybrid layer')] = MQ.hybridLayer();
              }

              if (map_settings.mapquest_maps_default != 'l' && map_settings.mapquest_maps_lightlayer) {
                layers[Backdrop.t('Light layer')] = MQ.lightLayer();
              }
              if (map_settings.mapquest_maps_default != 'd' && map_settings.mapquest_maps_darklayer) {
                layers[Backdrop.t('Dark layer')] = MQ.darkLayer();
              }

              gotmap = true;
            }

          }

          if (! gotmap) {
            // do the default layer first and separately
            var default_layer_name = map_settings.default_layer_name;
            var default_layer_label = map_settings.default_layer_label;
            var default_map_layer = L.tileLayer.provider(default_layer_name);
            //var default_layer = map_layers[default_layer_name];

            var thunderforest_key = map_settings.thunderforest_key;
            var thunderforest_patt = /^Thunderforest\./;
            if (thunderforest_key && default_map_layer.options.apikey !== 'undefined' && thunderforest_patt.test(default_layer_name)) {
              default_map_layer.options.apikey = thunderforest_key;
            }

            var openweathermap_key = map_settings.openweathermap_key;
            var openweathermap_patt = /^OpenWeatherMap\./;
            if (openweathermap_key && default_map_layer.options.apiKey !== 'undefined' && openweathermap_patt.test(default_layer_name) ) {
              default_map_layer.options.apiKey = openweathermap_key;
            }

            layers[default_layer_label] = default_map_layer.addTo(Backdrop.getlocations_leaflet_map[key]);

            for (var lkey in map_layers) {
              if (lkey != default_layer_name) {
                var layer = map_layers[lkey];
                var map_layer = L.tileLayer.provider(lkey);
                map_layer._leaflet_id = lkey;
                if (layer.options) {
                  for (var option in layer.options) {
                    map_layer.options[option] = layer.options[option];
                  }
                }
                // thunderforest
                if ( thunderforest_key && map_layer.options.apikey !== 'undefined' && thunderforest_patt.test(lkey) ) {
                  map_layer.options.apikey = thunderforest_key;
                }
                // openweathermap
                if (openweathermap_key && map_layer.options.apiKey !== 'undefined' && openweathermap_patt.test(lkey) ) {
                  map_layer.options.apiKey = openweathermap_key;
                }

                if (layer.type == 'base') {
                  layers[layer.label] = map_layer;
                }
                else if (layer.type == 'overlay') {
                  Backdrop.getlocations_leaflet_overlays[key][layer.label] = map_layer;
                }
              }
            }

          }

          if (layers.length) {
            layers.addTo(Backdrop.getlocations_leaflet_map[key]);
          }

          // fullscreen control
          if (map_settings.fullscreen) {
            var fsopts = {};
            if (map_settings.fullscreenposition) {
              fsopts.position = map_settings.fullscreenposition;
            }
            fsopts.title = Backdrop.t('Fullscreen');
            Backdrop.getlocations_leaflet_map[key].addControl(L.control.fullscreen(fsopts));
          }

          // magnifying glass
          if (map_settings.magnifyingglass) {
            var la =  L.tileLayer.provider(map_settings.default_layer_name);
            var magOpts = {
              zoomOffset: parseInt(map_settings.magnifyingglasszoomoffset),
              radius: parseInt(map_settings.magnifyingglassradius),
              fixedPosition: false,
              latLng: [0, 0],
              fixedZoom: -1,
              layers: [L.tileLayer(la._url, la.options)]
            };
            var magnifyingGlass = L.magnifyingGlass(magOpts);
            var magControlOpts = {
              forceSeparateButton: false,
              title: Backdrop.t('Magnifying Glass'),
              position: (map_settings.magnifyingglasscontrolposition ? map_settings.magnifyingglasscontrolposition : 'topleft')
            };
            Backdrop.getlocations_leaflet_map[key].addControl(L.control.magnifyingglass(magnifyingGlass, magControlOpts));
          }

          // pancontrol
          if (map_settings.leaflet_pancontrol) {
            var popts = {};
            if (map_settings.pancontrolposition) {
              popts.position = map_settings.pancontrolposition;
            }
            Backdrop.getlocations_leaflet_map[key].addControl(L.control.pan(popts));
          }

          // zoomslider
          if (map_settings.leaflet_zoomslider) {
            var popts = {};
            if (map_settings.zoomsliderposition) {
              popts.position = map_settings.zoomsliderposition;
            }
            Backdrop.getlocations_leaflet_map[key].addControl(L.control.zoomslider(popts));
          }

          // graticule
          if (map_settings.graticule) {
            var gropts = {};
            gropts.style = {};
            if (map_settings.graticule_color) {
              gropts.style.color = map_settings.graticule_color;
            }
            if (map_settings.graticule_opacity) {
              gropts.style.opacity = map_settings.graticule_opacity;
            }
            if (map_settings.graticule_weight) {
              gropts.style.weight = map_settings.graticule_weight;
            }
            if (map_settings.graticule_interval) {
              gropts.interval = parseInt(map_settings.graticule_interval);
            }
            var graticule = L.graticule(gropts);

            if (map_settings.graticule_show == 2) {
              var gratctlOpts = {
                forceSeparateButton: false,
                title: map_settings.graticule_ov_label,
                position: (map_settings.graticule_position ? map_settings.graticule_position : 'topleft')
              };
              Backdrop.getlocations_leaflet_map[key].addControl(L.control.graticule(graticule, gratctlOpts));
            }
            if ((map_settings.graticule_show && map_settings.graticule_state) || (! map_settings.graticule_show)) {
              graticule.addTo(Backdrop.getlocations_leaflet_map[key]);
            }
          }

          // Terminator or Day/Night
          if (map_settings.terminator) {
            if (! map_settings.terminator_strokecolor.match(/^#/)) {
              map_settings.terminator_strokecolor = '#' + map_settings.terminator_strokecolor;
            }
            if (! map_settings.terminator_fillcolor.match(/^#/)) {
              map_settings.terminator_fillcolor = '#' + map_settings.terminator_fillcolor;
            }
            var terminatorOpts = {
              color: map_settings.terminator_strokecolor,
              opacity: map_settings.terminator_strokeopacity,
              weight: parseInt(map_settings.terminator_strokeweight),
              fillColor: map_settings.terminator_fillcolor ,
              fillOpacity: map_settings.terminator_fillopacity,
              resolution: 2
            };
            var terminator = L.terminator(terminatorOpts);
            if (map_settings.terminator_show == 2) {
              var termctlOpts = {
                forceSeparateButton: false,
                title: map_settings.terminator_label,
                position: (map_settings.terminator_position ? map_settings.terminator_position : 'topleft')
              };
              Backdrop.getlocations_leaflet_map[key].addControl(L.control.terminator(terminator, termctlOpts));
            }
            if ((map_settings.terminator_show && map_settings.terminator_state) || (! map_settings.terminator_show)) {
              terminator.addTo(Backdrop.getlocations_leaflet_map[key]);
            }
          }

          // Zoom control
          if (map_settings.zoomControl) {
            var zoomopts = {};
            if (map_settings.zoomcontrolposition) {
              zoomopts.position = map_settings.zoomcontrolposition;
            }
            Backdrop.getlocations_leaflet_map[key].addControl(L.control.zoom(zoomopts));
          }

          // Attribution control
          if (map_settings.attributionControl && map_settings.attributioncontrolposition) {
            var attributionopts = {position: map_settings.attributioncontrolposition};
            var attribcontrol = L.control.attribution(attributionopts);
            Backdrop.getlocations_leaflet_map[key].addControl(attribcontrol);
            //attribcontrol.addAttribution(map_layers.earth.options.attribution);
          }

          // Mouseposition
          if (map_settings.mouseposition) {
            var mopts = {};
            mopts.emptystring = Backdrop.t('Unavailable');
            if (map_settings.mouseposition_position) {
              mopts.position = map_settings.mouseposition_position;
            }
            if (map_settings.mouseposition_display_dms) {
              mopts.lngFormatter = Backdrop.getlocations.geo.dd_to_dms_lng;
              mopts.latFormatter = Backdrop.getlocations.geo.dd_to_dms_lat;
            }
            else {
              mopts.lngFormatter = Backdrop.getlocations.geo.dd_lng;
              mopts.latFormatter = Backdrop.getlocations.geo.dd_lat;
            }
            Backdrop.getlocations_leaflet_map[key].addControl(L.control.mousePosition(mopts));
          }

          // Scale control
          if (map_settings.scaleControl) {
            var scaleopts = {};
            if (map_settings.scalecontrolposition) {
              scaleopts.position = map_settings.scalecontrolposition;
            }
            if (map_settings.scalecontrolunits) {
              if (map_settings.scalecontrolunits == 'metric') {
                scaleopts.metric = true;
                scaleopts.imperial = false;
              }
              else if (map_settings.scalecontrolunits == 'imperial') {
                scaleopts.metric = false;
                scaleopts.imperial = true;
              }
            }
            Backdrop.getlocations_leaflet_map[key].addControl(L.control.scale(scaleopts));
          }

          // Geocoder control
          if (map_settings.geocoder) {
            var geo_opts = {};
            geo_opts.placeholder = map_settings.geocoder_placeholder;
            geo_opts.errorMessage = map_settings.geocoder_errormessage;
            geo_opts.collapsed = (map_settings.geocodercollapsed ? true : false);
            if (map_settings.geocoderposition) {
              geo_opts.position = map_settings.geocoderposition;
            }
            if (map_settings.geocodersrc == 'b' && map_settings.geocoder_bing_key) {
              geo_opts.geocoder = L.Control.Geocoder.bing(map_settings.geocoder_bing_key);
              var geocoder_msg = Backdrop.t('Geocoding by Bing');
            }
            else if (map_settings.geocodersrc == 'm' && map_settings.mapquest_key) {
              geo_opts.geocoder = L.Control.Geocoder.mapQuest(map_settings.mapquest_key);
              var geocoder_msg = Backdrop.t('Geocoding by MapQuest');
            }
            else if (map_settings.geocodersrc == 'x' && map_settings.geocoder_mapbox_key) {
              geo_opts.geocoder = L.Control.Geocoder.mapbox(map_settings.geocoder_mapbox_key);
              var geocoder_msg = Backdrop.t('Geocoding by Mapbox');
            }
            else if (map_settings.geocodersrc == 'g' && map_settings.geocoder_google_key) {
              geo_opts.geocoder = L.Control.Geocoder.google(map_settings.geocoder_google_key);
              var geocoder_msg = Backdrop.t('Geocoding by Google');
            }
            else {
              geo_opts.geocoder = L.Control.Geocoder.nominatim();
              var geocoder_msg = Backdrop.t('Geocoding by Nominatim');
            }
            Backdrop.getlocations_leaflet_geocoder[key] = L.Control.geocoder(geo_opts);
            Backdrop.getlocations_leaflet_map[key].addControl(Backdrop.getlocations_leaflet_geocoder[key]);
            $(".leaflet-control-geocoder .leaflet-control-geocoder-icon").prop({title: geocoder_msg});
          }

          // latlons data
          if (datanum > 0) {

            // categories
            var categories = {};
            if (map_settings.category_showhide_buttons) {
              categories = (map_settings.categories ? map_settings.categories : {});
            }

            // markers
            var Markers = [];
            if (map_settings.markercluster) {
              if (map_settings.category_showhide_buttons) {
                for (var c in categories) {
                  Markers[c] = L.markerClusterGroup(map_settings.markerclusteroptions);
                }
              }
              else {
                Markers['loc'] = L.markerClusterGroup(map_settings.markerclusteroptions);
              }
            }
            else {
              if (map_settings.category_showhide_buttons) {
                for (var c in categories) {
                  Markers[c] = L.layerGroup();
                }
              }
              else {
                Markers['loc'] = L.layerGroup();
              }
            }

            // loop over latlons
            for (var i = 0; i < latlons.length; i++) {
              var latlon = latlons[i];
              var lat           = latlon[0];
              var lon           = latlon[1];
              var entity_key    = latlon[2];
              var entity_id     = latlon[3];
              var glid          = latlon[4];
              var title         = latlon[5];
              var markername    = latlon[6];
              var vector        = latlon[7];
              var markeraction  = latlon[8];
              var cat           = latlon[9];
              var icon = '';
              if (markername) {
                icon = icons[markername];
              }

              // get the marker
              Marker = Backdrop.getlocations_leaflet.makeMarker(map_settings, lat, lon, entity_key, entity_id, glid, title, icon, vector, markeraction, cat, key);

              // add the marker to the group(s)
              if (map_settings.category_showhide_buttons && cat) {
                for (var c in categories) {
                  if (cat == c) {
                    Markers[c].addLayer(Marker);
                  }
                }
              }
              else {
                Markers['loc'].addLayer(Marker);
              }

              // show_maplinks
              if (markeraction && markeraction.type && markeraction.data) {
                if (title && map_settings.show_maplinks) {
                  getlocations_leaflet_show_maplinks(key, glid, Marker, markeraction);
                }
              }

              // add marker to getlocations_leaflet_markers
              // still experimental
              Backdrop.getlocations_leaflet_markers[key].lids[glid] = Marker;

            } // end latlons

            // add the markers to the map
            if (map_settings.category_showhide_buttons) {
              for (var c in categories) {
                Backdrop.getlocations_leaflet_map[key].addLayer(Markers[c]);
              }
            }
            else {
              Backdrop.getlocations_leaflet_map[key].addLayer(Markers['loc']);
            }

            // set up overlays
            if (map_settings.category_showhide_buttons) {
              for (var c in categories) {
                Backdrop.getlocations_leaflet_overlays[key][categories[c]] = Markers[c];
              }
            }
            else if (map_settings.layercontrol_mark_ov) {
              Backdrop.getlocations_leaflet_overlays[key][map_settings.layercontrol_mark_ov_label] = Markers['loc'];
            }

            // adding graticule to overlay switches
            if (map_settings.graticule && map_settings.graticule_show == 1 ) {
              Backdrop.getlocations_leaflet_overlays[key][map_settings.graticule_ov_label] = graticule;
            }

            // adding terminator to overlay switches
            if (map_settings.terminator && map_settings.terminator_show == 1 ) {
              Backdrop.getlocations_leaflet_overlays[key][map_settings.terminator_label] = terminator;
            }

          } // end datanum > 0

          // Layer control
          if (map_settings.layerControl) {
            var layeropts = {};
            if (map_settings.layercontrolposition) {
              layeropts.position = map_settings.layercontrolposition;
            }
            if (map_settings.minimap) {
              Backdrop.getlocations_leaflet_layerscontrol[key] = L.control.layers.minimap(layers, Backdrop.getlocations_leaflet_overlays[key], layeropts).addTo(Backdrop.getlocations_leaflet_map[key]);
            }
            else {
              Backdrop.getlocations_leaflet_layerscontrol[key] = L.control.layers(layers, Backdrop.getlocations_leaflet_overlays[key], layeropts).addTo(Backdrop.getlocations_leaflet_map[key]);
            }
          }

          // bounds
          Backdrop.getlocations_leaflet.redoMap(key);

          // Usermarker
          if (map_settings.usermarker) {
            var usermarker = null;
            $("#getlocations_leaflet_gps_show_" + key).click( function() {
              $("#getlocations_leaflet_gps_throbber_" + key).removeClass('getlocations_leaflet_gps_throbber_inactive');
              $("#getlocations_leaflet_gps_throbber_" + key).addClass('getlocations_leaflet_gps_throbber_active');
              if (usermarker) {
                Backdrop.getlocations_leaflet_map[key].removeLayer(usermarker);
                usermarker = null;
              }
              Backdrop.getlocations_leaflet_map[key].on("locationfound", function(location) {
                if (! usermarker) {
                  usermarker_opts = {
                    pulsing: map_settings.usermarker_pulsing,
                    smallIcon: map_settings.usermarker_smallicon,
                    circleOpts: {
                      stroke: map_settings.usermarker_circle_stroke,
                      color: map_settings.usermarker_circle_strokecolor,
                      weight: map_settings.usermarker_circle_strokeweight,
                      opacity: map_settings.usermarker_circle_strokeopacity,
                      fillOpacity: map_settings.usermarker_circle_fillopacity,
                      fillColor: map_settings.usermarker_circle_fillcolor,
                      clickable: false
                    }
                  };
                  usermarker = L.userMarker(location.latlng, usermarker_opts).addTo(Backdrop.getlocations_leaflet_map[key]);
                  usermarker.setLatLng(location.latlng);
                  if (map_settings.usermarker_accuracy) {
                    usermarker.setAccuracy(location.accuracy);
                  }
                }
                getlocations_leaflet_deactive_throbber(key);
              });
              Backdrop.getlocations_leaflet_map[key].on("locationerror", function(error) {
                getlocations_leaflet_deactive_throbber(key);
                alert(Backdrop.t('Error: location failed.') + ' ' + error.message);
              });

              Backdrop.getlocations_leaflet_map[key].locate({
                watch: false,
                locate: true,
                setView: true,
                enableHighAccuracy: true
              });

            });

          }

          // leaflet hash
          if (map_settings.hashurl && typeof(L.Hash) !== 'undefined') {
            L.hash(Backdrop.getlocations_leaflet_map[key]);
          }

          // show_maplinks_viewport
          if (map_settings.show_maplinks && map_settings.show_maplinks_viewport) {
            Backdrop.getlocations_leaflet_map[key].on('moveend zoomend', function() {
              var b = Backdrop.getlocations_leaflet_map[key].getBounds();
              for (var i = 0; i < latlons.length; i++) {
                var latlon = latlons[i];
                var lat = latlon[0];
                var lon = latlon[1];
                var glid = latlon[4];
                var p = L.latLng(lat, lon);
                if (b.contains(p)) {
                  // hide and show the links for markers in the current viewport
                  $("li a.glid-" + glid).show();
                }
                else {
                  $("li a.glid-" + glid).hide();
                }
              }
            });
          }

        } // end is there really a map?
      }); // end once
    } // end attach
  }; // end behaviors


  // external functions
  Backdrop.getlocations_leaflet.makeMarker = function(gs, lat, lon, entity_key, entity_id, glid, title, icon, vector, markeraction, cat, mkey) {

    // categories
    if (cat) {
      Backdrop.getlocations_leaflet_markers[mkey].cat[glid] = cat;
    }

    var vicon = false;
    if (typeof(vector.data) !== undefined) {
      vicon = vector.data;
      var marker_type = vector.type;
    }

    // check for duplicates
    var hash = new String(lat + lon);
    if (Backdrop.getlocations_leaflet_markers[mkey].coords[hash] == null) {
      Backdrop.getlocations_leaflet_markers[mkey].coords[hash] = 1;
    }
    else {
      // we have a duplicate
      // 10000 constrains the max, 0.0001 constrains the min distance
      m1 = (Math.random() /10000) + 0.0001;
      // randomise the operator
      m2 = Math.random();
      if (m2 > 0.5) {
        lat = parseFloat(lat) + m1;
      }
      else {
        lat = parseFloat(lat) - m1;
      }
      m1 = (Math.random() /10000) + 0.0001;
      m2 = Math.random();
      if (m2 > 0.5) {
        lon = parseFloat(lon) + m1;
      }
      else {
        lon = parseFloat(lon) - m1;
      }
    }

    // make markers
    var latLng = L.latLng(lat, lon);
    var Marker = {};

    if (icon || (vicon && gs.awesome)) {
      if (vicon && gs.awesome) {
        // icon only
        if (marker_type == 'i') {
          var px = parseInt(vicon.px);
          var diopts = {
            className: vicon.classname,
            iconSize: [px, px],
            html: vicon.html
          };
          var thisIcon = L.divIcon(diopts);
        }
        else {
          var thisIcon = L.AwesomeMarkers.icon(vicon);
        }
      }
      else if (icon) {
        var thisIcon = L.icon({iconUrl: icon.iconUrl});
        // override applicable marker defaults
        if (icon.iconSize) {
          thisIcon.options.iconSize = L.point(parseInt(icon.iconSize.x, 10), parseInt(icon.iconSize.y, 10));
        }
        if (icon.iconAnchor) {
          thisIcon.options.iconAnchor = L.point(parseFloat(icon.iconAnchor.x, 10), parseFloat(icon.iconAnchor.y, 10));
        }
        if (icon.popupAnchor) {
          thisIcon.options.popupAnchor = L.point(parseFloat(icon.popupAnchor.x, 10), parseFloat(icon.popupAnchor.y, 10));
        }
        if (icon.shadowUrl !== undefined) {
          thisIcon.options.shadowUrl = icon.shadowUrl;
          if (icon.shadowSize) {
            thisIcon.options.shadowSize = L.point(parseInt(icon.shadowSize.x, 10), parseInt(icon.shadowSize.y, 10));
          }
          if (icon.shadowAnchor) {
            thisIcon.options.shadowAnchor = L.point(parseInt(icon.shadowAnchor.x, 10), parseInt(icon.shadowAnchor.y, 10));
          }
        }
      }
      Marker = L.marker(latLng, {icon: thisIcon});
    }
    else {
      // default leaflet marker
      Marker = L.marker(latLng);
    }

    if (title) {
      Marker.options.title = title;
    }

    // markeraction
    if (markeraction && markeraction.type && markeraction.data) {
      if (markeraction.type == 'popup') {
        Marker.bindPopup(markeraction.data);
      }
      else if (markeraction.type == 'link') {
        Marker.on('click', function() {
          window.location = markeraction.data;
        });
      }
    }
    else {
      Marker.options.clickable = false;
    }

    // bounce marker
    if (gs.bouncemarker) {
      Marker.options.bounceOnAdd = true;
      Marker.options.bounceOnAddDuration = gs.bouncemarker_duration;
      if (gs.bouncemarker_height) {
        Marker.options.bounceOnAddHeight = gs.bouncemarker_height;
      }
    }

    return Marker;
  };

  // redo map
  Backdrop.getlocations_leaflet.redoMap = function(key) {
    if (Backdrop.getlocations_leaflet_data[key].datanum > 1) {
      var minmaxes = (Backdrop.getlocations_leaflet_data[key].minmaxes ? Backdrop.getlocations_leaflet_data[key].minmaxes : '');
      if (minmaxes) {
        var mmarr = minmaxes.split(',');
        var sw = L.latLng(parseFloat(mmarr[2]), parseFloat(mmarr[3])),
          ne = L.latLng(parseFloat(mmarr[0]), parseFloat(mmarr[1])),
          bounds = L.latLngBounds(sw, ne).pad(0.1);
        Backdrop.getlocations_leaflet_map[key].invalidateSize().fitBounds(bounds, {reset: true});
      }
    }
  };

})(jQuery);
