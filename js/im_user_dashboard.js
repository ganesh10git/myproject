/**
 * @file JS file to show the Teaser in hover
 */

(function($) {
  Drupal.behaviors.im_user_dashboard = {};
  Drupal.behaviors.im_user_dashboard.attach = function(context) {
	  var js_user = Drupal.settings.im_user_dashboard.variables;	 
	  var data = jQuery.parseJSON(js_user);  
	  $('.content_manager_action_regional').click(function (e) {
		  var val = $(this).attr("id");
		   val = val.toString();
		   if ($(this).attr('checked')) {
			   $(".dashbaord_active_id_" + val).show();
			   $(".dashbaord_deactive_id_" + val).hide();
		   } 
		   else {
			   $(".dashbaord_active_id_" + val).hide();
			   $(".dashbaord_deactive_id_" + val).show();
		   }
	  });
	  $('.content_manager_action_regional').each(function (e) {
		  var val = $(this).attr("id");
		   val = val.toString();
		   if ($(this).attr('checked')) {
			   $(".dashbaord_active_id_" + val).show();
			   $(".dashbaord_deactive_id_" + val).hide();
		   } 
		   else {
			   $(".dashbaord_active_id_" + val).hide();
			   $(".dashbaord_deactive_id_" + val).show();
		   }
	  });
	  
	  $('.role-name').click(function(){
		  var id = $(this).attr("id");
		  if ($('#edit-users-roles-details-'+id).not(':checked')) { 
		    $('#edit-users-roles-details-'+id).attr('checked',true);
		    $(this).closest('tr').toggleClass('selected');
		  }
		});
	  $('#edit-remove').click(function(){
		  var user_names = '';
	    $('.users-checkbox:checked').each(function(){
			var uid = $(this).val();			
		    $.each(data, function(index, value) {
		      if (index == uid) {
		        user_names += value+ '\n';		        
		      }      
		    });		    
		});
	    if (!confirm("Are you sure you want to delete these Users?" +'\n'+user_names)) {
	    	return false;
	    }
	    
	 });
	 Drupal.tableSelect = function () {
       if ($('td input:checkbox', this).length == 0) {
	     return;
	    }
		// Keep track of the table, which checkbox is checked and alias the settings.
		var table = this, checkboxes, lastChecked;
		var strings = { 'selectAll': Drupal.t('Select all rows in this table'), 'selectNone': Drupal.t('Deselect all rows in this table') };
		var updateSelectAll = function (state) {
		// Update table's select-all checkbox (and sticky header's if available).
		$(table).prev('table.sticky-header').andSelf().find('th.select-all input:checkbox').each(function() {
		  $(this).attr('title', state ? strings.selectNone : strings.selectAll);
		  this.checked = state;
		  });
	    };
	    // Find all <th> with class select-all, and insert the check all checkbox.
		$('th.select-all', table).prepend($('<input type="checkbox" class="form-checkbox" />').attr('title', strings.selectAll)).click(function (event) {
		  if ($(event.target).is('input:checkbox')) {
		    // Loop through all checkboxes and set their state to the select all checkbox' state.
		    $('.users-checkbox:checkbox').each(function () {
			  this.checked = event.target.checked;
			  // Either add or remove the selected class based on the state of the check all checkbox.
			  $(this).closest('tr').toggleClass('selected', this.checked);
			});
			// Update the title and the state of the check all box.
			updateSelectAll(event.target.checked);
		  }
		});
	   // For each of the checkboxes within the table that are not disabled.
	   checkboxes = $('td input:checkbox:enabled', table).click(function (e) {
	   // Either add or remove the selected class based on the state of the check all checkbox.
	   $(this).closest('tr').toggleClass('selected', this.checked);
	   // If this is a shift click, we need to highlight everything in the range.
	   // Also make sure that we are actually checking checkboxes over a range and
	   // that a checkbox has been checked or unchecked before.
	   if (e.shiftKey && lastChecked && lastChecked != e.target) {
	     // We use the checkbox's parent TR to do our range searching.
		 Drupal.tableSelectRange($(e.target).closest('tr')[0], $(lastChecked).closest('tr')[0], e.target.checked);
	   }
	   // If all checkboxes are checked, make sure the select-all one is checked too, otherwise keep unchecked.
		updateSelectAll((checkboxes.length == $(checkboxes).filter(':checked').length));
       // Keep track of the last checked checkbox.
	   lastChecked = e.target;
	   });
	 };
   }
 })(jQuery);