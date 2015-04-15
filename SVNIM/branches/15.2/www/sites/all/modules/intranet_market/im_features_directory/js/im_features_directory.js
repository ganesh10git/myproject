/**
*
*/
(function($) {
  Drupal.behaviors.im_features_directory = {};
  Drupal.behaviors.im_features_directory.attach = function(context) {
    //Removed the directory node which are not fetching data from webservices.
    $(".im-app-directory .app-teasers").each(function () {
      if (!$(this).is(":visible")) {
        $(this).remove();
      }
    });
    
    var inc = 1;
    var last = '';
    $(".view-content div").each(function (index, value) {
      if ($(this).attr("class").indexOf('im-app-directory') != -1) {
        inc = 1;
        last = '';
      }
      if ($(this).attr("class").indexOf('app-teasers') != -1) {
        last = '';
        if (inc % 4 == 0) {
          last = 'last-count';
        }
        inc++;
        $(this).addClass(last);
      }
    }); 
  }
})(jQuery);