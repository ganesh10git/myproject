<?php

/**
 * @file
 * Process theme data.
 *
 * Use this file to run your theme specific implimentations of theme functions,
 * such preprocess, process, alters, and theme function overrides.
 *
 * Preprocess and process functions are used to modify or create variables for
 * templates and theme functions. They are a common theming tool in Drupal, often
 * used as an alternative to directly editing or adding code to templates. Its
 * worth spending some time to learn more about these functions - they are a
 * powerful way to easily modify the output of any template variable.
 *
 * Preprocess and Process Functions SEE: http://drupal.org/node/254940#variables-processor
 * 1. Rename each function and instance of "adaptivetheme_subtheme" to match
 *    your subthemes name, e.g. if your theme name is "footheme" then the function
 *    name will be "footheme_preprocess_hook". Tip - you can search/replace
 *    on "adaptivetheme_subtheme".
 * 2. Uncomment the required function to use.
 */


/**
 * Preprocess variables for the html template.
 */
/* -- Delete this line to enable.
function im_preprocess_html(&$vars) {
  global $theme_key;

  // Two examples of adding custom classes to the body.

  // Add a body class for the active theme name.
  // $vars['classes_array'][] = drupal_html_class($theme_key);

  // Browser/platform sniff - adds body classes such as ipad, webkit, chrome etc.
  // $vars['classes_array'][] = css_browser_selector();

}
// */


/**
 * Process variables for the html template.
 */
/* -- Delete this line if you want to use this function
function im_process_html(&$vars) {
}
// */


/**
 * Override or insert variables for the page templates.
 */

function im_preprocess_page(&$vars) {
  //Add theme hook suggestion for Operational model page theme.
	if (isset($vars['node'])) {
  // If the node type is "blog" the template suggestion will be "page--blog.tpl.php".
   $vars['theme_hook_suggestions'][] = "page__node__{$vars['node']->type}";;
  }
}
/* -- Delete this line if you want to use these functions
function im_process_page(&$vars) {
}
// */


/**
 * Override or insert variables into the node templates.
 */
/* -- Delete this line if you want to use these functions
function im_preprocess_node(&$vars) {
}
function im_process_node(&$vars) {
}
// */


/**
 * Override or insert variables into the comment templates.
 */
/* -- Delete this line if you want to use these functions
function im_preprocess_comment(&$vars) {
}
function im_process_comment(&$vars) {
}
// */


/**
 * Override or insert variables into the block templates.
 */
/* -- Delete this line if you want to use these functions
function im_preprocess_block(&$vars) {
}
function im_process_block(&$vars) {
}
// */

/**
 * Hiding the tab on node view page
 * Enter description here ...
 * @param unknown_type $variables
 */
function im_menu_local_task(&$variables) {
  global $user;
  $node = node_load(arg(1));
  $draft_status = '';
  if (strcasecmp($variables['element']['#link']['title'], 'Create new holiday') == 0) {
  	$variables['element']['#link']['title'] = t($variables['element']['#link']['title']);
  }
  if (isset($node->field_draft_status['und']))
    $draft_status = $node->field_draft_status['und'][0]['value'];
  $link = $variables['element']['#link'];
  if((!in_array('administrator', $user->roles) && !in_array('content_manager_action_regional', $user->roles) && !in_array('content_manager_action', $user->roles) && !in_array('content_manager_om', $user->roles) && !in_array('technical_director', $user->roles) && !in_array('expert', $user->roles)) && ($draft_status!=1)){  	
  	if((strcasecmp($variables['element']['#link']['title'], t('edit')) != 0) && (strcasecmp($variables['element']['#link']['title'], t('Edit')) != 0) && (strcasecmp($variables['element']['#link']['title'], t('Edit draft')) != 0) && (strcasecmp($variables['element']['#link']['title'], t('New draft')) != 0) && $variables['element']['#link']['path'] != "node/%/draft") {	  
	    $active = '<span class="element-invisible">' . t('(active tab)') . '</span>';
	    if (empty($link['localized_options']['html'])) {
	      $link['title'] = check_plain($link['title']);
	    }
	    $link['localized_options']['html'] = TRUE;
	    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
	    return '<li' . (!empty($variables['element']['#active']) ? ' class="active"' : '') . '>' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n";
	 }
  }
  else {
    if ($variables['element']['#link']['path'] != "node/%/draft") {
  		$active = '<span class="element-invisible">' . t('(active tab)') . '</span>';
	    if (empty($link['localized_options']['html'])) {
	      $link['title'] = check_plain($link['title']);
	    }
	    $link['localized_options']['html'] = TRUE;
	    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
	    return '<li' . (!empty($variables['element']['#active']) ? ' class="active"' : '') . '>' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n";
	}
  }
}
/*
function im_preprocess_search_result(&$variables) {
  $variables['search_results']['image_type'] = "image_type";
  $variables['search_results']['snippet'] = $variables['snippet'];
  $variables['search_results']['title'] = $variables['title'];
  $variables['search_results']['url'] = $variables['url'];
  $variables['search_results']['score'] = $variables['result']['score'];
  $variables['search_results']['published'] = $variables['result']['fields']['ds_changed'];
}*/
  
/**
 * Brief message to display when no results match the query.
 * override the N o results theming from apache solr search module
 * @see search_help()
 */
function im_apachesolr_search_noresults() {
	variable_set('search_noresult','noresult');
	$search_results = 0;
  _im_search_cuwa($search_results);
  $return = '<ul class="no-results-msg">';
  $return .= html_entity_decode(t('@li1Check if your spelling is correct, or try removing filters.@li2@li1Remove quotes around phrases to match each word individually: @em1blue drop @em1 will match less than @em1blue drop@em2.@li2@li1You can require or exclude terms using + and -: @em1big +blue drop@em2 will require a match on @em1blue@em2 while @em1big blue -drop@em2 will exclude results that contain @em1drop@em2.@li2@li2', array('@li1' => '<li>', '@li2' => '</li>', '@em1' => '<em>', '@em2' => '</em>')));
  return $return; 

}

function im_nice_menus_build($variables) {
  // Menu array from which to build the nested lists.
  $menu = $variables['menu'];

  // The number of children levels to display. Use -1 to display all children
  // and use 0 to display no children.
  $depth = $variables['depth'];

  // An array of parent menu items.
  $trail = $variables['trail'];
  // "Show as expanded" option.
  $respect_expanded = $variables['respect_expanded'];

  $output = '';
  // Prepare to count the links so we can mark first, last, odd and even.
  $index = 0;
  $count = 0;
  foreach ($menu as $menu_count) {
    if ($menu_count['link']['hidden'] == 0) {
      $count++;
    }
  }
  // Get to building the menu.
  foreach ($menu as $menu_item) {
    $mlid = $menu_item['link']['mlid'];
    // Check to see if it is a visible menu item.
    if (!isset($menu_item['link']['hidden']) || $menu_item['link']['hidden'] == 0) {
      // Check our count and build first, last, odd/even classes.
      $index++;
      $first_class = ($index == 1) ? 'first' : '';
      $oddeven_class = ($index % 2 == 0) ? 'even' : 'odd';
      $last_class = ($index == $count) ? 'last' : '';
      // Build class name based on menu path
      // e.g. to give each menu item individual style.
      $class = str_replace(array('http', 'https', '://', 'www'), '', $menu_item['link']['href']);
      // Strip funny symbols.
      $class = drupal_html_class('menu-path-' . $class);
      if ($trail && in_array($mlid, $trail)) {
        $class .= ' active-trail';
      }
      // If it has children build a nice little tree under it.
      // Build a nice little tree under it if it has children, and has been set
      // to expand (when that option is being respected).
      if ((!empty($menu_item['link']['has_children'])) &&
          (!empty($menu_item['below'])) && $depth != 0 &&
          ($respect_expanded == 0 || $menu_item['link']['expanded'])) {
        // Keep passing children into the function 'til we get them all.
        if ($menu_item['link']['depth'] <= $depth || $depth == -1) {
          $children = array(
            '#theme' => 'nice_menus_build',
            '#prefix' => '<ul>',
            '#suffix' => '</ul>',
            '#menu' => $menu_item['below'],
            '#depth' => $depth,
            '#trail' => $trail,
            '#respect_expanded' => $respect_expanded,
          );
        }
        else {
          $children = '';
        }
        // Set the class to parent only of children are displayed.
        $parent_class = ($children && ($menu_item['link']['depth'] <= $depth || $depth == -1)) ? 'menuparent ' : '';
        $element = array(
          '#below' => $children,
          '#title' => $menu_item['link']['title'],
          '#href' => $menu_item['link']['href'],
          '#localized_options' => $menu_item['link']['localized_options'],
          '#attributes' => array(
            'class' => array(
              'menu-' . $mlid,
              $parent_class,
              $class,
              $first_class,
              $oddeven_class,
              $last_class,
            ),
          ),
          '#original_link' => $menu_item['link'],
        );
        $variables['element'] = $element;

        // Check for context reactions menu.
        if (module_exists('context')) {
          context_preprocess_menu_link($variables);
          if (isset($variables['element']['#localized_options']['attributes']['class']) &&
            in_array('active', $variables['element']['#localized_options']['attributes']['class']) &&
            !in_array('active-trail', $variables['element']['#attributes']['class'])) {
            $variables['element']['#attributes']['class'][] = ' active-trail';
          }
        }
        $output .= theme('menu_link', $variables);
      }
      else {
        $element = array(
          '#below' => '',
          '#title' => $menu_item['link']['title'],
          '#href' => $menu_item['link']['href'],
          '#localized_options' => $menu_item['link']['localized_options'],
          '#attributes' => array(
            'class' => array(
              'menu-' . $mlid,
              $class,
              $first_class,
              $oddeven_class,
              $last_class,
            ),
          ),
          '#original_link' => $menu_item['link'],
        );
        $variables['element'] = $element;
     
        // Check for context reactions menu.
        if (module_exists('context')) {
          context_preprocess_menu_link($variables);
          if (isset($variables['element']['#localized_options']['attributes']['class']) &&
            in_array('active', $variables['element']['#localized_options']['attributes']['class']) &&
            !in_array('active-trail', $variables['element']['#attributes']['class'])) {
            $variables['element']['#attributes']['class'][] = ' active-trail';
          }
        }
        $apps_menu = im_blocks_application_headermenu();
        $output .= theme('menu_link', $variables);
        if(strcasecmp($class, 'menu-path-front') == 0){
        	$output .= '<div id="my-apps-submenu">'.$apps_menu.'</div>';
        }
      }
    }   
  }
  return $output;
}