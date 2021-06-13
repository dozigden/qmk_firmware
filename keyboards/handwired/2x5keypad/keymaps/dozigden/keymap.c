#include QMK_KEYBOARD_H

#define WIN_TAB LGUI(KC_TAB)
#define WIN_LOCK LGUI(KC_L)

enum layers {
  NORMAL_LAYER = 0,
  MEDIA_LAYER
};

float on_sound[][2] = SONG(AUDIO_ON_SOUND);
float off_sound[][2] = SONG(AUDIO_OFF_SOUND);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [NORMAL_LAYER] = LAYOUT(KC_MUTE, KC_VOLU, KC_F13, KC_F14, KC_F15, 
			              TO(1), KC_VOLD, KC_F16, KC_F17, KC_F18),

    [MEDIA_LAYER]  = LAYOUT(KC_TRNS, KC_CALC, KC_MPRV, KC_MNXT, KC_VOLU, 
			              TO(0), KC_TRNS, KC_MSTP, KC_MPLY, KC_VOLD)
};


void matrix_init_user(void)
{

}


layer_state_t layer_state_set_user(layer_state_t state)
{
    turn_off_leds();

    switch (get_highest_layer(state))
    {
    case NORMAL_LAYER:
        PLAY_SONG(off_sound);
	break;

    case MEDIA_LAYER:
        PLAY_SONG(on_sound);
	    turn_on_led(RED_LED);
	break;
	}
    return state;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        switch(biton32(layer_state)) {
            case NORMAL_LAYER:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            case MEDIA_LAYER:
                if (clockwise) {
                    SEND_STRING(SS_LCTL("y"));
                } else {
                    SEND_STRING(SS_LCTL("z"));
                }
                break;
        }
    } 
    return true;
}
