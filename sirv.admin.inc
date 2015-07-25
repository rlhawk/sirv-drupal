<?php

/**
 * @file
 * Administrative functionality for Sirv settings and profiles.
 */

/**
 * Menu callback for Sirv settings form.
 */
function sirv_settings_form($form, &$form_state) {
  $form = array();

  $form['sirv_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Key'),
    '#default_value' => variable_get('sirv_key', ''),
  );
  $form['sirv_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret Key'),
    '#default_value' => variable_get('sirv_secret_key', ''),
  );
  $form['sirv_bucket'] = array(
    '#type' => 'textfield',
    '#title' => t('Bucket'),
    '#default_value' => variable_get('sirv_bucket', ''),
  );
  $form['sirv_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Host'),
    '#default_value' => variable_get('sirv_host', 'http://s3.sirv.com'),
  );
  $form['sirv_profiles_directory'] = array(
    '#type' => 'textfield',
    '#title' => t('Profiles directory'),
    '#description' => t('Enter the name of the directory that contains Sirv profiles. The default name is %dir_name.', array('%dir_name' => 'Profiles')),
    '#default_value' => variable_get('sirv_profiles_directory', 'Profiles'),
  );

  return system_settings_form($form);
}
