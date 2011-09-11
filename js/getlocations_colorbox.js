
/**
 * @file
 * Javascript functions for getlocations module
 *
 * @author Bob Hutchinson http://drupal.org/user/52366
 * jquery stuff
*/
(function ($) {
  Drupal.behaviors.getlocations = function() {
    // check that colorbox is loaded
    if ((typeof($("a[rel='getlocationsbox']").colorbox) == 'function') && Drupal.settings.getlocations_colorbox.enable == 1) {
      $("a[rel='getlocationsbox']").colorbox({
        iframe: true,
        innerWidth: Drupal.settings.getlocations_colorbox.width,
        innerHeight: Drupal.settings.getlocations_colorbox.height
      });
    }
  }
})(jQuery);
