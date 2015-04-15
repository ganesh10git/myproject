<?php 
if (isset($agenda_week) && count($agenda_week) > 0) {
$title = ucfirst($agenda_week['type']);
$info_set_class = '';
$type = $agenda_week['type'];
if (isset($agenda_week['field_agenda_info'])) {
  $title = "Info";
  $type = "action-info";
  $info_set_class = "info-set-class";
}
drupal_add_js('jQuery(document).ready(function () { jQuery(".view-grouping-header").remove(); });', 'inline');
  if (empty($_SESSION['row_set_counter'])) {
  	$_SESSION['row_set_counter'] = 0;
  }
  $_SESSION['row_set_counter']++;
  if (empty($_SESSION['row_set_title'])) {
    $_SESSION['row_set_title'] = $title;
  } 
  $_SESSION['local_counter'] = 1;
  if (ucfirst($_SESSION['row_set_title']) != $title) {
  	$_SESSION['local_counter'] = 1;
  }
  else {
  	$_SESSION['local_counter']++;
  }
  $_SESSION['row_set_title'] = $title;
 ?>

<?php if (!empty($title)):
if ($_SESSION['local_counter'] == 1 || $_SESSION['row_set_counter'] == 1) {
	$agenda_week['views_row_class'] = 'views-row-'.($_SESSION['local_counter']).' views-row-odd views-row-first';
?>
  <div <?php print 'class = "agendatype-'.ucfirst($type) . ' ' . $info_set_class . '"'; ?>>
    <h2><?php print $title; ?></h2></div>
  <?php 
}
endif;

  //Initialize
  $agenda_week['teaser_title_class_name'] = isset($agenda_week['teaser_title_class_name']) ? $agenda_week['teaser_title_class_name'] : '';
  $agenda_week['teaser_corner_class_name'] = isset($agenda_week['teaser_corner_class_name']) ? $agenda_week['teaser_corner_class_name'] : '';
  $agenda_week['teaser_icon_class_name'] = isset($agenda_week['teaser_icon_class_name']) ? $agenda_week['teaser_icon_class_name'] : '';
  $agenda_week['image_class_name'] = isset($agenda_week['image_class_name']) ? $agenda_week['image_class_name'] : '';
  $agenda_week['views_row_class_style'] = isset($agenda_week['views_row_class_style']) ? $agenda_week['views_row_class_style'] : '';
  $agenda_week['teaser_corner_style'] = isset($agenda_week['teaser_corner_style']) ? $agenda_week['teaser_corner_style'] : '';
  $agenda_week['views_row_class'] = isset($agenda_week['views_row_class']) ? $agenda_week['views_row_class'] : '';

  $icon_color ='white';
  $department_color = !empty($agenda_week['color']) ? $agenda_week['color'] : '';
  $department_name =  !empty($agenda_week['name']) ? $agenda_week['name'] : '';
   
?>
    <div <?php print 'class = "agendatype-detail'.ucfirst($type) . ' ' . $info_set_class . '"'; ?>>
    <div <?php print 'class="' . $agenda_week['views_row_class'] . '"'; print $agenda_week['views_row_class_style'];?>>
  <div class = "<?php print $agenda_week['image_class_name']?>">
    <?php if($agenda_week['teaser_icon_class_name']) {?><div class="<?php print $agenda_week['teaser_icon_class_name']?>" style="color:<?php print $icon_color;?>"><span class="<?php print $type;?>-icon"></span></div> <?php  }?>
    <span class="<?php print $agenda_week['teaser_corner_class_name']?>" style="<?php print $agenda_week['teaser_corner_style']?>"></span>
    <?php if ($agenda_week['teaser_title_class_name']) { ?><p class="<?php print $agenda_week['teaser_title_class_name']?>" style="color:<?php print $department_color;?>"><?php print $department_name;?></p> <?php }?> 
</div>
<div class = "agenda-today-sec1">
 <?php $style = 'style="margin-left:110px"'; /* if(empty($agenda_week['teaser_icon_class_name'])) { $style = 'style="margin-left:110px"';  }*/?> <div class ="action_title" <?php if (!empty($style)) print $style;?>> <?php  print($agenda_week['title']);?> :</div>
  <div class ="action_body" <?php if (!empty($style)) print $style;?>><?php if(!empty($agenda_week['body'])){  print($agenda_week['body']); } ?> </div>
  <div class = <?php  if(!empty($agenda_week['attachment'])){ print "action_attachment"; }?> <?php if (!empty($style)) print $style;?> onclick="return xt_click(this, \'C\',\'1\',\'download::'.$type.'::'.str_replace(" ","_",$agenda_week['title']).'\',\'A\')">
     <?php if(!empty($agenda_week['attachment'])){print($agenda_week['attachment']);  }?>  </div>
</div>
  </div>
</div> 
<?php }?>