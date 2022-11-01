/*!
 * Mobile Monkey
 *
 * Based on jQuery UI Touch Punch 0.2.3
 *
 * Copyright 2011–2014, Dave Furfero
 * Dual licensed under the MIT or GPL Version 2 licenses.
 * 
 * Modifications for generalized jQuery support by Tyler Sommer 
 * https://github.com/tyler-sommer
 */
(function ($, window, document, undefined) {

    // Detect touch support
    $.support.touch = 'ontouchend' in document;
  
    // Ignore browsers without touch support
    if (!$.support.touch) {
      return;
    }
  
    var console = window.console || { log: $.noop };
  
    var ignoredElements = [
      document,
      document.firstChild.nextSibling
    ];
  
    $(function() {
      // TODO: Is there a better way to get the body? It might be possible for jQuery.on() to
      // have already been called by the time this is called.
      ignoredElements.push(document.body);
    });
  
    /**
     * ObjectStore, supports objects as keys
     * @constructor
     */
    function ObjectStore() {
      this.keys = [];
      this.values = {};
    }
  
    /**
     * Public members
     */
    ObjectStore.prototype = {
      constructor : ObjectStore,
  
      /**
       * Get a value
       * @param key
       * @returns {*}
       */
      get: function (key) {
        return this.values[this.keys.indexOf(key)];
      },
  
      /**
       * Set a value
       * @param key
       * @param value
       */
      set: function (key, value) {
        var id = this.keys.indexOf(key);
        if (id < 0) {
          id = this.keys.push(key);
        }
  
        this.values[id] = value;
      },
  
      /**
       * Increment a key
       * @param key
       * @param inc
       * @returns {*}
       */
      increment: function (key, inc) {
        inc = inc || 1;
        var value = (this.get(key) || 0) + inc;
  
        this.set(key, value);
  
        return value;
      },
  
      /**
       * Decrement a key
       * @param key
       * @param dec
       * @returns {number}
       */
      decrement: function (key, dec) {
        dec = dec || 1;
        var value = (this.get(key) || 0) - dec;
        if (value < 0) {
          value = 0;
        }
  
        this.set(key, value);
  
        return value;
      }
    };
  
    /**
     * A simulated mouse that listens for touch events and fires mouse events
     * @constructor
     */
    function SimulatedMouse() {
      this._touchMoved   = false;
      this._storage      = new ObjectStore();
      this._touchHandled = false;
    }
  
    /**
     * Simulate a mouse event based on a corresponding touch event
     * @param {Object} event A touch event
     * @param {String} simulatedType The corresponding mouse event
     */
    var _simulateMouseEvent = function(event, simulatedType) {
      // Ignore multi-touch events
      if (event.originalEvent.touches.length > 1) {
        return;
      }
  
      // Ignore direct touches on inputs and text areas
      if ($(event.target).is('input, textarea')) {
        // TODO: This is necessary because the keyboard's appearance changes the screenX and Y.
        // Could probably use some hack to get the position, or maybe trigger the touchstart after a short timeout
        return;
      }
  
      // Do not prevent default on:
      // touchstart -- this allows scrolling. If you intend to disallow touch scrolling when touching 
      //               an element, you must bind a touchstart event and call event.preventDefault() yourself.
      // touchmove  -- the first touchmove event is what transforms the event to a scroll.
      if (event.type !== 'touchstart' && event.type !== 'touchmove') {
        event.preventDefault();
      }
  
      var touch = event.originalEvent.changedTouches[0],
        simulatedEvent = document.createEvent('MouseEvents');
  
      // Initialize the simulated mouse event using the touch event's coordinates
      simulatedEvent.initMouseEvent(
        simulatedType,    // type
        true,             // bubbles                    
        true,             // cancelable                 
        window,           // view                       
        1,                // detail                     
        touch.screenX,    // screenX                    
        touch.screenY,    // screenY                    
        touch.clientX,    // clientX                    
        touch.clientY,    // clientY                    
        false,            // ctrlKey                    
        false,            // altKey                     
        false,            // shiftKey                   
        false,            // metaKey                    
        0,                // button                     
        null              // relatedTarget              
      );
  
      console.log('Dispatching simulated event', simulatedType, 'for real event', event.type, event.target);
  
      // Dispatch the simulated event to the target element
      event.target.dispatchEvent(simulatedEvent);
    };
  
    /**
     * Handle the jQuery UI widget's touchstart events
     * @param {Object} event The widget element's touchstart event
     */
    var _touchStart = function (event) {
  
      var self = this;
  
      // Ignore the event if another widget is already being handled
      if (self._touchHandled) {
        return;
      }
  
      // Set the flag to prevent other widgets from inheriting the touch event
      self._touchHandled = true;
  
      // Track movement to determine if interaction was a click
      self._touchMoved = false;
  
      // Simulate the mouseover event
      _simulateMouseEvent(event, 'mouseover');
  
      // Simulate the mousemove event
      _simulateMouseEvent(event, 'mousemove');
  
      // Simulate the mousedown event
      _simulateMouseEvent(event, 'mousedown');
    };
  
    /**
     * Handle the jQuery UI widget's touchmove events
     * @param {Object} event The document's touchmove event
     */
    var _touchMove = function (event) {
  
      var self = this;
  
      // Ignore event if not handled
      if (!self._touchHandled) {
        return;
      }
  
      // Interaction was not a click
      self._touchMoved = true;
  
      // Simulate the mousemove event
      _simulateMouseEvent(event, 'mousemove');
    };
  
    /**
     * Handle the jQuery UI widget's touchend events
     * @param {Object} event The document's touchend event
     */
    var _touchEnd = function (event) {
  
      var self = this;
  
      // Ignore event if not handled
      if (!self._touchHandled) {
        return;
      }
  
      // Simulate the mouseup event
      _simulateMouseEvent(event, 'mouseup');
  
      // Simulate the mouseout event
      _simulateMouseEvent(event, 'mouseout');
  
      // If the touch interaction did not move, it should trigger a click
      if (!self._touchMoved) {
  
        // Simulate the click event
        _simulateMouseEvent(event, 'click');
      }
  
      // Unset the flag to allow other widgets to inherit the touch event
      self._touchHandled = false;
    };
  
    /**
     * Public interface for SimulatedMouse
     * @type {{constructor: SimulatedMouse, bind: bind, unbind: unbind}}
     */
    SimulatedMouse.prototype = {
      constructor: SimulatedMouse,
  
      /**
       * Bind elements to this SimulatedMouse
       * @param elements
       */
      bind: function(elements) {
        if (!elements instanceof jQuery) {
          elements = $(elements);
        }
  
        var self = this;
        elements.each(function(index, element) {
          if (ignoredElements.indexOf(element) >= 0) {
            // continue
            return true;
          }
  
          if (self._storage.increment(element) == 1) {
            console.log('Binding touch handlers for ', element);
  
            $(element).bind({
              touchstart: $.proxy(_touchStart, self),
              touchmove: $.proxy(_touchMove, self),
              touchend: $.proxy(_touchEnd, self)
            });
          }
        });
      },
  
      /**
       * Unbind elements from this SimulatedMouse
       * @param elements
       */
      unbind: function(elements) {
        if (!elements instanceof jQuery) {
          elements = $(elements);
        }
  
        var self = this;
        elements.each(function(index, element) {
          if (ignoredElements.indexOf(element) >= 0) {
            // continue
            return true;
          }
  
          if (self._storage.decrement(element) <= 0) {
            console.log('Removing touch handlers for ', element);
  
            $(element).unbind({
              touchstart: $.proxy(_touchStart, self),
              touchmove: $.proxy(_touchMove, self),
              touchend: $.proxy(_touchEnd, self)
            });
          }
        });
      }
    };
  
  
    var mouse = new SimulatedMouse();
    var jQueryOn = $.prototype.on;
    $.prototype.on = function(types, selector, data, handler) {
      if (this.length > 0
        && typeof(types) === 'string'
        && (selector instanceof Function || ((data instanceof Function || handler instanceof Function) && !selector))
        && types.indexOf('click') === 0 // TODO: Allow more than only click events
      ) {
        mouse.bind(this);
      }
  
      return jQueryOn.apply(this, arguments);
    };
  
    var jQueryOff = $.prototype.off;
    $.prototype.off = function(types) {
      if (this.length > 0
        && typeof(types) === 'string'
        && types.indexOf('click') === 0 // TODO: Allow more than only click events
      ) {
        mouse.unbind(this);
      }
  
      return jQueryOff.apply(this, arguments);
    };
  
  })(jQuery, this, this.document);