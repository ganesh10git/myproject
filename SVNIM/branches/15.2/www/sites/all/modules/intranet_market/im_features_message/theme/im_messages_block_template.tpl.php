<div class="messages-item-list">
	<div class="messages-title"> <?php print t('Infos'); ?></div>
	<ul id="carousel" class="jcarousel-skin-aqua">
		<?php $i = 1; $control = '';?>
		  <?php foreach($result as $message_data) :?>  
		    <?php 
		    $image_message = '';
		    if(!empty($message_data['message_image'])){
		      $mes_image = array(
		        'style_name'=> 'im_message_image',
		        'path' => $message_data['message_image'],
		        'title' => 'Message image',
		      );
		      $image_message = theme('image_style', $mes_image);
		    }
		    ?>
		    <li><?php print $image_message?><?php print $message_data['message_desc']?></li>
		  <?php 
		  $message_data['message_desc'] = html_entity_decode($message_data['message_desc']);
		  $message_data['message_desc'] = str_replace("&#039;", "\'", $message_data['message_desc']);		  
		  $control .= '<a href="#"  onclick="return xt_med(\'F\',\'1\',\'display::actu::'.substr(rawurlencode(rawurldecode($message_data['message_desc'])), 0, 100).'\',\'&x1='.$message_data['im_cuwa_x1'].'&x2='.$message_data['im_cuwa_x2'].'&x3='.$message_data['im_cuwa_x3'].'&x4='.$message_data['message_nid'].'&x5='.$message_data['im_cuwa_x5'].'\')">'.$i.'</a>';
		  $i++;
		  ?>
  		<?php endforeach;?>
 	</ul>
 	<div class="jcarousel-control"> <?php print $control;?></div>
</div>
