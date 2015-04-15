/**

 *@file : To add default values to regional profiles. 
 */

(function($) {
  Drupal.behaviors.regional_profiles_node_form = {};
  Drupal.behaviors.regional_profiles_node_form.attach = function(context) {  
  $(document).ready(function() { });
  /*
   * UATIM_590 - POP up reloading issue while after session expired in the portal has resolved. 
   */
  $('a.ctools-use-modal').click(function (e) {
   $.ajax({ url: '/user_sess_info', type: 'POST', success:function(data){   console.log(data.myval); },
	  error:function(){ Drupal.CTools.Modal.dismiss(); window.location.href = ''; return false;
      }
    }); 
  });
  $(".close").click(function(e) {
	  Drupal.settings.profile_options = '';
	  Drupal.settings.profile_node_edit = '';
  });
  $("#edit-rmp-cancel").click(function(e) {
	  Drupal.settings.profile_options = '';
	  Drupal.settings.profile_node_edit = '';
  });
  $(".user-profile-submit").click(function(e){
	  Drupal.settings.profile_options = '';
	  Drupal.settings.profile_node_edit = '';
  });
  
  var profile_node_edit = Drupal.settings.profile_node_edit;
  if(profile_node_edit){
	  var items = $('.field_regional_profile_options_sel option');
	  var list = $('.field_regional_profile_options_unsel');
	  var profile_options = Drupal.settings.profile_options;
	  $.each(items, function(index, item) {
		  if(profile_options){
			  if(!profile_options[item.value]){
				jQuery(list).append('<option value="' + item.value + '">' + item.text + '</option>');
			    $('.field_regional_profile_options_sel option[value='+item.value+']').remove();
		      }
		  }
		  else{
		 	jQuery(list).append('<option value="' + item.value + '">' + item.text + '</option>');
		    $('.field_regional_profile_options_sel option[value='+item.value+']').remove();
		  }
	  });	    
  }
  else {
    var sel_items = $('.field_regional_profile_options_sel option');
    var sel_list = $('.field_regional_profile_options_unsel');
    if($('form').hasClass('node-regional_profiles-form')){
	    $.each(sel_items, function(index, item) {
		   	sel_list.append('<option value="' + item.value + '">' + item.text + '</option>');
		    $('.field_regional_profile_options_sel option[value='+item.value+']').remove();
	    });
    }
  }
  }
})(jQuery);
