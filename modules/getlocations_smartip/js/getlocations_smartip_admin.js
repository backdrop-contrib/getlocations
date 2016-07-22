/**
 * @file
 * getlocations_smartip.admin.js
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations_smartip module admin
 * jquery stuff
 */
(function ($) {
  Backdrop.behaviors.getlocations_admin_smartip = {
    attach: function() {
      // smartip button
      if ($("input[id$=smartip-button]").is('input')) {
        if ($("input[id$=smartip-button]").prop('checked')) {
          $("#wrap-getlocations-smartip-button").show();
        }
        else {
          $("#wrap-getlocations-smartip-button").hide();
        }
        $("input[id$=smartip-button]").change(function() {
          if ($(this).prop('checked')) {
            $("#wrap-getlocations-smartip-button").show();
          }
          else {
            $("#wrap-getlocations-smartip-button").hide();
          }
        });
      }
    }
  };
}(jQuery));
