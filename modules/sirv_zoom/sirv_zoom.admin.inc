<?php

/**
 * @file
 * Administrative functionality for Sirv Zoom profiles.
 */

/**
 * Menu callback; displays the list of Sirv Zoom profiles.
 */
function sirv_zoom_profiles_list() {
  $profiles = sirv_zoom_get_profiles();

  $header = array(
    t('Name'),
    array('data' => t('Operations'), 'colspan' => '2'),
  );
  $rows = array();

  foreach ($profiles as $name => $profile) {
    $label = $profile['label'];
    $name = $profile['name'];

    $profile_url_string = str_replace('_', '-', $name);

    $variables = array(
      'label' => $label,
      'name' => $name,
    );

    // Set the name column.
    $row = array(theme('sirv_zoom_profiles_list_description', $variables));

    // Set the edit column.
    $row[] = array('data' => l(t('edit'), SIRV_ZOOM_MENU_PATH . '/edit/' . $profile_url_string));

    // Set the delete column.
    $row[] = array('data' => l(t('delete'), SIRV_ZOOM_MENU_PATH . '/delete/' . $profile_url_string));

    $rows[] = $row;
  }

  $build['sirv_zoom_profiles_list_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No Sirv Zoom profiles are available. <a href="@link">Add a profile</a>.', array('@link' => url(SIRV_ZOOM_MENU_PATH . '/add'))),
  );

  return $build;
}

/**
 * Form constructor for the Sirv Zoom profile edit form.
 *
 * @param array $profile
 *   (optional) An array representing the profile, when editing an
 *   existing profile.
 *
 * @ingroup forms
 */
function sirv_zoom_profile_form($form, &$form_state, $profile = NULL) {
  $true_false_options = array('true' => t('True'), 'false' => t('False'));

  $form['label'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#default_value' => $profile['label'],
    '#description' => t('The human-readable name of the profile.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => $profile['name'],
    '#maxlength' => 32,
    '#disabled' => isset($profile['name']),
    '#machine_name' => array(
      'exists' => 'sirv_zoom_profile_load',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for the profile. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['zoom_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Zoom options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['zoom_options']['click_to_zoom'] = array(
    '#type' => 'select',
    '#title' => t('Click to zoom'),
    '#description' => t('Number of clicks to zoom in (@disabled = disabled zoom on click; default: @default).', array('@disabled' => 0, '@default' => 1)),
    '#empty_option' => t('Default'),
    '#options' => array(0, 1, 2),
    '#default_value' => $profile['click_to_zoom'],
  );
  $form['zoom_options']['zoom_on_wheel'] = array(
    '#type' => 'select',
    '#title' => t('Zoom on wheel'),
    '#description' => t('Zoom in and out on mouse wheel (default: @default).', array('@default' => t('True'))),
    '#empty_option' => t('Default'),
    '#options' => $true_false_options,
    '#default_value' => $profile['zoom_on_wheel'],
  );

  $form['fullscreen_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Full screen options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['fullscreen_options']['fullscreen'] = array(
    '#type' => 'select',
    '#title' => t('Fullscreen'),
    '#description' => t('Enable the full screen view (default: @default).', array('@default' => t('True'))),
    '#empty_option' => t('Default'),
    '#options' => $true_false_options,
    '#default_value' => $profile['fullscreen'],
  );
  $form['fullscreen_options']['fullscreen_only'] = array(
    '#type' => 'select',
    '#title' => t('Fullscreen only'),
    '#description' => t('Click main image to go immediately to full-screen (default: @default).', array('@default' => t('False'))),
    '#empty_option' => t('Default'),
    '#options' => $true_false_options,
    '#default_value' => $profile['fullscreen_only'],
  );

  $form['thumbnail_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Thumbnail options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['thumbnail_options']['thumbnails'] = array(
    '#type' => 'textfield',
    '#title' => t('Thumbnails position'),
    '#description' => t('Options: @options (use @id to put thumbnails in an external box; default: @default).', array('@options' => 'bottom, left, right, #id', '@id' => '#id', '@default' => 'bottom')),
    '#default_value' => $profile['thumbnails'],
  );
  $form['thumbnail_options']['thumbnails_orientation'] = array(
    '#type' => 'select',
    '#title' => t('Thumbnails orientation'),
    '#description' => t('Orientation of thumbnails when they are positioned outside (via @id). (default: @default).', array('@id' => '#id', '@default' => t('Horizontal'))),
    '#empty_option' => t('Default'),
    '#options' => array('horizontal' => t('Horizontal'), 'vertical' => t('Vertical')),
    '#default_value' => $profile['thumbnails_orientation'],
  );
  $form['thumbnail_options']['square_thumbnails'] = array(
    '#type' => 'select',
    '#title' => t('Square thumbnails'),
    '#description' => t('Enable square thumbnails (default: @default).', array('@default' => t('True'))),
    '#empty_option' => t('Default'),
    '#options' => $true_false_options,
    '#default_value' => $profile['square_thumbnails'],
  );

  $form['context_menu_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Context menu options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['context_menu_options']['context_menu'] = array(
    '#type' => 'select',
    '#title' => t('Enable context menu'),
    '#description' => t('Enable context menu (default: @default).', array('@default' => t('True'))),
    '#empty_option' => t('Default'),
    '#options' => $true_false_options,
    '#default_value' => $profile['context_menu'],
  );
  $form['context_menu_options']['text_zoom_in'] = array(
    '#type' => 'textfield',
    '#title' => t('Zoom-in text'),
    '#description' => t('The text to display for the menu option to zoom in (default: @default).', array('@default' => 'Zoom In')),
    '#default_value' => $profile['text_zoom_in'],
  );
  $form['context_menu_options']['text_zoom_out'] = array(
    '#type' => 'textfield',
    '#title' => t('Zoom-out text'),
    '#description' => t('The text to display for the menu option to zoom out (default: @default).', array('@default' => 'Zoom Out')),
    '#default_value' => $profile['text_zoom_out'],
  );
  $form['context_menu_options']['text_enter_fullscreen'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter full screen text'),
    '#description' => t('The text to display for the menu option to enter full screen view (default: @default).', array('@default' => 'Enter Full Screen')),
    '#default_value' => $profile['text_enter_fullscreen'],
  );
  $form['context_menu_options']['text_exit_fullscreen'] = array(
    '#type' => 'textfield',
    '#title' => t('Exit full screen text'),
    '#description' => t('The text to display for the menu option to exit full screen view (default: @default).', array('@default' => 'Exit Full Screen')),
    '#default_value' => $profile['text_exit_fullscreen'],
  );
  $form['context_menu_options']['text_download'] = array(
    '#type' => 'textfield',
    '#title' => t('Download image text'),
    '#description' => t('The text to display for the menu option to download the image (default: @default).', array('@default' => 'Download Image')),
    '#default_value' => $profile['text_download'],
  );

  $form['other_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Other options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['other_options']['retina'] = array(
    '#type' => 'select',
    '#title' => t('Retina'),
    '#description' => t('Enable retina images (default: @default).', array('@default' => t('False'))),
    '#empty_option' => t('Default'),
    '#options' => $true_false_options,
    '#default_value' => $profile['retina'],
  );

  $form['created'] = array(
    '#type' => 'value',
    '#value' => $profile['created'],
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save profile'),
    '#submit' => array('sirv_zoom_profile_form_submit'),
    '#weight' => 40,
  );
  if (isset($profile['name'])) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete profile'),
      '#submit' => array('sirv_zoom_profile_form_delete_submit'),
      '#limit_validation_errors' => array(),
      '#weight' => 45,
    );
  }
  $form['actions']['cancel'] = array(
    '#type' => 'link',
    '#title' => t('Cancel'),
    '#href' => SIRV_ZOOM_MENU_PATH,
    '#weight' => 50,
  );

  return $form;
}

/**
 * Form submission handler for sirv_zoom_profile_form().
 */
function sirv_zoom_profile_form_submit($form, &$form_state) {
  $fields = array();
  $schema = drupal_get_schema('sirv_zoom_profile');
  $field_list = array_keys($schema['fields']);
  foreach ($field_list as $field_list_item) {
    if (!empty($form_state['values'][$field_list_item])) {
      $fields[$field_list_item] = $form_state['values'][$field_list_item];
    }
    else {
      $fields[$field_list_item] = NULL;
    }
  }

  sirv_zoom_save_profile($fields);

  $form_state['redirect'] = SIRV_ZOOM_MENU_PATH . '/list';
}

/**
 * Form submission handler for sirv_zoom_profile_form().
 *
 * Handles the 'Delete' button on the Sirv Zoom profile form.
 */
function sirv_zoom_profile_form_delete_submit($form, &$form_state) {
  $form_state['redirect'] = SIRV_ZOOM_MENU_PATH . '/delete/' . str_replace('_', '-', $form['name']['#default_value']);
}

/**
 * Menu callback to delete a Sirv Zoom profile.
 */
function sirv_zoom_profile_delete_confirm($form, &$form_state, $profile) {
  $form['name'] = array('#type' => 'value', '#value' => $profile['name']);
  $form['label'] = array('#type' => 'value', '#value' => $profile['label']);

  $message = t('Are you sure you want to delete the Sirv Zoom profile %label?', array('%label' => $profile['label']));
  $caption = '<p>' . t('This action cannot be undone.') . '</p>';

  return confirm_form($form, filter_xss_admin($message), SIRV_ZOOM_MENU_PATH, filter_xss_admin($caption), t('Delete'));
}

/**
 * Submit handler for sirv_zoom_profile_delete_confirm.
 */
function sirv_zoom_profile_delete_confirm_submit($form, &$form_state) {
  db_delete('sirv_zoom_profile')
    ->condition('name', $form_state['values']['name'])
    ->execute();

  $t_args = array('%label' => $form_state['values']['label']);
  drupal_set_message(t('The Sirv Zoom profile %label has been deleted.', $t_args));
  watchdog('sirv_zoom', 'Deleted Sirv Zoom profile %label.', $t_args, WATCHDOG_NOTICE);

  $form_state['redirect'] = SIRV_ZOOM_MENU_PATH;
}
