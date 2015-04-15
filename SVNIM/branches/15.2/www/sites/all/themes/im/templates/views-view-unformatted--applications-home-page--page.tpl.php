<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<div class="im-app-category-container">
<?php if (!empty($title)): ?>
  <h3 class="app-category-title"><?php print $title; ?></h3>
<?php endif; ?>
<?php 
$inc = 1;
foreach ($rows as $id => $row):  
//to check which button  is present add/remove.  
$exploded_class =array();$add_class_value='';$contains_add ='';
$exploded_class = explode('class="',$row);
  $add_class_value = end($exploded_class);
  $contains_add = strstr($add_class_value,"add");
  if($contains_add){
  	$add_class = "";
  }
  else {
  	$add_class = "remove-class";
  }
  if ($inc % 4 == 0) {
  	$fourth_box = 'last-cont';
  }
  else {
  	$fourth_box = '';
  }
  $inc++;
  ?>
	<div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .' '. 'single-app-container' .' '.  $fourth_box .' '.  $add_class .'"'; } ?>>
    <?php print $row; ?>
  </div>
<?php endforeach; ?>
</div>