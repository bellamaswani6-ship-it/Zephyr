#include <zephyr/kernel.h>
#include "led_lib.h"

int main(void)
{
    while (1)
    {
        led_on();
        k_sleep(K_SECONDS(1));

        led_off();
        k_sleep(K_SECONDS(1));

        led_toggle();
        k_sleep(K_SECONDS(1));
    }

    return 0;
}
