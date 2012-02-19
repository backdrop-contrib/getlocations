
/**
 * @file
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations_fields module admin
 * jquery gee whizzery
*/
(function ($) {
  Drupal.behaviors.getlocations_fields_admin = {
    attach: function() {

      // config page
      if ($("#edit-getlocations-fields-defaults-use-address").is('input')) {
        if ($("#edit-getlocations-fields-defaults-use-address").attr('checked')) {
          $("#wrap-input_address_width").show();
        }
        else {
          $("#wrap-input_address_width").hide();
        }
        $("#edit-getlocations-fields-defaults-use-address").change(function() {
          if ($(this).attr('checked')) {
            $("#wrap-input_address_width").show();
          }
          else {
            $("#wrap-input_address_width").hide();
          }
        });
      }

      // content-type config
      if ($("#edit-field-settings-use-address").is('input')) {
        if ($("#edit-field-settings-use-address").attr('checked')) {
          $("#wrap-input_address_width").show();
        }
        else {
          $("#wrap-input_address_width").hide();
        }
        $("#edit-field-settings-use-address").change(function() {
          if ($(this).attr('checked')) {
            $("#wrap-input_address_width").show();
          }
          else {
            $("#wrap-input_address_width").hide();
          }
        });
       }



    }
  }
})(jQuery);
