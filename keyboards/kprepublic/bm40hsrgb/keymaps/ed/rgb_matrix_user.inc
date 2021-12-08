RGB_MATRIX_EFFECT(LAYACTIVE)
//RGB_MATRIX_EFFECT(EDBREATH)
//RGB_MATRIX_EFFECT(CYCLE_VAL_UP_DOWN)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include <stdint.h>
#include "color.h"
#include "print.h"

static HSV LAYACTIVE_math(HSV hsv, uint16_t offset) {
    hsv.h += qadd8(0, offset);
    //hsv.v += qadd8(1, offset);
    return hsv;
}

bool LAYACTIVE(effect_params_t* params) {
    return effect_runner_reactive(params, &LAYACTIVE_math);
}
/*
static HSV CYCLE_VAL_UP_DOWN_math(HSV hsv, uint8_t i, uint8_t time) {
    hsv.v = scale8(abs8(sin8(g_led_config.point[i].y - time) - 128) * 2, 100 );
    return hsv;
}

bool CYCLE_VAL_UP_DOWN(effect_params_t* params) { return effect_runner_i(params, &CYCLE_VAL_UP_DOWN_math); }


static uint16_t f_timer = 0;
static bool animation_active;
static uint8_t count = 0;

bool EDBREATH(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

   // if (timer > g_rgb_timer) {
   //     return false;
  //  }

    if (params->init) {
        f_timer = timer_read();
        animation_active = true;
        count = 0;
    }


    //if (params->iter == 0) {
   //    animation_active = timer_elapsed(f_timer) >= 5000;//RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS;
    //    if (animation_active) {
   //         //f_timer = timer_read();
   //c     }
  //  }



    if(!animation_active) {
        animation_active = timer_elapsed(f_timer) > 60000;
    }

    if (animation_active) {
        HSV      hsv  = rgb_matrix_config.hsv;
        //uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
        hsv.v         = scale8(abs8(sin8(++count/2) - 128) * 2, hsv.v/ 2 );
        RGB rgb       = rgb_matrix_hsv_to_rgb(hsv);
        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_TEST_LED_FLAGS();
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }

        if(count == 255) {
            animation_active = false;
            f_timer = timer_read();
            count = 0;
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}
*/
#endif
