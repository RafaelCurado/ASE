#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

#define LED_GPIO 6
#define SW1_GPIO 3

void setup_switch1(void) {
    gpio_reset_pin(SW1_GPIO);
    gpio_set_direction(SW1_GPIO, GPIO_MODE_INPUT);
}

void setup_led(void) {
    gpio_reset_pin(LED_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
}

void set_led(uint32_t level) {
    gpio_set_level(LED_GPIO, level);
}

void get_switch(void) {
    gpio_get_level(SW1_GPIO);
}

void app_main(void)
{
    setup_switch1();
    setup_led();
    uint32_t led_level = 0;
    int sw1_value;

    while(1) {
        sw1_value = get_switch();
        ESP_LOGI("Switch", "Switch Value: %d", sw1_value);

        if (sw1_value == 1) {
            led_level = 1;
        } else {
            led_level = 0;
        }

        set_led(led_level);
        
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
