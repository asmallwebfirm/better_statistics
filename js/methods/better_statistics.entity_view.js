/**
 * Callback method to handle async processing of entity views.
 */
BetterStatistics.prototype.entity_view = function(entity_type, entity_id) {
  var entityInfo = this.get('entityInfo');
  entityInfo = typeof(entityInfo) == 'undefined' ? {} : entityInfo;

  // Re-map array values passed in to the named variables.
  if (entity_type instanceof Array && entity_type.length == 2) {
    entity_id = entity_type.pop();
    entity_type = entity_type.shift();
  }

  entityInfo.entity_type = entity_type;
  entityInfo.entity_id = entity_id;
  entityInfo.timestamp = Math.round(this.get('i') / 1000);

  // Trigger an event to gather data.
  this.trigger('statistics.entity_view', entityInfo);

  // POST to the callback URL.
  this.post('entity_view', entityInfo);
};
