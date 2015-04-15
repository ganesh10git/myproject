<?php
//$form = $variables['output'];
?>
<div class="store-preference-popup-title"><?php  print drupal_render($form['up_page_header_title']); ?></div>
<div id="user-store-preference">
	<div class="store-preference-topsec">
		<span class="topsec-title"><?php  print drupal_render($form['up_page_title']); ?></span>
		 <div class="dcplus-store-stat">
		     <div class="dc-dr-cf">
		     		<span class="title"><?php  print drupal_render($form['do_title']); ?></span>
		     		<?php  print drupal_render($form['usp_do']); ?>
		      	<?php  print drupal_render($form['usp_drcf']); ?>
		     </div>
		     <div class="store-status">
		    	  <?php  print drupal_render($form['usp_store_status']); ?>
		     </div>
     </div>
     <div class="additional-criteria">
     <?php  print drupal_render($form['criteria_title']); ?>
	      <?php  print drupal_render($form['addtional_criteria_set']); ?>
	      <?php  print drupal_render($form['addtional_criteria_set']['usp_autocomplete_field']); ?>
	      <?php  print drupal_render($form['addtional_criteria_set']['usp_operator']); ?>
	      <?php  print drupal_render($form['addtional_criteria_set']['usp_autocomplete_value_text']); ?>
	      <?php  print drupal_render($form['addtional_criteria_set']['addtional_criteria']); ?>
	      <?php  print drupal_render($form['addtional_criteria_set']['usp_save']); ?>
      </div>
  </div>
  <div class="store-preference-bottomsec">   
      <div class="select-stores-options">
      	<?php  print drupal_render($form['usp_return_store']); ?>
      </div>
      <div class="reference-weather-sec" >
     		 <?php  print drupal_render($form['usp_weather']); ?>
      </div>
  </div>
  <div class="user-store-preference-submit-sec" >
	      <?php  print drupal_render($form['usp_cancel']); ?>
	      <?php  print drupal_render($form['usp_validate']); ?>
  </div>
  <div class= "user-preference"> <?php  print drupal_render_children($form); ?> </div>
</div>

    