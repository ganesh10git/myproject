<?php
$result_count = (isset($form['dmd_search_result']['#options'])&& is_array($form['dmd_search_result']['#options'])) ? sizeof($form['dmd_search_result']['#options']) : 0; 
?>
<div class="dmd-assignment-wrapper">
  <div class="assignment-store"><?php print drupal_render($form['dmd_store']);?></div>
  <div class="dmd-filter-form">
  	<div class="dmd-search-form-sec">
	    <div class="assignment-first-name"><?php print drupal_render($form['dmd_first_name']);?></div>
	    <div class="assignment-last-name"><?php print drupal_render($form['dmd_last_name']);?></div>
	    <div class="assignment-mail"><?php print drupal_render($form['dmd_employee_id']);?></div>
	    <div class="assignment-search"><?php print drupal_render($form['dmd_search']);?></div>
	    <div class="assignment-cancel"><?php print drupal_render($form['dmd_cancel']);?></div>
    </div>
    <div class="assignment-search-result-sec">
    	<div class="assignment-search-result-title"><?php print drupal_render($form['dmd_result_title']);?></div>
	    <div class="assignment-search-result"><?php print drupal_render($form['dmd_search_result']);?></div>
	    <div class="assignment-search-result-mail"><?php print drupal_render($form['dmd_search_result_mail']);?></div>
	    <div class="assignment-search-result-mail"><?php print drupal_render($form['dmd_search_result_uid']);?></div>
	    
	    <div class="dmd-date">
		    <div class="assignment-begin-date"><?php print drupal_render($form['dmd_begin_date']);?></div>
		    <div class="assignment-end-date"><?php print drupal_render($form['dmd_end_date']);?></div>
		    <div class="assignment-assign"><?php print drupal_render($form['dmd_assign']);?></div>
	    </div>
	    <div class="dmd-pager"><?php print drupal_render($form['dmd_result_pager']);?></div>
    </div>
    <?php print drupal_render_children($form) ?>
  </div>
  <div class="dmd-assigned-records-wrapper">
  <div class="assignment-store"><?php print t('Assigned & Past');?></div>
  <?php 
    $dmd_assignment = module_invoke("im_user",'block_view', "im_user_dmd_assigned");
    print render($dmd_assignment['content']);
  ?>
  </div>
</div>