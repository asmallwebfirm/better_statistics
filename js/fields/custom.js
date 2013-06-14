document.addEventListener('statistics.accesslog', function(event) {
  // Cache Status: Impossible to know from the client-side, so we pass in a
  // dummy value to ensure no misleading values are saved.
  event.data.cache = 'UNKN';

  // Peak Memory: There's no way to know this, so we pass a bum value to
  // ensure the misleading peak memory value of the callback is overridden.
  event.data.peak_memory = 0;
}, false);
