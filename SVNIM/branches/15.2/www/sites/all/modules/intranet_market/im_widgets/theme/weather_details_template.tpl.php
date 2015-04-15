<?php  
  global $base_url;
  $todays_date =date('M-j');
  $weather_image_url = isset($data['current_condition'][0]['weatherIconUrl'][0]['value']) ? $data['current_condition'][0]['weatherIconUrl'][0]['value'] : '';
  $temperature = isset($data['current_condition'][0]['temp_C']) ? $data['current_condition'][0]['temp_C'] : '';  
  $windspeedKmph =  isset($data['current_condition'][0]['windspeedKmph']) ? $data['current_condition'][0]['windspeedKmph'] : '';
  $humidity = isset($data['current_condition'][0]['humidity']) ? $data['current_condition'][0]['humidity'] : '';
  $precipMM = isset($data['current_condition'][0]['precipMM']) ? $data['current_condition'][0]['precipMM'] : '';
  $area_name = isset($data['nearest_area'][0]['areaName'][0]['value']) ? $data['nearest_area'][0]['areaName'][0]['value'] : ''; 
?>
<div class="weather-wrapper" style="display:none;">
  <div class="weather-title">
  	<span class="weather"><?php print t('Weather');?></span>
  	<span class="city"><?php print $area_name;?></span>
  </div>
  <?php  $timestamp = date("l  d.m.y");
  $timestamp =strtotime($timestamp); 
  ?>
    <div class="day-info"><?php print format_date($timestamp,'custom','l  d.m.Y'). ' - '. $saint_of_the_day;?></div>
  <div class="todays-weather-info">  
    <?php  
         if(isset($data['weather']) && is_array($data['weather'])) {         	
    ?>
    <div class="temp-wrapper">
      <div class="today-weather-icon"><?php print $weather_image_url ? '<img src="/' . drupal_get_path('module', 'im_widgets') . '/images/wsymbol/' . preg_replace('/^.+[\\\\\\/]/', '', $weather_image_url).'">' : ''?></div>
      <div class="temp-value"><?php print $temperature;?></div>
      <div class="temp-category"><span class=" active celsius">°C</span>|<span class="fahrenheit ">°F</span></div>
    </div>
    <div class="weather-info-details">
      <div class="wind"><?php print t('Wind Speed') . ' : ' . $windspeedKmph;?>Km/h</div>
      <div class="humidity"><?php print t('Humidity') . ' : ' . $humidity .'%';?></div>
      <div class="precipitation"><?php print t('Precipitation') . ' : ' . $precipMM."mm";?></div>
    </div>
    <?php         //print 'Weather service is down try reloading page in a few minutes'; 
         } else {
            print t('Weather service is down try reloading page in a few minutes'); 
         } 
    ?>
  </div>
  <div class="weather-future-days">
  <?php
  $degree_symbol ='°';
  $temp_array = array();

  //to load the current temperatures in C and F.
  $temperature_f = '';
  $temperature_f = isset($data['current_condition'][0]['temp_F']) ? $data['current_condition'][0]['temp_F'] : '';
  $temp_array['curr_temp']['C'] = isset($temperature) ? $temperature : '';
  $temp_array['curr_temp']['F'] = isset($temperature_f) ? $temperature_f : '';

  if(isset($data['weather']) && is_array($data['weather'])) {
  	foreach ($data['weather'] as $index => $weather) {
  		print '<div class="weather-future">';
  		print t(date('D',strtotime($weather['date'])));
  		//print '<img src="'.$weather['weatherIconUrl'][0]['value'].'">';
  		print '<img src="/' . drupal_get_path('module', 'im_widgets') . '/images/wsymbol/' . preg_replace('/^.+[\\\\\\/]/', '', $weather['weatherIconUrl'][0]['value']).'">';
  		$temp_array[$index]['tempMaxC'] = $weather['tempMaxC'];
  		$temp_array[$index]['tempMinC'] = $weather['tempMinC'];
  		$temp_array[$index]['tempMaxF'] = $weather['tempMaxF'];
        $temp_array[$index]['tempMinF'] = $weather['tempMinF'];
  		print '<span class="temp-max max-'.$index.'">' . $weather['tempMaxC'].$degree_symbol. '</span><span class="temp-min min-'.$index.'"">' .$weather['tempMinC'].$degree_symbol. '</span>';
  		print '</div>'; 
  	}
  }
  
  drupal_add_js(array('tempObj' => drupal_json_encode($temp_array)), 'setting');
  ?>
  </div>
</div>