<?php

/**
 * @file
 * Display Suite bw_forum_post template.
 */

// bottom middle has two parts.
$bottom_middle = '';
foreach (array(
  'bottom_middle_left', 'bottom_middle_right'
) as $region_name) {
  $region = $$region_name;
  if ($region) {
    $bottom_middle .= <<<EOT
<div class="bw_forum_post-$region_name">$region</div>
EOT;
  }
}

// Wrap all regions in div with class.
foreach (array(
  'header_left', 'header_right',
  'left', 'middle',
  'bottom_left', 'bottom_middle',
  'comments_region',
) as $region_name) {
  $region = $$region_name;
  // Wrap the region, even if it's empty.
  ${'div_'. $region_name} = <<<EOT
<div class="bw_forum_post-$region_name">$region</div>
EOT;
  $regions[$region_name] = $region;
}

?>
<div class="bw_forum_post <?php print $classes;?> clearfix">

  <?php if ($header_left || $header_right): ?>
    <div class="bw_forum_post-header clearfix">
      <?php print $div_header_left; ?>
      <?php print $div_header_right; ?>
    </div>
  <?php endif; ?>

  <div class="bw_forum_post-main">
    <div class="bw_forum_post-middle-outer"><?php print $div_middle; ?></div>
    <?php print $div_left; ?>
  </div>

  <?php if ($bottom_left || $bottom_middle): ?>
    <div class="bw_forum_post-bottom clearfix">
      <div class="bw_forum_post-bottom_middle-outer">
        <?php print $div_bottom_middle; ?>
      </div>
      <?php print $div_bottom_left; ?>
    </div>
  <?php endif; ?>
</div>

<?php if ($comments_region): ?>
  <?php print $div_comments_region; ?>
<?php endif; ?>
