document.addEventListener('statistics.accesslog', function(event) {
  var bs = window.BetterStatsObj;

  // Page title:
  event.data.title = document.title;

  // Path is set programatically on the server-side.
  event.data.path = window[bs]('get', 'path');

  // URL (referer):
  event.data.url = document.referrer

  // Timer:
  window.performance = window.performance || {};
  if (performance.hasOwnProperty('timing')) {
    var t = performance.timing;
    event.data.timer = t.responseStart - t.requestStart;
  }
  else {
    event.data.timer = 0;
  }

  // Timestamp:
  event.data.timestamp = Math.round(window[bs]('get', 'i') / 1000);
}, false);
