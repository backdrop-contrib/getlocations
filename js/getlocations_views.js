
/**
 * @file
 * @author Bob Hutchinson http://drupal.org/user/52366
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations module in views using custom-content in infobubble/infowindow
 * jquery stuff
*/

(function ($) {

  Drupal.behaviors.getlocations_views = function() {

      if($('#edit-style-options-markeraction').val() == 1 || $('#edit-style-options-markeraction').val() == 2) {
        $('#wrap-custom-content-enable').show();

          if($('#edit-style-options-custom-content-enable').attr('checked')) {
            $('#wrap-custom-content-source').show();
          }
          else {
            $('#wrap-custom-content-source').hide();
          }
      }
      else {
        $('#wrap-custom-content-enable').hide();
        $('#wrap-custom-content-source').hide();
      }

      $("#edit-style-options-markeraction").change(function() {
        if($(this).val() == 1 || $(this).val() == 2) {
          $('#wrap-custom-content-enable').show();

          if($('#edit-style-options-custom-content-enable').attr('checked')) {
            $('#wrap-custom-content-source').show();
          }
          else {
            $('#wrap-custom-content-source').hide();
          }
        }
        else {
          $('#wrap-custom-content-enable').hide();
          $('#wrap-custom-content-source').hide();
        }
      });

      $("#edit-style-options-custom-content-enable").change(function() {
        if($('#edit-style-options-markeraction').val() == 1 || $('#edit-style-options-markeraction').val() == 2) {
            if($(this).attr('checked')) {
              $('#wrap-custom-content-source').show();
            }
            else {
              $('#wrap-custom-content-source').hide();
            }
        }
      });

  }

})(jQuery);

