<?php

function load_congregation_records() {

  $controller = entity_get_controller('congregation');

  try { 
    $controller->save((object)array('cid' => '2', 'congregation_name' => 'Enfield', 'khid' => '2', 'phone' => '(860)749-9100', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'MA3A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '4', 'congregation_name' => 'Palmer', 'khid' => '4', 'phone' => '(413)245-3066', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'MA 9', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '5', 'congregation_name' => 'Longmeadow', 'khid' => '2', 'phone' => '(860)749-9100', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => ' ', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '9', 'congregation_name' => 'Spfld - Forrest Park', 'khid' => '9', 'phone' => '(413)733-9846', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'MA 9', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '14', 'congregation_name' => 'Wallingford', 'khid' => '14', 'phone' => '', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => '', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '15', 'congregation_name' => 'Middletown Central', 'khid' => '15', 'phone' => '(860)347-2881', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2B', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '16', 'congregation_name' => 'Cranston', 'khid' => '16', 'phone' => '', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => '', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '17', 'congregation_name' => 'Preston', 'khid' => '17', 'phone' => '(860)885-0552', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => '', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '18', 'congregation_name' => 'Chicopee East', 'khid' => '18', 'phone' => '(413)532-8713', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'MA 3', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '19', 'congregation_name' => 'Devon', 'khid' => '19', 'phone' => '(203)874-6965', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => '', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '20', 'congregation_name' => 'Bristol West', 'khid' => '20', 'phone' => '', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => ' ', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '21', 'congregation_name' => 'East Hartford', 'khid' => '36', 'phone' => '(860)528-2717', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2B', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '22', 'congregation_name' => 'New Britain North', 'khid' => '22', 'phone' => '(860)223-9117', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '23', 'congregation_name' => 'Bloomfield', 'khid' => '23', 'phone' => '(860)242-3134', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '24', 'congregation_name' => 'Hartford South', 'khid' => '24', 'phone' => '(860)524-1414', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '25', 'congregation_name' => 'Granby', 'khid' => '25', 'phone' => '(860)653-2635', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'MA3A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '26', 'congregation_name' => 'Warehouse Point', 'khid' => '26', 'phone' => '(860)623-6022', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'MA3A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '27', 'congregation_name' => 'Willimantic', 'khid' => '43', 'phone' => '(860)423-6920', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2B', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '28', 'congregation_name' => 'Plainville', 'khid' => '28', 'phone' => '(860)747-2636', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => ' ', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '29', 'congregation_name' => 'Middletown North', 'khid' => '15', 'phone' => '(860)347-2881', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2B', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '30', 'congregation_name' => 'Wintergreen Hills', 'khid' => '30', 'phone' => '(203)387-9182', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => ' ', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '32', 'congregation_name' => 'Middletown South', 'khid' => '15', 'phone' => '(860)347-2881', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2B', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '33', 'congregation_name' => 'Hartford North', 'khid' => '36', 'phone' => '(860)528-4131', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '34', 'congregation_name' => 'Wethersfield', 'khid' => '34', 'phone' => '(860)529-7146', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2B', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '35', 'congregation_name' => 'Blue Hills', 'khid' => '35', 'phone' => '(860)243-3408', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '36', 'congregation_name' => 'South Windsor', 'khid' => '36', 'phone' => '(860)528-2717', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '37', 'congregation_name' => 'Westbrook', 'khid' => '37', 'phone' => '(860)669-1654', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '38', 'congregation_name' => 'Waterbury West', 'khid' => '38', 'phone' => '(203)573-1538', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => '', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '39', 'congregation_name' => 'Canton', 'khid' => '39', 'phone' => '(860)693-0563', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '40', 'congregation_name' => 'Vernon', 'khid' => '1', 'phone' => '', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'GA 12', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '41', 'congregation_name' => 'Stafford Springs', 'khid' => '41', 'phone' => '(860)684-2419', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2B', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '42', 'congregation_name' => 'Windsor', 'khid' => '36', 'phone' => '(860)528-2717', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '43', 'congregation_name' => 'Columbia', 'khid' => '43', 'phone' => '(860)456-8308', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2B', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '44', 'congregation_name' => 'Spfld - Liberty Height', 'khid' => '44', 'phone' => '', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => ' ', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '45', 'congregation_name' => 'Hartford Central', 'khid' => '35', 'phone' => '(960)527-1371', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '1', 'congregation_name' => 'Manchester', 'khid' => '1', 'phone' => '(860)646-1490', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '46', 'congregation_name' => 'New Britain Central', 'khid' => '46', 'phone' => '(860)832-8700', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2A', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '47', 'congregation_name' => 'Berlin', 'khid' => '47', 'phone' => '(860)832-8700', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2B', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '48', 'congregation_name' => 'Newington', 'khid' => '48', 'phone' => '(860)666-3690', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2B', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '49', 'congregation_name' => 'West Hartford', 'khid' => '49', 'phone' => '(860)521-1531', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => 'CT2B', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '50', 'congregation_name' => 'Colchester', 'khid' => '50', 'phone' => '', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => '', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '51', 'congregation_name' => 'Norwich North', 'khid' => '17', 'phone' => '(860)887-5438', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => '', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '53', 'congregation_name' => 'Bristol East', 'khid' => '20', 'phone' => '(860)583-0897', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => '', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '55', 'congregation_name' => 'Meriden North', 'khid' => '55', 'phone' => '(203)634-0141', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => '', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '56', 'congregation_name' => 'East Westfield', 'khid' => '56', 'phone' => '(413)568-1780', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => ' ', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '57', 'congregation_name' => ' ', 'khid' => '57', 'phone' => '(413)734-0040', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => '', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '58', 'congregation_name' => 'Quinnipiac', 'khid' => '58', 'phone' => '', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => '', 'is_new' => TRUE,));
    $controller->save((object)array('cid' => '59', 'congregation_name' => 'Meriden South', 'khid' => '59', 'phone' => '(203)634-0141', 'ptcid' => NULL, 'last_trade_date' => NULL, 'active' => 1, 'circuit' => '', 'is_new' => TRUE,));
  } 
  catch (Exception $e) 
  {
    $transaction->rollback();
  }
}
