/**
 * @file
 * inc file for holiday and sales plan content type.
 */
/**
 * function to check the calender field has same year or not. 
 */

(function($) {
  Drupal.behaviors.im_user_sales_plan_holiday_bo = {};
  Drupal.behaviors.im_user_sales_plan_holiday_bo.attach = function(context) {
	  var tempflag = [];
	  var inputvalues = ['Toussaint', 'Noel', 'Hiver', 'Vaccances de Printemps', 'Ete'];
	  var lineinc = 0;
	  $("table input").each(function( index ) {
		    var element = $(this).attr("id").toString();
		    if(element.indexOf('field-holiday-type') > 0 ) 
		     {
		    	if (jQuery.inArray(element, tempflag)) {
		    		tempflag.push(element);
		    		if ($("#" + element).val() == "Toussaint" || $("#" + element).val() == inputvalues[lineinc+1]) {
		    			$("#" + element).val(inputvalues[lineinc]);
		    		}
		    		lineinc++;
		    	}
	        }
		  });
	  lineinc = 0;
	  //to check holiday content type is created for previous year selection
	  $('#edit-field-holiday-calender-year').keyup(function(){
		  $('#edit-title').val($('#edit-field-holiday-calender-year').val());
		  var holiday_title_value = $('#edit-title').val();
	      var data = "data=" + $('#edit-title').val();
		  $.ajax({
	          url: '/calender_field_validation/"'+holiday_title_value+'"',
	          type: 'POST',
	          data: data,
	          success: function(a) {
			  if(a != "") {
				  window.location.href = "/node/"+a+"/edit";
			   }
	          }
	        });
	  });
	  $('.date-clear').focus();
		//calender image in holiday content type 
	  $(window).load(function(){
			$('.date-clear').focus();
	  });
  }
})(jQuery);