/**
 *@file Add drag and drop from one table to another table. 
 */
(function($) {
  Drupal.behaviors.im_user_getdms_form = {};
  Drupal.behaviors.im_user_getdms_form.attach = function(context) {
    $tabs = $(".table_global");
    $( ".table-trans-replace tbody" ).sortable({
      connectWith: ".table-trans-replace tbody",
      appendTo: $tabs,
      helper:"clone",
      zIndex: 999990 ,
      start: function(){ $tabs.addClass("dragging")
      },
      stop: function(){ 
        $tabs.removeClass("dragging");
        var save_table_value = $('#table-second-save').html();
        $('#edit-textbox').val(save_table_value);
        var search_data = $('#edit-getdms-textbox').val(); 
        var data = "data=" + $('#edit-textbox').val();
        $.ajax({
          url: '/admin/im/getdms/"'+search_data+'"/ajax',
          type: 'POST',
          data: data,
          success: function(a) {
          }
        });
      }
    })
      .disableSelection();

  var $tab_items = $($tabs).droppable({
    accept: ".table-trans-replace tbody",
    //hoverClass: "ui-state-hover",
    over: function( event) {
      var $item = $( this );
      alert($item);
      $item.find("a").tab("show");
    },
    drop: function( event) {
      return false;
    }
  });

  }
})(jQuery);
