(function($) {
  Drupal.behaviors.im_features_questionnaire = {};
  Drupal.behaviors.im_features_questionnaire.attach = function(context) {	  
   //To set the webform_nid field value in action content type on change of questionnaire dropdown 
    $("#edit-field-webform-list").change(function(){
    if ($("#edit-field-webform-list option:selected").val() == '-none-') {
      $("#edit-field-action-webform-nid-und-0-value").val('');
    }
    else{
      $("#edit-field-action-webform-nid-und-0-value").val($("#edit-field-webform-list option:selected").val());
    }
    });    
    $(".webform-date").blur(function(){    	
    	if($(".webform-date").val() == ''){    		
    	  $(".webform-date").val(Drupal.t('DD/MM/YYYY'));
    	} 
    });
    $(".webform-date").focus(function(){  
        if($(".webform-date").val() == Drupal.t('DD/MM/YYYY')) {    	
    	  $(".webform-date").val('');
        }
    });  
	if ($(".webform-date").length && $(".webform-date").val() == '') {    	
    	$(".webform-date").val(Drupal.t('DD/MM/YYYY'));
    } 
  }
})(jQuery);