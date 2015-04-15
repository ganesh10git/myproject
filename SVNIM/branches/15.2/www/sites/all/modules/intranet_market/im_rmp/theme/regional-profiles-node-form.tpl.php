<?php
/*
 * @file
 *
 * Template file for Regional Moderator Profile form.
 */
  print drupal_render($form['form_build_id']);
  print drupal_render($form['form_token']); 
  print drupal_render($form['form_id']);

?>
<div class="store-preference-popup-title"><?php  print drupal_render($form['profile_popup_header_title']); ?></div>
  <div id="user-store-preference">
	<div class="store-preference-bottomsec">
   		<div class="pointer-arrow"> </div>
     		<div class="select-stores-options"><?php  print drupal_render($form['field_regional_profile_options']); ?></div>
    </div>
   	<div class="user-store-preference-submit-sec" >
   	<?php  print drupal_render($form['rmp_cancel']); 
   	 	   print drupal_render($form['actions']['submit']); ?>
   </div>
   	<div class= "user-preference"><?php  //print drupal_render_children($form); ?></div>
</div>

