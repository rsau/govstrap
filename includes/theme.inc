<?php

/**
 * @file
 * theme.inc
 */

/**
 * Implements theme_breadrumb().
 */
function govstrap_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    $page_type = arg(0);
    if ($page_type == 'node') {
      $node_id = arg(1);
      if (!empty($node_id) && is_numeric($node_id)) {
        $node = node_load(arg(1));
        switch ($node->type) {
          case 'webform':
            $breadcrumb[] = 'Form';
            $breadcrumb[] = $node->field_title['und'][0]['value'];
            break;
        }
      }
    }
    elseif ($page_type == 'search') {
      $breadcrumb = array('<a href="/">Home</a>', 'Search');
    }
    else {
      $breadcrumb[] = drupal_get_title();
    }

    $breadcrumbs = '<ol class="breadcrumb">';
    foreach ($breadcrumb as $key => $value) {
      $breadcrumbs .= '<li>' . $value . '</li>';
    }
    $breadcrumbs .= '</ol>';

    return $breadcrumbs;
  }
}

/**
 * Implements of theme_status_messages.
 */
function govstrap_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );

  // Map our drupal statuses to bootstrap classes
  $bootstrap_statuses = array(
    'status' => 'alert-success',
    'error' => 'alert-error',
    'warning' => 'alert-warning',
  );

  foreach (drupal_get_messages($display) as $type => $messages) {
    // Grab the bootstrap class that corresponds to $type
    $bootstrap_class = $bootstrap_statuses[$type];
    $output .= "<div class=\"alert $bootstrap_class\">";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>";
    }
    if (count($messages) > 1) {
      $output .= " <ul>";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>";
      }
      $output .= " </ul>";
    }
    else {
      $output .= $messages[0];
    }
    $output .= "</div>";
  }
  return $output;
}
