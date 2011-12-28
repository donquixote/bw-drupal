<?php

/**
 * @file
 * Display Suite bw_shout layout.
 */


// Wrap all regions in div with class.
foreach (array(
  'bottom', 'left', 'main',
) as $region_name) {
  $region = $$region_name;
  // Wrap the region, even if it's empty.
  ${'div_'. $region_name} = <<<EOT
<div class="bw_shout-$region_name">$region</div>
EOT;
  $regions[$region_name] = $region;
}

?>
<div class="bw_shout <?php print $classes;?> clearfix">

  <div class="bw_shout-middle-outer"><div class="bw_shout-middle">
    <?php print $div_main; ?>
    <?php print $div_bottom; ?>
  </div></div>

  <?php print $left; ?>
</div>
