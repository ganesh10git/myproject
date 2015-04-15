/**
 * @file JS file to show the Teaser in hover
 */
  if (jQuery.browser.msie) {
    function alert() {
      return false;  
    }
  }
  else {
    alert = function(){};
  }
(function($) {  
  Drupal.behaviors.im_agenda = {};
  Drupal.behaviors.im_agenda.attach = function(context) {
  /*
   * UATIM_590 - POP up reloading issue while after session expired in the portal has resolved. 
   */
  $('a.ctools-use-modal').click(function (e) {
   $.ajax({ 
	   url: '/user_sess_info', 
	   type: 'POST', 
	   success:function(data){   
//	   console.log(data.myval); 
	   },
	   error:function(){ 
	     Drupal.CTools.Modal.dismiss();
	     window.location.href = ''; 
	     return false;
      }
    }); 
  });	    
  /* Fix for UATIM-504 for IE browser*/
  $("#edit-agenda-day-submit").click(function (e) {
	 e.preventDefault();
	 var window_url = window.location;
	 window_url = window_url.toString();
	 window_url = window_url.split("/");
	 var date_value = $("#edit-user-date-select-datepicker-popup-0").val();
	 date_value = date_value.toString();
	 date_value = date_value.split("/");
	 final_date_value = date_value[2] + date_value[1] + date_value[0]; //Ymd
	 var depart_value = '';
	 var depart_flag = 1;
	 $("#agenda-user-input-department input").each(function () {
		 if ($(this).attr("checked")) {
			 if ($(this).val() == 0) {
				 depart_value = 'all';
				 depart_flag = 0;
			 }
			 if (depart_flag == 1) {
				 depart_value = depart_value + $(this).val() + ',';
			 }
		 }
	 });
	 depart_value = depart_value.replace(/^,|,$/g,'');
	 window_url[4] = final_date_value;
	 window_url[6] = depart_value;
	 window_url_final = window_url.join("/");
	 window.location = window_url_final;
	 return false;
	 e.stopImmediatePropagation();
  });
  $(document).ajaxComplete(function( event,request, settings ) {
	var urls = settings.url;
	if (urls.indexOf("agenda-detail/list") != -1) {
		var flag_error = 0;
		if (settings.iframeSrc) {
			$("#modalContent input").each(function() {
				if ($(this).attr("class").indexOf('error') != -1 && $(this).val() == "") {
					flag_error = 1;
				}
				else if ($(this).attr("class").indexOf('error') != -1 && ($(this).attr('type') == 'checkbox' || $(this).attr('type') == 'radio')) {
					flag_error = 1;
				}				
			});
			$("#modalContent select").each(function() {
				if ($(this).attr("class").indexOf('error') != -1 && $(this).val() == "") {
					flag_error = 1;
				}
			});
			$("#modalContent textarea").each(function() {
				if ($(this).attr("class").indexOf('error') != -1 && $(this).val() == "") {
					flag_error = 1;
				}
			});
			if (flag_error == 0) {
				$("#modalContent").hide();
    			$("#modalBackdrop").hide();
			}
		}
    	event.stopImmediatePropagation();
	}
  });
  $('.load-more-content').click(function(e){
    var selected_date = $(this).attr("class");
    selected_date = selected_date.toString();
    selected_date = selected_date.split(" ");
    selected_date_value = selected_date[2];    
    var id_value = 'agenda-day-' + $(this).attr("id");
    id_value = id_value.toString();
    if ($(this).text() == Drupal.t('Less')) {
      $('.animation_image_load_' + selected_date_value).show();
      hide_aditional_content("#" + id_value, selected_date_value);
      e.stopImmediatePropagation();
    }
    if ($(this).text() == Drupal.t('More')) {
      $('.animation_image_load_' + selected_date_value).show();
      load_aditional_content("#" + id_value, selected_date_value);
      e.stopImmediatePropagation();
    }    
    return false;
  });
  function load_aditional_content(id, selected_date_value) {      
    id = id.toString();
    selected_date_value = selected_date_value.toString();
    var settings_flag = Drupal.settings.date_filters[selected_date_value];
    var targetURL = settings_flag.baseURL + '/view-all-content/';
    var URL = '/view-all-content/';
    var start_date = settings_flag.start_date;
    var store = settings_flag.store;
    var department =  settings_flag.department;
    var classToReplace =  settings_flag.classToReplace;
    var type =  'full';
    jQuery.ajax({
      type: "POST",
      data: {start_date : start_date, store:store, department:department, type:type},
      url: targetURL,
      success: function (response) {
        $("#" + classToReplace).html(response);
        Drupal.attachBehaviors("#content");
        var link_id = id.replace('agenda-day-', '');
        link_id =link_id.toString();
        $(link_id +' a').text(Drupal.t('Less'));
        $('.animation_image_load_' + selected_date_value).hide();       
        $(".widget_detail").addClass('extra-class');
        $(".widget_teaser").addClass('extra-class');
      },
      error: function (jqXHR, textStatus, errorThrown) {
        //callback_function(false);
      },
    });
    return false;
  }
    
    function hide_aditional_content(id, selected_date_value) {
      id = id.toString();
      var type =  'less';
      selected_date_value = selected_date_value.toString();
      var settings_flag = Drupal.settings.date_filters[selected_date_value];
      var targetURL = settings_flag.baseURL + '/view-less-content/';
      var start_date = settings_flag.start_date;
      var store = settings_flag.store;
      var department =  settings_flag.department;
      var classToReplace =  settings_flag.classToReplace;
      jQuery.ajax({
        type: "POST",
        data: {start_date : start_date, store:store, department:department, type:type},
        url: targetURL,
        success: function (response) {
          $(".animation_image").hide();
              $("#" + classToReplace).html(response);
              if (!$(".message-widget-teaser").is(":visible")) {
                  $("#" + classToReplace + " .additional-four").hide();
              }
              Drupal.attachBehaviors("#content");
              var link_id = id.replace('agenda-day-', '');
              link_id =link_id.toString();
              $(link_id +' a').text(Drupal.t('More'));
              
              $('.animation_image_load_' + selected_date_value).hide();
               $(".widget_detail").removeClass('extra-class');
              $(".widget_teaser").removeClass('extra-class');
            },
            error: function (jqXHR, textStatus, errorThrown) {
              //callback_function(false);
            },
        });
      return false;
      }  

  $("#agenda-date-selection-display").hide();
    $(".user-store-preference-submit-sec #edit-submit").click(function(e) {
          var url = window.location;
          url = url.toString();
          if (url.indexOf("node") < 1) {
                $("body").prepend('<div id="please-wait-loading" class="please-wait-loading" style="font-weight:bold; font-size:25px; width:auto; left:45%; top:50%; color:#9A7D78; position:absolute">' + Drupal.t("Please wait...")+ '</div>');
          }
    });
    $(".user-store-preference-submit-sec #edit-submit--2").click(function(e) {
          var url = window.location;
          url = url.toString();
          if (url.indexOf("node") < 1) {
                $("body").prepend('<div id="please-wait-loading" class="please-wait-loading" style="font-weight:bold; font-size:25px; width:auto; left:45%; top:50%; color:#9A7D78; position:absolute">' + Drupal.t("Please wait...")+ '</div>');
          }
    });
    $(window).load(function(){
      $("#edit-user-date-select-datepicker-popup-0").focus();
      $("#edit-user-department").focus();
      $("#please-wait-loading").hide();
      
      $(".agendatype-detailAction input").each(function() {
	    if ($(this).attr("type") == "hidden") {
		  $(this).remove();
	    }
	  });
    }); 
    //make the image clickable in agenda for the day.
    $('.agenda-teaser-title').each(function(){
      var stylevalue = '';
      stylevalue = $(this).attr("style");
      $(this).children('a').attr("style", stylevalue);
    });
  $(".action_image").click(function(){
    $(this).children(".agenda-teaser-title").children("a").trigger("click");
  });

  $(".agenda-teaser-popup").mouseleave(function(){
    if ($(".agenda-teaser-popup").length) {
      $(".agenda-teaser-popup").removeClass("overlay-class");
    }
  });
  $(".agenda-day-row").mouseleave(function(){
    if ($(".agenda-teaser-popup").length) {
      $(".agenda-teaser-popup").removeClass("overlay-class");
    }
  });
  
    $("a.agenda-teaser-min").mousemove(function(){
      var id = $(this).attr("id");//teaser-5
      id =id.toString();
      if($(".agenda-teaser-popup").hasClass("overlay-class")){
        $(".agenda-teaser-popup").removeClass("overlay-class");
      }
      $("#detail-"+id).addClass("overlay-class");
       $("#detail-"+id).mouseleave(function () {
           $("#detail-"+id).removeClass("overlay-class");
         });
    });
    $("#edit-field-agenda-source-und-0-value").attr('readonly', true);
    $("#add-user-to-form").click(function(e) {
       if($("input:radio[name='user_results']:checked").val() != null) {
      $("#edit-field-agenda-source-und-0-value").val($("input:radio[name='user_results']:checked").val());
      $("#edit-field-agenda-source-und-0-value--2").val($("input:radio[name='user_results']:checked").val());
      e.stopImmediatePropagation();
      $(".close").trigger("click");
    }
        return false;
      });
    
    $("#reset-user-form").click(function(e) {
      $("#user-first-name").val("");
      $("#user-last-name").val("");      
        // e.stopImmediatePropagation();
          //return false;
      });
    
    $("#cancel-user-form").click(function(e) {
      $(".close").trigger("click");      
         e.stopImmediatePropagation();
          return false;
      });
    
    $("#edit-field-publication-from-date-und-0-value-datepicker-popup-0").datepicker({
      dateFormat: 'dd/mm/yy',
      defaultDate: new Date(),
    });
    $("#edit-field-publication-to-date-und-0-value-datepicker-popup-0").datepicker({
      dateFormat: 'dd/mm/yy',
      defaultDate: new Date(),
    });
    //Publication End date for the Action Content type.
    $('#action-node-form #edit-field-publication-from-date-und-0-value-datepicker-popup-0').change(function(){
      var agenda_todate = Drupal.settings.im_agenda.action_to_date;
        var date1 = $('#edit-field-publication-from-date-und-0-value-datepicker-popup-0').datepicker('getDate');
        var date = new Date( Date.parse( date1 ) ); 
        date.setMonth( date.getMonth() + parseInt(agenda_todate));

        var newDate = date.toDateString(); 
        newDate = new Date(Date.parse(newDate));
        $('#edit-field-publication-to-date-und-0-value-datepicker-popup-0').datepicker('setDate', newDate );
        $('#edit-field-publication-to-date-und-0-value-datepicker-popup-0').datepicker("refresh");
    });
   //Publication End date for the Alert content type
    $('#alert-node-form #edit-field-publication-from-date-und-0-value-datepicker-popup-0').change(function(){
      var agenda_todate = Drupal.settings.im_agenda.alert_to_date;
        var date1 = $('#edit-field-publication-from-date-und-0-value-datepicker-popup-0').datepicker('getDate');
        var date = new Date( Date.parse( date1 ) ); 
        date.setMonth( date.getMonth() + parseInt(agenda_todate));

        var newDate = date.toDateString(); 
        newDate = new Date(Date.parse(newDate));
        $('#edit-field-publication-to-date-und-0-value-datepicker-popup-0').datepicker('setDate', newDate );
        $('#edit-field-publication-to-date-und-0-value-datepicker-popup-0').datepicker("refresh");
    });
    //Publication End date for the News content type
    $('#news-node-form #edit-field-publication-from-date-und-0-value-datepicker-popup-0').change(function(){
      var agenda_todate = Drupal.settings.im_agenda.news_to_date;
        var date1 = $('#edit-field-publication-from-date-und-0-value-datepicker-popup-0').datepicker('getDate');
        var date = new Date( Date.parse( date1 ) ); 
        date.setMonth( date.getMonth() + parseInt(agenda_todate));

        var newDate = date.toDateString(); 
        newDate = new Date(Date.parse(newDate));
        $('#edit-field-publication-to-date-und-0-value-datepicker-popup-0').datepicker('setDate', newDate );
        $('#edit-field-publication-to-date-und-0-value-datepicker-popup-0').datepicker("refresh");
    });
    //Publication End date for the Benchmark content type
    $('#benchmark-node-form #edit-field-publication-from-date-und-0-value-datepicker-popup-0').change(function(){
      var agenda_todate = Drupal.settings.im_agenda.benchmark_to_date;
        var date1 = $('#edit-field-publication-from-date-und-0-value-datepicker-popup-0').datepicker('getDate');
        var date = new Date( Date.parse( date1 ) ); 
        date.setMonth( date.getMonth() + parseInt(agenda_todate));

        var newDate = date.toDateString(); 
        newDate = new Date(Date.parse(newDate));
        $('#edit-field-publication-to-date-und-0-value-datepicker-popup-0').datepicker('setDate', newDate );
        $('#edit-field-publication-to-date-und-0-value-datepicker-popup-0').datepicker("refresh");
    });

    //publication to date field readonly and hide the date popup
    /*$("#edit-field-publication-to-date-und-0-value-datepicker-popup-0").attr('readonly', 'readonly');
    $(".form-item-field-publication-to-date-und-0-value-date").click(function(e){
      e.preventDefault();
      $(".ui-datepicker").hide();
    });
    $(".form-item-field-publication-to-date-und-0-value-date").focus(function(e){
      e.preventDefault();
      $(".ui-datepicker").hide();
    });*/
    
    //Hide the Moderation State dropdown
    $("#edit-workbench-moderation-state-new").hide();
    $('#edit-workbench-moderation-state-new').parent().hide();
    
    $(".print").click(function(e) {      
      $('.previous-agenda-day').hide();
      $('.next-agenda-day').hide();      
      $('.agenda-day-bottom').hide();
      $('.function-concern').css("border", '1px solid');
      $('.relay-store').css("border", '1px solid');
      $('.author').css("border", '1px solid');
      $(".agenda-day-wrapper").printElement({
            printMode:'popup',           //dont' like the popup
            overrideElementCSS:[
                            '/sites/all/modules/intranet_market/im_agenda/css/im_agenda.css',
                            { href:'/sites/all/modules/intranet_market/im_agenda/css/im_agenda.css',media:'print',
                              href:'/sites/all/themes/im/css/custom_print.css',media:'print'}],
            leaveOpen: false //For debugging then you can make it false
         });      
      $('.previous-agenda-day').show();
      $('.next-agenda-day').show();
      $('.agenda-day-bottom').show();
      $('.function-concern').css("border", 'none');
      $('.relay-store').css("border", 'none');
      $('.author').css("border", 'none');

    });
    
     $(".print-agenda-today").click(function(e) {
     window.print();
      // $('#agenda-user-input-date').hide();
      // $('.previous-date').hide();
      // $('.next-date').hide();
      // $('.print-agenda-today').hide();
      
      // $("#agenda-date-selection-display").show();
      
      // $(".agenda-date-selection-data").printElement({
            // printMode:'popup',           //dont' like the popup
            // overrideElementCSS:[
                            // '/sites/all/modules/intranet_market/im_agenda/css/im_agenda.css',
                            // { href:'/sites/all/modules/intranet_market/im_agenda/css/im_agenda.css',media:'print',
                              // href:'/sites/all/themes/im/css/custom_print.css',media:'print'}],
            // leaveOpen: false //For debugging then you can make it false
         // });
      // $('#agenda-user-input-date').show();
      // $('.previous-date').show();
      // $('.next-date').show();
      // $('.print-agenda-today').show();
         // $("#agenda-date-selection-display").hide();
    });
    $('.agenda-teaser-popup a').click(function() {
      var id = $(this).parent().siblings('.agenda-teaser-min').attr('id');
      changeteaser(id);
    });
    $('.next-agenda-day a').click(function() {
      var url = $(this).attr('href');
      var urldata = url.split("/");
      var id = 'teaser-' + urldata[urldata.length - 1];
      changeteaser(id.toString());
    });
    $('.previous-agenda-day a').click(function() {
      var url = $(this).attr('href');
      var urldata = url.split("/");
      var id = 'teaser-' + urldata[urldata.length - 1];
      changeteaser(id.toString());
    });
    function changeteaser(id){
      if(id){
        if(!$('#' + id + '').children('.agenda-teaser').hasClass('dotted-read-content')){
          $('#' + id + '').children('.agenda-teaser').addClass('dotted-read-content');
          $('#' + id + '').children('.agenda-teaser').children('.agenda-teaser-icon').css('color', 'white');
          var color = $('#' + id + '').children('.agenda-teaser').children('.agenda-dept-name').css('color');
          var color_diff = $('#' + id + '').children('.agenda-teaser').children('.agenda-dept-name').attr('id');
          if(color) {
          color = (color.length && color[0] == '#') ? color.slice(1) : color;
          }
          if(color){
            if(color_diff == 'ag_default') {
            	var corner_class = ' ag_default';	
            }else {
            	var corner_class = 'cc' + hex(color).toUpperCase();	
            }
           }
          if(color == 'rgb(128, 128, 128)' || color == 'gray'){
          var corner_class = 'gray';
          }
          $('#' + id + '').children('.agenda-teaser').children('.agenda-teaser-icon').addClass(corner_class);
          // Commented the below code to fix UATIM-224
          $('#' + id + '').children('.agenda-teaser').children('.agenda-teaser-corner').remove();
        }
      }
    }
    function hex( c ) {
      var m = /rgba?\((\d+), (\d+), (\d+)/.exec( c );
      return m ? '' + ( m[1] << 16 | m[2] << 8 | m[3] ).toString(16) : c;
   };
   var loading  = false; //to prevents multipal ajax loads
   var end_date = Drupal.settings.agenda_end_date;
   $(window).scroll(function(e){     
       if ($(window).scrollTop() + $(window).height() == $(document).height()) {
       if(loading==false) //there's more data to load
     {
      loading = true; 
      $('.animation_image').show();
      loadMore();
       }
     }
       e.stopImmediatePropagation();
     });
   function loadMore() {
         $.ajax({
           url: '/agenda/list/load_content',
             type: 'POST',
             dataTypeString: 'text',
             success: function (data, textStatus, jqXHR) {
        	  
           $('.animation_image').hide(); //hide loading image once data is received
           $('.animation_image').attr('class', 'animation_image_processed');
           $("#agenda-list-week .agenda-day-row:last").removeClass("last");
           data = data.toString();
           var data_output = data.split('*****');
           var response_output = data_output[0];
           response_output = response_output.toString();
           response_output = response_output.replace('<div class="ajax_page_load_extra" style="display:none">', '');
           $("#agenda-list-week").append(data);//
           if (!$(".message-widget-teaser").is(":visible")) {
             $(".additional-four").hide();
           }
               var json_value = data_output[1];
               json_value = json_value.toString();
               json_value = json_value.replace('</div>', '');
               json_value = json_value.split("####");
               var incval = 0;
               for (i = 0; i < ((json_value.length) / 5); i++) {
                 var json_obj = {};
                 if (json_value[incval] != '') {
	               json_obj.baseURL = json_value[incval];  //0
	               incval++;
	               json_obj.start_date = json_value[incval];  //1
	               var start_date_flag = json_value[incval];
	               incval++;
	               json_obj.store = json_value[incval];  //2
	               incval++;
	               json_obj.department = json_value[incval];  //3
	               incval++
	               var classtoreplace_value = json_value[incval];  //4
	               if (classtoreplace_value != '' && classtoreplace_value != null) {
	                 classtoreplace_value = classtoreplace_value.toString();
	                 if (classtoreplace_value.indexOf('<') != -1) {
	                   classtoreplace_value = classtoreplace_value.split('<');
	                   json_obj.classToReplace = classtoreplace_value[0];
	                 }
	                 else {
	                   json_obj.classToReplace = json_value[incval];
	                 }
	               }
	               else {
	                 json_obj.classToReplace = json_value[incval];
	               }
	               Drupal.settings.date_filters[start_date_flag] = json_obj;
	               incval++;
               }
             }
               loading = false;
               Drupal.attachBehaviors($('#agenda-list-week'));
           },
       });
     }
     $(".action_questionnaire :input").attr("disabled", true);
     $(".action_questionnaire :input.form-submit").remove();
     $(".submitted").hide();
     
     
     //For questionnaire pop up close.
     if($(".agenda-day-content-left").find(".agenda-day-questionnaire").length) {

       //if not submitted bind
       var submitted = Drupal.settings.submitted;
       if(submitted === null ) {
    	   submitted = 'no-popup';
       }
       if(submitted == 'popup') {
         $(".close").unbind("click");
         $(".close").bind("click", questionnaireClose);        
       }
       else if(submitted == 'no-popup') {
         $('.agenda-day-bottom .close-pop').click(function() {
           $('.im-popups-close .close').trigger('click');
         });
       }
     }
     else {
       $('.close-pop').click(function() {
        $('.close').trigger('click');
       });
     }


     //function to overwrite the close functionality.
     function questionnaireClose(){    
         var formid = $(".webform-client-form").attr("id");
         var form_change = FormChanges(document.getElementById(formid));
         
         var submitted = Drupal.settings.submitted;
         if(submitted === null ) {
      	   submitted = 'no-popup';
         }
         
        if(form_change == '' || submitted == 'no-popup') {
          $('#modalContent').remove();
            $('#modalBackdrop').remove();
        }
        else {
           
          $.alerts.okButton = Drupal.t("OK");
          $.alerts.cancelButton = Drupal.t("Cancel");
    
          jConfirm(Drupal.t("Do you really want to close the questionnaire?"), Drupal.t("Confirm"), function(r) {
            if (r == false)
            {
            //Do stuff for no
              return;
            }
            else
            {
            //Do stuff for yes
              $('#modalContent').remove();
                  $('#modalBackdrop').remove();
            }
    
          });
         }
     }
     
     // Function to check any chagnges are done to a particular form
     function FormChanges(form) {
         // get form
         if (typeof form == "string") form = document.getElementById(form);
         if (!form || !form.nodeName || form.nodeName.toLowerCase() != "form") return null;
         
         // find changed elements
         var changed = [], n, c, def, o, ol, opt;
         for (var e = 0, el = form.elements.length; e < el; e++) {
           n = form.elements[e];
             c = false;
             
             switch (n.nodeName.toLowerCase()) {
                         
               case "select":
                            def = 0;
                            for (o = 0, ol = n.options.length; o < ol; o++) {
                                opt = n.options[o];
                                c = c || (opt.selected != opt.defaultSelected);
                                if (opt.defaultSelected) def = o;
                            }
                            if (c && !n.multiple) c = (def != n.selectedIndex);
                            break;
                                           
               // input / textarea
               case "textarea":
               case "input":
                                                           
                   switch (n.type.toLowerCase()) {
                     case "checkbox":
                     case "radio":
                     // checkbox / radio
                     c = (n.checked != n.defaultChecked);
                     break;                     
                     default:
                     // standard values
                     c = (n.value != n.defaultValue);
                     break;                                                   
                   }
               break;
                         }
                         
                 if (c) changed.push(n);
         }
         
         return changed;

     }        
}
})(jQuery);
 