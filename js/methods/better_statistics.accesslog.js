/**
 * Callback method to handle async processing of pageviews in accesslog.
 */
BetterStatistics.prototype.accesslog = function() {
  var accessStats = this.get('accessStats');
  accessStats = typeof(accessStats) == 'undefined' ? {} : accessStats;

  // Trigger an event to gather data.
  this.trigger('statistics.accesslog', accessStats);

  // POST to the callback URL.
  this.post('accesslog', accessStats);;
};
