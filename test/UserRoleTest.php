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
class UserTest extends PHPUnit_Framework_TestCase {
  public function test_search_for_titles() {
    $input_roles_array = array('input' => array('selected_role' => array('76' => array('9-expert' => '1', '3-content_manager_action' => '1'))));
    $check_user_roles = im_user_dashboard_process_action($input_roles_array, 'add');    
  }
}
?>