<?php 
/**
 * template file Sales Plan Right side bar content
 */  
define("SALES_DATA_WIDTH", 37);
$nodes_processed_by_date = array(); 
$this_week_begin = $sales_plan_details[0]['this_week_begin']; //This week begin time
$this_week =  $sales_plan_details[0]['this_week']; //Get days in the current week
?>

<div class="sp-widget-detail" style="display:none;">

  <!-- Sales plan block title and week number -->
  <div class="sp-widget-header">
	  <div class="sp-widget-title"><?php print t('Sales plan')?></div>
	  <div class="sp-widget-week-title"><?php print t('Week') ?>&nbsp;<?php print $sales_plan_details[0]['this_week_no'] ?></div>
  </div>
  
  <!-- This Week days -->
  <div class="sp-widget-week">
  <?php 
    $week_begin_time = $this_week_begin;
	  for($day = 1; $day < 8; $day++) {
	  	$sep = '&nbsp; -';
	  	if ($day == 7) $sep = '';
			$today = (date('d/m/Y', $week_begin_time) == date('d/m/Y')) ? 'today' : '';
			$day_text = t(date('D', $week_begin_time));
			print '<div class="sp-widget-week-day ' . $today . '">'. $day_text[0] . ' ' . date('d', $week_begin_time) . $sep . '</div>';
			$week_begin_time += 60*60*24; 	  	
	  }  
  ?>
  </div>  

  <!-- Special holidays -->
  <div class="sp-widget-sp-holiday">
  <?php 
    $week_begin_time = $this_week_begin;
    for($day = 1; $day < 8; $day++) {
      $today = (date('d/m/Y', $week_begin_time) == date('d/m/Y')) ? 'today' : '';
      if(in_array(date('d/m/Y', $week_begin_time), $sales_plan_details[0]['special_holidays'])) {
        print '<div class="special-holiday selected ' . $today . '"></div>';
      } else {
        print '<div class="special-holiday ' . $today . '"></div>';
      }
      $week_begin_time += 60*60*24; 
    } 
  ?>
  </div>
  
	<!-- Region A holidays -->
	<div class="sp-widget-region-a">
	<?php 
    $week_begin_time = $this_week_begin;
		for($day = 1; $day < 8; $day++) {
			$today = (date('d/m/Y', $week_begin_time) == date('d/m/Y')) ? 'today' : '';
			if(in_array(date('d/m/Y', $week_begin_time), $sales_plan_details[0]['regional_holidays']['zone_a'])) {
			  print '<div class="zone-a selected ' . $today . '"></div>';
			} else {
				print '<div class="zone-a ' . $today . '"></div>';
			}
	    $week_begin_time += 60*60*24; 
		}	
  ?>
  </div>
  
  <!-- Region B holidays -->
  <div class="sp-widget-region-b">
  <?php 
    $week_begin_time = $this_week_begin;
    for($day = 1; $day < 8; $day++) {
    	$today = (date('d/m/Y', $week_begin_time) == date('d/m/Y')) ? 'today' : '';
      if(in_array(date('d/m/Y', $week_begin_time), $sales_plan_details[0]['regional_holidays']['zone_b'])) {
        print '<div class="zone-b selected ' . $today . '"></div>';
      }  else {
        print '<div class="zone-b ' . $today . '"></div>';
      }
      $week_begin_time += 60*60*24; 
    } 
  ?>
  </div>
  
  <!-- Region C holidays -->
  <div class="sp-widget-region-c">
  <?php 
    $week_begin_time = $this_week_begin;
    for($day = 1; $day < 8; $day++) {
    	$today = (date('d/m/Y', $week_begin_time) == date('d/m/Y')) ? 'today' : '';
      if(in_array(date('d/m/Y', $week_begin_time), $sales_plan_details[0]['regional_holidays']['zone_c'])) {
        print '<div class="zone-c selected ' . $today . '"></div>';
      } else {
        print '<div class="zone-c ' . $today . '"></div>';
      }
      $week_begin_time += 60*60*24; 
    } 
  ?>
  </div>
  
  <!-- Nodes -->
  <?php 
  //Get sales plan nodes
  $this_week_nodes = $sales_plan_details[0]['sales_plan_data'];

  //Process Nodes in this week
	$this_week_node_count = 0;
	while ($this_week_node_count != sizeof($this_week_nodes)) {
		foreach ($this_week_nodes as $this_week_node) { 
			$week_node_id = $this_week_node['nid']; //Node id
			if (sizeof($nodes_processed_by_date) == 0) {
				foreach ($this_week_node['dates'] as $node_date) { 
					//Save the node to the global node array 
					$nodes_processed_by_date[] =  "1#$week_node_id:$node_date";         
				}
				$this_week_node_count++;
			}
			else {
				//Get the 'row' postion of the node
				$row = check_date_in_proceesed_nodes($this_week_node['dates'][0], $nodes_processed_by_date);
				$row = $row ? $row : 1;				
				foreach ($this_week_node['dates'] as $node_date) {  
					//Save the node to the global node array
					$nodes_processed_by_date[] =  "$row#$week_node_id:$node_date";        
				} 
				$this_week_node_count++;        
			}  
		}
	}
	
	//Sort the global node array
	asort($nodes_processed_by_date);
  ?>
  <div class="sp-widget-data">
    <?php
     $time_now = date("Ymd");
     if(arg(2) == 'today' || arg(2) == $time_now) {
    ?>
      <div class="sp-today <?php print date("D") ?>"></div>
    <?php } ?>
	  <?php $row_count = get_nodes_processed_row_count($nodes_processed_by_date); //Total Rows in sales plan data ?>
	  <div class="sp-widget-node-data-wrapper">
	  <?php 
	  $widget_height = 0;
	  for($row_processed = 1; $row_processed <= $row_count; $row_processed++) {
	    print '<div class="sp-widget-node">';
	    $widget_height++;
	    foreach($this_week_nodes as $show_node) {	    		      
	      $process_key = $row_processed.'#'.$show_node['nid'].':';
	      foreach ($nodes_processed_by_date as $data_item) {
          $row_val = explode(':', $data_item);
          if($process_key == $row_val[0].':') { //eg. 11#19: == 2#21:   
            /** Get dates of the sales plan node in this week */
            $this_week_node_dates = array_intersect($this_week, $show_node['dates']);
            if (sizeof($this_week_node_dates) > 0) {
            	//Calculate width of this node
            	$item_width = (SALES_DATA_WIDTH * sizeof($this_week_node_dates)) . 'px'; 
              $day_class = '';
            	//If node begin date is within the week add day class
              if (in_array($show_node['dates'][0], $this_week)) {
                $day_class = date('D', strtotime($show_node['dates'][0])); //Day style- Class
              } 
              $ongoing  = in_array(date('d-m-Y'), $show_node['dates']) ? ' ongoing' : ''; //Active sales plan style- Class              
              $future  = (date('Y/m/d',  strtotime($show_node['dates'][0])) > date('Y/m/d')) ? ' future' : ''; //Future sales plan style- Class
              $past  = (date('Y/m/d',  strtotime(end($show_node['dates']))) < date('Y/m/d')) ? ' past' : ''; //Finished sales plan style- Class 
            }            
            print '<div class="sp-widget-node-title ' . $day_class . '" style="width:'. $item_width .'">';
            print l($show_node['title'], 'sales-plan/now/all', array('attributes' => array('class' => array('content-link'))));
            print '<div class="sp-widget-node-color-line ' . $ongoing . $future . $past . '"></div>';
            print '</div>';
            
            break;
	        }
	      }
	    }
	    print '</div>';
	  }
	  drupal_add_js(array('widget_height' => $widget_height), 'setting');
	  ?>
	  </div>
  </div>
  
  <!-- Color identifiers -->
  <div class="sp-widget-color-ids">
  	<div class="sp-widget-past"><span class="past-idnt">&nbsp;</span><?php print t('Past') ?></div>
    <div class="sp-widget-ongoing"><span class="ongoing-idnt">&nbsp;</span><?php print t('Ongoing') ?></div>
    <div class="sp-widget-future"><span class="future-idnt">&nbsp;</span><?php print t('Future') ?></div>
  </div>
  <div class="sp-widget-help"><p class="zoneA">A</p><p class="zoneB">B</p><p class="zoneC">C</p>&nbsp; <?php print t('School holidays') ?> </div>
</div>
