(function ($) {
$(document).ready(function() {
   $(Drupal.settings.dropdown_checkboxes.dcid).each(function() {
    $("#" + this).dropdownchecklist({icon:{placement:'right',toOpen:'ui-icon-triangle-1-s',}, maxDropHeight: 300});
   });
 });
 })(jQuery);
