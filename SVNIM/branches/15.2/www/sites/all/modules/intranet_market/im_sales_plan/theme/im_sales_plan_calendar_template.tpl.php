<?php
  define("UNIT_CELL_WIDTH", 23);
  define("UNIT_CELL_HEIGHT", 20);
  
  $national_height = UNIT_CELL_HEIGHT;
  $regional_height = UNIT_CELL_HEIGHT;
  $non_alimentare_height = UNIT_CELL_HEIGHT;
 
  $time_stamp = $begin_time;
  $national_nodes_processed_by_date = array();
  $regional_nodes_processed_by_date = array();
  $nonfood_nodes_processed_by_date = array();
  
  drupal_add_js(array('national_height' => UNIT_CELL_HEIGHT), 'setting');
  drupal_add_js(array('regional_height' => UNIT_CELL_HEIGHT), 'setting');
  drupal_add_js(array('nonfood_height' => UNIT_CELL_HEIGHT), 'setting');
  preg_match('/MSIE (.*?);/', $_SERVER['HTTP_USER_AGENT'], $matches);
  $ie = '';
  if (count($matches)>1){
    //Then we're using IE
    $version = $matches[1];
    switch(true){
      case ($version == 8):
        $ie = 'ie8';
        break;
  
      default:
        //You get the idea
    }
  }
  $days = array('Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun');
  //Append Previous Year days - which is there in 1st week
  for ($day = 0; $day < 7; $day++) {
    if(date('D', $time_stamp) == $days[0]) {
      break;
    }else{
      $time_stamp = strtotime('-1 day', $time_stamp);
    }
  }
?>
<div class="sp-watermark-confidentiel <?php print $ie;?>">Confidentiel</div>
<div class="sp-holiday-wrapper">
  <div class="sp-holiday-navigator"><?php $navigation_form = drupal_get_form('im_sales_plan_navigation_form');print render($navigation_form);?> </div>
  <div class="sp-holiday-calendar">
		<div class="sp-holiday-title-left">
			  <div class="school-holidays">
			    <div class="school-holidays-label"><?php print t('School holidays')?></div>
			    <div class="regions">
					  <div>A</div>
					  <div>B</div>
					  <div>C</div>
			    </div>
			  </div>
		      <div class="national" style="height:<?php print $national_height;?>px;"><?php print t('National')?></div>
		      <div class="regional" style="height:<?php print $regional_height;?>px;"><?php print t('Regional')?></div>
		      <div class="non-food" style="height:<?php print $non_alimentare_height;?>px;"><?php print t('NON ALIMENTAIRE')?></div>
		      <div id="holiday-pos-file" style="display:none;"><?php $file_year = date('Y', strtotime($_SESSION['date-end'])); if(isset($holiday_pos_file[$file_year])) print $holiday_pos_file[$file_year];?></div>
		</div>
		<div class="sp-jcarousel-exterior">
			  <ul id="holiday-carousel" class="jcarousel-skin-tango">
			  <?php for($week = $week_duration['week_beg']; $week <= $week_duration['week_end']; $week++) { ?>
			    <li class="week">
			   		<div class="week-header">
				      <div class="month-title"><?php print t(date('M', $time_stamp)) . '.';?></div>
				      <div class="week-title">S<?php print date('W', $time_stamp) . '/' . date('y', $time_stamp+60*60*24*3); ?> </div>
			      </div>
			      <?php
			      //Week Letter
			      $week_begin = $time_stamp;
			      print '<div class="day-title-wrapper">';
			      for($day = 1;$day < 8; $day++) {
			      	$today = (date('d/m/Y', $time_stamp) == date('d/m/Y')) ? 'today' : '';
			      	$trans_day = t(date('D', $time_stamp));
			      	print '<div class="day-title ' . $today . '">'. $trans_day[0] .'</div>';
			      	$time_stamp = strtotime('+1 day', $time_stamp); 
			      }
			      print '</div>';
			      //Date number
			      $time_stamp = $week_begin;
			      print '<div class="date-wrapper">';
			      for($day = 1;$day < 8; $day++) {
			      	$today = (date('d/m/Y', $time_stamp) == date('d/m/Y')) ? 'today' : '';
			      	print '<div class="day-date ' . $today . '">'. date('d', $time_stamp) .'</div>';
			      	$time_stamp = strtotime('+1 day', $time_stamp); 
			      }
			      print '</div>';
			      //Special Holiday
			      $time_stamp = $week_begin;
			      print '<div class="special-day-wrapper">';
			      for($day = 1;$day < 8; $day++) {
			      	$today = (date('d/m/Y', $time_stamp) == date('d/m/Y')) ? 'today' : '';
			      	if(in_array(date('d/m/Y',$time_stamp), array_keys($special_holidays))) {
			      	  print '<a href="" class="special-holiday selected ' . $today . '" id="'.$time_stamp.'"></a>';
			      	  $holiday_title = isset($special_holidays[date('d/m/Y',$time_stamp)]) ? $special_holidays[date('d/m/Y',$time_stamp)] : '';
			      	  print '<div id="title-'.$time_stamp.'" class="special-holiday-title" style="display:none;">' . $holiday_title . '</div>';
			      	}
			      	else{
			      	  print '<div class="special-holiday ' . $today . '"></div>';
			      	}
			      	$time_stamp = strtotime('+1 day', $time_stamp); 
			      }
			      print '</div>';
			      //Region Holiday - A
			      $time_stamp = $week_begin;
			      print '<div class="region-a-wrapper">';
			      for($day = 1;$day < 8; $day++) {
			      	$today = (date('d/m/Y', $time_stamp) == date('d/m/Y')) ? 'today' : '';
			      	if(in_array(date('d/m/Y',$time_stamp), $regional_holidays['zone_a'])) {
			      	  print '<div class="zone-a selected ' . $today . '"></div>';
			      	}
			      	else {
			      	  print '<div class="zone-a ' . $today . '"></div>';
			      	}
			      	$time_stamp = strtotime('+1 day', $time_stamp); 
			      }
			      print '</div>';
			      //Region Holiday - b
			      $time_stamp = $week_begin;
			      print '<div class="region-b-wrapper">';
			      for($day = 1;$day < 8; $day++) {
			      	$today = (date('d/m/Y', $time_stamp) == date('d/m/Y')) ? 'today' : '';
			      	if(in_array(date('d/m/Y',$time_stamp), $regional_holidays['zone_b'])) {
			      	  print '<div class="zone-b selected ' . $today . '"></div>';
			      	}
			      	else {
			      	  print '<div class="zone-b ' . $today . '"></div>';
			      	}
			      	$time_stamp = strtotime('+1 day', $time_stamp); 
			      }
			      print '</div>';
			      //Region Holiday - c
			      $time_stamp = $week_begin;
			      print '<div class="region-c-wrapper">';
			      for($day = 1;$day < 8; $day++) {
			      	$today = (date('d/m/Y', $time_stamp) == date('d/m/Y')) ? 'today' : '';
			      	if(in_array(date('d/m/Y',$time_stamp), $regional_holidays['zone_c'])) {
			      	  print '<div class="zone-c selected ' . $today . '"></div>';
			      	}
			      	else {
			      	  print '<div class="zone-c ' . $today . '"></div>';
			      	}
			      	$time_stamp = strtotime('+1 day', $time_stamp); 
			      }
			      print '</div>';
			      
			      //Loop-throgh Plan de vente (NATIONAL/REGIONAL/NON ALIMENTARE)
			      print '<div class="plan-de-vente">';		      

			      
						/**
						 * NATIONAL Sales Plan Data
						 */ 
	          print '<div class="pn-national-wrapper">';
	            $time_stamp = $week_begin;
              $time_stamp_tdy = $week_begin;
              for($day = 1; $day < 8; $day++) {
                if (date('d/m/Y', $time_stamp_tdy) == date('d/m/Y')) {
                  $day_text = date('D', $time_stamp_tdy); //Day style- Class   
                  print '<div class="pn-national-today '. $day_text .'"></div>';
                }
                $time_stamp_tdy = strtotime('+1 day', $time_stamp_tdy); 
              }
	            
							$time_stamp = $week_begin;
							$date_time = date('m/d/Y',$time_stamp);
							//Get days in the current week
							$this_week = date_range($date_time, date('m/d/Y', strtotime('+6 days', $time_stamp)));
							$this_week_nodes = array();
							
							//Get nodes which are begining in this Week of type 'nationale'
							foreach ($plan_de_vente as $nid => $sales_data) {
							  if($sales_data['type'] == 'nationale') {
							    $date_in_range = array_intersect($this_week, $sales_data['dates']);
							    if(in_array($sales_data['dates'][0], $this_week)) {
							      $this_week_nodes[$nid] = $sales_data;
							    }
							  }
							}
							
							//Process Nodes in this week
							$this_week_node_count = 0;
							while ($this_week_node_count != sizeof($this_week_nodes)) {
							  foreach ($this_week_nodes as $this_week_node) { 
							    $week_node_id = $this_week_node['nid']; //Node id
							    if (sizeof($national_nodes_processed_by_date) == 0) {
							      foreach ($this_week_node['dates'] as $node_date) { 
							      	//Save the node to the global node array 
							        $national_nodes_processed_by_date[] =  "1#$week_node_id:$node_date";         
							      }
							      $this_week_node_count++;
							    }
							    else {
							    	//Get the 'row' postion of the node
							      $row = check_date_in_proceesed_nodes($this_week_node['dates'][0], $national_nodes_processed_by_date);
							      $row = $row ? $row : 1;
							      
							      foreach ($this_week_node['dates'] as $node_date) {  
							      	//Save the node to the global node array
							        $national_nodes_processed_by_date[] =  "$row#$week_node_id:$node_date";        
							      } 
							      $this_week_node_count++;        
							    }  
							  }
							}
							
							//Sort the global node array
							asort($national_nodes_processed_by_date); 
							
							
							$row_count = get_nodes_processed_row_count($national_nodes_processed_by_date); //Total Rows in national type
							$national_wrapper_height = $row_count * UNIT_CELL_HEIGHT; //Height of national div
							if ($national_wrapper_height != 0) {
							 drupal_add_js(array('national_height' => $national_wrapper_height), 'setting');
							 setcookie('national_height', $national_wrapper_height, time()+3600, '/');
							}
							else{
								setcookie('national_height', UNIT_CELL_HEIGHT, time()+3600, '/');
							}
							for($row_processed = 1; $row_processed <= $row_count; $row_processed++){
							  print '<div class="pn-national">';
							  foreach($this_week_nodes as $show_node) {
							  	$day_text = date('D', strtotime($show_node['dates'][0])); //Day style- Class        
							  	$future  = (date('Y/m/d',  strtotime($show_node['dates'][0])) > date('Y/m/d')) ? ' future' : ''; //Future sales plan style- Class
                  $ongoing  = in_array(date('d-m-Y'), $show_node['dates']) ? ' ongoing' : ''; //Active sales plan style- Class					  	
                  $past  = (date('Y/m/d',  strtotime(end($show_node['dates']))) < date('Y/m/d')) ? ' past' : ''; //Finished sales plan style- Class 
                  if(strtotime("now") >= strtotime($show_node['plan_de_begin_date']) && strtotime("now") <= strtotime($show_node['plan_de_end_date'])){
								    $future = '';
								    $ongoing = ' ongoing';
								  }
                  $process_key = $row_processed.'#'.$show_node['nid'].':';
                  foreach ($national_nodes_processed_by_date as $data_item) {
                    $row_val = explode(':', $data_item);
                    if($process_key == $row_val[0].':') { //eg. 11#19: == 2#21:
						        	$item_width = (UNIT_CELL_WIDTH * sizeof($show_node['dates'])-2) . 'px';
						        	$salesplanduration = (strtotime($show_node['plan_de_end_date'])-strtotime($show_node['plan_de_begin_date']))/(60 * 60 * 24);
                      if(strlen($show_node['title'])>13 && $salesplanduration<7){
                    		$salesplan_title = substr($show_node['title'], 0, 13);
                    		$tooltiptitle    = $show_node['title'];              		
                    	}else{
                    		$salesplan_title = $show_node['title'];
                    		$tooltiptitle    = '';
                    	}
	                    print '<div class="national-title ' . $day_text . $ongoing . $future . $past . '" style="width:'. $item_width .'">' . l($salesplan_title, 'sales-plan/content/' . $show_node['nid'], array('attributes' => array('class' => array('content-link'),'title'=>''.$tooltiptitle.''))) . '</div>';
	                    break;
	                  }
                  }
							  }
							  print '</div>';
							}

            print '</div>'; //pn-national-wrapper end

            /**
             * REGIONAL Sales Plan Data
             */ 			      
			      $time_stamp = $week_begin;
			      print '<div class="pn-regional-wrapper">';
              $time_stamp_tdy = $week_begin;
              for($day = 1; $day < 8; $day++) {
                if (date('d/m/Y', $time_stamp_tdy) == date('d/m/Y')) {
                  $day_text = date('D', $time_stamp_tdy); //Day style- Class   
                  print '<div class="pn-regional-today '. $day_text .'"></div>';
                }
                $time_stamp_tdy = strtotime('+1 day', $time_stamp_tdy); 
              }
							
							$time_stamp = $week_begin;
							$date_time = date('m/d/Y',$time_stamp);
							//Get days in the current week
							$this_week_reg = date_range($date_time, date('m/d/Y', strtotime('+6 days', $time_stamp)));
							$this_week_reg_nodes = array();
							            
							//Get nodes which are begining in this Week of type 'regionale'
							foreach ($plan_de_vente as $nid => $sales_data) {
							  if($sales_data['type'] == 'regionale') {
							    $date_in_range = array_intersect($this_week_reg, $sales_data['dates']);
							    if(in_array($sales_data['dates'][0], $this_week_reg)) {
							      $this_week_reg_nodes[$nid] = $sales_data;
							    }
							  }
							}
							
							//Nodes in this week
							$this_week_reg_node_count = 0;
							while ($this_week_reg_node_count != sizeof($this_week_reg_nodes)) {
							  foreach ($this_week_reg_nodes as $this_week_reg_node) { 
							    $week_node_id = $this_week_reg_node['nid']; //Node id
							    if (sizeof($regional_nodes_processed_by_date) == 0) {
							      foreach ($this_week_reg_node['dates'] as $node_date) {  
							      	//Save the node to the global node array
							        $regional_nodes_processed_by_date[] =  "1#$week_node_id:$node_date";         
							      }
							      $this_week_reg_node_count++;
							    }
							    else {
							    	//Get the 'row' postion of the node
							      $row = check_date_in_proceesed_nodes($this_week_reg_node['dates'][0], $regional_nodes_processed_by_date);
							      $row = $row ? $row : 1;
							      
							      foreach ($this_week_reg_node['dates'] as $node_date) { 
							      	//Save the node to the global node array 
							        $regional_nodes_processed_by_date[] =  "$row#$week_node_id:$node_date";        
							      } 
							      $this_week_reg_node_count++;        
							    }  
							  }
							}
							
							//Sort the global node array
							asort($regional_nodes_processed_by_date); 
							
							$row_count = get_nodes_processed_row_count($regional_nodes_processed_by_date); //Total Rows in national type
              $regional_wrapper_height = $row_count * UNIT_CELL_HEIGHT; //Height of regional div
              if ($regional_wrapper_height != 0) {
                drupal_add_js(array('regional_height' => $regional_wrapper_height), 'setting');
                setcookie('regional_height', $regional_wrapper_height, time()+3600, '/');
              }
              else{
                setcookie('regional_height', UNIT_CELL_HEIGHT, time()+3600, '/');
              }
							for($row_processed = 1; $row_processed <= $row_count; $row_processed++){
							  print '<div class="pn-regional">';
							  foreach($this_week_reg_nodes as $show_node) {
                  $day_text = date('D', strtotime($show_node['dates'][0])); //Day style- Class   
                  $ongoing  = in_array(date('d-m-Y'), $show_node['dates']) ? ' ongoing' : ''; //Active sales plan style- Class              
                  $future  = (date('Y/m/d',  strtotime($show_node['dates'][0])) > date('Y/m/d')) ? ' future' : ''; //Future sales plan style- Class
                  $past  = (date('Y/m/d',  strtotime(end($show_node['dates']))) < date('Y/m/d')) ? ' past' : ''; //Finished sales plan style- Class 
							  	if(strtotime("now") >= strtotime($show_node['plan_de_begin_date']) && strtotime("now") <= strtotime($show_node['plan_de_end_date'])){
								    $future = '';
								    $ongoing = ' ongoing';
								  }
                  $process_key = $row_processed.'#'.$show_node['nid'].':';
                  foreach ($regional_nodes_processed_by_date as $data_item) {
                    $row_val = explode(':', $data_item);
                    if($process_key == $row_val[0].':') { //eg. 11#19: == 2#21:
                    	$salesplanduration = (strtotime($show_node['plan_de_end_date'])-strtotime($show_node['plan_de_begin_date']))/(60 * 60 * 24);
                    	if(strlen($show_node['title'])>13 && $salesplanduration<7){
                    		$salesplan_title = substr($show_node['title'], 0, 13);
                    		$tooltiptitle    = $show_node['title'];              		
                    	}else{
                    		$salesplan_title = $show_node['title'];
                    		$tooltiptitle    = '';
                    	}
						        	$item_width = (UNIT_CELL_WIDTH * sizeof($show_node['dates'])-2) . 'px';
				              print '<div class="regional-title ' . $day_text . $ongoing . $future . $past . '" style="width:'. $item_width .'">' . l($salesplan_title, 'sales-plan/content/' . $show_node['nid'], array('attributes' => array('class' => array('content-link'),'title'=>''.$tooltiptitle.''))) . '</div>';
				              break;
				            }
					        }
							  }
							  print '</div>';
							} 
			      
				    print '</div>'; //pn-regional-wrapper end				    
				    
            /**
             * NON ALIMENTARE Sales Plan Data
             */   
			      print '<div class="pn-non-food-wrapper">';
              $time_stamp_tdy = $week_begin;
              for($day = 1; $day < 8; $day++) {
                if (date('d/m/Y', $time_stamp_tdy) == date('d/m/Y')) {
                  $day_text = date('D', $time_stamp_tdy); //Day style- Class   
                  print '<div class="pn-non-alimenaire-today '. $day_text .'"></div>';
                }
                $time_stamp_tdy = strtotime('+1 day', $time_stamp_tdy); 
              }
			      
				      $time_stamp = $week_begin;
							$date_time = date('m/d/Y',$time_stamp);
							//Get days in the current week
							$this_week_nonfood = date_range($date_time, date('m/d/Y', strtotime('+6 days', $time_stamp)));
							$this_week_nonfood_nodes = array();
							            
							//Get nodes which are begining in this Week of type 'non_alimentare'
							foreach ($plan_de_vente as $nid => $sales_data) {
							  if($sales_data['type'] == 'non_alimentare') {
							    $date_in_range = array_intersect($this_week_nonfood, $sales_data['dates']);
							    if(in_array($sales_data['dates'][0], $this_week_nonfood)) {
							      $this_week_nonfood_nodes[$nid] = $sales_data;
							    }
							  }
							}
							
							//Nodes in this week
							$this_week_nonfood_node_count = 0;
							while ($this_week_nonfood_node_count != sizeof($this_week_nonfood_nodes)) {
							  foreach ($this_week_nonfood_nodes as $this_week_nonfood_node) { 
							    $week_node_id = $this_week_nonfood_node['nid']; //Node id
							    if (sizeof($nonfood_nodes_processed_by_date) == 0) {
							      foreach ($this_week_nonfood_node['dates'] as $node_date) {  
							      	//Save the node to the global node array
							        $nonfood_nodes_processed_by_date[] =  "1#$week_node_id:$node_date";         
							      }
							      $this_week_nonfood_node_count++;
							    }
							    else {
							    	//Get the 'row' postion of the node
							      $row = check_date_in_proceesed_nodes($this_week_nonfood_node['dates'][0], $nonfood_nodes_processed_by_date);
							      $row = $row ? $row : 1;
							      
							      foreach ($this_week_nonfood_node['dates'] as $node_date) {  
							      	//Save the node to the global node array
							        $nonfood_nodes_processed_by_date[] =  "$row#$week_node_id:$node_date";        
							      } 
							      $this_week_nonfood_node_count++;        
							    }  
							  }
							}
							
							//Sort the global node array
							asort($nonfood_nodes_processed_by_date); 
							
							$row_count = get_nodes_processed_row_count($nonfood_nodes_processed_by_date); //Total Rows in national type
              $nonfood_wrapper_height = $row_count * UNIT_CELL_HEIGHT; //Height of non-food div
              if ($nonfood_wrapper_height != 0) {
                drupal_add_js(array('nonfood_height' => $nonfood_wrapper_height), 'setting');
                setcookie('nonfood_height', $nonfood_wrapper_height, time()+3600, '/');
              }
              else{
                setcookie('nonfood_height', UNIT_CELL_HEIGHT, time()+3600, '/');
              }
							for($row_processed = 1; $row_processed <= $row_count; $row_processed++){
							  print '<div class="pn-non-alimenaire">';
							  foreach($this_week_nonfood_nodes as $show_node) {
                  $day_text = date('D', strtotime($show_node['dates'][0])); //Day style- Class        
                  $ongoing  = in_array(date('d-m-Y'), $show_node['dates']) ? ' ongoing' : ''; //Active sales plan style- Class              
                  $future  = (date('Y/m/d',  strtotime($show_node['dates'][0])) > date('Y/m/d')) ? ' future' : ''; //Future sales plan style- Class
                  $past  = (date('Y/m/d',  strtotime(end($show_node['dates']))) < date('Y/m/d')) ? ' past' : ''; //Finished sales plan style- Class 
							  	if(strtotime("now") >= strtotime($show_node['plan_de_begin_date']) && strtotime("now") <= strtotime($show_node['plan_de_end_date'])){
								    $future = '';
								    $ongoing = ' ongoing';
								  }
                  $process_key = $row_processed.'#'.$show_node['nid'].':';
                  foreach ($nonfood_nodes_processed_by_date as $data_item) {
                    $row_val = explode(':', $data_item);
                    if($process_key == $row_val[0].':') { //eg. 11#19: == 2#21:
                    	$item_width = (UNIT_CELL_WIDTH * sizeof($show_node['dates'])-2) . 'px';
                    	$salesplanduration = (strtotime($show_node['plan_de_end_date'])-strtotime($show_node['plan_de_begin_date']))/(60 * 60 * 24);
                      if(strlen($show_node['title'])>13 && $salesplanduration<7){
                    		$salesplan_title = substr($show_node['title'], 0, 13);
                    		$tooltiptitle    = $show_node['title'];              		
                    	}else{
                    		$salesplan_title = $show_node['title'];
                    		$tooltiptitle    = '';
                    	}
                      print '<div class="non-alimentare-title ' . $day_text . $ongoing . $future . $past . '" style="width:'. $item_width .'">' . l($salesplan_title, 'sales-plan/content/' . $show_node['nid'], array('attributes' => array('class' => array('content-link'),'title'=>''.$tooltiptitle.''))) . '</div>';
                      break;
                    }
                  }
							  }
							  print '</div>';
							} 
			      
            print '</div>'; //pn-non-food-wrapper end							
			      
			      $time_stamp = $week_begin;
			      $time_stamp = strtotime('+7 day', $time_stamp);
			      print '</div>';
			      ?>
			    </li>
			  <?php } ?> 
			  </ul>
	  </div>
  </div>
</div>
<a href="javascript:void(0)" class="jcarousel-control-prev"></a>&nbsp;&nbsp;
                <a href="javascript:void(0)" class="jcarousel-control-next"></a><div id="spinner" style="display:none;"></div>
<?php
?>