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
  public function test_region_code() {
    $titles = fetch_region_code('3021080655604');
    $this->assertEquals($titles, 'TEST Store A');
  }
}
?>