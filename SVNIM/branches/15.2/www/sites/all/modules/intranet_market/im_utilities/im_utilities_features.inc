<?php
/**
 * @file
 * Provide utilities functions relative to features
 */

/**
 * Get all the feature to revert, and revert it
 * (Code adapted from drush)
 *
 * @see drush_features_revert_all
 */
function im_utilities_features_revert_all() {
  $features_to_revert = array();
  $features_to_exclude = array();
  foreach (features_get_features() as $module) {
    if ($module->status && !in_array($module->name, $features_to_exclude)) {
      $features_to_revert[] = $module->name;
    }
  }
  foreach ($features_to_revert as $module_name) {
    im_utilities_features_revert($module_name);
  }
}
/**
 * Force the revert of all feature components
 * (Code adapted from drush)
 *
 * @see drush_features_revert
 * @param String $module
 */
function im_utilities_features_revert($module) {
  module_load_include('inc', 'features', 'features.export');
  features_include();
  if (($feature = feature_load($module, TRUE)) && module_exists($module)) {
    $components = array();
    // Forcefully revert all components of a feature.
    foreach (array_keys($feature->info['features']) as $component) {
      if (features_hook($component, 'features_revert')) {
        $components[] = $component;
      }
    }
    foreach ($components as $component) {
      features_revert(array($module => array($component)));
    }
  }
}