/**
 * @file
 * getlocations_admin.js
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations module admin
 * jquery stuff
 */
(function ($) {
  Backdrop.behaviors.getlocations_admin_gps = {
    attach: function() {
      // gps button
      if ($("input[id$=gps-button]").is('input')) {
        if ($("input[id$=gps-button]").prop('checked')) {
          $("#wrap-getlocations-gps-button").show();
        }
        else {
          $("#wrap-getlocations-gps-button").hide();
        }
        $("input[id$=gps-button]").change(function() {
          if ($(this).prop('checked')) {
            //$("#wrap-getlocations-gps-button").show();
            var cg = $(this);
            $("#wrap-getlocations-gps-button").slideDown({
              duration: 'fast',
              easing: 'linear',
              complete: function () {
                Backdrop.getlocations.divScrollIntoView(cg);
                cg.animating = false;
              }
            });
          }
          else {
            $("#wrap-getlocations-gps-button").hide();
          }
        });
      }
    }
  };
}(jQuery));
