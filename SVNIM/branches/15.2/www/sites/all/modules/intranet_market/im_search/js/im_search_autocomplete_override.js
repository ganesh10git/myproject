/**
 * @file
 * Add commons behaviors
 */

(function($) {
  /**
   * Hides the autocomplete suggestions.
   * override for auto submit on enter  for autonomy search
   */
	if(typeof Drupal.jsAC != 'undefined') {
  Drupal.jsAC.prototype.hidePopup = function (keycode) {
	  var element_name = this.input.name;
	  var element_id = this.input.id;
	// Hide popup.
	    var popup = this.popup;
	    if (popup) {
	      this.popup = null;
	      $(popup).fadeOut('fast', function () { $(popup).remove(); });
	    }
	    
	  if (element_name == 'search_block_form' || element_id == 'om-search' ) {
	    // Select item if the right key or mousebutton was pressed.
	    if (this.selected && ((keycode && keycode != 46 && keycode != 8 && keycode != 27) || !keycode)) {
	      this.input.value = $(this.selected).data('autocompleteValue');
	      this.input.form.submit();
	    }
	    // Hide popup.
	    var popup = this.popup;
	    if (popup) {
	      this.popup = null;
	      $(popup).fadeOut('fast', function () { $(popup).remove(); });
	    }
	    this.selected = false;
	    $(this.ariaLive).empty();
	    if (keycode == 13) {
	      if($(this.input).hasClass('auto_submit') && $(this.input).val()){
	        this.input.form.submit();
	       }
	     }
	  }
	  
   };
  }
  
})(jQuery);
