<?php 
function get_weather_details() {
  global $user;
  $weather_response = array();
  $user_profile = user_load($user->uid);
  $field_user_stores = (isset($user_profile->field_user_stores['und'][0]['value']) && $user_profile->field_user_stores['und'][0]['value']) ? $user_profile->field_user_stores['und'][0]['value'] : '';
  $field_user_forecast = (isset($user_profile->field_user_forecast['und'][0]['value']) && $user_profile->field_user_forecast['und'][0]['value']) ? $user_profile->field_user_forecast['und'][0]['value'] : ''; 
  if($field_user_stores | $field_user_forecast) {
  	$profile_store = current(explode(',', $field_user_forecast)) ? current(explode(',', $field_user_forecast)) : current(explode(',', $field_user_stores));
  	if($profile_store) {
      $cache_key = 'weather_'.$profile_store;
      if ($weather_response = cache_get($cache_key)) {
      	return $weather_response->data;
      }
      $latitude = db_query("SELECT ite_lib_value AS latitude FROM {store_item_fields} WHERE pve_code = :profile_store AND dit_cod_item = 'latitude'", array(':profile_store' => $profile_store));
      $longitude = db_query("SELECT ite_lib_value AS longitude FROM {store_item_fields} WHERE pve_code = :profile_store AND dit_cod_item = 'longitude'", array(':profile_store' => $profile_store));
      $latitudeObj = $latitude->fetchObject(); 
      $longitudeObj = $longitude->fetchObject();
      if(isset($latitudeObj->latitude) && isset($longitudeObj->longitude)) {
      	//$requestURL = "http://api.worldweatheronline.com/free/v1/weather.ashx?lat=" . $latitudeObj->latitude . "&lon=" . $longitudeObj->longitude . "&format=json&extra=localObsTime&num_of_days=5&includelocation=yes&key=2ganbfgdp265xf69wz3px3jf";
      	$requestURL = variable_get('weather_api_settings', '');
      	$requestURL = str_replace('{latitude}', $latitudeObj->latitude, str_replace('{longitude}', $longitudeObj->longitude, $requestURL));
      	$response = drupal_http_request($requestURL);
      	if(isset($response->data)) {
      	  $weather_response = drupal_json_decode($response->data);
      	  $weather_forecast_cache_hours = variable_get('weather_forecast_cache_hours', '12');      	  
      	  if(!isset($weather_response['data']['error'])){
      	  	cache_set($cache_key, $weather_response, 'cache', time() + 60*60*$weather_forecast_cache_hours);
      	  }
        }	
      }
    }
  }
  return $weather_response;
}