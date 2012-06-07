
/**
 * @file
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations module admin
 * jquery stuff
*/
(function ($) {

  Drupal.behaviors.getlocations_admin = {
    attach: function() {

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

      if ($("#edit-getlocations-default-returnlink-term-enable").attr('checked')) {
        $("#wrap-term-link").show();
      }
      else {
        $("#wrap-term-link").hide();
      }
      $("#edit-getlocations-default-returnlink-term-enable").change(function() {
        if ($(this).attr('checked')) {
          $("#wrap-term-link").show();
        }
        else {
          $("#wrap-term-link").hide();
        }
      });

      if ($("#edit-getlocations-default-returnlink-comment-enable").attr('checked')) {
        $("#wrap-comment-link").show();
      }
      else {
        $("#wrap-comment-link").hide();
      }
      $("#edit-getlocations-default-returnlink-comment-enable").change(function() {
        if ($(this).attr('checked')) {
          $("#wrap-comment-link").show();
        }
        else {
          $("#wrap-comment-link").hide();
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

      if ($("#edit-getlocations-colorbox-marker-enable").attr('checked')) {
        $("#wrap-getlocations-marker-colorbox").show();
      }
      else {
        $("#wrap-getlocations-marker-colorbox").hide();
      }
      $("#edit-getlocations-colorbox-marker-enable").change(function() {
        if ($(this).attr('checked')) {
          $("#wrap-getlocations-marker-colorbox").show();
        }
        else {
          $("#wrap-getlocations-marker-colorbox").hide();
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

      if ($("#edit-getlocations-term-marker-enable").attr('checked')) {
        $("#wrap-getlocations-term-markers").show();
      }
      else {
        $("#wrap-getlocations-term-markers").hide();
      }
      $("#edit-getlocations-term-marker-enable").change(function() {
        if ($(this).attr('checked')) {
          $("#wrap-getlocations-term-markers").show();
        }
        else {
          $("#wrap-getlocations-term-markers").hide();
        }
      });

      if ($("#edit-getlocations-default-markermanagertype").val() == 1) {
        // markermanager
        $(".form-item-getlocations-default-usemarkermanager").show();
        $("#wrap-getlocations-clusteropts").hide();
      }
      else if ($("#edit-getlocations-default-markermanagertype").val() == 2) {
        // markerclusterer
        $(".form-item-getlocations-default-usemarkermanager").hide();
        $("#wrap-getlocations-clusteropts").show();
      }
      else {
        // none
        $(".form-item-getlocations-default-usemarkermanager").hide();
        $("#wrap-getlocations-clusteropts").hide();
      }
      $("#edit-getlocations-default-markermanagertype").change(function() {
        if ($(this).val() == 1) {
          // markermanager
          $(".form-item-getlocations-default-usemarkermanager").show();
          $("#wrap-getlocations-clusteropts").hide();
        }
        else if ($(this).val() == 2) {
          // markerclusterer
          $(".form-item-getlocations-default-usemarkermanager").hide();
          $("#wrap-getlocations-clusteropts").show();
        }
        else {
          // none
          $(".form-item-getlocations-default-usemarkermanager").hide();
          $("#wrap-getlocations-clusteropts").hide();
        }
      });

      if ($("#edit-getlocations-default-weather-use").attr('checked')) {
        $("#wrap-getlocations-weather").show();
      }
      else {
        $("#wrap-getlocations-weather").hide();
      }
      $("#edit-getlocations-default-weather-use").change(function() {
        if ($(this).attr('checked')) {
          $("#wrap-getlocations-weather").show();
        }
        else {
          $("#wrap-getlocations-weather").hide();
        }
      });

    }
  }

})(jQuery);
