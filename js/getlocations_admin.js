
/**
 * @file
 * Javascript functions for getlocations module admin
 *
 * @author Bob Hutchinson http://drupal.org/user/52366
 * jquery stuff
*/
(function ($) {

  Drupal.behaviors.getdirections_admin = {
    attach: function() {

      if ($("#edit-getlocations-default-returnlink-page-enable").attr('checked')) {
        $("#wrap-page-link").show();
      }
      else {
        $("#wrap-page-link").hide();
      }
      $("#edit-getlocations-default-returnlink-page-enable").change(function() {
        if ($("#edit-getlocations-default-returnlink-page-enable").attr('checked')) {
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
        if ($("#edit-getlocations-default-returnlink-user-enable").attr('checked')) {
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
        if ($("#edit-getlocations-colorbox-enable").attr('checked')) {
          $("#wrap-getlocations-colorbox").show();
        }
        else {
          $("#wrap-getlocations-colorbox").hide();
        }
      });

    }
  }

})(jQuery);
