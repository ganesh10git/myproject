/**
* @file JS file to show the Teaser in hover
*/
(function($) {
  Drupal.behaviors.im_custom = {};
  Drupal.behaviors.im_custom.attach = function(context) {
    $( document ).ajaxComplete(function(event, xhr, settings) {    	
      if (settings.url.indexOf('/file/ajax') != -1) {
    	var attachment_url = settings.url;
      	attachment_url = attachment_url.toString();
      	attachment_url = attachment_url.split("/");
        var attachment_name =  attachment_url[3];
        var tableidcreated = '';
        var attachment_name_formated = attachment_name.replace(/[#_]/g,'-');
        tableidcreated = $('#edit-'+attachment_name_formated).find('.sticky-enabled').attr('id');
       if(tableidcreated && ($('#edit-field-holiday-pos-file').hasClass('field-name-field-holiday-pos-file-form') == false)) { 
         var splitedid = tableidcreated.split('--');
         var searchid = splitedid[1].search('-');
         var numberofrow = splitedid[1].substr(0, searchid);
         var attachment_name_formated = attachment_name.replace(/[#_]/g,'-');
         var rowlength = $('#edit-'+attachment_name_formated+'-und--'+numberofrow+'-table tbody tr').length;
         var attached_file_classname = '';
         var fileId = new Array(); 
         if(rowlength > 0) {
           for(j=0;j<rowlength;j++) {
            if((rowlength-1) == j){
              attached_file_classname = ".ajax-new-content";
             }
              fileId[fileId.length]  = jQuery(attached_file_classname+' .form-managed-file [name="'+attachment_name+'[und]['+j+'][fid]"]').val();
            } 
          }
          var l = 1;
          $.each(fileId, function( index, value ) {
            $("#edit-"+attachment_name_formated+" table tbody tr:nth-child("+l+") span.file a").attr('href','/check_file_access/'+value);
            l++;
           });
         } else {
          var fid = '';
          fid = jQuery('#edit-'+attachment_name_formated+' .form-managed-file [name="'+attachment_name+'[und][0][fid]"]').val();
          $("#edit-"+attachment_name_formated+" .form-managed-file span.file a").attr('href','/check_file_access/'+fid);
         }
       event.stopImmediatePropagation();
       }
       if (settings.url.indexOf('/file/ajax') != -1 && xhr.responseText.indexOf("messages error") != -1) {
        $("#file-validation-error").html(xhr.responseText);
        $("input:file").val('');
        $('input[type=file]').each(function(){
        $(this).after($(this).clone(true)).remove();
        });
       $(window).scrollTop(0);
       event.stopImmediatePropagation();
       }        
    });
  }
})(jQuery);
