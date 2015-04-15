<?php

/**
 * Utility file to check Drupal's health.
 * When called without parameters checks only database connection.
 * May be called with 'target' parameter to check only memcached or solr connection.
 */

// To read configurations
include_once '../sites/default/settings.php';

if (!empty($_GET['target'])) {
  switch($_GET['target']) {
    // Check mysql server connection
    case 'pgsql':
      list($result, $message) = check_pgsql();
      break;

    // Check memcached server connection
    case 'memcached':
      list($result, $message) = check_memcached();
      break;

    // Check solr server connection
    case 'solr':
      list($result, $message) = check_solr();
      break;

    // None of them
    default:
      list($result, $message) = array(FALSE, "Script: wrong target parameter");
  }
}
else {
  list($result, $message) = check_pgsql();
}

// Build the response
if ($result) {
  echo "<p>[GLOBAL OK]</p>";
}
else {
  echo "<p>[GLOBAL KO]</p>";
}
echo "<p>" . $message . "</p>";

// Return error code 500 in case of failure
if (!$result) {
  header('HTTP/1.1 500 Internal Server Error');
}

// End of the script
exit;


/**
 * Check mysql connection (master & slaves).
 *
 * @return array(FALSE, "") in case of failure and array(TRUE, "") otherwise.
 */
function check_pgsql() {
  global $databases;

  // collect response time
  $time = microtime();

  // check master connection
  $master = $databases['default']['default'];
  $connection_string="host=".$master['host']. ' ' ."port=".$master['port']. ' ' ."dbname=". $master['database']  . ' ' ."user=". $master['username']. ' ' ."password=". $master['password'];
  $db_connection = pg_connect($connection_string);
  if (!$db_connection) {
    return array(FALSE, "pgsql: cannot connect to postgres master");
  }
  pg_close($db_connection);

  // collect response time
  $time_spent = microtime() - $time;
  $time_spent = round(1000 * $time_spent) . "ms"; // convert in ms

  // check slaves connections if any
  if (!isset($databases['default']['slave'])) {
    return array(TRUE, "pgsql: OK (" . $time_spent . ")");
  }

  $slaves = $databases['default']['slave'];
  foreach ($slaves as $slave) {
$connection_string="host=".$slave['host']. ' ' ."port=".$slave['port']. ' ' ."dbname=". $slave['database']  . ' ' ."user=". $slave['username']. ' ' ."password=". $slave['password'];
    $db_connection = pg_connect($connection_string);
    if (!$db_connection) {
      return array(FALSE, "PgSQL: cannot connect to PgSql slave (" . $slave['host'] . ")");
    }
    pg_close($db_connection);
  }

  return array(TRUE, "PgSQL: OK (" . $time_spent . ")");
}

/**
 * Check memcached connection.
 *
 * @return array(FALSE, "") in case of failure and array(TRUE, "") otherwise.
 */
function check_memcached() {
  global $conf;

  if (isset($conf['memcache_servers']) && is_array($conf['memcache_servers']) && !empty($conf['memcache_servers'])) {
    // collect response time
    $time = microtime();

    // Check connection to each Memecached server in the pool of servers
    foreach ($conf['memcache_servers'] as $s => $c) {
      list($host, $port) = explode(':', $s);
      $memcache = new Memcache;
      $result = $memcache->connect($host, $port);
      if (!$result) {
        // The current server cannot be reached
        return array(FALSE, "Memcached: cannot connect to Memcached server (" . $host . ")");
      }
    }

    // collect response time
    $time_spent = microtime() - $time;
    $time_spent = round(1000 * $time_spent) . "ms"; // convert in ms

    // All Memcached servers are up
    return array(TRUE, "Memcached: OK (" . $time_spent . ")");
  }

  // Use of Memcached is not configured
  return array(FALSE, "Memcached: Drupal is not configured to use Memcached");
}

/**
 * Check solr connection.
 * WARNING: must not be called to often as it performs a SQL query (one call per minute would be fine).
 *
 * @return array(FALSE, "") in case of failure and array(TRUE, "") otherwise.
 */
function check_solr() {
  global $databases;

  // Retrieve Solr's information from MySQL slave if possible
  if (isset($databases['default']['slave'][0])) {
    $database = $databases['default']['slave'][0];
  }
  elseif (isset($databases['default']['default'])) {
    $database = $databases['default']['default'];
  }
  else {
    return array(FALSE, "SolR: cannot find database configuration");
  }

  $db_connection = mysql_connect($database['host']. ':' .$database['port'], $database['username'], $database['password']);
  if (!$db_connection) {
    return array(FALSE, "SolR: cannot connect to database server");
  }

  if (!mysql_select_db($database['database'], $db_connection)) {
    mysql_close($db_connection);
    return array(FALSE, "SolR: cannot select the database");
  }

  $sql_request = 'SELECT url FROM apachesolr_environment LIMIT 1';
  $sql_request_result = mysql_query($sql_request, $db_connection);
  if (!$sql_request_result) {
    mysql_close($db_connection);
    return array(FALSE, "SolR: SELECT query failed");
  }

  $sql_request_result_data = mysql_fetch_assoc($sql_request_result);
  if (!$sql_request_result_data) {
    mysql_close($db_connection);
    return array(FALSE, "SolR: SELECT query did not return any result");
  }

  $solr_url = $sql_request_result_data['url'];
  mysql_close($db_connection);

  // ping Solr server
  include_once '../includes/common.inc';
  include_once '../includes/bootstrap.inc';

  // collect response time
  $time = microtime();

  $solr_http_request = drupal_http_request($solr_url.'/admin/ping');
  if($solr_http_request->code != 200){
    return array(FALSE, "SolR: cannot connect to SolR server (" . $solr_url . ")");
  }

  // collect response time
  $time_spent = microtime() - $time;
  $time_spent = round(1000 * $time_spent) . "ms"; // convert in ms

  return array(TRUE, "SolR: OK (" . $time_spent . ")");
}
