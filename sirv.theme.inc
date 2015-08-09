<?php

/**
 * Returns HTML for an image field that uses Sirv.
 *
 * @param $variables
 *   An associative array containing:
 *   - item: Associative array of image data, which may include "uri", "alt",
 *     "width", "height", "title" and "attributes".
 *   - sirv_profile: An optional Sirv profile.
 *   - path: An array containing the link 'path' and link 'options'.
 *
 * @ingroup themeable
 */
function theme_sirv_image_formatter($variables) {
  $item = $variables['item'];
  $uri = $item['uri'];

  $parameters = array();

  // If a profile is specified, add it as a query parameter.
  if ($variables['sirv_profile']) {
    $parameters['profile'] = urlencode($variables['sirv_profile']);
  }

  // If additional options were entered, add them as query parameters.
  if ($variables['additional_options']) {
    // parse_str is not used here, because it converts periods to underscores.
    $options = explode('&', $variables['additional_options']);
    foreach ($options as $option) {
      $parameter = explode('=', $option);
      if (!empty($parameter[0]) && !empty($parameter[1])) {
        $parameters[$parameter[0]] = $parameter[1];
      }
    }
  }

  // Add the query parameters to the URI.
  if (!empty($parameters)) {
    $uri .= '?' . drupal_http_build_query($parameters);
  }

  $image = array(
    'path' => $uri,
  );

  if (array_key_exists('alt', $item)) {
    $image['alt'] = $item['alt'];
  }

  if (isset($item['attributes'])) {
    $image['attributes'] = $item['attributes'];
  }

  // Do not output an empty 'title' attribute.
  if (isset($item['title']) && drupal_strlen($item['title']) > 0) {
    $image['title'] = $item['title'];
  }

  $output = theme('sirv_image', $image);

  // The link path and link options are both optional, but for the options to be
  // processed, the link path must at least be an empty string.
  if (isset($variables['path']['path'])) {
    $path = $variables['path']['path'];
    $options = isset($variables['path']['options']) ? $variables['path']['options'] : array();
    // When displaying an image inside a link, the html option must be TRUE.
    $options['html'] = TRUE;
    $output = l($output, $path, $options);
  }

  return $output;
}

/**
 * Returns HTML for a Sirv image.
 *
 * @param $variables
 *   An associative array containing:
 *   - path: Either the path of the image file (relative to base_path()) or a
 *     full URL.
 *   - width: The width of the image (if known).
 *   - height: The height of the image (if known).
 *   - alt: The alternative text for text-based browsers.
 *   - title: The title text is displayed when the image is hovered in some
 *     popular browsers.
 *   - url_attribute: The attribute to use for the URL (src or data-src,
 *     for example).
 *   - attributes: Associative array of attributes to be placed in the img tag.
 */
function theme_sirv_image($variables) {
  $attributes = $variables['attributes'];

  $url_attribute = (!empty($variables['url_attribute'])) ? $variables['url_attribute'] : 'src';
  $attributes[$url_attribute] = file_create_url($variables['path']);

  foreach (array('width', 'height', 'alt', 'title') as $key) {
    if (isset($variables[$key])) {
      $attributes[$key] = $variables[$key];
    }
  }

  return '<img' . drupal_attributes($attributes) . ' />';
}
