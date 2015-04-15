/**
 *@file Radio button toggle 
 */
(function($) {
  Drupal.behaviors.im_user_product_guide_form = {};
  Drupal.behaviors.im_user_product_guide_form.attach = function(context) {
	  
    if($("#edit-pg-url-textbox").val()!= ''){
    	$("#edit-pg-url-radio-url").attr("checked" , true);
    	$('#edit-pg-ldap-fr-tag-textbox').attr("disabled", true);
    }
    if($("#edit-pg-ldap-fr-tag-textbox").val()!= ''){
    	$("#edit-pg-ldap-fr-tag-radio-ldap-fr-tag").attr("checked" , true);
    	$('#edit-pg-url-textbox').attr("disabled", true);
    }
	  
    $("#edit-pg-url-radio-url").click(function(){
      if($("input[name='pg_url_radio']:radio:checked").val()== "url"){
        $("#edit-pg-ldap-fr-tag-radio-ldap-fr-tag").attr("checked" , false );
        $('#edit-pg-ldap-fr-tag-textbox').attr("disabled", true);
        $('#edit-pg-url-textbox').attr("disabled", false);
      }
    });
    $("#edit-pg-ldap-fr-tag-radio-ldap-fr-tag").click(function(){
      if($("input[name='pg_ldap_fr_tag_radio']:radio:checked").val()=="ldap_fr_tag"){
        $("#edit-pg-url-radio-url").attr("checked" , false );
        $('#edit-pg-url-textbox').attr("disabled", true);
        $('#edit-pg-ldap-fr-tag-textbox').attr("disabled", false); 
      }
    });
  }
})(jQuery);
