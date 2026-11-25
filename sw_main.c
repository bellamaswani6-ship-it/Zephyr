
/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* Device tree aliases */
#define LED0_NODE DT_ALIAS(led0)
#define SW0_NODE  DT_ALIAS(sw0)

/* Get GPIO specifications */
static const struct gpio_dt_spec led =
    GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static const struct gpio_dt_spec button =
    GPIO_DT_SPEC_GET(SW0_NODE, gpios);

int main(void)
{
    int ret;
    bool led_state = false;

    /* Check LED readiness */
    if (!gpio_is_ready_dt(&led)) {
        printk("LED device not ready\n");
        return 0;
    }

    /* Check button readiness */
    if (!gpio_is_ready_dt(&button)) {
        printk("Button device not ready\n");
        return 0;
    }

    /* Configure LED as output */
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        printk("LED configuration failed\n");
        return 0;
    }

    /* Configure button as input */
    ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
    if (ret < 0) {
        printk("Button configuration failed\n");
        return 0;
    }

    printk("Switch controlled LED started\n");

    while (1) {

        /* Read switch state */
        int button_state = gpio_pin_get_dt(&button);

        if (button_state < 0) {
            printf("Button read failed\n");
            return 0;
        }

        if (button_state == 1) {

            /* Switch pressed: toggle LED */
            led_state = !led_state;

            gpio_pin_set_dt(&led, led_state);

            printk("LED: %s\n", led_state ? "ON" : "OFF");

            k_msleep(CONFIG_TD_BLINK_PERIOD_MS);
        }
        else {

            /* Switch released: turn LED OFF */
            led_state = false;

            gpio_pin_set_dt(&led, 0);

            k_msleep(20);
        }
    }

    return 0;
}

