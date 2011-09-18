<?php
/**
 * @file getlocations-view-map.tpl.php
 * Default simple view template to display a list of rows as icons on a map.
 * Derived from views-view-unformatted.tpl.php
 * fed from function template_preprocess_getlocations_view_map
 *
 * @ingroup views_templates
 */
?>
<!-- getlocations-view-map.tpl -->
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<div id="getlocations_map_wrapper">
<?php print $map; ?>
</div>
<!-- /getlocations-view-map.tpl -->
