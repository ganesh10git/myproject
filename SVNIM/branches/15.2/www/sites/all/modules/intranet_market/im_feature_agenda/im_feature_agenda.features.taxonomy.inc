<?php
/**
 * @file
 * im_feature_agenda.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function im_feature_agenda_taxonomy_default_vocabularies() {
  return array(
    'agenda_department' => array(
      'name' => 'Département',
      'machine_name' => 'agenda_department',
      'description' => '',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'fonctions' => array(
      'name' => 'Interlocuteurs',
      'machine_name' => 'fonctions',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
