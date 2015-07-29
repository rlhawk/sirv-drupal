<?php

/**
 * Returns HTML for an image field that uses Sirv Zoom.
 *
 * @param $variables
 *   An associative array containing:
 *   - items: A multidimensional array of image data, which may include "uri",
 *     "alt", "width", "height", "title" and "attributes".
 *   - sirv_zoom_profile: An optional Sirv Zoom profile.
 *   - default_sirv_profile: An optional Sirv profile to use as the default.
 *   - responsive_sirv_profiles: A comma-delimited list of profiles to use
 *     for responsive behavior.
 *
 * @ingroup themeable
 */
function theme_sirv_zoom_image_formatter($variables) {
  $items = $variables['items'];

  $attributes = array(
    'class' => 'Sirv',
    'data-effect' => 'zoom',
  );

  $options = array();
  if (!empty($variables['sirv_zoom_profile'])) {
    $sirv_zoom_profile = sirv_zoom_get_profile($variables['sirv_zoom_profile']);

    // Add options.
    $all_options = array(
      'click_to_zoom' => 'click-to-zoom',
      'zoom_on_wheel' => 'zoom-on-wheel',
      'fullscreen' => 'fullscreen',
      'fullscreen_only' => 'fullscreen-only',
      'retina' => 'retina',
      'thumbnails' => 'thumbnails',
      'thumbnails_orientation' => 'thumbnails-orientation',
      'square_thumbnails' => 'squareThumbnails',
      'contextmenu' => 'contextmenu',
      'text_zoom_in' => 'textZoomIn',
      'text_zoom_out' => 'textZoomOut',
      'text_enter_fullscreen' => 'textEnterFullscreen',
      'text_exit_fullscreen' => 'textExitFullscreen',
      'text_download' => 'textDownload',
    );
    foreach ($sirv_zoom_profile as $option => $value) {
      if (array_key_exists($option, $all_options) && !empty($value)) {
        $options[] = $all_options[$option] . ': ' . $value;
      }
    }
    if (!empty($options)) {
      $attributes['data-options'] = implode('; ', $options);
    }

    // If Sirv profiles are specified, add them as an attribute.
    $sirv_profiles = array();
    if (!empty($variables['responsive_sirv_profiles'])) {
      $sirv_profiles[] = $variables['responsive_sirv_profiles'];
    }
    if (!empty($variables['default_sirv_profile'])) {
      $sirv_profiles[] = $variables['default_sirv_profile'];
    }
    if (!empty($sirv_profiles)) {
      $attributes['data-profiles'] = implode(', ', $sirv_profiles);
    }
  }

  $output = '<figure' . drupal_attributes($attributes) . '>';
  foreach ($items as $delta => $item) {
    $uri = $item['uri'];

    $image = array(
      'path' => $uri,
      'url_attribute' => 'data-src',
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

    $output .= theme('sirv_image', $image);
  }
  $output .= '</figure>';

  return $output;
}

/**
 * Returns HTML for a Sirv Zoom profile description.
 *
 * @param array $variables
 *   An associative array containing:
 *   - label: The human-readable label of the profile.
 *   - name: The machine name of the profile.
 *
 * @ingroup themeable
 */
function theme_sirv_zoom_profiles_list_description($variables) {
  $label = $variables['label'];
  $name = $variables['name'];

  $output = check_plain($label);
  $output .= ' <small>' . t('(Machine name: @name)', array('@name' => $name)) . '</small>';

  return $output;
}
