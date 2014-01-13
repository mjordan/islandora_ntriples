<?php

/**
 * @file
 * Drush integration file for the Islandora N-Triples module.
 *
 * Loads an N-Triples file into the local Drupal database.
 * 
 * @todo: -Add function to delete triples with specific pattern in subject.
 *   -Add function to update triples using subject as key
 */

/**
 * Implements hook_drush_help().
 */
function islandora_ntriples_drush_help($command) {
  switch ($command) {
    case 'drush:load-islandora-ntriples':
      return dt('Populate the islandora_ntriples_triples table in the current Drupal database.');
  }
}

/**
 * Implements hook_drush_command().
 */
function islandora_ntriples_drush_command() {
  $items = array();
  $items['load-islandora-ntriples'] = array(
    'description' => dt('Populate the islandora_ntriples_triples table in the current Drupal database.'),
    'arguments'   => array(
      'file'    => dt('Path to the N-Triples data file you want to load.'),
    ),
    'examples' => array(
      'Standard example' => 'drush load-islandora-ntriples /path/to/data.nt',
      'Alias example' => 'drush lin /path/to/data.nt',
    ),
    'aliases' => array('lin'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );
  return $items;
}

/**
 * Callback function for drush load-islandora-ntriples.
 * 
 * Loads input file containing N-Triples into the 'islandora_ntriples_triples'
 * table.
 */
function drush_islandora_ntriples_load_islandora_ntriples($file = '') {
  // Four columns: subject, predicate, object, search_string
  // <http://id.loc.gov/vocabulary/graphicMaterials/tgm012200> <http://www.loc.gov/mads/rdf/v1#authoritativeLabel> "Diving boards"@en .

  $handle = fopen($file, "r");
  if ($handle) {
    while (($line = fgets($handle)) !== false) {
      // Remove the ' .' from the end of each N-Triple statement.
      $line = preg_replace('/\s\./', '', $line);
      $triple = explode(' ', $line, 3);
      // To get the strings we'll be searching against, get the autoriatitveLabel
      // triple and remove the quotation marks and language attribute (e.g. @en).
      if (preg_match('/authoritativeLabel/', $line)) {
        $search_string = trim($triple[2], '"');
        $search_string = preg_replace('/"@.+$/', '', $search_string);
        $triple[] = $search_string;
      }
      // For all other triples, assign a blank search string.
      else {
        $triple[] = '';
      }
      // Load this triple into the database.
      islandora_ntriples_load_triple($triple);
    }
  } else {
    // @todo: Report error opening the input file.
  }
}

/**
 * Insert a single triple into the database.
 * 
 * @param array $triple
 * 
 */
function islandora_ntriples_load_triple($triple) {
  $columns = array('subject','predicate', 'object', 'search_string');
  $entry = array_combine($columns, $triple);
  try {
    $return_value = db_insert('islandora_ntriples_triples')
      ->fields($entry)
      ->execute();
  }
  catch (Exception $e) {
    drupal_set_message(t('db_insert failed. Message = %message, query= %query',
      array('%message' => $e->getMessage(), '%query' => $e->query_string)), 'error');
  }
}
