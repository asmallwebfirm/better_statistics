(function (w) {
  // Determine the name of the stats object and save the existing queue.
  var bs = w['BetterStatsObj'];
  var queue = w[bs].q || [];

  // Redefine the global Better Statistics object to a facade that handles all
  // Better Statistics JS API calls, rather than queueing commands.
  w[bs] = new BetterStatistics();

  // Iterate over previously queued commands and execute them.
  for (var i = 0; i < queue.length; ++i) {
    switch (queue[i].length) {
      case 1: w[bs](queue[i][0]); break;
      case 2: w[bs](queue[i][0], queue[i][1]); break;
      case 3: w[bs](queue[i][0], queue[i][1], queue[i][2]); break;
    }
  }
})(window);
