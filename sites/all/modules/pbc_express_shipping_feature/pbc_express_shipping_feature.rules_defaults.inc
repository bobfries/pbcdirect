<?php
/**
 * @file
 * pbc_express_shipping_feature.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function pbc_express_shipping_feature_default_rules_configuration() {
  $items = array();
  $items['rules_calculate_by_field'] = entity_import('rules_config', '{ "rules_calculate_by_field" : {
      "LABEL" : "Calculate by field",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "commerce_line_item", "commerce_shipping" ],
      "ON" : { "commerce_shipping_calculate_rate" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "commerce-line-item:type" ], "value" : "shipping" } },
        { "data_is" : {
            "data" : [ "commerce-line-item:commerce-shipping-service" ],
            "value" : "express_shipping"
          }
        }
      ],
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "commerce-line-item:order:commerce-line-items" ] },
            "ITEM" : { "line_item" : "Line Item" },
            "DO" : [
              { "component_rules_calculate_shipping_amount_using_shipping_field" : {
                  "USING" : { "line_item" : [ "line_item" ] },
                  "PROVIDE" : { "shipping_for_line_item" : { "shipping_for_line_item" : "Shipping cost for line item" } }
                }
              },
              { "commerce_line_item_unit_price_add" : {
                  "commerce_line_item" : [ "commerce_line_item" ],
                  "amount" : [ "shipping-for-line-item:amount" ],
                  "component_name" : "flat_rate_express_shipping",
                  "round_mode" : "2"
                }
              }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_calculate_shipping_amount_using_shipping_field'] = entity_import('rules_config', '{ "rules_calculate_shipping_amount_using_shipping_field" : {
      "LABEL" : "Calculate shipping amount using shipping field",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "line_item" : { "label" : "Line Item", "type" : "commerce_line_item" },
        "shipping_for_line_item" : {
          "label" : "Shipping cost for line item",
          "type" : "commerce_price",
          "parameter" : false
        }
      },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "line-item" ], "field" : "commerce_product" } },
        { "entity_has_field" : {
            "entity" : [ "line-item:commerce-product" ],
            "field" : "field_express_shipping_price"
          }
        }
      ],
      "DO" : [
        { "data_calc" : {
            "USING" : {
              "input_1" : [ "line-item:commerce-product:field-express-shipping-price:amount" ],
              "op" : "*",
              "input_2" : [ "line-item:quantity" ]
            },
            "PROVIDE" : { "result" : { "line_item_calculated_shipping_cost" : "Line Item Calculated Shipping Cost" } }
          }
        },
        { "data_set" : {
            "data" : [ "shipping-for-line-item:amount" ],
            "value" : [ "line-item-calculated-shipping-cost" ]
          }
        }
      ],
      "PROVIDES VARIABLES" : [ "shipping_for_line_item" ]
    }
  }');
  return $items;
}
