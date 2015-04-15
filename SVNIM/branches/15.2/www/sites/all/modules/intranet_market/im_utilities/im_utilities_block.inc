<?php
/**
 * @file
 * Provide utilities functions relative to blocks
 */

/**
 * Enabling blocks (theme, region..)
 *
 * @param Array $values
 * @example array(array(
 *    'module' => 'core_search',
 *    'delta' => 'form',
 *    'theme' => $default_theme,
 *    'status' => 1,
 *    'weight' => 0,
 *    'region' => 'footer',
 *    'visibility' => 1
 *    'pages' => '',
 *    'cache' => -1,
 *  ), ...)
 */
function im_utilities_block_enable($blocks = array()) {
  foreach ($blocks as $block) {
    db_merge('block')
      ->key(array('module' => $block['module']))
      ->key(array('delta'  => $block['delta']))
      ->key(array('theme' => $block['theme']))
      ->fields(array(
        'status' => (isset($block['status'])) ? $block['status'] : BLOCK_CUSTOM_DISABLED,
        'weight' => (isset($block['weight'])) ? $block['weight'] : 0,
        'region' => (isset($block['region'])) ? $block['region'] : -1,
        'visibility' => (isset($block['visibility'])) ? $block['visibility'] : 0,
        'pages'  => (isset($block['pages'])) ? $block['pages'] : '',
        'cache'  => (isset($block['cache'])) ? $block['cache'] : DRUPAL_NO_CACHE,
      ))
      ->execute();
  }
}
/**
 * Enable a block for a content type
 * @example array(
    array(
      'module' => 'views',
      'delta'  => 'product_list-block_1',
      'type'   => 'product_sheet',
    ),
  );
 */
function im_utilities_enable_block_content_type($blocks = array()) {
  foreach ($blocks as $block) {
    db_merge('block_node_type')
      ->key(array('module' => $block['module']))
      ->key(array('delta'  => $block['delta']))
      ->key(array('type' => $block['type']))
      ->execute();
  }
}
