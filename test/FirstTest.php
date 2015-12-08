<?php
/**
 * 
 * Phpunit class to Test for same array ...
 * @author gshanmug
 *
 */
class FirstTest extends PHPUnit_Framework_TestCase
{
  public function test_two_plus_two_is_four()
  {
    $this->assertEquals(2+2, 4);
  }
}