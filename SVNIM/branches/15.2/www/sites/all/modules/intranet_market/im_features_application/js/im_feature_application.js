/**
 *@file Toggle add and remove link in the application page. 
 */
if (jQuery.browser.msie) {
    function alert() {
      return false;  
    }
  }
  else {
    alert = function(){};
  }
(function($) {
  Drupal.behaviors.im_features_application_togglebutton = {};
  Drupal.behaviors.im_features_application_togglebutton.attach = function(context) {
	  $(".views-more-link").click(function(){
		  return false;
	  });
    if ($("input[name='field_ldap_sso_checkbox[und]']:radio:checked").val()== 1){
      $(".form-item-field-ldap-sso-redirect-und").show();
      $(".form-item-field-app-url-und-0-value").hide();
    }
    if ($("input[name='field_ldap_sso_checkbox[und]']:radio:checked").val()== 0){
      $(".form-item-field-ldap-sso-redirect-und").hide();
      $(".form-item-field-app-url-und-0-value").show();
    }

    var path = location.pathname;
    if ($("input[name='field_app_help_button[und]']:radio:checked").val()== 0){
        $(".form-item-field-app-document-und-0-value").show();
    }
    else {
      $(".form-item-field-app-document-und-0-value").hide();
    }
    	
    if ($("input[name='field_app_help_button[und]']:radio:checked").val()== 1){
      $(".field-name-field-documentation-file-upload-form").show();
    }
    else {
      $(".field-name-field-documentation-file-upload-form").hide();
    }
    
    
    $("#edit-field-ldap-sso-checkbox-und-1").click(function(){
        $(".form-item-field-ldap-sso-redirect-und").show();
        $(".form-item-field-app-url-und-0-value").hide();
      });
    $("#edit-field-ldap-sso-checkbox-und-0").click(function(){
        $(".form-item-field-ldap-sso-redirect-und").hide();
        $(".form-item-field-app-url-und-0-value").show();
    });
    

    //called on click of add/remove button
    $('.field-content a').click(function(e){
      var value = $(this).text();
      var title = $(this).attr('href');
      var title = title.replace('/','')
      var title_val = title.split('/'); 
      if(value == 'Add' || value == 'Ajouter'){
        e.preventDefault();
        xt_click(this, 'C','5',"add::"+title_val[2],'A');
      }
      e.stopImmediatePropagation();
    });
    
    //help button radion button 
    $("#edit-field-app-help-button-und-0").click(function(){
      $(".form-item-field-app-document-und-0-value").show();
      $(".field-name-field-documentation-file-upload-form").hide();
    });
    $("#edit-field-app-help-button-und-1").click(function(){
       $(".field-name-field-documentation-file-upload-form").show();
       $(".form-item-field-app-document-und-0-value").hide();
    });

  }
})(jQuery);