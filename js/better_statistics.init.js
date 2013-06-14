function BetterStatistics() {
  if (!instance) var instance = this;
  var i = 1 * new Date();

  /**
   * Set properties on the global Better Statistics object.
   */
  instance.set = function(property, value) {
    if (typeof value !== 'undefined') {
      instance[property] = value;
    }
    else if (property instanceof Array && property.length == 2) {
      instance[property.shift()] = property.shift();
    }
  }

  /**
   * Get properties from the global Better Statistics object.
   */
  instance.get = function(property) {
    if(typeof property === 'string') {
      return instance[property];
    }
    else if (property instanceof Array && property.length == 1) {
      return instance[property.shift()];
    }
  }

  /**
   * Trigger a JavaScript event of a given name with a given set of data.
   */
  instance.trigger = function(name, data) {
    var event;
    if (document.createEvent) {
      event = document.createEvent("HTMLEvents");
      event.initEvent(name, true, true);
    }
    else {
      event = document.createEventObject();
      event.eventType = name;
    }

    event.eventName = name;
    event.data = data || {};

    if (document.createEvent) {
      document.dispatchEvent(event);
    }
    else {
      document.fireEvent('on' + event.eventType, event);
    }

    data = event.data;
  }

  /**
   * Send an asynchronous POST request with an optional data payload to the
   * Better Statistics callback path.
   */
  instance.post = function(type, payload) {
    var request = new XMLHttpRequest();
    if (!request) return;
    payload = typeof(payload) == 'undefined' ? {} : payload;
    request.open('POST', this.basePath + 'statistics/ajax/' + type, true);
    request.setRequestHeader('Content-type', 'application/json; charset=utf-8');
    request.send(JSON.stringify(payload));
  }

  /**
   * Primary interface to the Better Statistics facade.
   */
  function BetterStatistics() {
    var args = [].slice.call(arguments, 0);
    if (args.length > 0) {
      var func = args.shift();
      if (instance[func] instanceof Function) {
        return instance[func](args);
      }
    }
  }

  return BetterStatistics;
}
