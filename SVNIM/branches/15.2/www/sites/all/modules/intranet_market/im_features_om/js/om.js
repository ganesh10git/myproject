/**
 * 
 */
(function ($) {
  var validaddress = '';
  Drupal.behaviors.im_features_om = {};
  Drupal.behaviors.im_features_om.attach = function(context) {
	  $('.om-top-sec #selected-location').hide();
      jQuery('.om-print').click(function(event){
      window.print();
      });
      jQuery('#om-search').click(function(event){
          var searchvalue = $.trim($(this).val());
          if (searchvalue == Drupal.t("Search procedure")) {
              $(this).val("");
          }
      });
      jQuery('#om-search').blur(function(){
          var searchvalue = $.trim($(this).val());
          if (searchvalue == "") {
              $(this).val(Drupal.t("Search procedure"));
          }
      });
      jQuery('.om-top-sec #selected-location').click(function(event){
          if ($('#operation-model-locations').is(':visible')) {
              $('#operation-model-locations').hide();
          }
          else {
              $('#operation-model-locations').show();
              $('.om-top-sec #selected-location').hide();
          }
      });

      jQuery(".minimizer").click(function(event) {
    		$('.om-top-sec #selected-location').show();
    		$('#operation-model-locations').hide();
    	    $.cookie('noShowMap', 1, { path: '/modele-operationnel' });
    	});
      jQuery('#operation-model-locations div').mouseover(function(event){
          var idval = jQuery(this).attr("id");
          if (idval > 0) {
              $(this).attr("style", "cursor: pointer");
          }
      });
      jQuery('#operation-model-locations div').click(function(event){
          var idval = jQuery(this).attr("id");
          if (idval > 0) {
              var url = window.location;
              url = url.toString();
              url = url.split('?name=documentation');
              if (url.length == 2) {
                  url = url[0];
              }
              else {
                  url = url;
              }              
              var urlarray = url.toString();
              urlarray = urlarray.split("/");
              urlarraylength = urlarray.length;
              var taxoid = urlarray[urlarraylength-1];
              var nodeid = urlarray[urlarraylength-2];
              if (isNaN(taxoid)  == false && isNaN(nodeid) == false) {
                  urlarray[urlarraylength-1] = idval;
              }
              else {
                  if (urlarray[urlarraylength-1] == "modele-operationnel") {
                      urlarray[urlarraylength] = Drupal.settings.om_nid;
                      urlarray[urlarraylength+1] = idval;
                  }
                  else {
                      urlarray[urlarraylength] = idval;
                  }
              }
              url = urlarray.join("/");
              
              if(url.indexOf('?') >= 1){
            	  var string = url.substring(url.indexOf('?'))
                  var new_string = string.split('/');
                  url = url.replace(new_string[0],'');
              }              
              
              if(url.indexOf('/tid') != -1) {
                url = url.replace('/tid','');
              }
              

              if(url.indexOf('?js=1') != -1) {
            	  url = url.replace('?js=1','');
              }
              url = url + '?js=1';
              window.location = url;
            return false;
          }
          event.stopImmediatePropagation();
      });
      
    if ($(".om-body-content").length > 0) {
        var ht = $(".om-right-sec").height();
        var left_side = $(".om-left-sec").height();
        if(left_side > ht) {
          $(".om-menu-sec ul").attr("style", "overflow-y: scroll; overflow-x: hidden; text-align: left; height: " + ht + "px");
          }
        var htmpinner = '';
        $( ".om-body-content h1" ).each(function( index ) {
            htmpinner = htmpinner + '<li><a href="#' + $(this).attr("id") + '">' + $(this).text() + "</a></li>";
        });
        var htmp = '';
        if (htmpinner != "") {
            htmp = '<ul>';
            htmp = htmp + htmpinner;
            htmp = htmp + '</ul>';
        }
        $(".h2-head-lines").html(htmp);
    }
      
    jQuery('.enabled-for-ajax-subdomain-custom').change(function(event){
        domain = jQuery('.enabled-for-ajax-domain-custom').val();
        subdomain = jQuery('.enabled-for-ajax-subdomain-custom').val();
        jQuery.ajax({
              url: '/node/add/operational-model/set_reference_procedure',
              type: 'POST',
              data: {'domain' : domain, 'subdomain' : subdomain},success: function(data) {
                  if (data != "") {
                      data = data.toString();
                      jQuery('#reference-wrapper input').val(data);
                  }
            }
        });
        event.stopImmediatePropagation();
    });
    
    //Trigger the autocomplete after 3 characters on OM procedure search
    jQuery('#om-search').keyup(function(event){
        var searchvalue = $.trim($(this).val());
        if (searchvalue.length < 3) {
        	event.stopImmediatePropagation();
        }
    });
  };
})(jQuery);