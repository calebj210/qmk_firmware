/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

bool capsState  = false;

float onSong[][2]   = SONG(AUDIO_ON_SOUND);
float offSong[][2]  = SONG(AUDIO_OFF_SOUND);

/**
 * Define initialization code
 */
void keyboard_post_init_user(void) {
    audio_set_tempo(75);
    audio_startup();
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl | Ctrl | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_planck_grid(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
        KC_LCTL, KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    
    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |  <   |   >  |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |RECMAC|      |      |      |      |             |      |      | PGDN | PGUP |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_planck_grid(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_DEL,
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_EQL,     KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,    KC_LT,      KC_GT,   _______, _______,
        DM_REC1, _______, _______, _______, _______, _______, _______, _______,    _______,    KC_PGDN, KC_PGUP, _______
    ),
    
    /* Raise
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   +  |   [  |   ]  |  \   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | Mute |  <   |   >  |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |MACRO |      |      |      |      |             |      |      | Vol- | Vol+ |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_planck_grid(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE, KC_LT,   KC_GT,   _______, _______,
        DM_PLY1, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, _______
    ),
    
    /* Adjust (Lower + Raise)
     *                      v------------------------RGB CONTROL--------------------v
     * ,-----------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | CAPS |MUMODE|MU TOG|AU TOG|      |RGBTOG|RGBMO+| HUE+ | SAT+ |BRGTH+|EFECT+|RESET |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |Voice-|Voice+|      |      |      |RGBMO-| HUE- | SAT- |BRGTH-|EFECT-|DEBUG |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_planck_grid(
        _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,
        KC_CAPS, MU_MOD,  MU_TOG,  AU_TOG,  _______, RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RESET,
        _______, MUV_DE,  MUV_IN,  _______, _______, _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, DEBUG,
        _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPS:
            if (record->event.pressed) {
                if (capsState) {
                    capsState = false;
                    PLAY_SONG(offSong);
                } else {
                    capsState = true;
                    PLAY_SONG(onSong);
                }
            }
            return true;
        default:
            return true;
    }
}

void dynamic_macro_record_start_user(void) {
    PLAY_SONG(onSong);
}

void dynamic_macro_record_end_user(int8_t direction) {
    PLAY_SONG(offSong);
}
