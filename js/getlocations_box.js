
/**
 * @file
 * getlocations_box.js
 * @author Bob Hutchinson http://backdrop.org/user/52366
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations module in colorbox
 * jquery stuff
*/
(function ($) {

  Backdrop.behaviors.getlocations_box = {
    attach: function() {
      // hide the returnlinks in a box
      $(".getlocations_returnlink").hide();
    }
  };

})(jQuery);
