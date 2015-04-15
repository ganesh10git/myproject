<?php
 /**  */
?>

<?php
global $base_url;
$_SESSION['row_set_counter'] = 0;
$_SESSION['row_set_title'] = '';
$date = arg(1);
$timestamp = $date;
$timestamp_previous = strtotime($timestamp)-1;
$dateprevious = format_date($timestamp_previous,'custom','l j F');

$timestamp_present = strtotime($timestamp);
$datepresent = format_date($timestamp_present,'custom', 'l j F Y');

$timestamp_next = strtotime('+1 day', strtotime($date));
$datenext = format_date($timestamp_next,'custom','l j F');


$previous_date =  date('Ymd', strtotime('-1 day', strtotime($date)));
$next_date =  date('Ymd', strtotime('+1 day', strtotime($date)));
?>
<div class="agenda-date-selection">
		<div class = "previous-date" ><?php print l($dateprevious,$base_url.'/agenda-day/'. $previous_date.'/'.arg(2).'/'.arg(3));?></div>
		<div class = "present-date"><?php print $datepresent;?></div>
		<div class = "next-date"><?php print l($datenext,$base_url.'/agenda-day/'. $next_date.'/'.arg(2).'/'.arg(3));  ?></div>
		<div class = "print-agenda-today"><?php print t('Print');?>
		<?php //print l(t('Print'), '', array('external' => TRUE));?>
		</div>
</div>
<div class="agenda-date-selection-data">
	<?php print $rows; ?>
</div>
