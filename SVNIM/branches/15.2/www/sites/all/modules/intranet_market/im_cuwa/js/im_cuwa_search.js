(function($) {
  Drupal.behaviors.im_cuwa_search = {};
  Drupal.behaviors.im_cuwa_search.attach = function(context) {
    var xt_mtcl = Drupal.settings.im_cuwa.xt_mtcl;
    var xt_npg = Drupal.settings.im_cuwa.xt_npg;

    //do not modify below
    if (window.xtparam!=null) {
      window.xtparam += "&mc="+xt_mtcl+"&np="+xt_npg;
    }
    else {
      window.xtparam = "&mc="+xt_mtcl+"&np="+xt_npg;
    };
  };
})(jQuery);