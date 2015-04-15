<?php
/**
 * @file
 * im_features_apachesolr_pages.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function im_features_apachesolr_pages_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "apachesolr_search" && $api == "apachesolr_search_defaults") {
    return array("version" => "3");
  }
}
