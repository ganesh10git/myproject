<?php
/**
 * @file
 */
?>
<div class = "agenda-main" >
<?php foreach ($agenda as $key => $value) { ?>
<div calss = "calendar-day">
<?php print date('j M',$key); ?>
</div>
<div class= "list-day">
<?php if (!empty($value)) { 
for ($i =0 ; $i < count($value); $i++) {  
if (isset($value[$i]['title'])) {?>
<div id="<?php print $value[$i]['title']?>" class="content-hover"> 
<?php print $value[$i]['title']; ?></div>
<div id="tesaer_<?php print $value[$i]['title']?>" style ="display:none">TEst tets tet shghsdghhsdghs htegshghasg</div>
<?php 
 }
 }
 }
 }?>

</div>
</div>