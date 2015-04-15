/**
 * @file
 * inc file for holiday and sales plan content type.
 */
/**
 * function to check the calender field has same year or not. 
 */

var week_no = 0; //global variable for storing week number in the carousel
var prev_flag = 0; 
(function($) {
  Drupal.behaviors.im_user_sales_plan_holiday = {};
  Drupal.behaviors.im_user_sales_plan_holiday.attach = function(context) {
    //UATIM-239 [SALES PLAN] Unique URL by Trafic- for default selection of node
    active_class();
    function active_class () {
      var page_url_segments =window.location.pathname.split('/');
        if (parseInt((page_url_segments[5]))) {

          var nid = page_url_segments[5];
          var url_nid = '/sales-plan/content/'+nid;
          var menuChildren = $('a[href="' + url_nid + '"]');
          menuChildren.parent().addClass('active-title');
        }
    }
		jQuery(document).ready(function(){
			week_no = Drupal.settings.current_week; //Starting week of jcarousel
			prev_flag = 0;
			$('#holiday-carousel').jcarousel({
		        start: Drupal.settings.current_week, 
		        scroll: 1,
		        buttonNextHTML: null,
		        buttonPrevHTML: null,
		    });
	    });
		jQuery('.jcarousel-control-next').live('click', function() {
			trigger_update_week('carousel', 'next');
	        return false;
	    });
		jQuery('.jcarousel-control-prev').live('click', function() {
			trigger_update_week('carousel', 'prev');
	        return false;
	    });
		
		$(window).load(function(){
			cellheight();	
	   });
	function cellheight(){
		if ($(".national").length) {
			$('.national').css('height', Drupal.settings.national_height + 'px');
			$('.national').css('line-height', Drupal.settings.national_height + 'px');
		}
		if ($(".regional").length) {
			$('.regional').css('height', Drupal.settings.regional_height + 'px');
			$('.regional').css('line-height', Drupal.settings.regional_height + 'px');
		}
		if ($(".non-food").length) {
			$('.non-food').css('height', Drupal.settings.nonfood_height + 'px');
			$('.non-food').css('line-height', Drupal.settings.nonfood_height + 'px');
		}
		if ($(".pn-national-wrapper").length) {
			$('.pn-national-wrapper').css('height', Drupal.settings.national_height + 'px');
		}
		if ($(".pn-regional-wrapper").length) {
			$('.pn-regional-wrapper').css('height', Drupal.settings.regional_height + 'px');
		}
		if ($(".pn-non-food-wrapper").length) {
			$('.pn-non-food-wrapper').css('height', Drupal.settings.nonfood_height + 'px');
		}
		if ($(".pn-national-today").length) {
			var today_nat_height = Drupal.settings.national_height + 3;
			$('.pn-national-today').css('height', today_nat_height + 'px');
		}
		if ($(".pn-regional-today").length) {
			var today_reg_height = Drupal.settings.regional_height + 3;
			$('.pn-regional-today').css('height', today_reg_height + 'px');
		}
		if ($(".pn-non-alimenaire-today").length) {
			var today_fd_height = Drupal.settings.nonfood_height + 3;
			$('.pn-non-alimenaire-today').css('height', today_fd_height + 'px');
		}
	}	
	/*$('.sp_year_link').live('click', function(e) {		
		var location = $(this).attr("href");
        var url_path_nid = window.location.pathname;
        var url_value = url_path_nid.split("/");
		if (week_no == 0) week_no = 1;
		if (location) {
		  location = location + '/' + week_no;
		  //if an existing node was present redirect to same node.
		  if(url_value.length == 6){
			location = location + '/' + url_value[5];
		  }
		  $(this).attr("href", location);
		}
	});*/

    $('.content-link').live('click', function(e) {
       if ($(".national-title").length) $('.national-title').removeClass('active-title');
       if ($(".regional-title").length) $('.regional-title').removeClass('active-title');
       if ($(".non-alimentare-title").length) $('.non-alimentare-title').removeClass('active-title');
       $(this).parent().addClass('active-title');
       var url_segments = $(this).attr("href").split('/');
       var nid = url_segments[3];
       var data = "nid=" + nid;
       
       //UATIM-239 [SALES PLAN] Unique URL by Trafic
       var url_path =  window.location.pathname;
       var year_reg = 'now';
       var sp_week = Drupal.settings.current_week;
       var change_week = ("0" + sp_week).slice(-2);;
       var url_val = url_path.split("/");
       if (url_val.length >= 3) {
           year_reg = url_val[2];
         }
       var region_value = $("#edit-sp-nothern-region").val();
       window.location.href = "/sales-plan/"+year_reg+"/"+region_value+"/"+change_week+"/"+nid;
        /*$.ajax({
          url: '/sales-plan-replace',
          type: 'POST',
          data: data,
          success: function(responseNode) {
        	$('#sales-content').html(responseNode);
          }
       });*/
    e.preventDefault();
    });
    $("#edit-sp-nothern-region").live('change', function(){
        var region_value = $("#edit-sp-nothern-region").val();
        var year_reg = 'now';
        var week_no_reg = '';      
        var url_path =  window.location.pathname;
        var url_val = url_path.split("/");
        var prev_nid = '';
        if (url_val.length >= 3) {
          year_reg = url_val[2];
        }
        if (url_val.length == 5 && week_no_reg == Drupal.settings.current_week) {
          week_no_reg = Drupal.settings.current_week;
          week_no_reg = '/'+week_no_reg;   
        }
        if (week_no_reg == ""){ 
      	  if (week_no == 0) week_no = 1;
      	  week_no_reg = week_no;
      	  if (week_no_reg > 1 ) {
      		  week_no_reg = week_no_reg + 1;
      	  }
      	  if ($.browser.msie || $.browser.webkit) {
      		week_no_reg = week_no_reg + 1;
      	  }
      	  week_no_reg = '/'+week_no_reg;    
        }
        if (url_val[5]){
          prev_nid = '/' + url_val[5]; 
        } 
        var formatted_week = ("0" + week_no_reg).slice(-2);        
        window.location.href = "/sales-plan/"+year_reg+"/"+region_value+"/"+formatted_week+prev_nid + '?region=selected';
      });
    $("a.special-holiday").live('hover', function(){
    	var id = $(this).attr("id");
    	id =id.toString();
    	if($("#title-"+id).is(':visible')){
        	$("#title-"+id).hide();	
        }else{
        	$("#title-"+id).show();
        }
  	  });
  
/**
 * Update Week number to global variable
 * @param carousel
 * @param state
 */
function trigger_update_week(carousel, state)
{
  if (state == 'next') {
    week_no = week_no+1;	
  }
  //To avoid first time trigerring of state - 'Prev' by Carousel
  if (state == 'prev') {
    week_no = week_no-1;
  }

  $('#spinner').center();
  $('#spinner').show();
  if(state == 'prev' || state == 'next'){
	  var today = new Date();
	  var dd = today.getDate();
	  var mm = today.getMonth()+1;
	  var yy = today.getFullYear();
	  var startDate = yy + '-' + mm + '-' + dd;
    jQuery.ajax({
      type: 'GET',
      data: {date:startDate,type:'ajax',statevalue:state},
      url: '/sales-plan/ajax',
      dataType: 'html',
      success: function(data){displaySalesPlan(data);},
      error: function(jqXHR, textStatus, errorThrown ){
    	  if (jqXHR.status === 0) {
              alert('Not connect.\n Verify Network.');
          } else if (jqXHR.status == 404) {
              alert('Requested page not found. [404]');
          } else if (jqXHR.status == 500) {
              alert('Internal Server Error [500].');
          } else if (exception === 'parsererror') {
              alert('Requested JSON parse failed.');
          } else if (exception === 'timeout') {
              alert('Time out error.');
          } else if (exception === 'abort') {
              alert('Ajax request aborted.');
          } else {
              alert('Uncaught Error.\n' + jqXHR.responseText);
          }
    	  $('#spinner').hide();
      }
    });
  }
}
//Ajax Callback function
function displaySalesPlan(data){
	var html = jQuery(data).find('#holiday-carousel').jcarousel();
	if(jQuery('.sp-header-file-download-link').html() != jQuery(data).find('#holiday-pos-file').html()) {
		var holiday_pos_file = jQuery(data).find('#holiday-pos-file').html();
		jQuery('.sp-header-file-download-link').html(holiday_pos_file);
	}
	Drupal.settings.regional_height = jQuery.cookie('regional_height');
	Drupal.settings.national_height = jQuery.cookie('national_height');
	Drupal.settings.nonfood_height = jQuery.cookie('nonfood_height');
	jQuery('#holiday-carousel').html(html);
	$('#spinner').hide();
	cellheight();
	active_class();
}
jQuery.fn.center = function () {
    this.css("position","fixed");
    this.css("top", ($(window).height() / 2) - (this.outerHeight() / 2) - 180);
    this.css("left", ($(window).width() / 2) - (this.outerWidth() / 2));
    return this;
  };
  $(window).resize(function(){
    $('#spinner').center();
  });
  
  }//behaviour end

})(jQuery);
