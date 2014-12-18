<?php
/**
 * @file
 * pbc_express_shipping_feature.features.inc
 */

/**
 * Implements hook_commerce_flat_rate_default_services().
 */
function pbc_express_shipping_feature_commerce_flat_rate_default_services() {
  $items = array(
    'express_shipping' => array(
      'name' => 'express_shipping',
      'base' => 'express_shipping',
      'display_title' => 'Express Delivery - Next Working Day',
      'description' => 'Orders received before 1pm will be dispatched same day',
      'shipping_method' => 'flat_rate',
      'rules_component' => TRUE,
      'price_component' => 'flat_rate_express_shipping',
      'weight' => 0,
      'callbacks' => array(
        'rate' => 'commerce_flat_rate_service_rate_order',
        'details_form' => 'express_shipping_details_form',
        'details_form_validate' => 'express_shipping_details_form_validate',
        'details_form_submit' => 'express_shipping_details_form_submit',
      ),
      'module' => 'commerce_flat_rate',
      'title' => 'Express Shipping',
      'base_rate' => array(
        'amount' => '0',
        'currency_code' => 'GBP',
        'data' => array(),
      ),
      'data' => array(),
      'admin_list' => TRUE,
    ),
  );
  return $items;
}
