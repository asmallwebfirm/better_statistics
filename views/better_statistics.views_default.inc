<?php

/**
 * @file
 * Views defaults for the Better Statistics module.
 */


/**
 * Implements hook_views_default_views().
 */
function better_statistics_views_default_views() {
  // Recent Hits report.
  $view = new view();
  $view->name = 'stats_recent_hits';
  $view->description = 'This page displays the site\'s most recent hits.';
  $view->tag = 'default';
  $view->base_table = 'accesslog';
  $view->human_name = 'Recent hits';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Recent hits';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access statistics';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['slave'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = array(
    'timestamp' => 'timestamp',
    'title' => 'title',
    'path' => 'path',
    'name' => 'name',
    'aid' => 'aid',
  );
  $handler->display->display_options['style_options']['default'] = 'timestamp';
  $handler->display->display_options['style_options']['info'] = array(
    'timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'path' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'aid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Relationship: Access log: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'accesslog';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Access log: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'accesslog';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  /* Field: Access log: Page title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'accesslog';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title]<br />';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['title']['display_as_link'] = FALSE;
  /* Field: Access log: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'accesslog';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = 'Page';
  $handler->display->display_options['fields']['path']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['path']['alter']['text'] = '[title]
  <a href="/[path]">[path]</a>';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['display_as_link'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Access log: Aid */
  $handler->display->display_options['fields']['aid']['id'] = 'aid';
  $handler->display->display_options['fields']['aid']['table'] = 'accesslog';
  $handler->display->display_options['fields']['aid']['field'] = 'aid';
  $handler->display->display_options['fields']['aid']['label'] = 'Operations';
  $handler->display->display_options['fields']['aid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['aid']['alter']['text'] = 'details';
  $handler->display->display_options['fields']['aid']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['aid']['alter']['path'] = 'admin/reports/access/[aid]';
  $handler->display->display_options['fields']['aid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['aid']['separator'] = '';
  /* Sort criterion: Access log: Timestamp */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'accesslog';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/reports/hits';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Recent hits';
  $handler->display->display_options['menu']['description'] = 'This page displays the site\'s most recent hits';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Export view. */
  $views[$view->name] = $view;


  // Top Pages report.
  $view = new view();
  $view->name = 'stats_top_pages';
  $view->description = 'View pages that have been hit frequently';
  $view->tag = 'default';
  $view->base_table = 'accesslog';
  $view->human_name = 'Top pages';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Top pages in the past %accesslog_interval';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access statistics';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['slave'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = array(
    'aid' => 'aid',
    'title' => 'title',
    'path' => 'path',
    'timer' => 'timer',
    'timer_1' => 'timer_1',
  );
  $handler->display->display_options['style_options']['default'] = 'aid';
  $handler->display->display_options['style_options']['info'] = array(
    'aid' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'path' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timer' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timer_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Field: COUNT(Access log: Aid) */
  $handler->display->display_options['fields']['aid']['id'] = 'aid';
  $handler->display->display_options['fields']['aid']['table'] = 'accesslog';
  $handler->display->display_options['fields']['aid']['field'] = 'aid';
  $handler->display->display_options['fields']['aid']['group_type'] = 'count';
  $handler->display->display_options['fields']['aid']['label'] = 'Hits';
  $handler->display->display_options['fields']['aid']['element_label_colon'] = FALSE;
  /* Field: Access log: Page title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'accesslog';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title]<br />';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['title']['display_as_link'] = FALSE;
  /* Field: Access log: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'accesslog';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = 'Page';
  $handler->display->display_options['fields']['path']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['path']['alter']['text'] = '[title]
    <a href="/[path]">[path]</a>';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['display_as_link'] = FALSE;
  /* Field: AVG(Access log: Timer) */
  $handler->display->display_options['fields']['timer']['id'] = 'timer';
  $handler->display->display_options['fields']['timer']['table'] = 'accesslog';
  $handler->display->display_options['fields']['timer']['field'] = 'timer';
  $handler->display->display_options['fields']['timer']['group_type'] = 'avg';
  $handler->display->display_options['fields']['timer']['label'] = 'Average page generation time';
  $handler->display->display_options['fields']['timer']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timer']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['timer']['precision'] = '0';
  $handler->display->display_options['fields']['timer']['separator'] = '';
  $handler->display->display_options['fields']['timer']['suffix'] = ' ms';
  $handler->display->display_options['fields']['timer']['granularity'] = '2';
  /* Field: SUM(Access log: Timer) */
  $handler->display->display_options['fields']['timer_1']['id'] = 'timer_1';
  $handler->display->display_options['fields']['timer_1']['table'] = 'accesslog';
  $handler->display->display_options['fields']['timer_1']['field'] = 'timer';
  $handler->display->display_options['fields']['timer_1']['group_type'] = 'sum';
  $handler->display->display_options['fields']['timer_1']['label'] = 'Total page generation time';
  $handler->display->display_options['fields']['timer_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timer_1']['precision'] = '0';
  $handler->display->display_options['fields']['timer_1']['separator'] = '';
  $handler->display->display_options['fields']['timer_1']['as_interval'] = TRUE;
  $handler->display->display_options['fields']['timer_1']['granularity'] = '2';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/reports/pages';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Top pages';
  $handler->display->display_options['menu']['description'] = 'View pages that have been hit frequently.';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'management';

  /* Export view. */
  $views[$view->name] = $view;


  // Top referrers report.
  $view = new view();
  $view->name = 'stats_top_referrers';
  $view->description = 'View top referrers.';
  $view->tag = 'default';
  $view->base_table = 'accesslog';
  $view->human_name = 'Top referrers';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Top referrers in the past %accesslog_interval';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access statistics';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['slave'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'url_1' => 'url_1',
    'url' => 'url',
    'timestamp' => 'timestamp',
  );
  $handler->display->display_options['style_options']['default'] = 'url_1';
  $handler->display->display_options['style_options']['info'] = array(
    'url_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'url' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Field: COUNT(Access log: Referrer) */
  $handler->display->display_options['fields']['url_1']['id'] = 'url_1';
  $handler->display->display_options['fields']['url_1']['table'] = 'accesslog';
  $handler->display->display_options['fields']['url_1']['field'] = 'url';
  $handler->display->display_options['fields']['url_1']['group_type'] = 'count';
  $handler->display->display_options['fields']['url_1']['label'] = 'Hits';
  $handler->display->display_options['fields']['url_1']['element_label_colon'] = FALSE;
  /* Field: Access log: Referrer */
  $handler->display->display_options['fields']['url']['id'] = 'url';
  $handler->display->display_options['fields']['url']['table'] = 'accesslog';
  $handler->display->display_options['fields']['url']['field'] = 'url';
  $handler->display->display_options['fields']['url']['label'] = 'URL';
  $handler->display->display_options['fields']['url']['alter']['max_length'] = '35';
  $handler->display->display_options['fields']['url']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['url']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['url']['hide_empty'] = TRUE;
  /* Field: MAX(Access log: Timestamp) */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'accesslog';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['group_type'] = 'max';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Last Visit';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'time ago';
  /* Filter criterion: Access log: Referrer */
  $handler->display->display_options['filters']['url']['id'] = 'url';
  $handler->display->display_options['filters']['url']['table'] = 'accesslog';
  $handler->display->display_options['filters']['url']['field'] = 'url';
  $handler->display->display_options['filters']['url']['operator'] = 'longerthan';
  $handler->display->display_options['filters']['url']['value'] = '0';
  /* Filter criterion: Access log: Referrer */
  $handler->display->display_options['filters']['url_1']['id'] = 'url_1';
  $handler->display->display_options['filters']['url_1']['table'] = 'accesslog';
  $handler->display->display_options['filters']['url_1']['field'] = 'url';
  $handler->display->display_options['filters']['url_1']['operator'] = 'not';
  $handler->display->display_options['filters']['url_1']['value'] = parse_url($GLOBALS['base_url'], PHP_URL_HOST);

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/reports/referrers';

  /* Export view. */
  $views[$view->name] = $view;


  // Top Visitors report.
  $view = new view();
  $view->name = 'stats_top_visitors';
  $view->description = 'View visitors that hit many pages.';
  $view->tag = 'default';
  $view->base_table = 'accesslog';
  $view->human_name = 'Top visitors';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Top visitors in the past %accesslog_interval';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access statistics';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['slave'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'hostname_1' => 'hostname_1',
    'hostname' => 'hostname',
    'name' => 'name',
    'uid' => 'uid',
    'timer' => 'timer',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = 'hostname_1';
  $handler->display->display_options['style_options']['info'] = array(
    'hostname_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'hostname' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'uid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timer' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Relationship: Access log: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'accesslog';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: COUNT(Access log: Hostname) */
  $handler->display->display_options['fields']['hostname_1']['id'] = 'hostname_1';
  $handler->display->display_options['fields']['hostname_1']['table'] = 'accesslog';
  $handler->display->display_options['fields']['hostname_1']['field'] = 'hostname';
  $handler->display->display_options['fields']['hostname_1']['group_type'] = 'count';
  $handler->display->display_options['fields']['hostname_1']['label'] = 'Hits';
  $handler->display->display_options['fields']['hostname_1']['element_label_colon'] = FALSE;
  /* Field: Access log: Hostname */
  $handler->display->display_options['fields']['hostname']['id'] = 'hostname';
  $handler->display->display_options['fields']['hostname']['table'] = 'accesslog';
  $handler->display->display_options['fields']['hostname']['field'] = 'hostname';
  $handler->display->display_options['fields']['hostname']['label'] = '';
  $handler->display->display_options['fields']['hostname']['exclude'] = TRUE;
  $handler->display->display_options['fields']['hostname']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['hostname']['element_label_colon'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['empty'] = '[hostname]';
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'Visitor';
  $handler->display->display_options['fields']['uid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['uid']['alter']['text'] = '[name]';
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['empty'] = '[hostname]';
  $handler->display->display_options['fields']['uid']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: SUM(Access log: Timer) */
  $handler->display->display_options['fields']['timer']['id'] = 'timer';
  $handler->display->display_options['fields']['timer']['table'] = 'accesslog';
  $handler->display->display_options['fields']['timer']['field'] = 'timer';
  $handler->display->display_options['fields']['timer']['group_type'] = 'sum';
  $handler->display->display_options['fields']['timer']['label'] = 'Total Page Generation Time';
  $handler->display->display_options['fields']['timer']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timer']['precision'] = '0';
  $handler->display->display_options['fields']['timer']['separator'] = '';
  $handler->display->display_options['fields']['timer']['as_interval'] = TRUE;
  $handler->display->display_options['fields']['timer']['granularity'] = '2';
  /* Field: Blocked IPs: Block IP */
  $handler->display->display_options['fields']['ip']['id'] = 'ip';
  $handler->display->display_options['fields']['ip']['table'] = 'blocked_ips';
  $handler->display->display_options['fields']['ip']['field'] = 'ip';
  $handler->display->display_options['fields']['ip']['label'] = 'Operations';
  $handler->display->display_options['fields']['ip']['element_label_colon'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/reports/visitors';

  /* Export view. */
  $views[$view->name] = $view;


  // Track page visits report
  $view = new view();
  $view->name = 'stats_track_page_visits';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'accesslog';
  $view->human_name = 'Track user visits';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Track page visits';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access statistics';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['slave'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'timestamp' => 'timestamp',
    'title' => 'title',
    'path' => 'path',
    'aid' => 'aid',
  );
  $handler->display->display_options['style_options']['default'] = 'timestamp';
  $handler->display->display_options['style_options']['info'] = array(
    'timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'path' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'aid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Relationship: Access log: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'accesslog';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Access log: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'accesslog';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  /* Field: Access log: Page title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'accesslog';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title]<br />';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['title']['display_as_link'] = FALSE;
  /* Field: Access log: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'accesslog';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = 'Page';
  $handler->display->display_options['fields']['path']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['path']['alter']['text'] = '[title]
    <a href="/[path]">[path]</a>';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['display_as_link'] = FALSE;
  /* Field: Access log: Aid */
  $handler->display->display_options['fields']['aid']['id'] = 'aid';
  $handler->display->display_options['fields']['aid']['table'] = 'accesslog';
  $handler->display->display_options['fields']['aid']['field'] = 'aid';
  $handler->display->display_options['fields']['aid']['label'] = 'Operations';
  $handler->display->display_options['fields']['aid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['aid']['alter']['text'] = 'details';
  $handler->display->display_options['fields']['aid']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['aid']['alter']['path'] = 'admin/reports/access/[aid]';
  $handler->display->display_options['fields']['aid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['aid']['separator'] = '';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['uid']['title'] = '%1';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'user';
  $handler->display->display_options['arguments']['uid']['default_argument_options']['user'] = FALSE;
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'user';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'user/%/track/navigation';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Track page visits';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  /* Export view. */
  $views[$view->name] = $view;


  // Track node report.
  $view = new view();
  $view->name = 'stats_track_node';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'accesslog';
  $view->human_name = 'Track content visits';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Track';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access statistics';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['slave'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'timestamp' => 'timestamp',
    'url' => 'url',
    'name' => 'name',
    'aid' => 'aid',
  );
  $handler->display->display_options['style_options']['default'] = 'timestamp';
  $handler->display->display_options['style_options']['info'] = array(
    'timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'url' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'aid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Relationship: Access log: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'accesslog';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Access log: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'accesslog';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Time';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  /* Field: Access log: Referrer */
  $handler->display->display_options['fields']['url']['id'] = 'url';
  $handler->display->display_options['fields']['url']['table'] = 'accesslog';
  $handler->display->display_options['fields']['url']['field'] = 'url';
  $handler->display->display_options['fields']['url']['alter']['max_length'] = '35';
  $handler->display->display_options['fields']['url']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['url']['element_label_colon'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Access log: Aid */
  $handler->display->display_options['fields']['aid']['id'] = 'aid';
  $handler->display->display_options['fields']['aid']['table'] = 'accesslog';
  $handler->display->display_options['fields']['aid']['field'] = 'aid';
  $handler->display->display_options['fields']['aid']['label'] = 'Operations';
  $handler->display->display_options['fields']['aid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['aid']['alter']['text'] = 'details';
  $handler->display->display_options['fields']['aid']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['aid']['alter']['path'] = 'admin/reports/access/[aid]';
  $handler->display->display_options['fields']['aid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['aid']['separator'] = '';
  /* Contextual filter: Access log: exact path */
  $handler->display->display_options['arguments']['path']['id'] = 'path';
  $handler->display->display_options['arguments']['path']['table'] = 'accesslog';
  $handler->display->display_options['arguments']['path']['field'] = 'path';
  $handler->display->display_options['arguments']['path']['ui_name'] = 'Access log: exact path';
  $handler->display->display_options['arguments']['path']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['path']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['path']['title'] = '%1';
  $handler->display->display_options['arguments']['path']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['path']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['path']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['path']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['path']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['path']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['path']['validate']['fail'] = 'empty';
  $handler->display->display_options['arguments']['path']['limit'] = '0';
  $handler->display->display_options['arguments']['path']['prefix'] = 'node/';
  $handler->display->display_options['arguments']['path']['and_or'] = TRUE;
  /* Contextual filter: Access log: associated local tasks */
  $handler->display->display_options['arguments']['path_1']['id'] = 'path_1';
  $handler->display->display_options['arguments']['path_1']['table'] = 'accesslog';
  $handler->display->display_options['arguments']['path_1']['field'] = 'path';
  $handler->display->display_options['arguments']['path_1']['ui_name'] = 'Access log: associated local tasks';
  $handler->display->display_options['arguments']['path_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['path_1']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['path_1']['default_argument_skip_url'] = TRUE;
  $handler->display->display_options['arguments']['path_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['path_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['path_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['path_1']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['path_1']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['path_1']['validate']['fail'] = 'ignore';
  $handler->display->display_options['arguments']['path_1']['limit'] = '0';
  $handler->display->display_options['arguments']['path_1']['prefix'] = 'node/';
  $handler->display->display_options['arguments']['path_1']['suffix'] = '/';
  $handler->display->display_options['arguments']['path_1']['operator'] = 'starts';
  $handler->display->display_options['arguments']['path_1']['and_or'] = TRUE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'node/%/track';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Track';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  /* Export view. */
  $views[$view->name] = $view;

  return $views;
}
