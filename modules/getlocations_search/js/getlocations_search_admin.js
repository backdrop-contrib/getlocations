/**
 * @file
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations_search admin
*/
(function ($) {

  Drupal.behaviors.getlocations_search_admin = {
    attach: function() {

      if ($("#edit-getlocations-search-defaults-method, #edit-getlocations-search-block-defaults-method").val() == 'vocab') {
        $("#getlocations_search_defaults_vocab").show();
      }
      else {
        $("#getlocations_search_defaults_vocab").hide();
      }
      $("#edit-getlocations-search-defaults-method, #edit-getlocations-search-block-defaults-method").change( function() {
        if ($(this).val() == 'vocab') {
          $("#getlocations_search_defaults_vocab").show();
        }
        else {
          $("#getlocations_search_defaults_vocab").hide();
        }
      });

      if ($("#edit-getlocations-search-defaults-restrict-by-country, #edit-getlocations-search-block-defaults-restrict-by-country").is('input')) {
        if ($("#edit-getlocations-search-defaults-restrict-by-country, #edit-getlocations-search-block-defaults-restrict-by-country").attr('checked')) {
          $("#getlocations_search_country").show();
        }
        else {
          $("#getlocations_search_country").hide();
        }
        $("#edit-getlocations-search-defaults-restrict-by-country, #edit-getlocations-search-block-defaults-restrict-by-country").change( function() {
          if ($("#edit-getlocations-search-defaults-restrict-by-country, #edit-getlocations-search-block-defaults-restrict-by-country").attr('checked')) {
            $("#getlocations_search_country").show();
          }
          else {
            $("#getlocations_search_country").hide();
          }
        });
      }

      if ($("#edit-getlocations-search-defaults-markermanagertype, #edit-getlocations-search-block-defaults-markermanagertype").val() == 1) {
        // markermanager
        $(".form-item-getlocations-search-defaults-usemarkermanager, .form-item-getlocations-search-block-defaults-usemarkermanager").show();
        $("#wrap-getlocations-clusteropts").hide();
      }
      else if ($("#edit-getlocations-search-defaults-markermanagertype, #edit-getlocations-search-block-defaults-markermanagertype").val() == 2) {
        // markerclusterer
        $(".form-item-getlocations-search-defaults-usemarkermanager, .form-item-getlocations-search-block-defaults-usemarkermanager").hide();
        $("#wrap-getlocations-clusteropts").show();
      }
      else {
        // none
        $(".form-item-getlocations-search-defaults-usemarkermanager, .form-item-getlocations-search-block-defaults-usemarkermanager").hide();
        $("#wrap-getlocations-clusteropts").hide();
      }
      $("#edit-getlocations-search-defaults-markermanagertype, #edit-getlocations-search-block-defaults-markermanagertype").change(function() {
        if ($(this).val() == 1) {
          // markermanager
          $(".form-item-getlocations-search-defaults-usemarkermanager, .form-item-getlocations-search-block-defaults-usemarkermanager").show();
          $("#wrap-getlocations-clusteropts").hide();
        }
        else if ($(this).val() == 2) {
          // markerclusterer
          $(".form-item-getlocations-search-defaults-usemarkermanager, .form-item-getlocations-search-block-defaults-usemarkermanager").hide();
          $("#wrap-getlocations-clusteropts").show();
        }
        else {
          // none
          $(".form-item-getlocations-search-defaults-usemarkermanager, .form-item-getlocations-search-block-defaults-usemarkermanager").hide();
          $("#wrap-getlocations-clusteropts").hide();
        }
      });

/////////////////////


/////////////////////


    }
  };
})(jQuery);
