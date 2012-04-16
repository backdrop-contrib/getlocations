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






    }
  };
})(jQuery);

