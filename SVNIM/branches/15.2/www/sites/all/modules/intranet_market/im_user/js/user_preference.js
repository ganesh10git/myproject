/**
 *@file Add drag and drop from one table to another table. 
 */
(function ($) {
	  Drupal.behaviors.user_preference_form = {
	    attach: function(context) {
	     //Add store search results to Selected options by default.
	      jQuery('.usp_return_store_unsel').selectAll();
	      jQuery('.usp_return_store_unsel').moveSelectionTo(jQuery('.usp_return_store_sel'));
	      
	      $("#edit-usp-validate").click(function(e) {        	 		    
		  $(".usp_return_store_sel option").attr('selected', 'selected');
		  var value = jQuery(".usp_return_store_sel").val();
		  var count = value.toString().split(',').length;		  
		  jQuery("#store-count").html(' (' + count + ')');	  
		  });
	    }
	  };
	})(jQuery);
