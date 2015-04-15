<div id="im-holiday">
	<div class="im-holiday-calender-year">
			<div class="im-holiday-date"><?php print render($form['field_holiday_calender_year']); ?></div>
			<div class="im-holiday-pos-file"><?php print render($form['field_holiday_pos_file']); ?></div>
	</div>
	<div class="holiday-vacation-period">
			<?php print render($form['field_holiday_period_des_vaccanc']); ?>
			<?php print render($form['field_holiday_type']); ?>
			<?php print render($form['field_holiday_zone_a']); ?>
			<?php print render($form['field_holiday_zone_b']); ?>
			<?php print render($form['field_holiday_zone_c']); ?>
	</div>
	<div class="special-holiday-days">
			<?php print render($form['field_holiday_jours_sp_ciaux']); ?>
	</div>
	<?php print render($form['field_holiday_special_name']); ?>
	<?php print render($form['field_holiday_special_day']); ?>
	<?php print drupal_render_children($form); ?>
</div>