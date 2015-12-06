<?php
/**
 * 
 * Php unit tets to test the regional code.
 * @author gshanmug
 *
 */
define('DRUPAL_ROOT', getcwd());

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
$_SERVER['REMOTE_ADDR'] = '127.0.0.1';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
//require_once DRUPAL_ROOT . '/sites/all/modules/intranet_market/im_user/includes/im_user_dashboard.inc';
module_load_include('inc', 'im_user', 'includes/im_user_dashboard');

class UserRole extends PHPUnit_Framework_TestCase {
  public function test_user_roles() {
    $_SESSION["dashboard_regional_moderator_users"]['76']['profile_nids'] = '1267';
    $input_roles_array = array('input' => array('selected_role' => array('76' => array('9-expert' => '1', '3-content_manager_action' => '1', '17-content_manager_action_regional' => '1'))), 'values' => array('users_roles_details' => array('76' => '76')));    
    $check_user_roles = im_user_dashboard_process_action($input_roles_array, 'add');
    xdebug_break();    
  }
}
?>