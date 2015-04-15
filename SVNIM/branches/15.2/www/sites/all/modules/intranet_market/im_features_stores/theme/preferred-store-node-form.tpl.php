<?php
/*
 * @file
 *
 * Template file for Preferred Store form.
 */

  print drupal_render($form['form_build_id']);
  print drupal_render($form['form_token']); 
  print drupal_render($form['form_id']);

?>
<div class="store-preference-popup-title"><?php  print drupal_render($form['preferred_page_header_title']); ?></div>
  <div id="user-store-preference">
    <div class="store-preference-topsec">
      <span class="topsec-title"><?php  print drupal_render($form['preferred_page_title']); ?></span>
      <div class="dcplus-store-stat">
        <div class="dc-dr-cf"><?php  print drupal_render($form['field_preferred_do_dr']); ?></div>
        <div class="store-status"><?php  print drupal_render($form['field_preferred_store_status']); ?></div>
      </div>
      <div class="additional-criteria"><?php  print drupal_render($form['field_preferred_criteria_set']); ?></div>
      <div class="store-preference-filter"> <?php  print drupal_render($form['preferred_filter']); ?></div>
      <div class="store-preference-reset"><?php  print drupal_render($form['preferred_reset']); ?></div>
   </div>
   <div class="store-preference-bottomsec">
   <div class="pointer-arrow"> </div>
     <div class="select-stores-checkbox-avl"><?php  print drupal_render($form['preferred_store_checkbox_avl']); ?></div>
     <div class="select-stores-checkbox-sel"><?php  print drupal_render($form['preferred_store_checkbox_sel']); ?></div>
     <div class="select-stores-options"><?php  print drupal_render($form['field_preferred_store_options']); ?></div>
     <div class="reference-weather-sec" ><?php  print drupal_render($form['field_preferred_store_choice']); ?></div>
   </div>
   <div class="user-store-preference-submit-sec" ><?php  print decode_entities(drupal_render($form['preferred_cancel']));  print drupal_render($form['actions']['submit']); ?>

<?php  /* fix for FATIM-637 */  
    if($_SESSION['messages']['error']){?>
    <div id="messages"><div class="messages error">
    <?php  if(isset($_SESSION['messages']['error'][0])){
    			print $_SESSION['messages']['error'][0];
   		  		unset($_SESSION['messages']['error']);
    }?>
   	</div></div></div>
<?php }?>
   <div class= "user-preference"> <?php //print drupal_render_children($form); ?> </div>
</div>

