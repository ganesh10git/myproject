<?php

/**
 * This file overrides default settings from settings.php.
 */

// ------------------
// DATABASES SETTINGS
// ------------------
$databases = array (
  'default' =>
  array (
    'default' =>
    array (
      'database' => 'crfr_im',
      'username' => 'carrefour',
      'password' => 'carrefour',
      'host' => '127.0.0.1',
      'port' => '',
      'driver' => 'pgsql',
      'prefix' => '',
    ),
  ),
);

// -------------
// CUWA SETTINGS
// -------------
$cuwa = array (
 'test' => array (
   'xtsd' => array(
     'http' => 'http://logc174',
     'https' => 'https://logs128',
   ),
   'xtsite' => '544940',
 ),
 'default' => array (
   'xtsd' => array(
     'http' => 'http://logc174',
     'https' => 'https://logs128',
   ),
   'xtsite' => '544941',
 ),
);

/*
 * Webservice 'annuuddi' WSDL path settings.
 */
$conf['annuuddi_settings'] = array(
  'service_url_ldap_auth_impl' => 'http://annuuddi.fr.carrefour.com/LdapWs/LdapWsAuthImpl?wsdl',
  'service_url_ldap_user_impl' => 'http://annuuddi.fr.carrefour.com/LdapWs/LdapWsUserImpl?wsdl',
);

/*
 * 'annuuddi' login URL.
 */
$conf['annuuddi_login_url'] = 'http://annuuddi.fr.carrefour.com/LdapWsWeb/login.jsp?fromURL={current_domain}/personal-space/login-validate&cssURL={current_domain}/sites/all/themes/im/css/login.css';

/*
 * weather API settings
 * api.worldweatheronline.com
 */
$conf['weather_api_settings'] = "http://api.worldweatheronline.com/free/v1/weather.ashx?lat={latitude}&lon={longitude}&format=json&extra=localObsTime&num_of_days=5&includelocation=yes&key=2ganbfgdp265xf69wz3px3jf";

//
// Architecture related settings
//

// Drupal core
// -----------

// Use of reverse proxies

// All the trusted IP addresses that may appear in HTTP_X_FORWARDED_FOR header
// Printing the values of $_SERVER['HTTP_X_FORWARDED_FOR'] and $_SERVER['REMOTE_ADDR'] might help to configure this variable
$conf['reverse_proxy_addresses'] =  array(
// Load balancer IP(s) (useful if the LB alters client IP)
  '127.0.0.1',

// Apache SSL + Varnish servers IPs
  '127.0.0.1',
);


// Varnish module
// --------------

// Remote purge of Varnish server(s)

// Administration channel (IP:PORT control_key)
//   - If you have several varnish servers, put them all in "varnish_control_terminal" by
//     separating them with line breaks
//   - The control key is usually the content of file "/etc/varnish/secret"
//   - If some (or all) of your varnish servers do not need control keys, just omit them
//   Example:
//   $conf['varnish_control_terminal'] = '192.168.0.10:6082 control_key_1
//   192.168.0.11:6098
//   192.168.0.12:6082 control_key_2';
$conf['varnish_control_terminal'] = '127.0.0.1:6082 rf<Ok13wX';

// ---------------------
// SOLR DEFAULT SETTINGS
// ---------------------
$default_settings_solr = array(
  'environment' => array (
    'solr' => 'http://localhost:8080/solr',
  ),
  'apachesolr_tika' => array(
    'apachesolr_attachments_tika_path' => 'sites/all/modules/contrib/apachesolr',
	'apachesolr_attachments_tika_jar' => 'tika-app-1.5.jar',
  ),
);


// Memcache module
// ---------------

// Memcached servers used by Drupal (one row per server)
$conf['memcache_servers'] = array(
  'localhost:11211' => 'default',
);



// Key prefix in case several Drupal site use the same Memcached instance
$conf['memcache_key_prefix'] = 'intranet_market';

// ---------------------
// Agenda home page no of the days settings for lazy load
//- ---------------------

$conf['agenda_content_settings'] = '7';
// ---------------------
// Weather Forecast : No of hours for cache
//- ---------------------

$conf['weather_forecast_cache_hours'] = '12';


// Core_performance module
// -----------------------

// Use of dedicated domains for static files (for performance purpose)

// List of domains used to generate URLs for static files
// The domains given below must be the same as those defined in vhost configuration
$conf['im_performance_static_files_domain'] = array(
  'static1.portal.im.dev.carrefour.com',
  'static2.portal.im.dev.carrefour.com',
);