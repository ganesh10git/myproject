if (jQuery.browser.msie) {
    function alert() {
      return false;  
    }
  }
  else {
    alert = function(){};
  }
(function($) {
  Drupal.behaviors.im_user_sales_plan_contenttype = {};
  Drupal.behaviors.im_user_sales_plan_contenttype.attach = function(context) {
	  $( document ).ajaxComplete(function(event, xhr, settings) {
		  if (settings.url.indexOf('/autosave/restore') != -1){
			  if($('#edit-field-sp-type-und--2').val()== 'regionale'){
			      $('.form-item-field-sp-regions-und--2 label').show();
			      $('#edit-field-sp-regions-und--2').show();
			    }
			    else{
			      $('.form-item-field-sp-regions-und--2 label').hide();
			      $('#edit-field-sp-regions-und--2').hide();
			    }			  
		  }
	  });
    //hidding the region taxonomy field in sales plan content type if regionale is not selected.
    if($('#edit-field-sp-type-und').val()== 'regionale'){
      $('.form-item-field-sp-regions-und label').show();
      $('#edit-field-sp-regions-und').show();
    }
    else{
      $('.form-item-field-sp-regions-und label').hide();
      $('#edit-field-sp-regions-und').hide();
    }
    $('#edit-field-sp-type-und').change(function(){
      if($('#edit-field-sp-type-und').val() == 'regionale'){
        $('.form-item-field-sp-regions-und label').show();
        $('#edit-field-sp-regions-und').show();
      }
       else{
         $('#edit-field-sp-regions-und').val('_none');
         $('.form-item-field-sp-regions-und label').hide();
         $('#edit-field-sp-regions-und').hide();
       }
    });
    $('#edit-field-sp-type-und--2').change(function(){
        if($('#edit-field-sp-type-und--2').val() == 'regionale'){
          $('.form-item-field-sp-regions-und--2 label').show();
          $('#edit-field-sp-regions-und--2').show();
        }
         else{
           $('#edit-field-sp-regions-und--2').val('_none');
           $('.form-item-field-sp-regions-und--2 label').hide();
           $('#edit-field-sp-regions-und--2').hide();
         }
      });
  }
})(jQuery);