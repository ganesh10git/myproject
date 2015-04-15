/**
 *@file Client side validations for user management filter form. 
 */
(function($) {
	Drupal.behaviors.im_user_dmd_assignment = {};
	  Drupal.behaviors.im_user_dmd_assignment.attach = function(context) {
		  //alert("+++++");
		  var errormsg = '';
		  $(".dmd-filter-form #edit-dmd-search").click(function(event){
			//alert("-------");
			  if($.trim($("#edit-dmd-first-name").val()) == '' && $.trim($("#edit-dmd-last-name").val()) == '' && $.trim($("#edit-dmd-employee-id").val()) == ''){
				  errormsg = Drupal.t("Please enter the value for any one of the field.");
				  alert(errormsg);
				  return false;
			  }
			  
			  if($.trim($("#edit-dmd-first-name").val()) != '' && ($.trim($("#edit-dmd-last-name").val()) == '' && $.trim($("#edit-dmd-employee-id").val()) == '')){
				  errormsg = Drupal.t("Please enter the value for Last name or Employee Id.");
				  alert(errormsg);
				  return false;
			  }
		  });
		  
	  }
})(jQuery);
