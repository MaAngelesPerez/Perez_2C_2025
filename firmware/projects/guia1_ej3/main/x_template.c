/*! @mainpage Template
 *
 * @section genDesc General Description
 *
 * This section describes how the program works.
 *
 * <a href="https://drive.google.com/...">Operation Example</a>
 *
 * @section hardConn Hardware Connection
 *
 * |    Peripheral  |   ESP32   	|
 * |:--------------:|:--------------|
 * | 	PIN_X	 	| 	GPIO_X		|
 *
 *
 * @section changelog Changelog
 *
 * |   Date	    | Description                                    |
 * |:----------:|:-----------------------------------------------|
 * | 20/08/2025 | Document creation		                         |
 *
 * @author Angeles Perez (maria.perez@ingenieria.uner.edu.ar)
 *
 */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"

/*==================[macros and definitions]=================================*/
#define ON 1
#define OFF 0
#define TOGGLE 2

struct leds {
    uint8_t mode;      // ON, OFF, TOGGLE
    uint8_t n_led;     // indica el número de led a controlar
    uint8_t n_ciclos;  // cantidad de ciclos de encendido/apagado
    uint16_t periodo;  // tiempo de cada ciclo en ms
} my_leds;

void ControlLED(struct leds *config) {
    uint8_t i = 0;
    uint8_t j = 0;

    if (config->mode == ON) {
        if (config->n_led == LED_1) {
            LedOn(LED_1);
        } else if (config->n_led == LED_2) {
            LedOn(LED_2);
        } else if (config->n_led == LED_3) {
            LedOn(LED_3);
        }
    } 
    else if (config->mode == OFF) {
        if (config->n_led == LED_1) {
            LedOff(LED_1);
        } else if (config->n_led == LED_2) {
            LedOff(LED_2);
        } else if (config->n_led == LED_3) {
            LedOff(LED_3);
        }
    } 
    else if (config->mode == TOGGLE) {
        while (i < config->n_ciclos) {
            if (config->n_led == LED_1) {
                LedToggle(LED_1);
            } else if (config->n_led == LED_2) {
                LedToggle(LED_2);
            } else if (config->n_led == LED_3) {
                LedToggle(LED_3);
            }

            i++;

            j = 0;
            while (j < 1) {  
                j++;
                vTaskDelay(100/portTICK_PERIOD_MS); // 500 ms
            }
        }
    } 
    else {
        printf("Modo inválido\n");
    }
}

void app_main(void) {
    // Configuración de ejemplo pedida en el ejercicio
    my_leds.mode = TOGGLE;   // modo Toggle
    my_leds.n_led = LED_1;   // LED1
    my_leds.n_ciclos = 10;   // 10 ciclos
    my_leds.periodo = 500;   // 500 ms

    LedsInit();
    ControlLED(&my_leds);

    printf("FIN\n");
}