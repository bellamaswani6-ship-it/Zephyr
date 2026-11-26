#include <zephyr/sys/printk.h>
#include "led_lib.h"

void led_on(void)
{
    printk("LED ON\n");
}

void led_off(void)
{
    printk("LED OFF\n");
}

void led_toggle(void)
{
    printk("LED TOGGLED\n");
}
