

#include "color.h"
#include "rgb_matrix.h"

#ifdef ED_LAYER_HELP
const uint8_t PROGMEM colormap[][MATRIX_ROWS][MATRIX_COLS] =
{
[_QWERTY] = LAYOUT_planck_mit(
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 ,
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0
),
[_LOWER] = LAYOUT_planck_mit(
    0,   0,    0,    0,    0,    0,    0,    0,    0,  170,  170,    1,
    0,   1,    1,    1,    1,    1,    1,   50,   50,  170,  170,    0,
    0,   1,    1,    1,    1,    1,    1,    0,    0,    0,    0,   20,
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0
),
[_RAISE] = LAYOUT_planck_mit(
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   0,    0,    0,    0,    0,    0,    0,    0,  170,  170,    0,
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 ,
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0
),
[_ENGINEERING] = LAYOUT_planck_mit(
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 ,
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0
),
[_ADJUST] = LAYOUT_planck_mit(
    0, 255,  255,  255,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 ,
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0
)
};

void rgb_matrix_indicators_user(void) {
    int c = 0;
    uint8_t layer = biton32(layer_state);
  if(rgb_matrix_get_mode() != RGB_MATRIX_CUSTOM_LAYACTIVE) return;

  switch (layer) {
      case 1:
      case 4:
        for (int i = 0; i < MATRIX_ROWS; i++) {
          for (int j = 0; j < MATRIX_COLS; j++) {
              uint8_t color = pgm_read_byte(&colormap[layer][i][j]);
              if(color > 0)
              {
                  if(color == 255)
                  {
                     // RGB code_rgb;
                      keypos_t key; // = {i, j};
                      key.row = i;
                      key.col = j;
                      uint16_t code = keymap_key_to_keycode(layer, key);
                      dprintf("%d %d %d %d\n", layer, i, j, code);
                      switch (code)
                      {
                          case RESET: rgb_matrix_set_color(c, RGB_RED); break;
                          case DEBUG: rgb_matrix_set_color(c, RGB_BLUE); break;
                          case RGB_TOG: rgb_matrix_set_color(c, RGB_WHITE); break;
                      }
                  }
                  else
                  {
                    HSV hsv = {color, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v};
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(c, rgb.r, rgb.g, rgb.b);
                  }
              }
              c++;
          }
        }
        break;
      default:
        break;
  }
}
#endif


#ifdef RGBLED_NUM
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 4, HSV_RED},       // Light 4 LEDs, starting with LED 6
    {12, 4, HSV_RED}       // Light 4 LEDs, starting with LED 12
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 2, HSV_CYAN}
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 2, HSV_PURPLE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_layer1_layer,    // Overrides caps lock layer
    my_layer2_layer     // Overrides other layers
);

void keyboard_post_init_user(void)
{
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

void set_light(layer_state_t state) // layer_state_set_user
{
    switch (get_highest_layer(state)) {
        case 0:
            rgblight_blink_layer(0, 500);
            break;
        case 1:
            rgblight_blink_layer(1, 500);
            break;
        case 2:
            rgblight_blink_layer(2, 500);
            break;
    }
}
#endif
