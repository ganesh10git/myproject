/**
 * @file
 * inc file for user header block.
 */
/**
 * function for menu dropdown in userheader block
 */

(function($) {
  Drupal.behaviors.im_user_userheader_block = {};
  Drupal.behaviors.im_user_userheader_block.attach = function(context) {
    $('#im-search-form-submit-header').click(function(e) {
    	Drupal.behaviors.im_user_userheader_block_func();
//      e.preventDefault();
      //$("#search-block-form").submit();
            
      /*if($('input[name="search_block_form"]').val()!=''){
    	  window.location = '/encode/search/site/' + $('input[name="search_block_form"]').val();
      }else{
    	  window.location = '/search/site';
      }*/
      e.stopImmediatePropagation();
    });
    $('.im_user_portal_time').jclock();
    $('#sub_menu').hide();
    $(".im_user_settings_menu").mouseenter(function(){
      $('#sub_menu').show();
    });
    $(".im_user_settings_menu").mouseleave(function(){
      $('#sub_menu').hide();
    });
    $("#sub_menu").mouseover(function(){
      $('#sub_menu').show();
    });
    $('#sub_menu1').hide();
    $(".im_stores_list_menu").mouseenter(function(){
      $('#sub_menu1').show();
    });
    $(".im_stores_list_menu").mouseleave(function(){
      $('#sub_menu1').hide();
    });
    $("#sub_menu1").mouseover(function(){
      $('#sub_menu1').show();
    });
    //For IE browser to implement placeholder like functionality.
    if ( $.browser.msie ) {
      var search_default_string = $('#edit-search-block-form--2').val();
      search_default_string = search_default_string.toString();
      if (search_default_string == "") {
	      $('#edit-search-block-form--2').val(Drupal.t('Enter your search'));
	      $('#edit-search-block-form--2').css('color', 'grey');
	      $('#edit-search-block-form--2').blur(function() {
	        var $this = $(this);
	        if($this.val() == ''){
	          $this.val(Drupal.t('Enter your search'));
	        }
	      });
	      $('#edit-search-block-form--2').focus(function() {
	        var $this = $(this);
	        if($this.val() == Drupal.t('Enter your search')){
	          $this.val('');
	        }
	      });
      }
    }
    //UATIM-533 to show the selected store on the top- (Set the selected store value on all pages except annuaire,homepage and agenda for the day) ...
    var pathname = window.location.pathname;
    var pathname_split = pathname.split('/');
    if (pathname_split[1] != 'agenda' && pathname_split[1] != 'agenda-day' && pathname_split[1] != 'annuaire' && pathname_split[1] != '') {
    //UATIM-533 fixes [The top link is not made clickable]
      $('.im_stores_list_menu div a').click(function(e){
        return false;
      });
      $('#sub_menu1 li a').click(function(e){
        var url_link = $(this).attr('href');
        if (url_link != '') {
          url_split = url_link.split('/');	
          var store_id = url_split.length-2; 
          var data = "data=" +url_split[store_id];        
          $.ajax({
              url: '/store-selection/"'+url_split[store_id]+'"',
              type: 'POST',
              data: data,
              success: function(a) {
                location.reload();
              }
          });
        }
      return false;
      });
    }
    /***************jclock********************/
  /*
   // Create a newDate() object
    var newDate = new Date();
    setInterval( function() {
    	// Create a newDate() object and extract the seconds of the current time on the visitor's
    	var seconds = new Date().getSeconds();
    	// Add a leading zero to seconds value
    	$(".sec").html(( seconds < 10 ? "0" : "" ) + seconds);
    	},1000);
    	
    setInterval( function() {
    	// Create a newDate() object and extract the minutes of the current time on the visitor's
    	var minutes = new Date().getMinutes();
    	// Add a leading zero to the minutes value
    	$(".min").html(( minutes < 10 ? "0" : "" ) + minutes);
        },1000);
    	
    setInterval( function() {
    	// Create a newDate() object and extract the hours of the current time on the visitor's
    	var hours = new Date().getHours();
    	// Add a leading zero to the hours value
    	$(".hours").text(( hours < 10 ? "0" : "" ) + hours+":");
        }, 1000);
    */
     
    if($("div.apps-submenu-col-1").length){
	$("#my-apps-submenu").css("width", "222px");
	}
	if($("div.apps-submenu-col-2").length){
		$("#my-apps-submenu").css("width", "444px"); 
	}
	if($("div.apps-submenu-col-3").length){
		$("#my-apps-submenu").css("width", "670px"); 
	}
  }  
  Drupal.behaviors.im_user_userheader_block_func = function() {
	  jQuery("#search-block-form").submit();
	  document.getElementById("search-block-form").submit();
  }    
})(jQuery);