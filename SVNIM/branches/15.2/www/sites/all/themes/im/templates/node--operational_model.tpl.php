<?php
/**
 * @file
 * Adaptivetheme implementation to display a node.
 *
 * Adaptivetheme variables:
 * AT Core sets special time and date variables for use in templates:
 * - $submitted: Submission information created from $name and $date during
 *   adaptivetheme_preprocess_node(), uses the $publication_date variable.
 * - $datetime: datetime stamp formatted correctly to ISO8601.
 * - $publication_date: publication date, formatted with time element and
 *   pubdate attribute.
 * - $datetime_updated: datetime stamp formatted correctly to ISO8601.
 * - $last_update: last updated date/time, formatted with time element and
 *   pubdate attribute.
 * - $custom_date_and_time: date time string used in $last_update.
 * - $header_attributes: attributes such as classes to apply to the header element.
 * - $footer_attributes: attributes such as classes to apply to the footer element.
 * - $links_attributes: attributes such as classes to apply to the nav element.
 * - $is_mobile: Bool, requires the Browscap module to return TRUE for mobile
 *   devices. Use to test for a mobile context.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 * @see adaptivetheme_preprocess_node()
 * @see adaptivetheme_process_node()
 */

/**
 * Hiding Content and Printing it Separately
 *
 * Use the hide() function to hide fields and other content, you can render it
 * later using the render() function. Install the Devel module and use
 * <?php print dsm($content); ?> to find variable names to hide() or render().
 */
/* 
 * Highlighted Procedure will be listed first in the selection queue. 
 */
drupal_add_js('jQuery(document).ready(function () {
 jQuery(".om-menu-sec ul li a").each(function(){
  if( jQuery(this).hasClass("active") ){
    jQuery(this).parent().addClass("active-li");
   }else{
    jQuery(this).parent().removeClass("active-li");
   }
});
jQuery(".om-menu-sec ul li.active-li").prependTo( ".om-menu-sec ul" );  });', 'inline');
/* 
 * map hidden after click on a case issue fixed. 
 */ 
if(arg(2) != 'tid' || (!empty($_GET['selected_code']) && $_GET['selected_code'] != '')) {
 drupal_add_js('jQuery(document).ready(function () {
  jQuery(".om-top-sec #selected-location").show();
  jQuery("#operation-model-locations").hide();
 });', 'inline');
}

$today_date = date('Y-m-d');
hide($content['comments']);
hide($content['links']);
$om_localtion_vocabulary = taxonomy_vocabulary_machine_name_load('operational_model_location');
$om_location_term_tree = taxonomy_get_tree($om_localtion_vocabulary->vid);
$tid = array();
$selected_location_name = '';
$selected_location_code = '';
$addselectedstrecode    = '';
$addstoresearchstringw  = '';
$selected_location_id = arg(2); 
$selected_location_tid = '';
$inc = 0;
$im_cuwa_x5 = '';
foreach ($om_location_term_tree as $key=>$terms) {
  $om_location_terms = taxonomy_term_load($terms->tid); 
  $field_location_code = field_get_items('taxonomy_term', $om_location_terms, 'field_om_location_code');
  $code = $field_location_code[0]['value'];
  $om_location_items[$code]['name'] = $om_location_terms->name;
  $om_location_items[$code]['tid'] = $om_location_terms->tid;
  if (empty($selected_location_id) && $inc == 0) {
    $selected_location_name = $om_location_terms->name;
    $im_cuwa_x5 = $om_location_terms->name;
    $selected_location_code = $code;
    $selected_location_tid = $terms->tid;
  }
  if (!empty($selected_location_id) && $terms->tid == $selected_location_id) {
    $selected_location_name = $om_location_terms->name;
    $im_cuwa_x5 = $om_location_terms->name;
    $selected_location_code = $code;
    $selected_location_tid = $terms->tid;
  }
  $inc++;
}
if (arg(2)) {
  $operation_model_locations_style = "";
  $operation_model_selected_locations_style = "display: none;";
}
else {
  $operation_model_locations_style = "display: none;";
  $operation_model_selected_locations_style = "";
}
$nid = arg(1);
$arg_tid = 0;

//Retrive the user store's tatus
$store_status = _get_user_store_status();
$store_status_join = '';
$store_status_condition = '';            
if(isset($store_status) && $store_status){
	$store_status_join = "LEFT JOIN field_data_field_om_status field_data_field_om_status ON node.nid = field_data_field_om_status.entity_id AND (field_data_field_om_status.entity_type = 'node' AND field_data_field_om_status.deleted = '0') ";
    $store_status_condition = " AND field_data_field_om_status.field_om_status_value = '".$store_status."'";
}

//Retrieve the user cadre status
$cadre_status = _get_user_cadre_status();
//enters the loop when we click on the Documentation in Header menu.
if (empty($nid)) {
	if($cadre_status != 'cadre' && (!in_array('content_manager_om',$user->roles) && !in_array('contributor_om',$user->roles) && !in_array('administrator',$user->roles) && !in_array('technical_director',$user->roles))){
      $sql = "SELECT node.title AS node_title, node.nid AS nid, count(node_view_count.nid) AS node_view_count_nid 
      		  FROM node node 
      		  LEFT JOIN users users_node ON node.uid = users_node.uid 
      		  LEFT JOIN field_data_field_om_publication_period field_data_field_om_publication_period ON node.nid = field_data_field_om_publication_period.entity_id AND (field_data_field_om_publication_period.entity_type = 'node' AND field_data_field_om_publication_period.deleted = '0') 
      		  INNER JOIN field_data_field_om_access field_data_field_om_access ON node.nid = field_data_field_om_access.entity_id AND (field_data_field_om_access.entity_type = 'node' AND field_data_field_om_access.deleted = '0') 
      		  LEFT JOIN node_view_count node_view_count ON node.nid = node_view_count.nid ";
			  if(!empty($store_status_join)){
              	$sql.=$store_status_join;
			  }	
      		  $sql.=" WHERE ((( (node.type IN  ('operational_model')) AND (node.status = '1') 
      		  AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') <= :today_date) 
      		  AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value2, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') >= :today_date) 
      		  AND (field_data_field_om_access.field_om_access_value = '1') ";
		      if(!empty($store_status_condition)){
              	$sql.=$store_status_condition;
			  }
      		  $sql.=" ))) group by node.nid ORDER BY node_view_count_nid desc LIMIT 1";
    }
  else{
    $sql = "SELECT node.title AS node_title, node.nid AS nid, count(node_view_count.nid) AS node_view_count_nid 
    		FROM  node node 
    		LEFT JOIN users users_node ON node.uid = users_node.uid 
    		LEFT JOIN field_data_field_om_publication_period field_data_field_om_publication_period ON node.nid = field_data_field_om_publication_period.entity_id AND (field_data_field_om_publication_period.entity_type = 'node' AND field_data_field_om_publication_period.deleted = '0') 
    		LEFT JOIN node_view_count node_view_count ON node.nid = node_view_count.nid "; 
    		if(!empty($store_status_join)){
              $sql.=$store_status_join;
		    }
    		$sql.=" WHERE ((( (node.type IN  ('operational_model')) AND (node.status = '1') 
    		AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') <= :today_date) 
    		AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value2, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') >= :today_date) ";
    		if(!empty($store_status_condition)){
              	$sql.=$store_status_condition;
			} 
    		$sql.=" ))) group by node.nid ORDER BY node_view_count_nid desc LIMIT 1";
  }
  $query = ($sql);
  $result = db_query($query, array(':today_date'=> $today_date, ':tid' => $arg_tid))->fetchAssoc();
  
  //$i = 1;
  $nid = $result['nid'];
  if ($arg_tid == 0) {
  	if(!empty($_GET['selected_code']) && $_GET['selected_code'] != ''){
     /*
      * changes done for UATIM-767 fix.
      */
      $newurlsearch = str_replace('//', '/'.$_SESSION['nodeid'].'/',request_uri());
      $missedstringquery = strpos($newurlsearch, '?'); 
      $appendalterambersonstring = '';
      if(is_numeric($missedstringquery) == TRUE) {
       $missedalterquerystringurl  = explode('?', $newurlsearch);
       $missedarguurl = explode('=', $missedalterquerystringurl[1]);
       $missedfirstargument = urldecode($missedarguurl[0]); 
       $missedfirstargumentvalue = urldecode($missedarguurl[1]);
       $stringamber = strpos($missedarguurl[1], '&');
       if(is_numeric($stringamber) == TRUE) {
        $missedalterambersonurl  = explode('&', $missedarguurl[1]);  
        $missedfirstargumentvalue = urldecode($missedalterambersonurl[0]);
        drupal_goto(substr($missedalterquerystringurl[0], 1), array('query' => array($missedfirstargument => $missedfirstargumentvalue, $missedalterambersonurl[1] => $missedarguurl[2])));
        unset($_SESSION['nodeid']);
       }
      }
      /*
       * end
       */
      exit;
  	}
    drupal_goto("modele-operationnel/" . $nid."/" . 'tid', array('query' => array('name'=>'documentation')));
    exit;
  }
}
//Executes this loop, on click of 'Location' in OM map, to find most view node in the particular location.
if (isset($_GET['js'])) {
	if($cadre_status != 'cadre' && (!in_array('content_manager_om',$user->roles) && !in_array('contributor_om',$user->roles) && !in_array('administrator',$user->roles) && !in_array('technical_director',$user->roles))){
      $sql = "SELECT node.title AS node_title, node.nid AS nid, count(node_view_count.nid) AS node_view_count_nid 
      		  FROM node node 
      		  LEFT JOIN users users_node ON node.uid = users_node.uid 
      		  LEFT JOIN field_data_field_om_publication_period field_data_field_om_publication_period ON node.nid = field_data_field_om_publication_period.entity_id AND (field_data_field_om_publication_period.entity_type = 'node' AND field_data_field_om_publication_period.deleted = '0') 
      		  INNER JOIN field_data_field_om_access field_data_field_om_access ON node.nid = field_data_field_om_access.entity_id AND (field_data_field_om_access.entity_type = 'node' AND field_data_field_om_access.deleted = '0') 
      		  LEFT JOIN field_data_field_om_location field_data_field_om_location ON node.nid = field_data_field_om_location.entity_id AND (field_data_field_om_location.entity_type = 'node' AND field_data_field_om_location.deleted = '0') 
      		  LEFT JOIN node_view_count node_view_count ON node.nid = node_view_count.nid ";
			  if(!empty($store_status_join)){
              	$sql.=$store_status_join;
			  }
      		  $sql.=" WHERE (((field_data_field_om_location.field_om_location_tid = :tid ) )
      		  AND(( (node.type IN  ('operational_model')) AND (node.status = '1') 
      		  AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') <= :today_date) 
      		  AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value2, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') >= :today_date) 
      		  AND (field_data_field_om_access.field_om_access_value = '1') ";
			  if(!empty($store_status_condition)){
              	$sql.=$store_status_condition;
			  }	
      		 $sql.=" ))) group by node.nid ORDER BY node_view_count_nid desc limit 1";
    }
  else {
    $sql = "SELECT node.title AS node_title, node.nid AS nid, count(node_view_count.nid) AS node_view_count_nid 
    		FROM  node node 
    		LEFT JOIN users users_node ON node.uid = users_node.uid 
    		LEFT JOIN field_data_field_om_publication_period field_data_field_om_publication_period ON node.nid = field_data_field_om_publication_period.entity_id AND (field_data_field_om_publication_period.entity_type = 'node' AND field_data_field_om_publication_period.deleted = '0') 
    		LEFT JOIN field_data_field_om_location field_data_field_om_location ON node.nid = field_data_field_om_location.entity_id AND (field_data_field_om_location.entity_type = 'node' AND field_data_field_om_location.deleted = '0') 
    		LEFT JOIN node_view_count node_view_count ON node.nid = node_view_count.nid ";
  			if(!empty($store_status_join)){
              	$sql.=$store_status_join;
			}
    		$sql.=" WHERE (((field_data_field_om_location.field_om_location_tid = :tid ) )
    				AND(( (node.type IN  ('operational_model')) AND (node.status = '1') 
    				AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') <= :today_date) 
    				AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value2, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') >= :today_date)";
  			if(!empty($store_status_condition)){
            	$sql.=$store_status_condition;
			} 
    		$sql.=" ))) group by node.nid ORDER BY node_view_count_nid desc limit 1";
  }
    $query = ($sql);
    $result = db_query($query, array(':today_date'=> $today_date, ':tid' => arg(2)))->fetchAssoc();
    if(!empty($result)){
      $nid = $result['nid'];
      drupal_goto("modele-operationnel/" . $nid."/" . arg(2));
    }
    else{
      drupal_goto("modele-operationnel/" . arg(1)."/" . arg(2));
    }
  }
//Execute this loop in node preview page.
if((arg(0) == 'node' || arg(0)== 'modele-operationnel') && is_numeric(arg(1)) && arg(2) == '') {
  //$node_taxo_tid_query = db_query("select field_om_location_tid  from field_data_field_om_location where entity_id = :nid",array(':nid'=> arg(1)))->fetchAssoc();
  $taxo_location_tid = $node->field_om_location[LANGUAGE_NONE][0]['tid'];
  drupal_goto("node/" . $nid."/" . $taxo_location_tid);
}
?>
<div id="operation-model-locations" style="<?php print $operation_model_locations_style?>">
  <div id="om-store-map">
    <div class="green-bed-left"></div>
    <div class="road1"></div>
    <div class="gray-box-left">
      <?php if(isset($om_location_items)) { ?>     
      <div class="quaiReception <?php if ($om_location_items['quaiReception']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['quaiReception']['tid']?>"><?php print $om_location_items['quaiReception']['name']?></div>
      <div class="drive <?php if ($om_location_items['drive']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['drive']['tid']?>"><?php print $om_location_items['drive']['name']?></div>
      <?php } ?>
    </div>
    <div class="road2"></div>
    <div class="gray-box-middle">
      <?php if(isset($om_location_items)) { ?>  
      <div class="top reserve <?php if ($om_location_items['reserve']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['reserve']['tid']?>"><?php print $om_location_items['reserve']['name']?></div>
      <?php } ?>
      <div class="bottom">
       <?php if(isset($om_location_items)) { ?> 
        <div class="blue-sec">
          <div class="charcuterie <?php if ($om_location_items['charcuterie']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['charcuterie']['tid']?>"><?php print $om_location_items['charcuterie']['name']?></div>
          <div class="fromage <?php if ($om_location_items['fromage']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['fromage']['tid']?>"><?php print $om_location_items['fromage']['name']?></div>
          <div class="boucherie <?php if ($om_location_items['boucherie']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['boucherie']['tid']?>"><?php print $om_location_items['boucherie']['name']?></div>
          <div class="poisson blue last <?php if ($om_location_items['poisson']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['poisson']['tid']?>"><?php print $om_location_items['poisson']['name']?></div>
        </div>
        <?php } ?>
        <?php if(isset($om_location_items)) { ?> 
        <div class="bottom-mid">
          <div class="nonAI <?php if ($om_location_items['nonAI']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['nonAI']['tid']?>"><?php print $om_location_items['nonAI']['name']?></div>
          <div  class="PGC <?php if ($om_location_items['PGC']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['PGC']['tid']?>"><?php print $om_location_items['PGC']['name']?></div>
          <div class="PVP <?php if ($om_location_items['PVP']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['PVP']['tid']?>"><?php print $om_location_items['PVP']['name']?></div>
          <div class="FLplantes <?php if ($om_location_items['FLplantes']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['FLplantes']['tid']?>"><?php print $om_location_items['FLplantes']['name']?></div>
        </div>
        <?php } ?>
        <?php if(isset($om_location_items)) { ?> 
        <div class="bottom-bottom">
          <div class="DAB <?php if ($om_location_items['DAB']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['DAB']['tid']?>"><?php print $om_location_items['DAB']['name']?></div>
          <div class="caisse <?php if ($om_location_items['caisse']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['caisse']['tid']?>"><?php print $om_location_items['caisse']['name']?></div>
          <div class="coffre <?php if ($om_location_items['coffre']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['coffre']['tid']?>"><?php print $om_location_items['coffre']['name']?></div>
          <div class="accueil <?php if ($om_location_items['accueil']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['accueil']['tid']?>"><?php print $om_location_items['accueil']['name']?></div>
        </div>
        <?php } ?>
      </div>
    </div>
    <?php if(isset($om_location_items)) { ?> 
    <div class="gray-box-bottom">
      <div class="carimg"><div class="parking <?php if ($om_location_items['parking']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['parking']['tid']?>"><?php print $om_location_items['parking']['name']?></div></div>
      <div  class="stationService <?php if ($om_location_items['stationService']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['stationService']['tid']?>"><?php print $om_location_items['stationService']['name']?></div>
    </div>
    <?php } ?>
    <?php if(isset($om_location_items)) { ?>   
    <div class="gray-box-right">
      <div class="administratif <?php if ($om_location_items['administratif']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['administratif']['tid']?>"><?php print $om_location_items['administratif']['name']?></div>
      <div class="informatique <?php if ($om_location_items['informatique']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['informatique']['tid']?>"><?php print $om_location_items['informatique']['name']?></div>
      <div class="gestionDesHommes <?php if ($om_location_items['gestionDesHommes']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['gestionDesHommes']['tid']?>"><?php print $om_location_items['gestionDesHommes']['name']?></div>
      <div class="actifsSecuriteMaintenance <?php if ($om_location_items['actifsSecuriteMaintenance']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['actifsSecuriteMaintenance']['tid']?>"><?php print $om_location_items['actifsSecuriteMaintenance']['name']?></div>
      <div class="qualiteDevDurable <?php if ($om_location_items['qualiteDevDurable']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['qualiteDevDurable']['tid']?>"><?php print $om_location_items['qualiteDevDurable']['name']?></div>
      <?php if (isset($om_location_items['Securite']['tid'])) {?>
        <div class="Securite <?php if ($om_location_items['Securite']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['Securite']['tid']?>"><?php print $om_location_items['Securite']['name']?></div>
      <?php }?>
      <div class="vieDansCite <?php if ($om_location_items['vieDansCite']['tid'] == $selected_location_tid) { print ' active'; }?>" id="<?php print $om_location_items['vieDansCite']['tid']?>"><?php print $om_location_items['vieDansCite']['name']?></div>
    </div>
    <?php } ?> 
    <div class="green-bed-right"></div>
    <div class="minimizer"></div>
  </div>
</div>
<div id="operational-model" class="node-<?php print $node->nid. " ". $classes; ?> clearfix"<?php print $attributes;  ?>">
  <div class="om-left-content">
  <?php $nid = arg(1);
            //Node preview page taxonomy term id is set.
            if (arg(2) != '' && (arg(0) == 'node') || arg(0) == 'modele-operationnel') {
              $selected_location_tid = arg(2);
            }
            else{
              $node_taxo_tid_query = db_query("select field_om_location_tid  from field_data_field_om_location where entity_id = :nid",array(':nid'=> $nid))->fetchAssoc();
              $selected_location_tid = $node_taxo_tid_query['field_om_location_tid'];
            }
            $title_search = '';
            if(isset($_GET['search'])){            	
//            	$search_text = _im_feature_manage_content_views_query_chars_support($_GET['search']);
                $search_text = $_GET['search'];
            	//$string_decode = decode_entities($search_text['string_decode']);
   				//$string_encode = decode_entities($search_text['string_encode']);
   				/*$string_decode = $search_text['string_decode'];
   				$string_encode = $search_text['string_encode'];*/
//   				$title_search = " AND (translate(lower(node.title), 'âãäåāăąèééêëēĕėęěìíîïìĩīĭóôõöōŏőùúûüũūŭů', 'aaaaaaaeeeeeeeeeeiiiiiiiiooooooouuuuuuu') ILIKE '%" . $string_decode . "%' OR translate(lower(node.title), 'aaaaaaaeeeeeeeeeeiiiiiiiiooooooouuuuuuu', 'âãäåāăąèééêëēĕėęěìíîïìĩīĭóôõöōŏőùúûüũūŭů') ILIKE '%" . $string_encode . "%')";
   				$title_search = " AND node.title LIKE  '%". $search_text ."%'";
            }
            
            //Left side filtered content is shown, when we select by location
            if(is_numeric(arg(2))) {
            	if($cadre_status == 'cadre' || (in_array('content_manager_om',$user->roles) || in_array('contributor_om',$user->roles) || in_array('administrator',$user->roles) || in_array('technical_director',$user->roles))){
                 $query = "SELECT node.title AS node_title, node.nid AS nid, count(node_view_count.nid) AS node_view_count_nid 
                 			FROM  node node LEFT JOIN users users_node ON node.uid = users_node.uid 
                 			LEFT JOIN field_data_field_om_publication_period field_data_field_om_publication_period ON node.nid = field_data_field_om_publication_period.entity_id AND (field_data_field_om_publication_period.entity_type = 'node' AND field_data_field_om_publication_period.deleted = '0') 
                 			LEFT JOIN field_data_field_om_location field_data_field_om_location ON node.nid = field_data_field_om_location.entity_id AND (field_data_field_om_location.entity_type = 'node' AND field_data_field_om_location.deleted = '0') 
                 			LEFT JOIN node_view_count node_view_count ON node.nid = node_view_count.nid
                 			LEFT JOIN field_data_field_node_archive field_data_field_node_archive ON node.nid = field_data_field_node_archive.entity_id AND (field_data_field_node_archive.entity_type = 'node' AND field_data_field_node_archive.deleted = '0') ";
                 			if(!empty($store_status_join)){
              					$query.=$store_status_join;
              				}
              				$query.=" WHERE (( (field_data_field_om_location.field_om_location_tid = :tid ) )
                 					  AND(( (node.type IN  ('operational_model')) 
                 					  AND (node.status = '1') 
                 					  AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') <= :today_date) 
                 					  AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value2, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') >= :today_date)
                 					  AND field_data_field_node_archive.field_node_archive_value = '0' ))";
                					  if(!empty($store_status_condition)){
              							$query.=$store_status_condition;
              						  }
	  		                 		  $query.= $title_search;
				                 	  $query.= ") group by node.nid ORDER BY node_view_count_nid desc";				                 	 
				                 	 
                }
            else{              
              $query = "SELECT node.title AS node_title, node.nid AS nid, count(node_view_count.nid) AS node_view_count_nid 
              			FROM  node node 
              			LEFT JOIN users users_node ON node.uid = users_node.uid 
              			LEFT JOIN field_data_field_om_publication_period field_data_field_om_publication_period ON node.nid = field_data_field_om_publication_period.entity_id 
              			AND (field_data_field_om_publication_period.entity_type = 'node' AND field_data_field_om_publication_period.deleted = '0') 
              			INNER JOIN field_data_field_om_access field_data_field_om_access ON node.nid = field_data_field_om_access.entity_id 
              			AND (field_data_field_om_access.entity_type = 'node' AND field_data_field_om_access.deleted = '0') 
              			LEFT JOIN field_data_field_om_location field_data_field_om_location ON node.nid = field_data_field_om_location.entity_id 
              			AND (field_data_field_om_location.entity_type = 'node' AND field_data_field_om_location.deleted = '0') 
              			LEFT JOIN node_view_count node_view_count ON node.nid = node_view_count.nid
              			LEFT JOIN field_data_field_node_archive field_data_field_node_archive ON node.nid = field_data_field_node_archive.entity_id AND (field_data_field_node_archive.entity_type = 'node' AND field_data_field_node_archive.deleted = '0') ";
              			if(!empty($store_status_join)){
              				$query.=$store_status_join;
              			}
              			$query.=" WHERE (( (field_data_field_om_location.field_om_location_tid = :tid ) )
              					AND(( (node.type IN  ('operational_model')) AND (node.status = '1') 
              					AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') <= :today_date) 
              					AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value2, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') >= :today_date) 
              					AND (field_data_field_om_access.field_om_access_value = '1')
              					AND field_data_field_node_archive.field_node_archive_value = '0' ))";
              			if(!empty($store_status_condition)){
              				$query.=$store_status_condition;
              			}
              	$query.= $title_search;
              	$query.= ") group by node.nid ORDER BY node_view_count_nid desc";
            }
            $view_block = '<div class="view-content">';
            $result_set  = db_query($query, array(':today_date'=> $today_date, ':tid'=>$selected_location_tid, ':nid' => $nid))->Fetchall();            
            }
            //Left side unfiltered content is shown, when we visit the page by header menu.
            else {
               if($cadre_status == 'cadre' || (in_array('content_manager_om',$user->roles) || in_array('contributor_om',$user->roles) || in_array('administrator',$user->roles) || in_array('technical_director',$user->roles))){
                 $query = "SELECT node.title AS node_title, node.nid AS nid, count(node_view_count.nid) AS node_view_count_nid 
                 			FROM  node node 
                 			LEFT JOIN users users_node ON node.uid = users_node.uid 
                 			LEFT JOIN field_data_field_om_publication_period field_data_field_om_publication_period ON node.nid = field_data_field_om_publication_period.entity_id AND (field_data_field_om_publication_period.entity_type = 'node' AND field_data_field_om_publication_period.deleted = '0') 
                 			LEFT JOIN node_view_count node_view_count ON node.nid = node_view_count.nid
                 			LEFT JOIN field_data_field_node_archive field_data_field_node_archive ON node.nid = field_data_field_node_archive.entity_id AND (field_data_field_node_archive.entity_type = 'node' AND field_data_field_node_archive.deleted = '0') ";
               				if(!empty($store_status_join)){
              					$query.=$store_status_join;
              				} 
                 			$query.=" WHERE ((( (node.type IN  ('operational_model')) 
                 			AND (node.status = '1') 
                 			AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') <= :today_date) 
                 			AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value2, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') >= :today_date)
                 			AND field_data_field_node_archive.field_node_archive_value = '0' ))";
               				if(!empty($store_status_condition)){
              					$query.=$store_status_condition;
              				}
                 	$query.= $title_search;		
                 	$query.=") group by node.nid ORDER BY node_view_count_nid desc";
               }
             else{
                $query = "SELECT node.title AS node_title, node.nid AS nid, count(node_view_count.nid) AS node_view_count_nid 
                		   FROM  node node 
                		   LEFT JOIN users users_node ON node.uid = users_node.uid 
                		   LEFT JOIN field_data_field_om_publication_period field_data_field_om_publication_period ON node.nid = field_data_field_om_publication_period.entity_id AND (field_data_field_om_publication_period.entity_type = 'node' AND field_data_field_om_publication_period.deleted = '0') 
                		   INNER JOIN field_data_field_om_access field_data_field_om_access ON node.nid = field_data_field_om_access.entity_id AND (field_data_field_om_access.entity_type = 'node' AND field_data_field_om_access.deleted = '0') 
                		   LEFT JOIN node_view_count node_view_count ON node.nid = node_view_count.nid
                		   LEFT JOIN field_data_field_node_archive field_data_field_node_archive ON node.nid = field_data_field_node_archive.entity_id AND (field_data_field_node_archive.entity_type = 'node' AND field_data_field_node_archive.deleted = '0') ";
             			   if(!empty($store_status_join)){
              				 $query.=$store_status_join;
              			   } 
                		   $query.=" WHERE ((( (node.type IN  ('operational_model')) 
                		   AND (node.status = '1') 
                		   AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') <= :today_date) 
                		   AND (TO_CHAR(TO_DATE(field_data_field_om_publication_period.field_om_publication_period_value2, 'FMYYYY-FMMM-FMDDTFMHH24:FMMI:FMSS'), 'YYYY-MM-DD') >= :today_date) 
                		   AND (field_data_field_om_access.field_om_access_value = '1')
                		   AND field_data_field_node_archive.field_node_archive_value = '0'))";
             			   if(!empty($store_status_condition)){
              				 $query.=$store_status_condition;
              			   }
                $query.= $title_search;
                $query.=") group by node.nid ORDER BY node_view_count_nid desc";
            }
            $view_block = '<div class="view-content">';
            $result_set = db_query($query,array(':today_date'=> $today_date,':nid' => $nid))->Fetchall();
            }
            $i = 1;
             $result_set_flag = '';
             $node_from_date = strtotime(substr($node->field_om_publication_period['und'][0]['value'], 0, 10));
             $node_to_date = strtotime(substr($node->field_om_publication_period['und'][0]['value2'], 0, 10));
             $today_from_date = strtotime(date('Y-m-d'));
             if(arg(2) == 'tid') {
              	$field_access_value = TRUE;
             	$user_store_status = '';
             	if($cadre_status != 'cadre'){
             		if((isset($node->field_om_access['und'][0]['value']) && $node->field_om_access['und'][0]['value']=='0') && (!in_array('content_manager_om',$user->roles) && !in_array('contributor_om',$user->roles) && !in_array('administrator',$user->roles) && !in_array('technical_director',$user->roles))){
             			$field_access_value = FALSE;
             		}else{
             			$field_access_value = TRUE;
             		}
             	}
             	$field_om_status = 0;
             	if(isset($store_status) && $store_status){
	             	foreach($node->field_om_status['und'] as $status_magasin){
	             		if($store_status == $status_magasin['value']){
	             			$field_om_status++;
	             		}
	             	}
             	}
             	
               	if($node->type == 'operational_model' && $node->status == '1' && $field_access_value && $node_from_date<=$today_from_date && $node_to_date>=$today_date){
             		if(isset($store_status) && $store_status){
             			if($field_om_status == 1){
             				$result_set_flag = '1';
             			}else{
             				$result_set_flag = '';
             			}
             		}else{
              			$result_set_flag = '1';
             		}
              	}else{
              		$result_set_flag = '';
              	}
             }
             else{
             	//If Back Office user, display the content whether it is published or not 
             	if(in_array('content_manager_om',$user->roles) || in_array('contributor_om',$user->roles) || in_array('administrator',$user->roles) || in_array('technical_director',$user->roles)){
             		$tid_condition = '';
             		if(is_numeric(arg(2))) {
             			$tid_condition = " AND field_data_field_om_location.field_om_location_tid = ".arg(2);
             		}
	            	$query = "SELECT node.title AS node_title, node.nid AS nid
	                 			FROM  node node LEFT JOIN users users_node ON node.uid = users_node.uid 
	                 			LEFT JOIN field_data_field_om_publication_period field_data_field_om_publication_period ON node.nid = field_data_field_om_publication_period.entity_id AND (field_data_field_om_publication_period.entity_type = 'node' AND field_data_field_om_publication_period.deleted = '0') 
	                 			LEFT JOIN field_data_field_om_location field_data_field_om_location ON node.nid = field_data_field_om_location.entity_id AND (field_data_field_om_location.entity_type = 'node' AND field_data_field_om_location.deleted = '0') 
	                 			LEFT JOIN field_data_field_node_archive field_data_field_node_archive ON node.nid = field_data_field_node_archive.entity_id AND (field_data_field_node_archive.entity_type = 'node' AND field_data_field_node_archive.deleted = '0')  
	                 			WHERE (node.nid = :nid ";
	            			 if(!empty($tid_condition)){
	            				$query.=$tid_condition;
	            			 }
	                 		$query.=")";
	            	$result_set_flag = db_query($query, array(':nid' => $nid))->Fetchall();
	            }else{
	             	$field_access_value = TRUE;
	             	$user_store_status = '';
	             	if($cadre_status != 'cadre'){
	             		if(isset($node->field_om_access['und'][0]['value']) && $node->field_om_access['und'][0]['value']=='0' && (!in_array('content_manager_om',$user->roles) && !in_array('contributor_om',$user->roles) && !in_array('administrator',$user->roles) && !in_array('technical_director',$user->roles))){
	             			$field_access_value = FALSE;
	             		}else{
	             			$field_access_value = TRUE;
	             		}
	             	}
	             	$field_om_location_id = 0;
	             	foreach($node->field_om_location['und'] as $location_id){
	             		if($selected_location_tid == $location_id['tid']){
	             			$field_om_location_id++;
	             		}
	             	}
		            $field_om_status = 0;
	             	if(isset($store_status) && $store_status){
		             	foreach($node->field_om_status['und'] as $status_magasin){
		             		if($store_status == $status_magasin['value']){
		             			$field_om_status++;
		             		}
		             	}
	             	}
	              	if($node->type == 'operational_model' && $node->status == '1' && $field_om_location_id == 1 && $field_access_value && $node_from_date<=$today_from_date && $node_to_date>=$today_date){
		              	if(isset($store_status) && $store_status){
	             			if($field_om_status == 1){
	             				$result_set_flag = '1';
	             			}else{
	             				$result_set_flag = '';
	             			}
	             		}else{
	              			$result_set_flag = '1';
	             		}
              		}else{
              			$result_set_flag = '';
              		}
	             }
	        }
	        if (!empty($result_set_flag)) {
            ?>
    <div class="om-left-sec">
        <div class="om-top-sec">
            <div class="<?php print $selected_location_code;?>" id="selected-location" style="<?php print $operation_model_selected_locations_style?>"><div class="ic-img"></div><?php print strtoupper($selected_location_name);?></div>
            <div class="om-search-sec">
				<?php print @render(drupal_get_form('_om_search_form'));?>
             </div>
            
        </div>
        <div class="om-menu-sec">
        
            <div class="om-selected"><?php print t("Procedures of the selected area");?></div>
            <ul>
          <?php
            foreach($result_set as $results) {
              if($i == 1) {
                $first_node_title = $results->node_title;
                $first_node_nid = $results->nid;
                $i++;
              } 
              $view_block .= '</div>
              <div class="views-field views-field-title">
              <span class="field-content">
              	<a href="/node/'.$results->nid.'">'.$results->node_title.'</a></span></div>
              </div>';
            }
            $view_block .='</div>';
            //$view_block = $view->preview("block_1", array(arg(0), $nid, $selected_location_tid));
            $block_content = strip_tags($view_block, '<a>');
            $block_content = explode("\n", $block_content);
            $node_nid_cuwa_value = '';
            $node_title_cuwa = '';
            foreach($block_content as $keyval=>$node_title) {
              $node_title = trim($node_title);
              if (!empty($node_title)) {
                $exploded_title = explode(">",$node_title);
                if(isset($exploded_title)) {
                  $node_nid_cuwa_array= explode('/',$exploded_title[0]);
                  if(isset($node_nid_cuwa_array[2])) {
                    $node_nid_cuwa_value = substr($node_nid_cuwa_array[2],0,-1);
                  }
                  if(!empty($exploded_title[1])) {
                      $node_title_cuwa = drupal_html_to_text($exploded_title[1], $allowed_tags = NULL);
                  }
                  $node_title_cuwa = rawurlencode(rawurldecode($node_title_cuwa));
                 }
            ?>
                <li><?php 
                //cuwa page
                $im_cuwa_x1 = '';
                $im_cuwa_x2 = '';
                $im_cuwa_x3 = '';
               if (isset($_SESSION['ldap_user_role'])) {
                 if ($_SESSION['ldap_user_role'] == 'store_director'){
                   $im_cuwa_x1 = 1;
                   $im_cuwa_x2 = 1;
                 }
                 if ($_SESSION['ldap_user_role'] == 'store_manager') {
                    $im_cuwa_x1 = 2;
                    $im_cuwa_x2 = 1;
                 }
                 if ($_SESSION['ldap_user_role'] == 'store_employee') {
                   $im_cuwa_x1 = 3;
                   $im_cuwa_x2 = 1;
                 }
                 if ($_SESSION['ldap_user_role'] == 'salarie_siege') {
                   $im_cuwa_x2 = 2;
                 }
                 if ($_SESSION['ldap_user_role'] == 'store_director_trainee') {
                   $im_cuwa_x1 = 4;
                 }
                 if ($_SESSION['ldap_user_role'] == 'store_manager_trainee') {
                   $im_cuwa_x1 = 5;
                 }
               }
               if(isset($user->uid)) {
                 $im_cuwa_x3 = $user->uid;
               }
                $arg2 = $selected_location_tid;
                if (!empty($arg2)) {
                	$class_clicked = '';
                	if(is_numeric(arg(1)) && $node_nid_cuwa_value == arg(1)) {
                    $class_clicked = "active";
                	}
                  $addstoresearchstring = empty($_GET['search']) ? '' : "?search=".$_GET['search'];	
                  $node_title = str_replace('">', '/' . $selected_location_tid .$addstoresearchstring.'"'.'onclick = "return xt_click(this,\'C\',\'2\',\'dispaly::documentation::'.$node_title_cuwa.' \',\'&x1='.$im_cuwa_x1.'&x2='.$im_cuwa_x2.'&x3='.$im_cuwa_x3.'&x4='.$node_nid_cuwa_value.'&x5='.$im_cuwa_x5.'\')" class ="'.$class_clicked.'">', $node_title);
                  if (arg(0) == "modele-operationnel") {
                    $node_title = str_replace('node/', 'modele-operationnel/', $node_title);
                  }
                  print $node_title;
                } 
                else {
                  if (arg(0) == "modele-operationnel") {
                    $node_title = str_replace('node/', 'modele-operationnel/' . '"'.'onclick = "return xt_click(this,\'C\',\'2\',\'dispaly::documentation::'.$node_title_cuwa.' \',\'&x1='.$im_cuwa_x1.'&x2='.$im_cuwa_x2.'&x3='.$im_cuwa_x3.'&x4='.$node_nid_cuwa_value.'&x5='.$im_cuwa_x5.'\')"', $node_title);
                  } 
                  print $node_title;
                }
                ?>
                </li>
            <?php }}  ?>
            </ul>
        </div>
    </div>
  </div> 
    <div class="om-right-sec">
        <div class="white-boxes">
    <a href=<?php print $_SERVER['REQUEST_URI'];?> class="om-print" onclick = <?php print "return xt_click(this, 'C','2','print::documentation::".str_replace('','_',rawurlencode(rawurldecode($title)))."','A')".'"'?> > <?php print t("Print procedure");?></a>
    <?php 
     /* 
     * Implemented redirection for the first result when user searching procedure.
     * */
    global $base_url;
    $appendsymbol = '';
   if($_GET['type'] == 'search') {
   	 if($_GET['selected_code']) {
       $appendstring = $_GET['selected_code'];
      }else {
       $appendstring = 'tid';
      }
      $addselectedstrecode = isset($_GET['selected_code']) ? "selected_code=".$_GET['selected_code'] : '';
      $addstoresearchstringw = empty($_GET['search']) ? '' : "?search=".$_GET['search'];
      if(empty($addstoresearchstringw)) { $appendsymbol = '?'; }
      if(empty($addselectedstrecode)) { $appendsymbol = ''; }
      if($addstoresearchstringw != '' && $addselectedstrecode != '') { print 'set '; $appendsymbol ='&'; }
      $first_url = urldecode($base_url.'/modele-operationnel/'.$first_node_nid.'/'.$appendstring.$addstoresearchstringw.$appendsymbol.$addselectedstrecode);
      drupal_goto($first_url);
     } 
    $tmp=''; $tmp = strip_tags(render($content['field_om_access'])); if (!empty($tmp)): ?>
          <div class="om-right-block">
           <h3 class="om-right-title"><?php print t("Acteurs");?></h3>
           <div class="om-right-content om-access"><?php 
           //$field_om_access_value = strtolower(render($content['field_om_access']));
           $list_of_actuers = '';
           if(isset($content['field_om_actuers']) && !empty($content['field_om_actuers']) ){
             $actuers = $content['field_om_actuers']['#object']->field_om_actuers['und'];
             foreach($actuers as $key => $value){
               $list_of_actuers .= $value['taxonomy_term']->name . ", ";
             }
             $list_of_actuers = trim($list_of_actuers, " ,");
           }
           print $list_of_actuers;
           //print render($content['field_om_actuers']);
          ?></div>
          </div>
    <?php endif; ?>
    <?php $tmp=''; $tmp = strip_tags(render($content['field_om_duration'])); if (!empty($tmp)): ?>
            <div class="om-right-block">
             <h3 class="om-right-title"><?php print t("Duration estimate");?></h3>
             <div class="om-right-content duration"><?php print render($content['field_om_duration']);?></div>
            </div>
            <?php endif; ?>
            <?php $tmp=''; $tmp = strip_tags(render($content['field_om_material'])); if (!empty($tmp)): ?>
              <div class="om-right-block">
             <h3 class="om-right-title"><?php print t("Material Necessary");?></h3>
             <div class="om-right-content material"><?php print render($content['field_om_material']);?></div>
            </div>
            <?php endif; ?>
            <?php  global $user;
             if(isset($node->uid)){
                $uid = $node->uid;
                $user_fields = user_load($node->uid);
                $fullname = '';
                if (isset($user_fields->field_full_name['und'][0]['value'])) {
                          $fullname = $user_fields->field_full_name['und'][0]['value'];
                }
             } 
                   ?>
            <?php //if (!empty($fullname)): ?>
<!--                 <div class="om-right-block"> -->
<!--             <h3 class="om-right-title"><?php //print t("Auters the procedure");?></h3>-->
<!--             <div class="om-right-content actuers"><?php //print $fullname;?></div>-->
<!--            </div>-->
            <?php //endif; ?>
            <?php //$tmp=''; $tmp = strip_tags(render($content['field_om_experts'])); if (!empty($tmp)): ?>
<!--              <div class="om-right-block">-->
<!--             <h3 class="om-right-title"><?php //print t("Experts the procedure");?></h3>-->
<!--             <div class="om-right-content experts"><?php //print render($content['field_om_experts']);?></div>-->
<!--            </div>-->
            <?php //endif; ?>
            <?php //$tmp=''; $tmp = strip_tags(render($content['field_om_publication_period'])); if (!empty($tmp)): ?>
<!--            <div class="om-right-block">-->
<!--             <h3 class="om-right-title"><?php //print t("End date of the validity");?></h3>-->
<!--             <div class="om-right-content end-date">--><?php
              //$end_date = strtotime(substr($content['field_om_publication_period']['#items'][0]['value2'], 0, 10)); 
              //print $end_date = format_date($end_date,'custom','l j F Y');?>
<!--            </div></div>-->
            <?php //endif; ?>
            <?php //$tmp=''; $tmp = strip_tags(render($content['field_om_status'])); if (!empty($tmp)): ?>
<!--            <div class="om-right-block">-->
<!--             <h3 class="om-right-title"><?php //print t("Ciblage");?></h3>-->
<!--             <div class="om-right-content om-status"><?php //print render($content['field_om_status']);?></div>-->
<!--            </div>-->
            <?php //endif; ?>
            <?php $tmp=''; $tmp = strip_tags(render($content['field_om_attachments'])); if (!empty($tmp)): ?>
            <div class="om-right-block">
             <h3 class="om-right-title"><?php print t("Documents");?></h3>
             <div class="om-right-content om-attachments">
             <div class="field field-name-field-om-attachments field-type-file field-label-hidden view-mode-full">
             <div class="field-items">
 	          <?php 
 	          	$count = 0;
	          	foreach ($content['field_om_attachments']['#object']->field_om_attachments['und'] as $fid) {
	          		if (isset($fid['fid'])) {
				    	$fid = $fid['fid'];
				    	$file = file_load($fid);
				    	print '<div class="'.(++$count%2 ? "field-item even" : "field-item odd").'"><span class="file"><img src="/modules/file/icons/application-pdf.png" title="application/pdf" alt="" class="file-icon">';
				    	print '<a href="/check_file_access/'. $fid.'" target="_blank" onclick="return xt_click(this, \'C\',\'2\',\'download::documentation::'.str_replace(" ","_",rawurlencode(rawurldecode($file->filename))).'\',\'A\')">' . $file->filename . '</a></span></div>';
	          		}
	          	}
	          ?>
	          </div>
	          </div>
	          </div>
            </div>
            <?php endif; ?>
        </div>
        <div class="om-cont-holder"><?php
        if (!isset($_GET['name'])) {
          if($node->nid && $user->uid) {
            module_load_include('inc', 'node_view_count', '/model/node_view_count.db');
            node_view_count_db_count_view_insert($node->nid, $user->uid);
          }
        }
        else{
          module_load_include('inc', 'node_view_count', '/model/node_view_count.db');
          node_view_count_db_count_view_insert($node->nid, $user->uid);
        }
        ?>
    <header<?php print $header_attributes; ?>>
      <?php if ($title): ?>
        <h1<?php print $title_attributes; ?>>
          <?php print $title; ?>
        </h1>
      <?php endif; ?>
    </header>
<?php //drupal_set_message('<pre>'.print_r($content, TRUE).'</pre>'); ?>
              <h4><?php print t('Objective');?></h4>

            <p><?php print render($content['field_om_objective']);?></p>
              <h4><?php print t('Summary');?></h4>
<div class="om-body-content"><div class="h2-head-lines"></div>
  <?php 
    $body_content = render($content['body']);
    $string_flag = explode("<h1", $body_content);
    if (count($string_flag) > 1) {
      for ($i=1; $i<count($string_flag); $i++) {
        $string_flag[$i] = '<h1 id="h1tag-' . $i . '"' . $string_flag[$i];
      }
    }
    print $body_content = implode("", $string_flag);
  ?>
  <?php } else {
              print t("No records found");
            }?>
</div>
       </div>
    </div>
</div>