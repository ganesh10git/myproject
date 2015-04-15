/**
 *@file Client side validations for user management filter form. 
 */
(function($) {
	Drupal.behaviors.im_user_validations = {};
	  Drupal.behaviors.im_user_validations.attach = function(context) {
		  $("#im-user-management-filter-form #edit-user-serach").click(function(event){
			  //event.preventDefault();
			  var errormsg = '';
			  if($.trim($("#edit-user-first-name").val()) == '' && $.trim($("#edit-user-last-name").val()) == '' && $.trim($("#edit-user-email").val()) == ''){
				  errormsg = Drupal.t("Please enter the value for any one of the field.");
				  alert(errormsg);
				  return false;
			  }
			  if($.trim($("#edit-user-first-name").val()) != '' && ($.trim($("#edit-user-last-name").val()) == '' && $.trim($("#edit-user-email").val()) == '')){
				  errormsg = Drupal.t("Please enter the value for Last name or Email.");
				  alert(errormsg);
				  return false;
			  }
			  if($.trim($("#edit-user-email").val()) != ''){
				  var reg_exp = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{1,3}$/;
				  if(!reg_exp.test($("#edit-user-email").val())){
					  errormsg = Drupal.t("Please enter the valid email address");
					  $("#edit-user-email").addClass("error");
					  alert(errormsg);
					  return false;
				  }
				  $("#edit-user-email").removeClass("error");
			  }
		  });
		  $("#edit-update-options").change(function(event){
			  $("#im-user-mangement-list-form #edit-update").attr('disabled',false);
		  });
		   $("#im-user-mangement-list-form #edit-update").click(function(event){			 
		     if ($("#edit-update-options").val() == "content_manager_action_regional") {
		       $("#im-user-mangement-list-form #edit-update").attr("disabled","disabled");
		       /*if(e.keyCode==27 && popupStatus==1){		    	 
		         return false;
		       }*/
		       event.preventDefault();
			   var checkbox_value = '';
			   var num_occures = 0;
			   $("tbody input").each(function() {
			     if ($(this).attr('checked')) {
			       checkbox_value = $(this).val();
				   num_occures++;
			     }
			   });
			  if (checkbox_value == "") {
			    alert(Drupal.t("Please select any one user"));
			    $("#im-user-mangement-list-form #edit-update").attr('disabled',false);
				return false;
			  }
              if (num_occures > 1) {
				alert(Drupal.t("Please select only one user to this role"));
				$("#im-user-mangement-list-form #edit-update").attr('disabled',false);
				return false;
			  }  
			  if (checkbox_value != "" && num_occures == 1) {
			    $.ajax({
				  url: '/admin/im/user-add/regional',
				  type: 'POST',
				  data: {'role' : 'content_manager_action_regional', 'user_id' : checkbox_value},
				  success: function (data, textStatus, jqXHR) {
				    if (data == "SUCCESS") {
				      jQuery("#rmp_popup a").trigger("click");
					  return false;	
				    }
				    else if(data == "USER EXITS") {
				    	alert("This user is already registered with content_manager_action_regional role.");
				    	return false;
				    }
				  },
				  error: function (jqXHR, textStatus, errorThrown) {					  
				  }
			   });
			   $("#im-user-mangement-list-form #edit-update").attr('disabled',false);
			   return false;					      
			}
		  }
		    event.stopImmediatePropagation();
	    });
	  }
})(jQuery);
