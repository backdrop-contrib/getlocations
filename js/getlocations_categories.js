
/**
 * @file
 * getlocations_categories.js
 * @author Bob Hutchinson http://backdrop.org/user/52366
 * @copyright GNU GPL
 *
 * Javascript functions for getlocations categories support
*/
(function ($) {
  Backdrop.behaviors.getlocations_categories = {
    attach: function() {

      function categoriesGetClicks(k, c, l) {
        var tgt = "#getlocations_toggle_" + c + '_' + k;
        if ($(tgt).is('input')) {
          $(tgt).click( function() {
            $.each(Backdrop.getlocations_markers[k].lids, function (lid, mark) {
              if (Backdrop.getlocations_markers[k].cat[lid] == c) {
                vis = mark.getVisible();
                if (vis) {
                  label = l + ' ' + Backdrop.t('On');
                  sv = false;
                  if (Backdrop.getlocations_settings[k].useclustermanager) {
                    Backdrop.getlocations_settings[k].cmgr.removeMarker(mark);
                  }
                }
                else {
                  label = l + ' ' + Backdrop.t('Off');
                  sv = true;
                  if (Backdrop.getlocations_settings[k].useclustermanager) {
                    Backdrop.getlocations_settings[k].cmgr.addMarker(mark);
                  }
                }
                mark.setVisible(sv);
                $(tgt).val(label);
              }
            });
          });
        }
      }

      $.each(Backdrop.settings.getlocations, function (key, settings) {
        // categories
        var cats = (settings.categories ? settings.categories : []);
        if (cats) {
          $.each(cats, function (cat, label) {
            categoriesGetClicks(key, cat, label);
          });
        }
      });

    }
  };
})(jQuery);
