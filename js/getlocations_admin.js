
/**
 * @file
 * Javascript functions for getlocations module admin
 *
 * @author Bob Hutchinson http://drupal.org/user/52366
 * jquery stuff
*/
(function ($) {

  Drupal.behaviors.getlocations_admin = function() {

    if ($("#edit-getlocations-default-returnlink-page-enable").attr('checked')) {
      $("#wrap-page-link").show();
    }
    else {
      $("#wrap-page-link").hide();
    }
    $("#edit-getlocations-default-returnlink-page-enable").change(function() {
      if ($(this).attr('checked')) {
        $("#wrap-page-link").show();
      }
      else {
        $("#wrap-page-link").hide();
      }
    });

    if ($("#edit-getlocations-default-returnlink-user-enable").attr('checked')) {
      $("#wrap-user-link").show();
    }
    else {
      $("#wrap-user-link").hide();
    }
    $("#edit-getlocations-default-returnlink-user-enable").change(function() {
      if ($(this).attr('checked')) {
        $("#wrap-user-link").show();
      }
      else {
        $("#wrap-user-link").hide();
      }
    });

    if ($("#edit-getlocations-colorbox-enable").attr('checked')) {
      $("#wrap-getlocations-colorbox").show();
    }
    else {
      $("#wrap-getlocations-colorbox").hide();
    }
    $("#edit-getlocations-colorbox-enable").change(function() {
      if ($(this).attr('checked')) {
        $("#wrap-getlocations-colorbox").show();
      }
      else {
        $("#wrap-getlocations-colorbox").hide();
      }
    });

    if ($("#edit-getlocations-node-marker-enable").attr('checked')) {
      $("#wrap-getlocations-node-markers").show();
    }
    else {
      $("#wrap-getlocations-node-markers").hide();
    }
    $("#edit-getlocations-node-marker-enable").change(function() {
      if ($(this).attr('checked')) {
        $("#wrap-getlocations-node-markers").show();
      }
      else {
        $("#wrap-getlocations-node-markers").hide();
      }
    });

    if ($("#edit-getlocations-default-trafficinfo").is('input')) {
      if ($("#edit-getlocations-default-trafficinfo").attr('checked')) {
        $("#wrap-getlocations-trafficinfo").show();
      }
      else {
        $("#wrap-getlocations-trafficinfo").hide();
      }
      $("#edit-getlocations-default-trafficinfo").change(function() {
        if ($(this).attr('checked')) {
          $("#wrap-getlocations-trafficinfo").show();
        }
        else {
          $("#wrap-getlocations-trafficinfo").hide();
        }
      });
    }

    if ($("#edit-getlocations-default-bicycleinfo").is('input')) {
      if ($("#edit-getlocations-default-bicycleinfo").attr('checked')) {
        $("#wrap-getlocations-bicycleinfo").show();
      }
      else {
        $("#wrap-getlocations-bicycleinfo").hide();
      }
      $("#edit-getlocations-default-bicycleinfo").change(function() {
        if ($(this).attr('checked')) {
          $("#wrap-getlocations-bicycleinfo").show();
        }
        else {
          $("#wrap-getlocations-bicycleinfo").hide();
        }
      });
    }

    if ($("#edit-getlocations-default-transitinfo").is('input')) {
      if ($("#edit-getlocations-default-transitinfo").attr('checked')) {
        $("#wrap-getlocations-transitinfo").show();
      }
      else {
        $("#wrap-getlocations-transitinfo").hide();
      }
      $("#edit-getlocations-default-transitinfo").change(function() {
        if ($(this).attr('checked')) {
          $("#wrap-getlocations-transitinfo").show();
        }
        else {
          $("#wrap-getlocations-transitinfo").hide();
        }
      });
    }

    if ( $("#edit-getlocations-default-panoramio-use").is('input') && $("#edit-getlocations-default-panoramio-show").is('input')) {

      if ($("#edit-getlocations-default-panoramio-use").attr('checked')) {
        $("#wrap-getlocations-panoramio-use").show();
      }
      else {
        $("#wrap-getlocations-panoramio-use").hide();
      }
      $("#edit-getlocations-default-panoramio-use").change(function() {
        if ($(this).attr('checked')) {
          $("#wrap-getlocations-panoramio-use").show();
        }
        else {
          $("#wrap-getlocations-panoramio-use").hide();
        }
      });

      if ($("#edit-getlocations-default-panoramio-show").attr('checked')) {
        $("#wrap-getlocations-panoramio").show();
      }
      else {
        $("#wrap-getlocations-panoramio").hide();
      }
      $("#edit-getlocations-default-panoramio-show").change(function() {
        if ($(this).attr('checked')) {
          $("#wrap-getlocations-panoramio").show();
        }
        else {
          $("#wrap-getlocations-panoramio").hide();
        }
      });
    }

    if ( $("#edit-getlocations-default-weather-use").is('input') && $("#edit-getlocations-default-weather-show").is('input')) {

      if ($("#edit-getlocations-default-weather-use").attr('checked')) {
        $("#wrap-getlocations-weather-use").show();
      }
      else {
        $("#wrap-getlocations-weather-use").hide();
      }
      $("#edit-getlocations-default-weather-use").change(function() {
        if ($(this).attr('checked')) {
          $("#wrap-getlocations-weather-use").show();
        }
        else {
          $("#wrap-getlocations-weather-use").hide();
        }
      });

      if ($("#edit-getlocations-default-weather-show").attr('checked')) {
        $("#wrap-getlocations-weather").show();
      }
      else {
        $("#wrap-getlocations-weather").hide();
      }
      $("#edit-getlocations-default-weather-show").change(function() {
        if ($(this).attr('checked')) {
          $("#wrap-getlocations-weather").show();
        }
        else {
          $("#wrap-getlocations-weather").hide();
        }
      });

      if ($("#edit-getlocations-default-weather-cloud").attr('checked')) {
        $("#wrap-getlocations-weather-cloud").show();
      }
      else {
        $("#wrap-getlocations-weather-cloud").hide();
      }
      $("#edit-getlocations-default-weather-cloud").change(function() {
        if ($(this).attr('checked')) {
          $("#wrap-getlocations-weather-cloud").show();
        }
        else {
          $("#wrap-getlocations-weather-cloud").hide();
        }
      });

    }

/*

    if ($("#edit-getlocations-vocabulary-marker-enable").attr('checked')) {
      $("#wrap-getlocations-vocabulary-markers").show();
    }
    else {
      $("#wrap-getlocations-vocabulary-markers").hide();
    }
    $("#edit-getlocations-vocabulary-marker-enable").change(function() {
      if ($(this).attr('checked')) {
        $("#wrap-getlocations-vocabulary-markers").show();
      }
      else {
        $("#wrap-getlocations-vocabulary-markers").hide();
      }
    });

    if ($("#edit-getlocations-roles-marker-enable").attr('checked')) {
      $("#wrap-getlocations-roles-markers").show();
    }
    else {
      $("#wrap-getlocations-roles-markers").hide();
    }
    $("#edit-getlocations-roles-marker-enable").change(function() {
      if ($(this).attr('checked')) {
        $("#wrap-getlocations-roles-markers").show();
      }
      else {
        $("#wrap-getlocations-roles-markers").hide();
      }
    });
*/
  }

})(jQuery);
