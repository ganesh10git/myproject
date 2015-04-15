(function($) {
  Drupal.behaviors.im_cuwa = {};
  Drupal.behaviors.im_cuwa.attach = function(context) {
    window.xtnv = document;        //parent.document or top.document or document         
    window.xtsite = Drupal.settings.im_cuwa.xtsite;
    window.xtn2 = Drupal.settings.im_cuwa.xtn2;        // level 2 site ID
    window.xtpage = Drupal.settings.im_cuwa.xtpage;  //page name 
    var xtdi = "";        //implication degree
    var xt_multc = "";  //all the xi indicators (like "&x1=...&x2=....&x3=...")
    var xt_an = Drupal.settings.im_cuwa.xt_an;         //user ID
    var x1 = Drupal.settings.im_cuwa.x1;	//&x1 indicator
    var x2 = Drupal.settings.im_cuwa.x2;	//&x2 indicator
    var x3 = Drupal.settings.im_cuwa.x3;    //&x3 indicator
    var x4 = Drupal.settings.im_cuwa.x4;    //&x4 indicator
    var x5 = Drupal.settings.im_cuwa.x5;    //&x5 indicator
    var x6 = Drupal.settings.im_cuwa.x6;    //&x5 indicator
/*    if (!xt_an) {
      xt_an = readCookie('Drupal.visitor.cuwa_cuid');
      Drupal.settings.im_cuwa.xt_an = xt_an;
    }*/

      if (x1) {
        xt_multc = xt_multc + '&x1='+x1;
      }
      if (x2) {
        xt_multc = xt_multc + '&x2='+x2;
      }
      if (x3) {
        xt_multc = xt_multc + '&x3='+x3;
      }
      if (x4) {
        xt_multc = xt_multc + '&x4='+x4;
      }
      if (x5) {
        xt_multc = xt_multc + '&x5='+x5;
      }
      if (x6) {
          xt_multc = xt_multc + '&x6='+x6;
        }
    var xt_ac = "";        //category ID
    //do not modify below
    if (window.xtparam!=null){
      if( window.xtparam.indexOf("&ac=") == -1 || window.xtparam.indexOf("&an=") == -1 ){
        window.xtparam+="&ac="+xt_ac+"&an="+xt_an+xt_multc;
      }
    }
    else{window.xtparam="&ac="+xt_ac+"&an="+xt_an+xt_multc;};

    // Add xtcore script to the page
    $('body').append('<script type="text/javascript" src="/' + Drupal.settings.im_cuwa.xtcore_path + '"></script>');
};


/*function readCookie(name) {
  var nameEQ = name + "=";
  var ca = document.cookie.split(';');
  for(var i=0;i < ca.length;i++) {
    var c = ca[i];
    while (c.charAt(0)==' ') c = c.substring(1,c.length);
    if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
  }
  return null;
}*/

})(jQuery);
