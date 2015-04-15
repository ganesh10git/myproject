(function (a) {
	var testflag = 0;
    a.widget("ui.dropdownchecklist", {
        version: function () {
            alert("DropDownCheckList v1.3")
        },
        _appendDropContainer: function (b) {
            var d = a("<div/>");
            d.addClass("ui-dropdownchecklist ui-dropdownchecklist-dropcontainer-wrapper");
            d.addClass("ui-widget");
            d.attr("id", b.attr("id") + "-ddw");
            d.css({
                position: "absolute",
                left: "-33000px",
                top: "-33000px"
            });
            var c = a("<div/>");
            c.addClass("ui-dropdownchecklist-dropcontainer ui-widget-content");
            c.css("overflow-y", "auto");
            d.append(c);
            d.insertAfter(b);
            d.isOpen = false;
            return d
        },
        _isDropDownKeyShortcut: function (c, b) {
            return c.altKey && (a.ui.keyCode.DOWN == b)
        },
        _isDropDownCloseKey: function (c, b) {
            return (a.ui.keyCode.ESCAPE == b) || (a.ui.keyCode.ENTER == b)
        },
        _keyFocusChange: function (f, i, c) {
            var g = a(":focusable");
            var d = g.index(f);
            if (d >= 0) {
                d += i;
                if (c) {
                    var e = this.dropWrapper.find("input:not([disabled])");
                    var b = g.index(e.get(0));
                    var h = g.index(e.get(e.length - 1));
                    if (d < b) {
                        d = h
                    } else {
                        if (d > h) {
                            d = b
                        }
                    }
                }
                g.get(d).focus()
            }
        },
        _handleKeyboard: function (d) {
            var b = this;
            var c = (d.keyCode || d.which);
            if (!b.dropWrapper.isOpen && b._isDropDownKeyShortcut(d, c)) {
                d.stopImmediatePropagation();
                b._toggleDropContainer(true)
            } else {
                if (b.dropWrapper.isOpen && b._isDropDownCloseKey(d, c)) {
                    d.stopImmediatePropagation();
                    b._toggleDropContainer(false);
                    b.controlSelector.focus()
                } else {
                    if (b.dropWrapper.isOpen && (d.target.type == "checkbox") && ((c == a.ui.keyCode.DOWN) || (c == a.ui.keyCode.UP))) {
                        d.stopImmediatePropagation();
                        b._keyFocusChange(d.target, (c == a.ui.keyCode.DOWN) ? 1 : -1, true)
                    } else {
                        if (b.dropWrapper.isOpen && (c == a.ui.keyCode.TAB)) {}
                    }
                }
            }
        },
        _handleFocus: function (f, d, b) {
            var c = this;
            if (b && !c.dropWrapper.isOpen) {
                f.stopImmediatePropagation();
                if (d) {
                    c.controlSelector.addClass("ui-state-hover");
                    if (a.ui.dropdownchecklist.gLastOpened != null) {
                        a.ui.dropdownchecklist.gLastOpened._toggleDropContainer(false)
                    }
                } else {
                    c.controlSelector.removeClass("ui-state-hover")
                }
            } else {
                if (!b && !d) {
                    if (f != null) {
                        f.stopImmediatePropagation()
                    }
                    c.controlSelector.removeClass("ui-state-hover");
                    c._toggleDropContainer(false)
                }
            }
        },
        _cancelBlur: function (c) {
            var b = this;
            if (b.blurringItem != null) {
                clearTimeout(b.blurringItem);
                b.blurringItem = null
            }
        },
        _appendControl: function () {
            var j = this,
                c = this.sourceSelect,
                k = this.options;
            var b = a("<span/>");
            b.addClass("ui-dropdownchecklist ui-dropdownchecklist-selector-wrapper ui-widget");
            b.css({
                display: "inline-block",
                cursor: "default",
                overflow: "hidden"
            });
            var f = c.attr("id");
            if ((f == null) || (f == "")) {
                f = "ddcl-" + a.ui.dropdownchecklist.gIDCounter++
            } else {
                f = "ddcl-" + f
            }
            b.attr("id", f);
            var h = a("<span/>");
            h.addClass("ui-dropdownchecklist-selector ui-state-default");
            h.css({
                display: "inline-block",
                overflow: "hidden",
                "white-space": "nowrap"
            });
            var d = c.attr("tabIndex");
            if (d == null) {
                d = 0
            } else {
                d = parseInt(d);
                if (d < 0) {
                    d = 0
                }
            }
            h.attr("tabIndex", d);
            h.keyup(function (l) {
                j._handleKeyboard(l)
            });
            h.focus(function (l) {
                j._handleFocus(l, true, true)
            });
            h.blur(function (l) {
                j._handleFocus(l, false, true)
            });
            b.append(h);
            if (k.icon != null) {
                var i = (k.icon.placement == null) ? "left" : k.icon.placement;
                var g = a("<div/>");
                g.addClass("ui-icon");
                g.addClass((k.icon.toOpen != null) ? k.icon.toOpen : "ui-icon-triangle-1-e");
                g.css({
                    "float": i
                });
                h.append(g)
            }
            var e = a("<span/>");
            e.addClass("ui-dropdownchecklist-text");
            e.css({
                display: "inline-block",
                "white-space": "nowrap",
                overflow: "hidden"
            });
            h.append(e);
            b.hover(function () {
                if (!j.disabled) {
                    h.addClass("ui-state-hover")
                }
            }, function () {
                if (!j.disabled) {
                    h.removeClass("ui-state-hover")
                }
            });
            b.click(function (l) {
            	// Expand and collapse the list - Carrefour
                if (!j.disabled) {
                    l.stopImmediatePropagation();
                    j._toggleDropContainer(!j.dropWrapper.isOpen)
                }
            });
            b.insertAfter(c);
            a(window).resize(function () {
                if (!j.disabled && j.dropWrapper.isOpen) {
                    j._toggleDropContainer(true)
                }
            });
            return b
        },
        _createDropItem: function (g, f, o, l, q, h, e, k) {
            var m = this,
                c = this.options,
                d = this.sourceSelect,
                p = this.controlWrapper;
            var t = a("<div/>");
            t.addClass("ui-dropdownchecklist-item");
            t.css({
                "white-space": "nowrap"
            });
            
            var j = e ? ' class="inactive"' : ' class="active"';
            var b = p.attr("id");
            var n = b + "-i" + g;
            
            var r = h ? ' checked="checked"' : '';
            if (n == "ddcl-edit-user-department-i0.0" && h == true) {
            	testflag = 1;
            }
            if (testflag == 1) {
            	r = ' checked="checked"';
            }
            var s;
            if (m.isMultiple) {
                s = a('<input disabled type="checkbox" id="' + n + '"' + r + j + ' tabindex="' + f + '" />')
            } else {
                s = a('<input disabled type="radio" id="' + n + '" name="' + b + '"' + r + j + ' tabindex="' + f + '" />')
            }
            s = s.attr("index", g).val(o);
            t.append(s);
            var i = a("<label for=" + n + "/>");
            i.addClass("ui-dropdownchecklist-text");
            if (q != null) {
                i.attr("style", q)
            }
            i.css({
                cursor: "default"
            });
            i.html(l);
            if (k) {
                t.addClass("ui-dropdownchecklist-indent")
            }
            t.addClass("ui-state-default");
            if (e) {
                t.addClass("ui-state-disabled")
            }
            i.click(function (u) {
             // Item label click event - Carrefour
            	var currentselectedid = a(this).attr("id");
                var setflag = 0;
                var stepval = 0;
                var totalcheckeditems = 0;
                var totalcheckboxes = (a("#ddcl-edit-user-department-ddw input").length - 1);
                a("#ddcl-edit-user-department-ddw input").each(function( index ) {
                	var allid = a(this).attr("id");
                    var allidstatus = a(this).attr("checked");
                    if (allid == "ddcl-edit-user-department-i0.0" && currentselectedid == "ddcl-edit-user-department-i0.0" && allidstatus == true) {
                      if (setflag == 0) {
                        stepval = 1;
                      }
                      setflag = 1;
                    }
                    else if (allid == "ddcl-edit-user-department-i0.0" && currentselectedid == "ddcl-edit-user-department-i0.0" && allidstatus == false) {
                      if (setflag == 0) {
                        stepval = 2;
                      }
                      setflag = 1;
                    }
                    else if (currentselectedid != "ddcl-edit-user-department-i0.0") {
                      if (setflag == 0) {
                        stepval = 3;
                      }
                      setflag = 1;
                    }
                });
                var incstepval = 1;
                a("#ddcl-edit-user-department-ddw input").each(function( index ) {
                  if (stepval == 1) {
                    a(this).attr("checked", "checked");
                  }
                  else if (stepval == 2) {
                    a(this).attr("checked", "");
                  } 
                  else if (stepval == 3) {
                    if (incstepval == 1) {
                      a(this).attr("checked", "");
                    }
                  }
                  incstepval++;
                });
                var incstepvalue = 1;
                a("#ddcl-edit-user-department-ddw input").each(function( index ) {
                  var idstatus = a(this).attr("checked");
                  var idvalue = a(this).attr("id");
                  if (idstatus == true && idvalue != "ddcl-edit-user-department-i0.0") {
                    totalcheckeditems = totalcheckeditems + 1;
                  }
                  incstepvalue++;
                });
                a("#ddcl-edit-user-department-ddw input").each(function( index ) {
                  if (totalcheckeditems == totalcheckboxes) {
                    a(this).attr("checked", "checked");
                  }
                });
				var v = a(this);
                u.stopImmediatePropagation();
                if (v.hasClass("active")) {
                    var x = m.options.onItemClick;
                    if (a.isFunction(x)) {
                        try {
                            x.call(m, v)
                        } catch (u) {
                            v.attr("checked", !v.attr("checked"));
                            return
                        }
                    }
                    m._syncSelected(v);
                    m.sourceSelect.trigger("change", "ddcl_internal");
                    if (!m.isMultiple && c.closeRadioOnClick) {
                        m._toggleDropContainer(false)
                    }
                }
            });
            t.append(i);
            t.hover(function (v) {
                var u = a(this);
                if (!u.hasClass("ui-state-disabled")) {
                    u.addClass("ui-state-hover")
                }
            }, function (v) {
                var u = a(this);
                u.removeClass("ui-state-hover")
            });
            s.click(function (w) {
            	// Item checkbox click event - Carrefour
				var currentselectedid = a(this).attr("id");
                var setflag = 0;
                var stepval = 0;
                var totalcheckeditems = 0;
                var totalcheckboxes = (a("#ddcl-edit-user-department-ddw input").length - 1);
                a("#ddcl-edit-user-department-ddw input").each(function( index ) {
                	var allid = a(this).attr("id");
                    var allidstatus = a(this).attr("checked");
                    if (allid == "ddcl-edit-user-department-i0.0" && currentselectedid == "ddcl-edit-user-department-i0.0" && allidstatus == true) {
                      if (setflag == 0) {
                        stepval = 1;
                      }
                      setflag = 1;
                    }
                    else if (allid == "ddcl-edit-user-department-i0.0" && currentselectedid == "ddcl-edit-user-department-i0.0" && allidstatus == false) {
                      if (setflag == 0) {
                        stepval = 2;
                      }
                      setflag = 1;
                    }
                    else if (currentselectedid != "ddcl-edit-user-department-i0.0") {
                      if (setflag == 0) {
                        stepval = 3;
                      }
                      setflag = 1;
                    }
                });
                var incstepval = 1;
                a("#ddcl-edit-user-department-ddw input").each(function( index ) {
                  if (stepval == 1) {
                    a(this).attr("checked", "checked");
                  }
                  else if (stepval == 2) {
                    a(this).attr("checked", "");
                  } 
                  else if (stepval == 3) {
                    if (incstepval == 1) {
                      a(this).attr("checked", "");
                    }
                  }
                  incstepval++;
                });
                var incstepvalue = 1;
                a("#ddcl-edit-user-department-ddw input").each(function( index ) {
                  var idstatus = a(this).attr("checked");
                  var idvalue = a(this).attr("id");
                  if (idstatus == true && idvalue != "ddcl-edit-user-department-i0.0") {
                    totalcheckeditems = totalcheckeditems + 1;
                  }
                  incstepvalue++;
                });
                a("#ddcl-edit-user-department-ddw input").each(function( index ) {
                  if (totalcheckeditems == totalcheckboxes) {
                    a(this).attr("checked", "checked");
                  }
                });
				
                var v = a(this);
                w.stopImmediatePropagation();
                if (v.hasClass("active")) {
                    var x = m.options.onItemClick;
                    if (a.isFunction(x)) {
                        try {
                            x.call(m, v)
                        } catch (u) {
                            v.attr("checked", !v.attr("checked"));
                            return
                        }
                    }
                    m._syncSelected(v);
                    m.sourceSelect.trigger("change", "ddcl_internal");
                    if (!m.isMultiple && c.closeRadioOnClick) {
                        m._toggleDropContainer(false)
                    }
                }
                
            });
            t.click(function (y) {
                var x = a(this);
                y.stopImmediatePropagation();
                if (!x.hasClass("ui-state-disabled")) {
                    var v = x.find("input");
                    var w = v.attr("checked");
                    v.attr("checked", !w);
                    var z = m.options.onItemClick;
                    if (a.isFunction(z)) {
                        try {
                            z.call(m, v)
                        } catch (u) {
                            v.attr("checked", w);
                            return
                        }
                    }
                    m._syncSelected(v);
                    m.sourceSelect.trigger("change", "ddcl_internal");
                    if (!w && !m.isMultiple && c.closeRadioOnClick) {
                        m._toggleDropContainer(false)
                    }
                } else {
                    x.focus();
                    m._cancelBlur()
                }
				
				// Item child label click event - Carrefour
				var currentselectedid = a(this).attr("id");
                var setflag = 0;
                var stepval = 0;
                var totalcheckeditems = 0;
                var totalcheckboxes = (a("#ddcl-edit-user-department-ddw input").length - 1);
                a("#ddcl-edit-user-department-ddw input").each(function( index ) {
                	var allid = a(this).attr("id");
                    var allidstatus = a(this).attr("checked");
                    if (allid == "ddcl-edit-user-department-i0.0" && currentselectedid == "ddcl-edit-user-department-i0.0" && allidstatus == true) {
                      if (setflag == 0) {
                        stepval = 1;
                      }
                      setflag = 1;
                    }
                    else if (allid == "ddcl-edit-user-department-i0.0" && currentselectedid == "ddcl-edit-user-department-i0.0" && allidstatus == false) {
                      if (setflag == 0) {
                        stepval = 2;
                      }
                      setflag = 1;
                    }
                    else if (currentselectedid != "ddcl-edit-user-department-i0.0") {
                      if (setflag == 0) {
                        stepval = 3;
                      }
                      setflag = 1;
                    }
                });
                var incstepval = 1;
                a("#ddcl-edit-user-department-ddw input").each(function( index ) {
                  if (stepval == 1) {
                    a(this).attr("checked", "checked");
                  }
                  else if (stepval == 2) {
                    a(this).attr("checked", "");
                  } 
                  else if (stepval == 3) {
                    if (incstepval == 1) {
                      a(this).attr("checked", "");
                    }
                  }
                  incstepval++;
                });
                var incstepvalue = 1;
                a("#ddcl-edit-user-department-ddw input").each(function( index ) {
                  var idstatus = a(this).attr("checked");
                  var idvalue = a(this).attr("id");
                  if (idstatus == true && idvalue != "ddcl-edit-user-department-i0.0") {
                    totalcheckeditems = totalcheckeditems + 1;
                  }
                  incstepvalue++;
                });
                a("#ddcl-edit-user-department-ddw input").each(function( index ) {
                  if (totalcheckeditems == totalcheckboxes) {
                    a(this).attr("checked", "checked");
                  }
                });
            });
            t.focus(function (v) {
                var u = a(this);
                v.stopImmediatePropagation()
            });
            t.keyup(function (u) {
                m._handleKeyboard(u)
            });
            return t
        },
        _createGroupItem: function (f, d) {
            var b = this;
            var e = a("<div />");
            e.addClass("ui-dropdownchecklist-group ui-widget-header");
            if (d) {
                e.addClass("ui-state-disabled")
            }
            e.css({
                "white-space": "nowrap"
            });
            var c = a("<span/>");
            c.addClass("ui-dropdownchecklist-text");
            c.css({
                cursor: "default"
            });
            c.text(f);
            e.append(c);
            e.click(function (h) {
                var g = a(this);
                h.stopImmediatePropagation();
                g.focus();
                b._cancelBlur()
            });
            e.focus(function (h) {
                var g = a(this);
                h.stopImmediatePropagation()
            });
            return e
        },
        _createCloseItem: function (e) {
            var b = this;
            var d = a("<div />");
            d.addClass("ui-state-default ui-dropdownchecklist-close ui-dropdownchecklist-item");
            d.css({
                "white-space": "nowrap",
                "text-align": "right"
            });
            var c = a("<span/>");
            c.addClass("ui-dropdownchecklist-text");
            c.css({
                cursor: "default"
            });
            c.html(e);
            d.append(c);
            d.click(function (g) {
                var f = a(this);
                g.stopImmediatePropagation();
                f.focus();
                b._toggleDropContainer(false)
            });
            d.hover(function (f) {
                a(this).addClass("ui-state-hover")
            }, function (f) {
                a(this).removeClass("ui-state-hover")
            });
            d.focus(function (g) {
                var f = a(this);
                g.stopImmediatePropagation()
            });
            return d
        },
        _appendItems: function () {
            var d = this,
                f = this.options,
                h = this.sourceSelect,
                g = this.dropWrapper;
            var b = g.find(".ui-dropdownchecklist-dropcontainer");
            h.children().each(function (j) {
                var k = a(this);
                if (k.is("option")) {
                    d._appendOption(k, b, j, false, false)
                } else {
                    if (k.is("optgroup")) {
                        var l = k.attr("disabled");
                        var n = k.attr("label");
                        if (n != "") {
                            var m = d._createGroupItem(n, l);
                            b.append(m)
                        }
                        d._appendOptions(k, b, j, true, l)
                    }
                }
            });
            if (f.explicitClose != null) {
                var i = d._createCloseItem(f.explicitClose);
                b.append(i)
            }
            var c = b.outerWidth();
            var e = b.outerHeight();
            return {
                width: c,
                height: e
            }
        },
        _appendOptions: function (g, d, f, c, b) {
            var e = this;
            g.children("option").each(function (h) {
                var i = a(this);
                var j = (f + "." + h);
                e._appendOption(i, d, j, c, b)
            })
        },
        _appendOption: function (g, b, h, d, n) {
            var m = this;
            var k = g.html();
            var j = g.val();
            var i = g.attr("style");
            var f = g.attr("selected");
            var e = (n || g.attr("disabled"));
            var c = m.controlSelector.attr("tabindex");
            var l = m._createDropItem(h, c, j, k, i, f, e, d);
            b.append(l)
        },
        _syncSelected: function (g) {
            var h = this,
                j = this.options,
                b = this.sourceSelect,
                d = this.dropWrapper;
            var c = b.get(0).options;
            var f = d.find("input.active");
            if (j.firstItemChecksAll) {
                if ((g == null) && a(c[0]).attr("selected")) {
                    f.attr("checked", true)
                } else {
                    if ((g != null) && (g.attr("index") == 0)) {
                        f.attr("checked", g.attr("checked"))
                    } else {
                        var e = true;
                        var i = null;
                        f.each(function (k) {
                            if (k > 0) {
                                var l = a(this).attr("checked");
                                if (!l) {
                                    e = false
                                }
                            } else {
                                i = a(this)
                            }
                        });
                        if (i != null) {
                            i.attr("checked", e)
                        }
                    }
                }
            }
            f = d.find("input");
            f.each(function (k) {
                a(c[k]).attr("selected", a(this).attr("checked"))
            });
            h._updateControlText();
            if (g != null) {
                g.focus()
            }
        },
        _sourceSelectChangeHandler: function (c) {
            var b = this,
                d = this.dropWrapper;
            d.find("input").val(b.sourceSelect.val());
            b._updateControlText()
        },
        _updateControlText: function () {
		    var labelstring = '';
		    a("#ddcl-edit-user-department-ddw input").each(function( index ) {
			  if (a(this).attr("checked")) {
			    if (labelstring == "") {
				  labelstring = (a( this ).parent().children("label").text());
				}
				else {
                  labelstring = labelstring + ", " +(a( this ).parent().children("label").text());
				}
			  }
            });
            var c = this,
                g = this.sourceSelect,
                d = this.options,
                f = this.controlWrapper;
            var h = g.find("option:first");
            var b = g.find("option");
			 
            var i = c._formatText(b, d.firstItemChecksAll, h);
            var e = f.find(".ui-dropdownchecklist-text");
            e.html(labelstring);
            e.attr("title", e.text())
        },
        _formatText: function (b, d, e) {
            var f;
            if (a.isFunction(this.options.textFormatFunction)) {
                try {
                    f = this.options.textFormatFunction(b)
                } catch (c) {
                    alert("textFormatFunction failed: " + c)
                }
            } else {
                if (d && (e != null) && e.attr("selected")) {
                    f = e.html()
                } else {
                    f = "";
                    b.each(function () {
                        if (a(this).attr("selected")) {
                            if (f != "") {
                                f += ", "
                            }
                            var g = a(this).attr("style");
                            var h = a("<span/>");
                            h.html(a(this).html());
                            if (g == null) {
                                f += h.html()
                            } else {
                                h.attr("style", g);
                                f += a("<span/>").append(h).html()
                            }
                        }
                    });
                    if (f == "") {
                        f = (this.options.emptyText != null) ? this.options.emptyText : "&nbsp;"
                    }
                }
            }
            return f
        },
        _toggleDropContainer: function (e) {
            var c = this;
            var d = function (f) {
                if ((f != null) && f.dropWrapper.isOpen) {
                    f.dropWrapper.isOpen = false;
                    a.ui.dropdownchecklist.gLastOpened = null;
                    var h = f.options;
                    f.dropWrapper.css({
                        top: "-33000px",
                        left: "-33000px"
                    });
                    var g = f.controlSelector;
                    g.removeClass("ui-state-active");
                    g.removeClass("ui-state-hover");
                    var j = f.controlWrapper.find(".ui-icon");
                    if (j.length > 0) {
                        j.removeClass((h.icon.toClose != null) ? h.icon.toClose : "ui-icon-triangle-1-s");
                        j.addClass((h.icon.toOpen != null) ? h.icon.toOpen : "ui-icon-triangle-1-e")
                    }
                    a(document).unbind("click", d);
                    f.dropWrapper.find("input.active").attr("disabled", "disabled");
                    if (a.isFunction(h.onComplete)) {
                        try {
                            h.onComplete.call(f, f.sourceSelect.get(0))
                        } catch (i) {
                            alert("callback failed: " + i)
                        }
                    }
                }
            };
            var b = function (n) {
                if (!n.dropWrapper.isOpen) {
                    n.dropWrapper.isOpen = true;
                    a.ui.dropdownchecklist.gLastOpened = n;
                    var g = n.options;
                    if ((g.positionHow == null) || (g.positionHow == "absolute")) {
                        n.dropWrapper.css({
                            position: "absolute",
                            top: n.controlWrapper.position().top + n.controlWrapper.outerHeight() + "px",
                            left: n.controlWrapper.position().left + "px"
                        })
                    } else {
                        if (g.positionHow == "relative") {
                            n.dropWrapper.css({
                                position: "relative",
                                top: "0px",
                                left: "0px"
                            })
                        }
                    }
                    var m = 0;
                    if (g.zIndex == null) {
                        var l = n.controlWrapper.parents().map(function () {
                            var o = a(this).css("z-index");
                            return isNaN(o) ? 0 : o
                        }).get();
                        var i = Math.max.apply(Math, l);
                        if (i >= 0) {
                            m = i + 1
                        }
                    } else {
                        m = parseInt(g.zIndex)
                    } if (m > 0) {
                        n.dropWrapper.css({
                            "z-index": m
                        })
                    }
                    var j = n.controlSelector;
                    j.addClass("ui-state-active");
                    j.removeClass("ui-state-hover");
                    var h = n.controlWrapper.find(".ui-icon");
                    if (h.length > 0) {
                        h.removeClass((g.icon.toOpen != null) ? g.icon.toOpen : "ui-icon-triangle-1-e");
                        h.addClass((g.icon.toClose != null) ? g.icon.toClose : "ui-icon-triangle-1-s")
                    }
                    a(document).bind("click", function (o) {
                        d(n)
                    });
                    var f = n.dropWrapper.find("input.active");
                    f.removeAttr("disabled");
                    var k = f.get(0);
                    if (k != null) {
                        k.focus()
                    }
                }
            };
            if (e) {
                d(a.ui.dropdownchecklist.gLastOpened);
                b(c)
            } else {
                d(c)
            }
        },
        _setSize: function (b) {
            var m = this.options,
                f = this.dropWrapper,
                l = this.controlWrapper;
            var k = b.width;
            if (m.width != null) {
                k = parseInt(m.width)
            } else {
                if (m.minWidth != null) {
                    var c = parseInt(m.minWidth);
                    if (k < c) {
                        k = c
                    }
                }
            }
            var i = this.controlSelector;
            i.css({
                width: k + "px"
            });
            var g = i.find(".ui-dropdownchecklist-text");
            var d = i.find(".ui-icon");
            if (d != null) {
                k -= (d.outerWidth() + 4);
                g.css({
                    width: k + "px"
                })
            }
            k = l.outerWidth();
            var j = (m.maxDropHeight != null) ? parseInt(m.maxDropHeight) : -1;
            var h = ((j > 0) && (b.height > j)) ? j : b.height;
            var e = b.width < k ? k : b.width;
            a(f).css({
                height: h + "px",
                width: e + "px"
            });
            f.find(".ui-dropdownchecklist-dropcontainer").css({
                height: h + "px"
            })
        },
        _init: function () {
            var c = this,
                d = this.options;
				
            if (a.ui.dropdownchecklist.gIDCounter == null) {
                a.ui.dropdownchecklist.gIDCounter = 1
            }
            c.blurringItem = null;
            var g = c.element;
            c.initialDisplay = g.css("display");
            g.css("display", "none");
            c.initialMultiple = g.attr("multiple");
            c.isMultiple = c.initialMultiple;
            if (d.forceMultiple != null) {
                c.isMultiple = d.forceMultiple
            }
            g.attr("multiple", true);
            c.sourceSelect = g;
            var e = c._appendControl();
            c.controlWrapper = e;
            c.controlSelector = e.find(".ui-dropdownchecklist-selector");
            var f = c._appendDropContainer(e);
            c.dropWrapper = f;
            var b = c._appendItems();
            c._updateControlText(e, f, g);
            c._setSize(b);
            if (d.firstItemChecksAll) {
                c._syncSelected(null)
            }
            if (d.bgiframe && typeof c.dropWrapper.bgiframe == "function") {
                c.dropWrapper.bgiframe()
            }
            c.sourceSelect.change(function (i, h) {
                if (h != "ddcl_internal") {
                    c._sourceSelectChangeHandler(i)
                }
            })
        },
        _refreshOption: function (e, d, c) {
            var b = e.parent();
            if (d) {
                e.attr("disabled", "disabled");
                e.removeClass("active");
                e.addClass("inactive");
                b.addClass("ui-state-disabled")
            } else {
                e.removeAttr("disabled");
                e.removeClass("inactive");
                e.addClass("active");
                b.removeClass("ui-state-disabled")
            }
            e.attr("checked", c)
        },
        _refreshGroup: function (c, b) {
            if (b) {
                c.addClass("ui-state-disabled")
            } else {
                c.removeClass("ui-state-disabled")
            }
        },
        close: function () {
            this._toggleDropContainer(false)
        },
        refresh: function () {
            var b = this,
                e = this.sourceSelect,
                d = this.dropWrapper;
            var c = d.find("input");
            var g = d.find(".ui-dropdownchecklist-group");
            var h = 0;
            var f = 0;
            e.children().each(function (i) {
                var j = a(this);
                var l = j.attr("disabled");
                if (j.is("option")) {
                    var k = j.attr("selected");
                    var n = a(c[f]);
                    b._refreshOption(n, l, k);
                    f += 1
                } else {
                    if (j.is("optgroup")) {
                        var o = j.attr("label");
                        if (o != "") {
                            var m = a(g[h]);
                            b._refreshGroup(m, l);
                            h += 1
                        }
                        j.children("option").each(function () {
                            var p = a(this);
                            var r = (l || p.attr("disabled"));
                            var q = p.attr("selected");
                            var s = a(c[f]);
                            b._refreshOption(s, r, q);
                            f += 1
                        })
                    }
                }
            });
            b._syncSelected(null)
        },
        enable: function () {
            this.controlSelector.removeClass("ui-state-disabled");
            this.disabled = false
        },
        disable: function () {
            this.controlSelector.addClass("ui-state-disabled");
            this.disabled = true
        },
        destroy: function () {
            a.Widget.prototype.destroy.apply(this, arguments);
            this.sourceSelect.css("display", this.initialDisplay);
            this.sourceSelect.attr("multiple", this.initialMultiple);
            this.controlWrapper.unbind().remove();
            this.dropWrapper.remove()
        }
    });
    a.extend(a.ui.dropdownchecklist, {
        defaults: {
            width: null,
            maxDropHeight: null,
            firstItemChecksAll: false,
            closeRadioOnClick: false,
            minWidth: 50,
            positionHow: "absolute",
            bgiframe: false,
            explicitClose: null
        }
    })
})(jQuery);