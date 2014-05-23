<?php
/**
 * @file
 * Enables modules and site configuration for a standard site installation.
 */

/**
 * Implements hook_install_tasks_alter().
 */
function ptc_assistant_install_tasks_alter(&$tasks, $install_state) {
  global $install_state;

  // Skip language selection install step and default language to English.
  $tasks['install_select_locale']['display'] = FALSE;
  $tasks['install_select_locale']['run'] = INSTALL_TASK_SKIP;
  $install_state['parameters']['locale'] = 'en';

  // Override "install_finished" task to redirect people to home page.
  //$tasks['install_finished']['function'] = 'commons_install_finished';
}

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function ptc_assistant_form_install_configure_form_alter(&$form, $form_state) {
  $form['site_information']['site_name']['#default_value'] = 'PTC Assistant';
	$form['server_settings']['site_default_country']['#default_value'] = 'US';
	//$form['server_settings']['date_default_timezone']['default_value'] = 'America/New_York';
	
	// We do not need to expose the choice to receive update notifications
	$form['update_notifications']['#type'] = 'hidden';
	$form['update_notifications']['update_status_module']['#value'] = array(0, 0);
	
}