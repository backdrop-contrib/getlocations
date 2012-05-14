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

      if ($("#edit-getlocations-search-defaults-method").val() == 'vocab') {
        $("#getlocations_search_defaults_vocab").show();
      }
      else {
        $("#getlocations_search_defaults_vocab").hide();
      }
      $("#edit-getlocations-search-defaults-method").change( function() {
        if ($(this).val() == 'vocab') {
          $("#getlocations_search_defaults_vocab").show();
        }
        else {
          $("#getlocations_search_defaults_vocab").hide();
        }
      });


      if ($("#edit-getlocations-search-defaults-markermanagertype").val() == 1) {
        // markermanager
        $(".form-item-getlocations-search-defaults-usemarkermanager").show();
        $("#wrap-getlocations-clusteropts").hide();
      }
      else if ($("#edit-getlocations-search-defaults-markermanagertype").val() == 2) {
        // markerclusterer
        $(".form-item-getlocations-search-defaults-usemarkermanager").hide();
        $("#wrap-getlocations-clusteropts").show();
      }
      else {
        // none
        $(".form-item-getlocations-search-defaults-usemarkermanager").hide();
        $("#wrap-getlocations-clusteropts").hide();
      }
      $("#edit-getlocations-search-defaults-markermanagertype").change(function() {
        if ($(this).val() == 1) {
          // markermanager
          $(".form-item-getlocations-search-defaults-usemarkermanager").show();
          $("#wrap-getlocations-clusteropts").hide();
        }
        else if ($(this).val() == 2) {
          // markerclusterer
          $(".form-item-getlocations-search-defaults-usemarkermanager").hide();
          $("#wrap-getlocations-clusteropts").show();
        }
        else {
          // none
          $(".form-item-getlocations-search-defaults-usemarkermanager").hide();
          $("#wrap-getlocations-clusteropts").hide();
        }
      });




    }
  };
})(jQuery);
