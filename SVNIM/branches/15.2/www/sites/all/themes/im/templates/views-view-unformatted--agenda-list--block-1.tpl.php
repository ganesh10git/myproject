<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php
  drupal_add_js('jQuery(document).ready(function () { jQuery(".view-grouping-header").remove(); });', 'inline');
    
  if (!isset($_SESSION['row_set_counter']) && empty($_SESSION['row_set_counter'])) {
    $_SESSION['row_set_counter'] = 0;
  }
  else {
    $_SESSION['row_set_counter']++;
  }
  
  $info_set_class = '';
  if (empty($_SESSION['row_set_title'])) {
    $_SESSION['row_set_title'] = $title;
  }
  if ($_SESSION['row_set_title'] == "News") {
    $_SESSION['row_set_counter_flag'] = 4;
  }
  else {
    $_SESSION['row_set_counter_flag'] = 3;
  }
  if ($_SESSION['row_set_counter'] == $_SESSION['row_set_counter_flag']) {
    $info_set_class = "info-set-class";
  }
  //echo "<pre>"; print_r($classes_array); echo "</pre>";
  ?>
  <?php 
  foreach ($rows as $id => $row): ?>
    
      <?php print $row; ?>
    
  <?php endforeach; ?>