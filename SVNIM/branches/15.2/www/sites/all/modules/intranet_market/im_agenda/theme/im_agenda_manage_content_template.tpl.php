<?php
 global $user;
?>

<div class="agenda-manage-content-wrapper">
  <div class="agenda-content-filter-wrapper">
    <div class="date-filter"><?php print drupal_render($form['agenda_date']);?></div>
    <div class="content-type-filter"><?php print drupal_render($form['agenda_type']);?></div>
    <div class="department-filter"><?php print drupal_render($form['agenda_department']);?></div>
    <div class="status-filter"><?php print drupal_render($form['agenda_status']);?></div>
    <div class="do-filter"><?php print drupal_render($form['agenda_do']);?></div>
    <div class="dr-cf-filter"><?php print drupal_render($form['agenda_dr_cf']);?></div>
    <div class="role-filter"><?php print drupal_render($form['agenda_roles']);?></div>
    <div class="search-filter"><?php print drupal_render($form['agenda_search']);?></div>
    <div class="search-submit"><?php print drupal_render_children($form) ?></div>
  </div>
  <div class="manage-agenda-content">
    <?php if(user_access('create action content')): ?>
    	<div class="add-action"><?php print l(t('Create Action'), 'node/add/action')?></div>
    <?php endif; ?>
    <?php if(user_access('create alert content')): ?>
      <div class="add-alert"><?php print l(t('Create Alert'), 'node/add/alert')?></div>
    <?php endif; ?>
    <?php if(user_access('create news content')): ?>
      <div class="add-news"><?php print l(t('Create News'), 'node/add/news')?></div>
    <?php endif; ?>
    <?php if(user_access('create benchmark content')): ?>
      <div class="add-benchmark"><?php print l(t('Create Benchmark'), 'node/add/benchmark')?></div>
    <?php endif; ?>
  </div>
  <div class="agenda-content-wrapper">
  <?php 
    $agenda_block = module_invoke("im_agenda",'block_view', "im_agenda_manage_content_block");
    print render($agenda_block['content']);
  ?>
  </div>
  
</div>