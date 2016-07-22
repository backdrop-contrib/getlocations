<?php
/**
 * @file
 * getlocations-leaflet-view-map.tpl.php
 * @author Bob Hutchinson https://backdropcms.org/account/hutch
 * @copyright GNU GPL
 *
 * Default simple view template to display a list of rows.
 * Derived from views-view-unformatted.tpl.php
 *
 * @ingroup views_templates
 */
?>
<!-- getlocations-leaflet-view-map.tpl -->
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<div class="getlocations_leaflet_map_wrapper">
<?php print $map; ?>
</div>
<!-- /getlocations-leaflet-view-map.tpl -->
