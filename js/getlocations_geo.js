
/**
 * @file
 * getlocations_geo.js
 * @author Bob Hutchinson http://backdrop.org/user/52366
 * @copyright GNU GPL
 *
 * Javascript geo functions for getlocations module for Backdrop 7
 * this is for googlemaps API version 3
 */

(function ($) {

  if ( typeof(Backdrop.getlocations) == 'undefined') {
    Backdrop.getlocations = {};
  }

  Backdrop.getlocations.geo = {};
  Backdrop.getlocations.geo.EARTH_RADIUS_SEMIMAJOR = 6378137.0;
  Backdrop.getlocations.geo.EARTH_FLATTENING = (1/298.257223563);
  Backdrop.getlocations.geo.EARTH_RADIUS_SEMIMINOR = (Backdrop.getlocations.geo.EARTH_RADIUS_SEMIMAJOR * (1 - Backdrop.getlocations.geo.EARTH_FLATTENING));
  //Backdrop.getlocations.geo.EARTH_ECCENTRICITY_SQ = (2*(1/298.257223563)-Math.pow((1/298.257223563), 2));

  /**
   * Normalizes a latitude to the [-90,90] range. Latitudes above 90 or
   * below -90 are capped, not wrapped.
   * @param {Number} lat The latitude to normalize, in degrees.
   * @type Number
   * @return Returns the latitude, fit within the [-90,90] range.
   */
  Backdrop.getlocations.geo.normalizeLat = function(lat) {
    return Math.max(-90, Math.min(90, lat));
  };

  /**
   * Normalizes a longitude to the [-180,180] range. Longitudes above 180
   * or below -180 are wrapped.
   * @param {Number} lng The longitude to normalize, in degrees.
   * @type Number
   * @return Returns the longitude, fit within the [-180,180] range.
   */
  Backdrop.getlocations.geo.normalizeLng = function(lng) {
    if (lng % 360 == 180) {
      return 180;
    }
    lng = lng % 360;
    return lng < -180 ? lng + 360 : lng > 180 ? lng - 360 : lng;
  };

  /**
   * Decimal Degrees to Radians.
   * @param {Number} Decimal Degrees
   * @returns {Number} Radians
   *
   */
  Backdrop.getlocations.geo.toRad = function(deg) {
    return deg * Math.PI / 180;
  };

  /**
   * Radians to Decimal Degrees.
   * @param {Number} Radians
   * @returns {Number} Decimal Degrees
   *
   */
  Backdrop.getlocations.geo.toDeg = function(rad) {
    return rad * 180 / Math.PI;
  };

  /**
   * Returns the earth's radius at a given latitude
   * @param {Number} Latitude
   * @returns {Number} radius
   *
   */
  Backdrop.getlocations.geo.earth_radius = function(latitude) {
    var lat = Backdrop.getlocations.geo.toRad(latitude);
    var x = (Math.cos(lat) / Backdrop.getlocations.geo.EARTH_RADIUS_SEMIMAJOR);
    var y = (Math.sin(lat) / Backdrop.getlocations.geo.EARTH_RADIUS_SEMIMINOR);
    var r = (1 / (Math.sqrt(x * x + y * y)));
    return r;
  };

  /**
   * Estimate the min and max longitudes within distance of a given location.
   * @param {Number} latitude
   * @param {Number} longitude
   * @param {Number} distance in meters
   * @returns {Array}
   *
   */
  Backdrop.getlocations.geo.earth_longitude_range = function(latitude, longitude, distance) {

    if (! distance > 0) {
      distance = 1;
    }
    latitude = parseFloat(latitude);
    longitude = parseFloat(longitude);
    distance = parseInt(distance);
    var lng = Backdrop.getlocations.geo.toRad(longitude);
    var lat =  Backdrop.getlocations.geo.toRad(latitude);
    var radius = Backdrop.getlocations.geo.earth_radius(latitude) * Math.cos(lat);
    var angle = 0;
    if (radius > 0) {
      angle = Math.abs(distance / radius);
      angle = Math.min(angle, Math.PI);
    }
    else {
      angle = Math.PI;
    }
    var minlong = lng - angle;
    var maxlong = lng + angle;
    if (minlong < -Math.PI) {
      minlong = minlong + Math.PI * 2;
    }
    if (maxlong > Math.PI) {
      maxlong = maxlong - Math.PI * 2;
    }
    var minlongDeg = Backdrop.getlocations.geo.toDeg(minlong);
    minlongDeg = Backdrop.getlocations.geo.normalizeLng(minlongDeg);
    var maxlongDeg = Backdrop.getlocations.geo.toDeg(maxlong);
    maxlongDeg = Backdrop.getlocations.geo.normalizeLng(maxlongDeg);
    var r = [minlongDeg.toFixed(6), maxlongDeg.toFixed(6)];
    return r;
  };

  /**
   * Estimate the min and max latitudes within distance of a given location.
   * @param {Number} latitude
   * @param {Number} longitude
   * @param {Number} distance in meters
   * @returns {Array}
   *
   */
  Backdrop.getlocations.geo.earth_latitude_range = function(latitude, longitude, distance) {

    if (! distance > 0) {
      distance = 1;
    }
    latitude = parseFloat(latitude);
    longitude = parseFloat(longitude);
    distance = parseInt(distance);
    var lng = Backdrop.getlocations.geo.toRad(longitude);
    var lat =  Backdrop.getlocations.geo.toRad(latitude);
    var radius = Backdrop.getlocations.geo.earth_radius(latitude);
    var angle = distance / radius;
    var minlat = lat - angle;
    var maxlat = lat + angle;
    var rightangle = Math.PI / 2;
    var overshoot = 0;
    if (minlat < -rightangle) { // wrapped around the south pole
      overshoot = -minlat - rightangle;
      minlat = -rightangle + overshoot;
      if (minlat > maxlat) {
        maxlat = minlat;
      }
      minlat = -rightangle;
    }
    if (maxlat > rightangle) { // wrapped around the north pole
      overshoot = maxlat - rightangle;
      maxlat = rightangle - overshoot;
      if (maxlat < minlat) {
        minlat = maxlat;
      }
      maxlat = rightangle;
    }
    var minlatDeg = Backdrop.getlocations.geo.toDeg(minlat);
    minlatDeg = Backdrop.getlocations.geo.normalizeLat(minlatDeg);
    var maxlatDeg = Backdrop.getlocations.geo.toDeg(maxlat);
    maxlatDeg = Backdrop.getlocations.geo.normalizeLat(maxlatDeg);
    var r = [minlatDeg.toFixed(6), maxlatDeg.toFixed(6)];
    return r;
  };

  /**
   * Estimate the earth-surface distance between two locations.
   *
   * @param {Number} latitude1
   * @param {Number} longitude1
   * @param {Number} latitude2
   * @param {Number} longitude2
   * @returns {Number} distance in meters
   */
  Backdrop.getlocations.geo.earth_distance = function(latitude1, longitude1, latitude2, longitude2) {
    var lat1 = Backdrop.getlocations.geo.toRad(parseFloat(latitude1));
    var lng1 = Backdrop.getlocations.geo.toRad(parseFloat(longitude1));
    var lat2 = Backdrop.getlocations.geo.toRad(parseFloat(latitude2));
    var lng2 = Backdrop.getlocations.geo.toRad(parseFloat(longitude2));
    var radius = Backdrop.getlocations.geo.earth_radius((parseFloat(latitude1) + parseFloat(latitude2)) / 2);
    var cosangle = Math.cos(lat1) * Math.cos(lat2) * (Math.cos(lng1) * Math.cos(lng2) + Math.sin(lng1) * Math.sin(lng2)) + Math.sin(lat1) * Math.sin(lat2);
    return Math.acos(cosangle) * radius;
  };

  /**
   * Estimate the earth-surface distance between two locations, Haversine formula.
   *
   * @param {Number} latitude1
   * @param {Number} longitude1
   * @param {Number} latitude2
   * @param {Number} longitude2
   * @returns {Number} distance in meters
   */
  Backdrop.getlocations.geo.earth_distance2 = function(latitude1, longitude1, latitude2, longitude2) {
    var lat1 = Backdrop.getlocations.geo.toRad(parseFloat(latitude1));
    var lng1 = Backdrop.getlocations.geo.toRad(parseFloat(longitude1));
    var lat2 = Backdrop.getlocations.geo.toRad(parseFloat(latitude2));
    var lng2 = Backdrop.getlocations.geo.toRad(parseFloat(longitude2));
    var radius = Backdrop.getlocations.geo.earth_radius((parseFloat(latitude1) + parseFloat(latitude2)) / 2);
    var latm = lat2 - lat1;
    var lngm = lng2 - lng1;
    var a = Math.sin(latm / 2) * Math.sin(latm / 2) + Math.cos(lat1) * Math.cos(lat2) * Math.sin(lngm / 2) * Math.sin(lngm / 2);
    return radius * 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
  };

  /**
   * Convert a distance to meters
   * @param {Number} distance
   * @param {String} the distance unit
   * @returns {Number} the distance in meters
   */
  Backdrop.getlocations.geo.convert_distance_to_meters = function(distance, distance_unit) {
    if (typeof(distance) !== 'number' || !distance > 0) {
      return null;
    }
    var units = {
      'km': 1000.0,
      'm': 1.0,
      'mi': 1609.344,
      'yd': 0.9144,
      'nmi': 1852.0
    };
    if (units[distance_unit] === undefined) {
      distance_unit = 'km';
    }
    var conv = units[distance_unit];
    var n = parseFloat(distance) * parseFloat(conv);
    var retval = n.toFixed(2);
    return retval;
  };

  /**
   * Convert meters to a distance
   * @param {Number} meters
   * @param {String} the distance unit
   * @returns {Number} the distance in the distance unit
   */
  Backdrop.getlocations.geo.convert_meters_to_distance = function(meters, distance_unit) {
    if (typeof(meters) !== 'number' || !meters > 0) {
      return null;
    }
    var units = {
      'km': 0.001,
      'm': 1.0,
      'mi': 0.000621371,
      'yd': 1.093613298,
      'nmi': 0.000539957
    };
    if (units[distance_unit] === undefined) {
      distance_unit = 'km';
    }
    var conv = units[distance_unit];
    var n = parseFloat(meters) * parseFloat(conv);
    var retval = n.toFixed(2);
    return retval;
  };

  /**
   * Convert Decimal Degrees to Degrees, minutes, seconds
   * @param {Number} coordinate in Decimal Degrees
   * @param {String} 'lat' for latitude or anything else for longitude
   * @return {String} Degrees, minutes, seconds formatted for webpage
   */
  Backdrop.getlocations.geo.dd_to_dms_do = function(coord, latlon, web) {
    if (typeof web == 'undefined') web = true;
    if (latlon == 'lat') {
      coord = Backdrop.getlocations.geo.normalizeLat(coord);
      direction = (coord < 0) ? 'S' : 'N';
    }
    else {
      coord = Backdrop.getlocations.geo.normalizeLng(coord);
      direction = (coord < 0) ? 'W' : 'E';
    }
    coord = Math.abs(coord);
    degrees = Math.floor(coord);
    coord = (coord - degrees) * 60;
    minutes = Math.floor(coord);
    coord = (coord - minutes) * 60;
    seconds = Math.round(coord, 6);
    if (web) {
      output = degrees + "&deg;&nbsp;" + minutes + "&#39;&nbsp;" + seconds + "&#34;&nbsp;" + direction;
    }
    else {
      output = degrees + '°' + minutes + '′' + seconds + '″' + direction;
    }

    return output;
  };

  /**
   * Convert Decimal Degrees Latitude to Degrees, minutes, seconds
   * @param {Number} coordinate in Decimal Degrees
   * @return {String} Degrees, minutes, seconds formatted for webpage
   */
  Backdrop.getlocations.geo.dd_to_dms_lat = function(coord) {
    return Backdrop.getlocations.geo.dd_to_dms_do(coord, 'lat');
  };

  /**
   * Convert Decimal Degrees Longitude to Degrees, minutes, seconds
   * @param {Number} coordinate in Decimal Degrees
   * @return {String} Degrees, minutes, seconds formatted for webpage
   */
  Backdrop.getlocations.geo.dd_to_dms_lng = function(coord) {
    return Backdrop.getlocations.geo.dd_to_dms_do(coord, 'lng');
  };

  /**
   * Format Decimal Degrees Latitude
   * @param {Number} coordinate in Decimal Degrees
   * @param {Number} number of digits after decimal point
   * @return {Number} formatted to standard length
   *
   */
  Backdrop.getlocations.geo.dd_lat = function(coord, len) {
    if (typeof len == 'undefined') len = 6;
    coord = Backdrop.getlocations.geo.normalizeLat(coord);
    return coord.toFixed(len);
  };

  /**
  * Format Decimal Degrees Longitude
  * @param {Number} coordinate in Decimal Degrees
  * @param {Number} number of digits after decimal point
  * @return {Number} formatted to standard length
  *
  */
  Backdrop.getlocations.geo.dd_lng = function(coord, len) {
    if (typeof len == 'undefined') len = 6;
    coord = Backdrop.getlocations.geo.normalizeLng(coord);
    return coord.toFixed(len);
  };

  /**
   * Convert Degrees, minutes, seconds to Decimal Degrees
   * from www.movable-type.co.uk/scripts/latlong.html
   * Sample usage:
   *   var lat = Backdrop.getlocations.geo.parseDMS('51° 28′ 40.12″ N');
   *   var lon = Backdrop.getlocations.geo.parseDMS('000° 00′ 05.31″ W');
   *
   * @param {String} Degrees, minutes, seconds
   * @return {Number} Decimal Degrees
   */
  Backdrop.getlocations.geo.parseDMS = function(dmsStr) {
    // check for signed decimal degrees without NSEW, if so return it directly
    if (typeof dmsStr == 'number' && isFinite(dmsStr)) return Number(dmsStr);

    // strip off any sign or compass dir'n & split out separate d/m/s
    var dms = String(dmsStr).trim().replace(/^-/,'').replace(/[NSEW]$/i,'').split(/[^0-9.,]+/);
    if (dms[dms.length-1]=='') dms.splice(dms.length-1);  // from trailing symbol

    if (dms == '') return NaN;
    // and convert to decimal degrees...
    var deg;
    switch (dms.length) {
      case 3:  // interpret 3-part result as d/m/s
        deg = dms[0]/1 + dms[1]/60 + dms[2]/3600;
        break;
      case 2:  // interpret 2-part result as d/m
        deg = dms[0]/1 + dms[1]/60;
        break;
      case 1:  // just d (possibly decimal) or non-separated dddmmss
        deg = dms[0];
        // check for fixed-width unseparated format eg 0033709W
        //if (/[NS]/i.test(dmsStr)) deg = '0' + deg;  // - normalise N/S to 3-digit degrees
        //if (/[0-9]{7}/.test(deg)) deg = deg.slice(0,3)/1 + deg.slice(3,5)/60 + deg.slice(5)/3600;
        break;
      default:
        return NaN;
    }
    if (/^-|[WS]$/i.test(dmsStr.trim())) deg = -deg; // take '-', west and south as -ve
    return Number(deg);

  };

  /**
   * Converts decimal degrees to deg/min/sec format
   *  - degree, prime, double-prime symbols are added, but sign is discarded, though no compass
   *    direction is added.
   *
   * @private
   * @param   {number} deg - Degrees to be formatted as specified.
   * @param   {string} [format=dms] - Return value as 'd', 'dm', 'dms'.
   * @param   {number} [dp=0|2|4] - Number of decimal places to use – default 0 for dms, 2 for dm, 4 for d.
   * @returns {string} Degrees formatted as deg/min/secs according to specified format.
   */
  Backdrop.getlocations.geo.toDMS = function(deg, format, dp) {
    if (isNaN(deg)) return null;  // give up here if we can't make a number from deg

    // default values
    if (typeof format == 'undefined') format = 'dms';
    if (typeof dp == 'undefined') {
      switch (format) {
        case 'd':   dp = 4; break;
        case 'dm':  dp = 2; break;
        case 'dms': dp = 0; break;
        default:    format = 'dms'; dp = 0;  // be forgiving on invalid format
      }
    }

    deg = Math.abs(deg);  // (unsigned result ready for appending compass dir'n)

    var dms, d, m, s;
    switch (format) {
      default: // invalid format spec!
      case 'd':
        d = deg.toFixed(dp);     // round degrees
        if (d<100) d = '0' + d;  // pad with leading zeros
        if (d<10) d = '0' + d;
        dms = d + '°';
        break;
      case 'dm':
        var min = (deg*60).toFixed(dp);  // convert degrees to minutes & round
        d = Math.floor(min / 60);    // get component deg/min
        m = (min % 60).toFixed(dp);  // pad with trailing zeros
        if (d<100) d = '0' + d;          // pad with leading zeros
        if (d<10) d = '0' + d;
        if (m<10) m = '0' + m;
        dms = d + '°' + m + '′';
        break;
      case 'dms':
        var sec = (deg*3600).toFixed(dp);  // convert degrees to seconds & round
        d = Math.floor(sec / 3600);    // get component deg/min/sec
        m = Math.floor(sec/60) % 60;
        s = (sec % 60).toFixed(dp);    // pad with trailing zeros
        if (d<100) d = '0' + d;            // pad with leading zeros
        if (d<10) d = '0' + d;
        if (m<10) m = '0' + m;
        if (s<10) s = '0' + s;
        dms = d + '°' + m + '′' + s + '″';
        break;
    }

    return dms;
  };

  /**
   * Converts numeric degrees to deg/min/sec latitude (2-digit degrees, suffixed with N/S).
   *
   * @param   {number} deg - Degrees to be formatted as specified.
   * @param   {string} [format=dms] - Return value as 'd', 'dm', 'dms'.
   * @param   {number} [dp=0|2|4] - Number of decimal places to use – default 0 for dms, 2 for dm, 4 for d.
   * @returns {string} Degrees formatted as deg/min/secs according to specified format.
   */
  Backdrop.getlocations.geo.toLat = function(deg, format, dp) {
    var lat = Backdrop.getlocations.geo.toDMS(deg, format, dp);
    return lat===null ? '–' : lat.slice(1) + (deg<0 ? 'S' : 'N');  // knock off initial '0' for lat!
  };

  /**
   * Convert numeric degrees to deg/min/sec longitude (3-digit degrees, suffixed with E/W)
   *
   * @param   {number} deg - Degrees to be formatted as specified.
   * @param   {string} [format=dms] - Return value as 'd', 'dm', 'dms'.
   * @param   {number} [dp=0|2|4] - Number of decimal places to use – default 0 for dms, 2 for dm, 4 for d.
   * @returns {string} Degrees formatted as deg/min/secs according to specified format.
   */
  Backdrop.getlocations.geo.toLon = function(deg, format, dp) {
    var lon = Backdrop.getlocations.geo.toDMS(deg, format, dp);
    return lon===null ? '–' : lon + (deg<0 ? 'W' : 'E');
  };

  /**
   * Converts numeric degrees to deg/min/sec as a bearing (0°..360°)
   *
   * @param   {number} deg - Degrees to be formatted as specified.
   * @param   {string} [format=dms] - Return value as 'd', 'dm', 'dms'.
   * @param   {number} [dp=0|2|4] - Number of decimal places to use – default 0 for dms, 2 for dm, 4 for d.
   * @returns {string} Degrees formatted as deg/min/secs according to specified format.
   */
  Backdrop.getlocations.geo.toBrng = function(deg, format, dp) {
    deg = (Number(deg)+360) % 360;  // normalise -ve values to 180°..360°
    var brng =  Backdrop.getlocations.geo.toDMS(deg, format, dp);
    return (brng === null ? '–' : brng.replace('360', '0'));  // just in case rounding took us up to 360°!
  };

  /**
  * Returns compass point (to given precision) for supplied bearing.
  *
  * @param   {number} bearing - Bearing in degrees from north.
  * @param   {number} [precision=3] - Precision (cardinal / intercardinal / secondary-intercardinal).
  * @returns {string} Compass point for supplied bearing.
  *
  * @example
  *   var point = Dms.compassPoint(24);    // point = 'NNE'
  *   var point = Dms.compassPoint(24, 1); // point = 'N'
  */
  Backdrop.getlocations.geo.compassPoint = function (bearing, precision) {
    if (precision === undefined) precision = 3;
    // note precision = max length of compass point; it could be extended to 4 for quarter-winds
    // (eg NEbN), but I think they are little used

    bearing = ((bearing%360)+360)%360; // normalise to 0..360

    var point;

    switch (precision) {
      case 1: // 4 compass points
        switch (Math.round(bearing*4/360)%4) {
          case 0: point = 'N'; break;
          case 1: point = 'E'; break;
          case 2: point = 'S'; break;
          case 3: point = 'W'; break;
        }
        break;
      case 2: // 8 compass points
        switch (Math.round(bearing*8/360)%8) {
          case 0: point = 'N';  break;
          case 1: point = 'NE'; break;
          case 2: point = 'E';  break;
          case 3: point = 'SE'; break;
          case 4: point = 'S';  break;
          case 5: point = 'SW'; break;
          case 6: point = 'W';  break;
          case 7: point = 'NW'; break;
        }
        break;
      case 3: // 16 compass points
        switch (Math.round(bearing*16/360)%16) {
          case  0: point = 'N';   break;
          case  1: point = 'NNE'; break;
          case  2: point = 'NE';  break;
          case  3: point = 'ENE'; break;
          case  4: point = 'E';   break;
          case  5: point = 'ESE'; break;
          case  6: point = 'SE';  break;
          case  7: point = 'SSE'; break;
          case  8: point = 'S';   break;
          case  9: point = 'SSW'; break;
          case 10: point = 'SW';  break;
          case 11: point = 'WSW'; break;
          case 12: point = 'W';   break;
          case 13: point = 'WNW'; break;
          case 14: point = 'NW';  break;
          case 15: point = 'NNW'; break;
        }
        break;
      default:
        throw new RangeError('Precision must be between 1 and 3');
    }
    return point;
  };

})(jQuery);
