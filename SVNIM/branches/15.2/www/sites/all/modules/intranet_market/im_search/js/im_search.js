/**
 * @file
 * file for search.
 */
(function($) {
	jQuery(document).ready(function(){
		jQuery('#edit-f4-datepicker-popup-0').focus();
		jQuery('#edit-f5-datepicker-popup-0').focus();
		jQuery('#edit-f7').focus();
		jQuery('#edit-f6').click(function(){
			document.getElementById("im-search-block-form").reset();
		});
		jQuery("#results_per_page").change(function(){
			var url = window.location;
			var urlarray = url.toString();
			urlarray = urlarray.split("?");
			urlarraylength = urlarray.length;

			if (urlarraylength == 2) {
				var urlarray1 = url.toString();
				urlarray1 = urlarray1.split("f9=");
				urlarraylength1 = urlarray1.length;
				if (urlarraylength1 == 2) {
				  urlarray1[1] = jQuery(this).val();
				  url = urlarray1.join("f9=");
				}
				else {
				  url = url + "&f9=" + jQuery(this).val();
				}
			}
			else {
				url = url + "?f9=" + jQuery(this).val();
			}
			
			window.location = url;
		});
	});
})(jQuery);