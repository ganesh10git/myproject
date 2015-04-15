/**

 *@file Add drag and drop from one table to another table. 
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
  Drupal.behaviors.preferred_store_node_form = {};
  Drupal.behaviors.preferred_store_node_form.attach = function(context) {
  $("#field_preferred_dr_cf").attr("class", "");
  $("#field_preferred_dr_cf").dblclick( function (event) {
    event.preventDefault();
    event.stopImmediatePropagation();
    return false;
  });
  $(window).load(function() {
    $("#unavail_filtered_store_count").text($(".field_preferred_store_options_unsel option").length);
    $("#avail_filtered_store_count").text($(".field_preferred_store_options_sel option").length);
    $(".store-preference-bottomsec .multiselect_labels .label_selected div").text($(".field_preferred_store_options_sel option").length);
    Drupal.preferred_store_node_form.store_count_validate();
  });
  $(document).ready(function() {
	  //Show the Dropdown option for the criteria item type is 5
	  $('[name^="field_preferred_criteria_set[und][0][field_auto_complete_value_type5][und][]"]').hide();
	  var elem_count = $(this).find('[name*="field_preferred_user_operator"]').length;
	  for(i=0;i<elem_count;i++){
		  if($('select[name="field_preferred_criteria_set[und]['+i+'][field_preferred_user_operator][und]"]').find('option:contains("In")').length===1){
			  $('[name^="field_preferred_criteria_set[und]['+i+'][field_auto_complete_value_type5][und][]"]').show();
			  $('[name^="field_preferred_criteria_set[und]['+i+'][field_auto_complete_value_type5][und][]"]').addClass("type5-select");
			  $('[id^="edit-field-preferred-criteria-set-und-'+i+'-field-preferred-auto-complete-und-0-value"]').hide();
		  }else{
			  $('[name^="field_preferred_criteria_set[und]['+i+'][field_auto_complete_value_type5][und][]"]').hide();
			  $('[id^="edit-field-preferred-criteria-set-und-'+i+'-field-preferred-auto-complete-und-0-value"]').show();
		  }
	  }
    $("#avail_filtered_store_count").text($(".field_preferred_store_options_sel option").length);
    $("#unavail_filtered_store_count").text($(".field_preferred_store_options_unsel option").length);
    $(".store-preference-bottomsec .multiselect_labels .label_selected div").text($(".field_preferred_store_options_sel option").length);
    Drupal.preferred_store_node_form.store_count_validate();
  });
  $(".multiselect-add-processed a").live("click", function (event) {
    $("#unavail_filtered_store_count").text($(".field_preferred_store_options_unsel option").length);
    $("#avail_filtered_store_count").text($(".field_preferred_store_options_sel option").length);
    $(".store-preference-bottomsec .multiselect_labels .label_selected div").text($(".field_preferred_store_options_sel option").length);
    Drupal.preferred_store_node_form.store_count_validate();
    Drupal.preferred_store_node_form.checkboxvalidate();
  });
  $(".multiselect-remove-processed a").live("click", function (event) {
    $("#avail_filtered_store_count").text($(".field_preferred_store_options_sel option").length);
    $("#unavail_filtered_store_count").text($(".field_preferred_store_options_unsel option").length);
    $(".store-preference-bottomsec .multiselect_labels .label_selected div").text($(".field_preferred_store_options_sel option").length);
    Drupal.preferred_store_node_form.store_count_validate();
    Drupal.preferred_store_node_form.checkboxvalidate();
  });
  $(".field_preferred_store_options_unsel").dblclick( function (event) {
    $("#unavail_filtered_store_count").text($(".field_preferred_store_options_unsel option").length);
    $("#avail_filtered_store_count").text($(".field_preferred_store_options_sel option").length);
    $(".store-preference-bottomsec .multiselect_labels .label_selected div").text($(".field_preferred_store_options_sel option").length);
    Drupal.preferred_store_node_form.store_count_validate();
    Drupal.preferred_store_node_form.checkboxvalidate();
  });
  $(".field_preferred_store_options_sel").dblclick( function (event) {
    $("#avail_filtered_store_count").text($(".field_preferred_store_options_sel option").length);
    $("#unavail_filtered_store_count").text($(".field_preferred_store_options_unsel option").length);
    $(".store-preference-bottomsec .multiselect_labels .label_selected div").text($(".field_preferred_store_options_sel option").length);
    Drupal.preferred_store_node_form.store_count_validate();
    Drupal.preferred_store_node_form.checkboxvalidate();
    jQuery('.field_preferred_store_options_sel').moveSelectionTo(jQuery('.field_preferred_store_options_unsel'));
  });
  $(".field_preferred_store_options_unsel").click( function (event) {
    $("#unavail_filtered_store_count").text($(".field_preferred_store_options_unsel option").length);
    $("#avail_filtered_store_count").text($(".field_preferred_store_options_sel option").length);
    $(".store-preference-bottomsec .multiselect_labels .label_selected div").text($(".field_preferred_store_options_sel option").length);
    Drupal.preferred_store_node_form.store_count_validate();
  });
  $(".field_preferred_store_options_sel").click( function (event) {
    $("#avail_filtered_store_count").text($(".field_preferred_store_options_sel option").length);
    $("#unavail_filtered_store_count").text($(".field_preferred_store_options_unsel option").length);
    $(".store-preference-bottomsec .multiselect_labels .label_selected div").text($(".field_preferred_store_options_sel option").length);
    Drupal.preferred_store_node_form.store_count_validate();
  });
  
  /*jQuery('.field_preferred_store_options_unsel').selectAll();
  jQuery('.field_preferred_store_options_unsel').moveSelectionTo(jQuery('.field_preferred_store_options_sel'));*/
  //Function to handle when the  Select All is checked.
  //modified for FATIM-638
  jQuery(".form-item-preferred-store-checkbox-avl .form-checkbox").click(function () {
	  if ($(this).attr('checked')) {
		  if ( $.browser.msie ) {
			  var options = '';
			  $(".field_preferred_store_options_unsel option").each(function(){
				  options += '<option value="' + this.value + '" selected="selected">' + this.text + '</option>'
			  });
			  $(".field_preferred_store_options_unsel").html(options);
		  }
		  else {
		    jQuery(".field_preferred_store_options_unsel option").attr('selected', 'selected');
		  }
	  }
	  else {
		  jQuery(".field_preferred_store_options_unsel option").removeAttr("selected");
	  }
  });
  
  jQuery(".preferred_do").change(function () {
    jQuery('#field_preferred_dr_cf').selectAll();
  });
  jQuery("input[name=field_preferred_criteria_set_add_more]").click(function (e) {
    e.preventDefault();
    jQuery("#field_preferred_dr_cf option:selected").removeAttr("selected");
  });
  jQuery("#edit-preferred-cancel").click(function (e) {
    e.preventDefault();
    $("#modalBackdrop").hide();
    $("#modalContent").hide();
    $("#modalBackdrop").remove();
    $("#modalContent").remove();
  });
  
  jQuery(".field-add-more-submit").click(function (e) {
    e.preventDefault();
    jQuery("#field_preferred_dr_cf option:selected").removeAttr("selected");
  });
  jQuery(".field-remove-submit").click(function (e) {
    jQuery("#field_preferred_dr_cf option:selected").removeAttr("selected");
  });
	jQuery(":reset").click(function () {
		jQuery("#field_preferred_dr_cf option:selected").removeAttr("selected");
	});
	//modified for FATIM-638
	jQuery(".form-item-preferred-store-checkbox-sel .form-checkbox").click(function () {
	  if ($(this).attr('checked')) {
		  if (jQuery(".field_preferred_store_options_sel").length > 0) {
			  if ( $.browser.msie ) {
				  var options = '';
				  $(".field_preferred_store_options_sel option").each(function(){
					  options += '<option value="' + this.value + '" selected="selected">' + this.text + '</option>'
				  });
				  $(".field_preferred_store_options_sel").html(options);
			  }
			  else{
			    jQuery(".field_preferred_store_options_sel option").attr('selected', 'selected');
		      }
		  }
		  else {
			  jQuery(".ajax_rendered_multiselect_box option").attr('selected', 'selected');
		  }
	  }
	  else {
		  if (jQuery(".field_preferred_store_options_sel").length > 0) {
			  jQuery(".field_preferred_store_options_sel option").removeAttr("selected");
		  }
		  else {
			  jQuery(".ajax_rendered_multiselect_box option").removeAttr("selected");
		  }
	  }
	});  
  $(".user-store-preference-submit-sec #edit-submit").click(function(e) {
	  if ( $.browser.msie ) {
		  var options = '';
		  $(".field_preferred_store_options_sel option").each(function(){
			  options += '<option value="' + this.value + '" selected="selected">' + this.text + '</option>'
		  });
		  $(".field_preferred_store_options_sel").html(options);
	  }
	  else {
	    $(".field_preferred_store_options_sel option").attr('selected', 'selected');
	  }
	  var value = jQuery(".field_preferred_store_options_sel").val();
	  var count = value.toString().split(',').length;		  
	  jQuery("#store-count").html(' (' + count + ')');	  
	  });
  $(".user-store-preference-submit-sec #edit-submit--2").click(function(e) {
	  $(".field_preferred_store_options_sel option").attr('selected', 'selected');
	  var value = jQuery(".field_preferred_store_options_sel").val();
	  var count = value.toString().split(',').length;		  
	  jQuery("#store-count").html(' (' + count + ')');	  
	  });
  $(".close").click(function(e) {
	  Drupal.settings.store_options = '';
  });
  $("#edit-preferred-cancel").click(function(e) {
	  Drupal.settings.store_options = '';
  });
  //UATIM-393 fixes.
  $(".user-store-submit").click(function(e){
	  Drupal.settings.store_options = '';
  });
  var location = window.location;
  location = location.toString();
  var preferred_node_edit = Drupal.settings.preferred_node_edit;
  if(preferred_node_edit && ($(".ajax_rendered_multiselect_box_filtered").length == 0)){
	  var items = $('.field_preferred_store_options_sel option');
	  var list = $('.field_preferred_store_options_unsel');
	  var store_options = Drupal.settings.store_options;
	  $.each(items, function(index, item) {
		  if(store_options){
			  if(!store_options[item.value]){
				jQuery(list).append('<option value="' + item.value + '">' + item.text + '</option>');
			    $('.field_preferred_store_options_sel option[value='+item.value+']').remove();
		      }
		  }
		  else{
		 	jQuery(list).append('<option value="' + item.value + '">' + item.text + '</option>');
		    $('.field_preferred_store_options_sel option[value='+item.value+']').remove();
		  }
	  });	  
	  $("#avail_filtered_store_count").text($(".field_preferred_store_options_sel option").length);
	    $("#unavail_filtered_store_count").text($(".field_preferred_store_options_unsel option").length);
	    $(".store-preference-bottomsec .multiselect_labels .label_selected div").text($(".field_preferred_store_options_sel option").length);
	    Drupal.preferred_store_node_form.store_count_validate();	    
   }
  }
  Drupal.preferred_store_node_form = {};
  Drupal.preferred_store_node_form.store_count_validate = function() {
	  if ($(".field_preferred_store_options_unsel option").length > 1) {
	    	$("#left-store-purual").text('s');
	    }
	    else {
	    	$("#left-store-purual").text('');
	    }
	    if ($(".field_preferred_store_options_sel option").length > 1) {
	    	$("#right-store-purual").text('s');
	    }
	    else {
	    	$("#right-store-purual").text('');
	    }
  };
//modified for FATIM-638
  Drupal.preferred_store_node_form.checkboxvalidate = function() {
	  if (jQuery(".field_preferred_store_options_sel").length) {
		  if (jQuery(".field_preferred_store_options_sel option").length == 0) {
			 jQuery(".form-item-preferred-store-checkbox-sel .form-checkbox").attr("checked", false); 
		  }
	  }
	  if (jQuery(".ajax_rendered_multiselect_box").length) {
		  if (jQuery(".ajax_rendered_multiselect_box option").length == 0) {
			 jQuery(".form-item-preferred-store-checkbox-sel .form-checkbox").attr("checked", false);
		  }
	  }
	  if (jQuery(".field_preferred_store_options_unsel").length) {
		  if (jQuery(".field_preferred_store_options_unsel option").length == 0) {
			 jQuery(".form-item-preferred-store-checkbox-avl .form-checkbox").attr("checked", false); 
		  }
	  }
  };
})(jQuery);
