/**
 * @file JS file for message pop-up
 */
(function($) {
	jQuery(document).ready(function(){
		
	    $("#edit-field-publication-from-date-und-0-value-datepicker-popup-0").datepicker({
	      dateFormat: 'dd/mm/yy',
	      defaultDate: new Date(),
	    });
	    $("#edit-field-publication-to-date-und-0-value-datepicker-popup-0").datepicker({
	      dateFormat: 'dd/mm/yy',
	      defaultDate: new Date(),
	    });
		   //Publication End date for the Message content type
		$('#message-node-form #edit-field-publication-from-date-und-0-value-datepicker-popup-0').change(function(){
		  var msg_todate = Drupal.settings.im_custom_message_date.message_to_date;
	      var date1 = $('#edit-field-publication-from-date-und-0-value-datepicker-popup-0').datepicker('getDate');
	      var date = new Date( Date.parse(date1)); 
		  date.setDate( date.getDate() + parseInt(msg_todate));
		  
	      var newDate = date.toDateString(); 
	      newDate = new Date(Date.parse(newDate));
	      $('#edit-field-publication-to-date-und-0-value-datepicker-popup-0').datepicker('setDate', newDate );
	      $('#edit-field-publication-to-date-und-0-value-datepicker-popup-0').datepicker("refresh");
	    });

  });
})(jQuery);