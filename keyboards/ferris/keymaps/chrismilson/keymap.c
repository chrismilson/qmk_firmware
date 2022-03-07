#include QMK_KEYBOARD_H

// Transparent Layer
// [n] = LAYOUT(
//     _______,          _______,          _______,          _______,          _______,
//     _______,          _______,          _______,          _______,          _______,

//     _______,          _______,          _______,          _______,          _______,
//     _______,          _______,          _______,          _______,          _______,

//     _______,          _______,          _______,          _______,          _______,
//     _______,          _______,          _______,          _______,          _______,

//     _______,          _______,
//     _______,          _______
// )

enum layers {
    // The base layer for most english typing
    _QWERTY,
    // Keys that should be available on all higher layers
    _COMMON,
    // Special characters
    _SPECIAL,
    // Arrow key layer WIP
    _ARROWS,
    // Numpad on right hand
    // Media keys on the left hand
    _NUMBERS,
    // Keys often required while using numbers on the right hand - plus, minus, etc.
    // Function keys on the left hand
    _NUMBERS_AUX,
};

enum {
    TO_SPECIAL = SAFE_RANGE,
    TO_NUMBERS,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TO_SPECIAL:
            if (record->event.pressed) {
                layer_move(_SPECIAL);
                layer_on(_COMMON);
            }
            return false;
        case TO_NUMBERS:
            if (record->event.pressed) {
                layer_move(_NUMBERS);
                layer_on(_COMMON);
            }
            return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT(
        KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,
        KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,

        KC_A,           KC_S,           LALT_T(KC_D),   LGUI_T(KC_F),   KC_G,
        KC_H,           LGUI_T(KC_J),   LALT_T(KC_K),   KC_L,           KC_SCLN,

        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,
        KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,

        KC_LCTL,        KC_SPC,
        TO_SPECIAL,     KC_LSFT
    ),

    [_COMMON] = LAYOUT(
        KC_GESC,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        KC_BSPC,

        KC_TAB,         _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        KC_ENT,

        KC_BTN1,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        KC_NO,

        _______,        TO(_QWERTY),
        _______,        _______
    ),

	[_SPECIAL] = LAYOUT(
        _______,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,
        KC_CIRC,        KC_AMPR,        KC_ASTR,        _______,        _______,

        _______,        KC_EXLM,        KC_EQL,         KC_MINS,        KC_QUOT,
        KC_GRV,         KC_BSLS,        KC_LCBR,        KC_RCBR,        _______,

        _______,        _______,        KC_PLUS,        KC_UNDS,        KC_DQUO,
        KC_LPRN,        KC_RPRN,        KC_LBRC,        KC_RBRC,        TG(_ARROWS),

        _______,        _______,
        TO_NUMBERS,     _______
    ),

    [_ARROWS] = LAYOUT(
        _______,        KC_WH_D,        KC_MS_U,        KC_WH_U,        RESET,
        _______,        _______,        _______,        _______,        _______,

        _______,        KC_MS_L,        KC_MS_D,        KC_MS_R,        _______,
        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RGHT,        _______,

        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,

        _______,        _______,
        _______,        _______
    ),

    [_NUMBERS] = LAYOUT(
        _______,        KC_MSTP,        KC_MPRV,        KC_MNXT,        _______,
        KC_UNDS,        KC_7,           KC_8,           KC_9,           KC_BSPC,

        _______,        KC_VOLD,        KC_VOLU,        KC_MPLY,        _______,
        KC_SPC,         KC_4,           KC_5,           KC_6,           KC_ENT,

        _______,        KC_BRID,        KC_BRIU,        KC_MUTE,        _______,
        KC_0,           KC_1,           KC_2,           KC_3,           OSL(_NUMBERS_AUX),

        _______,        _______,
        TO_SPECIAL,     _______
    ),

    [_NUMBERS_AUX] = LAYOUT(
        _______,        KC_F7,          KC_F8,          KC_F9,          KC_F12,
        _______,        _______,        _______,        _______,        _______,

        _______,        KC_F4,          KC_F5,          KC_F6,          KC_F11,
        _______,        KC_PLUS,        KC_ASTR,        KC_DOT,         _______,

        _______,        KC_F1,          KC_F2,          KC_F3,          KC_F10,
        _______,        KC_MINS,        KC_SLSH,        KC_COMM,        KC_NO,

        _______,        _______,
        _______,        _______
    )
};
