/**
 * Color Field jQuery
 */
(function ($) {
jQuery.fn.addColorPicker = function (props) {
  if (!props) { props = []; }

  props = jQuery.extend({
    currentColor:'',
    blotchElemType: 'span',
    blotchClass:'colorBox',
    clickCallback: function(ignoredColor) {},
    iterationCallback: null,
    fillString: '&nbsp;',
    fillStringX: '?',
    colors: ['#9D2235', '#C6A1CF', '#672146', '#94795D', '#59CBE8', '#5CB8B2', '#753BBD', '#78D64B', '#B7BF10', '#F1BE48', '#FC4C02', '#512F2E', '#FDDA24', '#EF3340', '#ECC7CD', '#EF4A81', '#E782A9', '#B9D9EB', '#EFD19F', '#43B02A', '#94795D', '#64CCC9', '#009639', '#0085CA', '#78D64B', '#E9EC6B', '#FFA38B'
    ]
  }, props);

  var count = props.colors.length;
  for (var i = 0; i < count; ++i) {
    var color = props.colors[i];
    var elem = jQuery('<' + props.blotchElemType + '/>')
      .addClass(props.blotchClass)
      .attr('color',color)
      .attr('title', hexToRgb(color))
      .css('background-color',color);
    // jq bug: chaining here fails if color is null b/c .css() returns (new String('transparent'))!
    if (props.currentColor == color) {
      elem.addClass('active');
    }
    if (props.clickCallback) {
      elem.click(function() {
        jQuery(this).parent().children('.colorBox').removeClass('active');
        jQuery(this).addClass('active');
        props.clickCallback(jQuery(this).attr('color'));
      });
    }
    this.append(elem);
    if (props.iterationCallback) {
      props.iterationCallback(this, elem, color, i);
    }
  }

  var elem = jQuery('<' + props.blotchElemType + '/>')
    .addClass('transparentBox')
    .attr('color', '')
    .css('background-color', '');
  if (props.currentColor == '') {
    elem.addClass('active');
  }
  if (props.clickCallback) {
    elem.click(function() {
      jQuery(this).parent().children('.colorBox').removeClass('active');
      jQuery(this).addClass('active');
      props.clickCallback(jQuery(this).attr('color'));
    });
  }
  this.append(elem);
  if (props.iterationCallback) {
    props.iterationCallback(this, elem, color, i);
  }

  return this;
};
//convert hex to rgb
function hexToRgb(hex) {
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    var rgb = 'rgb('+ parseInt(result[1], 16) +','+ parseInt(result[2], 16) +','+ parseInt(result[3], 16) +')';
    return rgb;
}

})(jQuery);
