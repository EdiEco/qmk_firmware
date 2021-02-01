RGB_MATRIX_EFFECT(LAYACTIVE)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include <stdint.h>
#include "color.h"

static HSV LAYACTIVE_math(HSV hsv, uint16_t offset) {
    hsv.h += qadd8(0, offset);
    //hsv.v += qadd8(1, offset);
    return hsv;
}

bool LAYACTIVE(effect_params_t* params) {
    return effect_runner_reactive(params, &LAYACTIVE_math);
}


#endif
