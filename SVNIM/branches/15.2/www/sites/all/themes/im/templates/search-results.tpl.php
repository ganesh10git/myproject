<?php

/**
 * @file
 * Default theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_search_result(). This and
 * the child template are dependent to one another sharing the markup for
 * definition lists.
 *
 * Note that modules may implement their own search type and theme function
 * completely bypassing this template.
 *
 * Available variables:
 * - $search_results: All results as it is rendered through
 *   search-result.tpl.php
 * - $module: The machine-readable name of the module (tab) being searched, such
 *   as "node" or "user".
 *
 *
 * @see template_preprocess_search_results()
 */
?>
<?php
// Search filter form block
?>
<?php if ($search_results) { ?>
     <?php if (!isset($search_results_no_title)) { ?>
          <div class="page-search-title clearfix">
           <div id="results">
		   <?php if($num_results > 1) { 	
			$pural = "s";
		   }
		   else {
			$pural = "";
		   }
		   ?>
           <?php print html_entity_decode(t('@st_span@num_results@end_span result@pural found', array('@st_span' => '<span class="result">', '@end_span' => '</span>', '@pural' => $pural, '@num_results' => $num_results))); ?>
           </div>
          </div>
       <div class="subtitle clearfix">
        <div id="relative-pager">
          <span class="orange"><?php print t('Page');?>&nbsp;<?php print $relative_pager_beginning;?></span>&nbsp;<?php print t('on')?>&nbsp;<?php print $relative_pager_end;?>
        </div>
       </div>
     <?php } ?>

    <ol class="search-results <?php print $module; ?>-results">
   <?php if($num_results > 1) {   
      $pural = "s";
    }
    else {
      $pural = "";
    }
       ?>
    <div id="numresult">
     <div class="numresults" style="float:left">
    <?php print html_entity_decode(t('@st_span@num_results@end_span result@pural found', array('@st_span' => '<span class="result">', '@end_span' => '</span>', '@pural' => $pural, '@num_results' => $num_results))); ?>
     </div>
     <div class="numrows" style="float:right">
    <?php print t("Results to be shown per page");?> 
    <?php 
    $select_options = array("30" => "30", "40" => "40", "50" => "50", "60" => "60", $num_results . "all" => t("All"));
    ?>
    <select id="results_per_page" class="results_per_page">
    <?php foreach ($select_options as $key=>$option) {
    	if (!empty($_GET['f9']) && $_GET['f9'] == $key) {
        print '<option value="' . $key . '" selected="selected">' . $option . '</option>';
    	}
    	else {
    		print '<option value="' . $key . '">' . $option . '</option>';
    	}
    }
    ?>
    </select>
    </div>
    </div>
	<table><thead><tr><th class="media"><?php print t("Media");?></th><th  class="resume"><?php print t("Resume");?></th><th  class="published"><?php print $publish_sort;?></th></tr></thead>
	<tbody>
    <?php print $search_results; ?>
	</tbody>
	</table>
  </ol>
  <?php print $pager; ?>
<?php } else { ?>
  <h2><?php print t('Your search did not match any results');?></h2>
  <?php print t('Make sure all words are spelled correctly, try different keywords and search options.'); ?>
<?php } ?>