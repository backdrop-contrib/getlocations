
/**
 * @file
 * getlocations_colorbox.js
 * @author Bob Hutchinson http://backdrop.org/user/52366
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations module
 * jquery stuff
*/
(function ($) {
  Backdrop.behaviors.getlocations_colorbox = {
    attach: function() {
      // check that colorbox is loaded
      if ((typeof($("a[rel='getlocationsbox']").colorbox) == 'function') && typeof Backdrop.settings.getlocations_colorbox !== 'undefined' && Backdrop.settings.getlocations_colorbox.enable == 1) {
        $("a[rel='getlocationsbox']").colorbox({
          iframe: true,
          innerWidth: Backdrop.settings.getlocations_colorbox.width,
          innerHeight: Backdrop.settings.getlocations_colorbox.height
        });
      }
    }
  };
})(jQuery);
