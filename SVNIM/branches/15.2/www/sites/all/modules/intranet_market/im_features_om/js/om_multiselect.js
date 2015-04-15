/**
 * 
 */
(function ($) {
  var setdisplayflag = 1;
  Drupal.behaviors.im_features_om_mul = {};
  Drupal.behaviors.im_features_om_mul.attach = function(context) {
      jQuery("#edit-field-om-domain-custom").ajaxStart(function( event, xhr, settings ) {
 		  if (Drupal.settings.url == "/node/add/operational-model/get_subdomain") {
			  jQuery(".enabled-for-ajax-subdomain-custom").attr("disabled", "disabled");
		  }
		  else if (Drupal.settings.url == "/node/add/operational-model/get_macro") {
			  jQuery("#edit-field-om-macro-activity-custom").attr("disabled", "disabled");
		  }
	  });
	  
	  jQuery("#edit-field-om-domain-custom").ajaxComplete(function( event, xhr, settings ) {
		  if (Drupal.settings.url == "/system/ajax") {
			  jQuery(".enabled-for-ajax-subdomain").trigger("change");
		  }
		  if (Drupal.settings.url == "/node/add/operational-model/get_subdomain") {
			  jQuery(".enabled-for-ajax-subdomain-custom").removeAttr("disabled");
		  }
		  else if (Drupal.settings.url == "/node/add/operational-model/get_macro") {
			  jQuery("#edit-field-om-macro-activity-custom").removeAttr("disabled");
		  }
	  }); 
	  //after restore
	  jQuery("#edit-field-om-domain-custom--2").ajaxStart(function( event, xhr, settings ) {
 		  if (Drupal.settings.url == "/node/add/operational-model/get_subdomain") {
			  jQuery(".enabled-for-ajax-subdomain-custom").attr("disabled", "disabled");
		  }
		  else if (Drupal.settings.url == "/node/add/operational-model/get_macro") {
			  jQuery("#edit-field-om-macro-activity-custom--2").attr("disabled", "disabled");
		  }
	  });
	  
	  jQuery("#edit-field-om-domain-custom--2").ajaxComplete(function( event, xhr, settings ) {
		  if (Drupal.settings.url == "/system/ajax") {
			  jQuery(".enabled-for-ajax-subdomain").trigger("change");
		  }
		  if (Drupal.settings.url == "/node/add/operational-model/get_subdomain") {
			  jQuery(".enabled-for-ajax-subdomain-custom").removeAttr("disabled");
		  }
		  else if (Drupal.settings.url == "/node/add/operational-model/get_macro") {
			  jQuery("#edit-field-om-macro-activity-custom--2").removeAttr("disabled");
		  }
	  }); 
	  $( document ).ajaxComplete(function(event, xhr, settings) {
		  if (settings.url.indexOf('/autosave/restore') != -1){
		  		var expert_options_om = Drupal.settings.expert_options;  		
		  		var list = $('.field_om_experts_unsel');
		  		
		  		var op_elements = [];  	
		  		$(".field_om_experts_sel option").each(function(){
			      op_elements.push($(this).val());
				});	
		  		
	  		    var unique_expert_options = [];
	  		    $.each(expert_options_om, function(i, e) {
	  		      if ($.inArray(e, unique_expert_options) == -1) unique_expert_options.push(e);
	  		    });
	  		    
		  		var unsel_expert_options = [];
		  		$.grep(unique_expert_options, function(el) {
		  		        if ($.inArray(el, op_elements) == -1) unsel_expert_options.push(el);
		  		});
		  		
		  		$.each(unsel_expert_options, function(index, value) {
		  				list.append('<option value="' + value + '">' + value + '</option>');
		  		  });
		  	 event.stopImmediatePropagation();
			}		  
	  });
	  /*jQuery('.enabled-for-ajax-domain-custom').trigger('change');*/
	  if (setdisplayflag == 1) {
	  var items = $('.field_om_experts_sel option');
	  var list = $('.field_om_experts_unsel');
	  if($('body').hasClass('page-node-add-operational-model')){
		  var expert_options = Drupal.settings.expert;
		  $.each(items, function(index, item) {
			if(!expert_options[item.value]){
		      list.append('<option value="' + item.value + '">' + item.text + '</option>');
		      $('.field_om_experts_sel option[value='+item.value+']').remove(); 
			}
		  });
	  }
	  if($('body').hasClass('node-type-operational-model')){
		  var expert_options = Drupal.settings.experts;
		  $.each(items, function(index, item) {
			  if(expert_options){
				  if(!expert_options[item.value]){
				    list.append('<option value="' + item.value + '">' + item.text + '</option>');
				    $('.field_om_experts_sel option[value='+item.value+']').remove();
			      }
			  }
			  else{
			 	list.append('<option value="' + item.value + '">' + item.text + '</option>');
			    $('.field_om_experts_sel option[value='+item.value+']').remove();
			  }
		  });
	  }
	  setdisplayflag = 0;
	  }
	  //var expert_options = Drupal.settings.expert;
	  
	  //publication field readonly and hide the date popup
	 $("#edit-field-om-publication-period-und-0-value2-datepicker-popup-0").attr('readonly', 'readonly');
	  $(".form-item-field-om-publication-period-und-0-value2-date").click(function(e){
		  e.preventDefault();
		  $(".ui-datepicker").hide();
	  });
	  $(".form-item-field-om-publication-period-und-0-value2-date").focus(function(e){
		  e.preventDefault();
		  $(".ui-datepicker").hide();
	  });
	  
	 jQuery('.enabled-for-ajax-domain-custom-field').change(function(event){
       subdomain_macro_follow_request();
	 });
	
	jQuery('.enabled-for-ajax-subdomain-custom').change(function(event){
	  macrovalues();
	  domain = jQuery('.enabled-for-ajax-domain-custom-field  option:selected').val();
	  subdomain = jQuery('.enabled-for-ajax-subdomain-custom  option:selected').val();
		jQuery.ajax({
		      url: '/node/add/operational-model/set_reference_procedure',
		      type: 'POST',
		      data: {'domain' : domain, 'subdomain' : subdomain},success: function(data) {
		    	  if (data != "") {
		    		  data = data.toString();
		    		  jQuery('#reference-wrapper input').val(data);
		    		  if($('#edit-field-om-reference-procedure-code').length<=0){
					      var label_value = jQuery('#edit-field-om-reference-procedure-code--2 label').html();
					      jQuery('#edit-field-om-reference-procedure-code--2').html('<label for="edit-field-om-reference-procedure-code--2">' + label_value + '</label>' + data);
		    		  }else{
		    			  var label_value = jQuery('#edit-field-om-reference-procedure-code label').html();
						  jQuery('#edit-field-om-reference-procedure-code').html('<label for="edit-field-om-reference-procedure-code">' + label_value + '</label>' + data);
		    		  }
		    	  }
			}
		});
	  //event.stopImmediatePropagation();
	});
	function macrovalues() {
		subdomain = jQuery('.enabled-for-ajax-subdomain-custom option:selected').val();
		jQuery.ajax({
		      url: '/node/add/operational-model/get_macro',
		      type: 'POST',
		      data: {'subdomain' : subdomain},success: function(data) {
		    	  if (data != "") {
				      var dynamic_subdomain_value = Drupal.settings.dynamic_macro_default_value;
		    		  data = data.toString();
					  data = data.split("#####");
					  subdomain_options_value_set = data[0];
					  subdomain_options_text_set = data[1]; 
					  subdomain_options_value_set = subdomain_options_value_set.toString();
					  subdomain_options_text_set = subdomain_options_text_set.toString();
					  subdomain_options_value_set = subdomain_options_value_set.split("***");
					  subdomain_options_text_set = subdomain_options_text_set.split("***");
					  if($('#edit-field-om-macro-activity-custom').length<=0){
						  var subdomain_options = $('#edit-field-om-macro-activity-custom--2');
						  subdomain_default_value = '';
						  if ($("#edit-field-om-macro-activity-custom--2 option:selected").val()) {
						    var subdomain_default_value = $("#edit-field-om-macro-activity-custom--2 option:selected").val();
						    subdomain_default_value = subdomain_default_value.toString();
					      }
						  if (dynamic_subdomain_value) {
						    subdomain_default_value = dynamic_subdomain_value;
						  }
						  $("#edit-field-om-macro-activity-custom--2 option").remove();
					  }
					  else{
						  var subdomain_options = $('#edit-field-om-macro-activity-custom');
						  subdomain_default_value = '';
						  if ($("#edit-field-om-macro-activity-custom option:selected").val()) {
						    var subdomain_default_value = $("#edit-field-om-macro-activity-custom option:selected").val();
						    subdomain_default_value = subdomain_default_value.toString();
					      }
						  if (dynamic_subdomain_value) {
						    subdomain_default_value = dynamic_subdomain_value;
						  }
						  $("#edit-field-om-macro-activity-custom option").remove();
					  }
					  for(i=0; i<subdomain_options_value_set.length; i++) {
		                subdomain_options.append('<option value="' + subdomain_options_value_set[i] + '">' + subdomain_options_text_set[i] + '</option>');
					  }
					  for(i=0; i<subdomain_options_value_set.length; i++) {
					    if (subdomain_default_value != "" && subdomain_default_value == subdomain_options_value_set[i]) {
		                  subdomain_options.val(subdomain_options_value_set[i]);
						}
					  }
		    	  }
			}
		});
	};
	
	/* Recalculate the Publication To Date when Publication From Date is changed */
	$("#edit-field-om-publication-period-und-0-value-datepicker-popup-0").datepicker({
    	dateFormat: 'dd/mm/yy',
		defaultDate: new Date(),
	});    
	$("#edit-field-om-publication-period-und-0-value2-datepicker-popup-0").datepicker({
		dateFormat: 'dd/mm/yy',
		defaultDate: new Date(),
	});
	$('#edit-field-om-publication-period-und-0-value-datepicker-popup-0').change(function(){
		  var om_todate = Drupal.settings.im_om_todate.om_to_date;
	      var date1 = $('#edit-field-om-publication-period-und-0-value-datepicker-popup-0').datepicker('getDate');
	      var date = new Date( Date.parse( date1 ) ); 
	      date.setMonth( date.getMonth() + parseInt(om_todate));

	      var newDate = date.toDateString(); 
	      newDate = new Date(Date.parse(newDate));
	      $('#edit-field-om-publication-period-und-0-value2-datepicker-popup-0').datepicker('setDate', newDate );
	      $('#edit-field-om-publication-period-und-0-value2-datepicker-popup-0').datepicker("refresh");
	});
    jQuery(document).ready(function (){
      subdomain_macro_follow_request();
    });
    function subdomain_macro_follow_request() { 
      domain = jQuery('.enabled-for-ajax-domain-custom-field option:selected').val();
		jQuery.ajax({
		      url: '/node/add/operational-model/get_subdomain',
		      type: 'POST',
		      data: {'domain' : domain},success: function(data) {
		    	  if (data != "") {
				      var dynamic_subdomain_value = Drupal.settings.dynamic_subdomain_default_value;
		    		  data = data.toString();
					  data = data.split("#####");
					  subdomain_options_value_set = data[0];
					  subdomain_options_text_set = data[1]; 
					  subdomain_options_value_set = subdomain_options_value_set.toString();
					  subdomain_options_text_set = subdomain_options_text_set.toString();
					  subdomain_options_value_set = subdomain_options_value_set.split("***");
					  subdomain_options_text_set = subdomain_options_text_set.split("***");
					  
					  var subdomain_options = $('.enabled-for-ajax-subdomain-custom');
					  subdomain_default_value = '';
					  if ($(".enabled-for-ajax-subdomain-custom option:selected").val()) {
					    var subdomain_default_value = $(".enabled-for-ajax-subdomain-custom option:selected").val();
					    subdomain_default_value = subdomain_default_value.toString();
				      }
					  if (dynamic_subdomain_value) {
					    subdomain_default_value = dynamic_subdomain_value;
					  }
					  $(".enabled-for-ajax-subdomain-custom option").remove();
					  for(i=0; i<subdomain_options_value_set.length; i++) {
		                subdomain_options.append('<option value="' + subdomain_options_value_set[i] + '">' + subdomain_options_text_set[i] + '</option>');
					  }
					  for(i=0; i<subdomain_options_value_set.length; i++) {
					    if (subdomain_default_value != "" && subdomain_default_value == subdomain_options_value_set[i]) {
		                  subdomain_options.val(subdomain_options_value_set[i]);
						}
					  }
					  macrovalues();
					  domain = jQuery('.enabled-for-ajax-domain-custom-field  option:selected').val();
					  subdomain = jQuery('.enabled-for-ajax-subdomain-custom  option:selected').val();
						jQuery.ajax({
							  url: '/node/add/operational-model/set_reference_procedure',
							  type: 'POST',
							  data: {'domain' : domain, 'subdomain' : subdomain},success: function(data) {
								  if (data != "") {
									  data = data.toString();
									  jQuery('#reference-wrapper input').val(data);
									  if($('#edit-field-om-reference-procedure-code').length<=0){
									  var label_value = jQuery('#edit-field-om-reference-procedure-code--2 label').html();
									  jQuery('#edit-field-om-reference-procedure-code--2').html('<label for="edit-field-om-reference-procedure-code--2">' + label_value + '</label>' + data);
									  }else{
										  var label_value = jQuery('#edit-field-om-reference-procedure-code label').html();
										  jQuery('#edit-field-om-reference-procedure-code').html('<label for="edit-field-om-reference-procedure-code">' + label_value + '</label>' + data);
									  }
								  }
							}
						});
		    	  }
			}
		});
		//event.stopImmediatePropagation();
		
	}	
  };
})(jQuery);