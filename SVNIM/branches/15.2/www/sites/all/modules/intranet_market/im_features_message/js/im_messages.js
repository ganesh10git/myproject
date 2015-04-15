/**
 * @file
 * inc file for holiday and sales plan content type.
 */
/**
 * function to check the calender field has same year or not. 
 */

(function($) {
  Drupal.behaviors.im_message = {};
  Drupal.behaviors.im_message.attach = function(context) {
		jQuery(document).ready(function(){
            function carousel_initCallback(carousel) {
                jQuery('.jcarousel-control a').bind('click', function () {
                    carousel.scroll(jQuery.jcarousel.intval(jQuery(this).text()));
                    return false; 
                });

                /*jQuery('#carousel-next').bind('click', function () {
                    carousel.next();
                    return false;
                });

                jQuery('#carousel-prev').bind('click', function () {
                    carousel.prev();
                    return false;
                });*/

                // Pause autoscrolling if the user moves with the cursor over the clip.
        	    carousel.clip.hover(function() {
        	        carousel.stopAuto();
        	    }, function() {
        	        carousel.startAuto();
        	    });

            };
            $('#carousel').jcarousel({
                scroll: 1, animation:700, visible:1, wrap:"both",
                      initCallback: carousel_initCallback,
                      itemVisibleInCallback: {
                          onAfterAnimation: function (c, o, i, s) {
                              i = (i - 1) % $('#carousel li').size();
                              jQuery('.jcarousel-control a').removeClass('active').addClass('inactive');
                              jQuery('.jcarousel-control a:eq(' + i + ')').removeClass('inactive').addClass('active');
                          }
                      }
            });
			
			

	    });

}
})(jQuery);
