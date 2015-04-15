/**
 * @file
 * js file for IM widgets
 */
/**
 * function for show and hide widgets
 */
(function($) {
  Drupal.behaviors.im_widgets_block = {};
  Drupal.behaviors.im_widgets_block.attach = function(context) {
	  $(".widget_teaser").click(function(){
		  $(".widget_detail").addClass('four-enable');
		  $("#content-column").addClass('widgets-view');
		  if (!$('.widget_teaser').hasClass('extra-class')) {
			  $('.additional-four').hide();
			  $('.more-agendas-ten').show();		  
		  }
	  });	
	  $(".widget_detail").click(function(){
		  $(".widget_detail").removeClass('four-enable');
	      $("#content-column").removeClass('widgets-view');
	      $('.additional-four').show();
	      $('.more-agendas-ten').hide();
      });
	 
	  $(".widget_teaser").click(function(){
		  $(".widget_detail").show();
		  $(".weather-wrapper").show();
		  $(".sp-widget-detail").show();
		  $(".widget_teaser").hide();
		  $(".messages-item-list").show();
	  });
  
  $(".widget_detail").click(function(){
	  $(".widget_detail").hide();
	  $(".weather-wrapper").hide();
	  $(".widget_teaser").show();
	  $(".sp-widget-detail").hide();
	  $(".messages-item-list").hide();
  });
  $(window).load(function(){
	  $(".messages-item-list").hide();
  });
 $(".info-class li.first img").mouseenter(function(){
	  this.src = "/sites/all/modules/intranet_market/im_widgets/images/info_teaser_ho.png";
   });
  $(".info-class li.first img").mouseout(function(){
	  this.src = "/sites/all/modules/intranet_market/im_widgets/images/info_teaser.png";
  });
  $(".weather-class li.first img").mouseenter(function(){
	  this.src = "/sites/all/modules/intranet_market/im_widgets/images/weather_teaser_ho.png";
    });
  $(".weather-class li.first img").mouseout(function(){
	  this.src = "/sites/all/modules/intranet_market/im_widgets/images/weather_teaser.png";
    });
  $(".plan-class li.first img").mouseenter(function(){
	  this.src = "/sites/all/modules/intranet_market/im_widgets/images/plan_teaser_ho.png";
    });
  $(".plan-class li.first img").mouseout(function(){
	  this.src = "/sites/all/modules/intranet_market/im_widgets/images/plan_teaser.png";
    });
  /*
  $(".mail-class li.first img").mouseenter(function(){
	  this.src = "/sites/all/modules/intranet_market/im_widgets/images/mail_teaser_ho.png";
    });
  $(".mail-class li.first img").mouseout(function(){
	  this.src = "/sites/all/modules/intranet_market/im_widgets/images/mail_teaser.png";
    });*/
  jQuery(document).ready(function(){
	$('.sp-today').css('height', (Drupal.settings.widget_height * 22)+ 3 + 'px');
	var obj = $.parseJSON(Drupal.settings.tempObj);
    $(".celsius").click(function(){
      $('.celsius').addClass('active');
      $('.fahrenheit').removeClass('active');
      for (var i=0; i<5; i++){
    	$('.temp-value').html(obj['curr_temp'].C);
        $('.max-'+i).html(obj[i].tempMaxC+"°");
        $('.min-'+i).html(obj[i].tempMinC+"°");
      }	
    });
    $(".fahrenheit").click(function(){
    	$('.fahrenheit').addClass('active');
    	$('.celsius').removeClass('active');
      for (var i=0; i<5; i++){
    	$('.temp-value').html(obj['curr_temp'].F);
        $('.max-'+i).html(obj[i].tempMaxF+"°");
        $('.min-'+i).html(obj[i].tempMinF+"°");
      }
    });
  });
//js for goto top of the page.
	  $(".go_top_link").click(function() {
	  $("html, body").animate({ scrollTop: 0 }, "slow");
	  return false;
	});
  }
})(jQuery);