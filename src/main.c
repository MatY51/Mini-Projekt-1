#include "main.h"
#include "daughterboard.h"
#include "milis.h"
#include "stm8s.h"

#include "delay.h"
#include <stdio.h>


#define LED1_PORT GPIOG
#define LED1_PIN GPIO_PIN_4

#define LED2_PORT GPIOG
#define LED2_PIN GPIO_PIN_7

#define LED3_PORT GPIOG
#define LED3_PIN GPIO_PIN_5

#define LED4_PORT GPIOG
#define LED4_PIN GPIO_PIN_6

#define LED5_PORT GPIOB
#define LED5_PIN GPIO_PIN_2


void setup(void) {
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovani MCU na 16MHz

    GPIO_Init(LED4_PORT, LED4_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(LED5_PORT, LED5_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(LED3_PORT, LED3_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(LED1_PORT, LED1_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(LED2_PORT, LED2_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);

    init_milis();

}

int main(void) {

    uint32_t time = 0;

    uint8_t minule;

    uint16_t minulee = 1;

    setup();
    while (1) {
        if (milis() - time > 33) {
            time = milis();

            if (PUSH(BTN) && minule == 0) {
                if (minulee == 1) {
                    REVERSE(LED1);
                    minulee = 2;
                } else if (minulee == 2) {
                    REVERSE(LED4);
                    REVERSE(LED1);
                    minulee = 3;
                } else if (minulee == 3) {
                    REVERSE(LED2);
                    REVERSE(LED4);
                    minulee = 4;
                } else if (minulee == 4) {
                    REVERSE(LED3);
                    REVERSE(LED2);
                    minulee = 5;
                } else if (minulee == 5) {
                    REVERSE(LED5);
                    REVERSE(LED3);
                    minulee = 6;
                } else if (minulee == 6) {
                    REVERSE(LED5);
                    minulee = 1;
                }
                minule = 1;
            }

            if (!PUSH(BTN)) {
                minule = 0;
            }
        }    
}
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"