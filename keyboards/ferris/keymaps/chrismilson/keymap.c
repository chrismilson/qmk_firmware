#include QMK_KEYBOARD_H

// Transparent Layer
// [n] = LAYOUT(
//     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
//     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,

//     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
//     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,

//     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
//     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,

//     KC_TRNS,        KC_TRNS,
//     KC_TRNS,        KC_TRNS
// )

enum layers {
    _QWERTY,
    _COLEMAK_DH,
    _SPECIAL,
    _KEYBOARD_SETTINGS,
    _AV_NUMPAD,
    _AV_NUMPAD_AUX,
    _NAV,
    _NAV_AUX
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT(
        KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,
        KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,

        KC_A,           KC_S,           LALT_T(KC_D),   LGUI_T(KC_F),   KC_G,
        KC_H,           LGUI_T(KC_J),   LALT_T(KC_K),   KC_L,           KC_SCLN,

        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,
        KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,

        KC_LCTL,        KC_SPC,
        TO(_SPECIAL),   KC_LSFT
    ),
    [_COLEMAK_DH] = LAYOUT(
        KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,
        KC_J,           KC_L,           KC_U,           KC_Y,           KC_SCLN,

        KC_A,           KC_R,           LALT_T(KC_S),   LGUI_T(KC_T),   KC_G,
        KC_M,           LGUI_T(KC_N),   LALT_T(KC_E),   KC_I,           KC_O,

        KC_Z,           KC_X,           KC_C,           KC_D,           KC_V,
        KC_K,           KC_H,           KC_COMM,        KC_DOT,         KC_SLSH,

        KC_LCTL,        KC_SPC,
        TO(_SPECIAL),   KC_LSFT
    ),
	[_SPECIAL] = LAYOUT(
        KC_GESC,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,
        KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_SCLN,        KC_BSPC,

        KC_TAB,         KC_EXLM,        KC_EQL,         KC_MINS,         KC_QUOT,
        KC_GRV,         KC_LCBR,        KC_RCBR,        KC_BSLS,        KC_ENT,

        RESET,          KC_JYEN,        KC_PLUS,        KC_UNDS,        KC_DQUO,
        KC_LPRN,        KC_LBRC,        KC_RBRC,        KC_RPRN,        OSL(_KEYBOARD_SETTINGS),

        KC_TRNS,        TG(_SPECIAL),
        TO(_AV_NUMPAD), KC_TRNS
    ),
    [_KEYBOARD_SETTINGS] = LAYOUT(
        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,

        KC_TRNS,        KC_TRNS,        LCG_SWP,        DF(_COLEMAK_DH),KC_TRNS,
        KC_TRNS,        DF(_QWERTY),    LCG_SWP,        KC_TRNS,        KC_TRNS,

        RESET,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,

        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS
    ),
    [_AV_NUMPAD] = LAYOUT(
        KC_GESC,        KC_MSTP,        KC_MPRV,        KC_MNXT,        KC_TRNS,
        KC_TRNS,        KC_7,           KC_8,           KC_9,           KC_BSPC,

        KC_TAB,         KC_VOLD,        KC_VOLU,        KC_MPLY,        KC_TRNS,
        KC_PEQL,        KC_4,           KC_5,           KC_6,           KC_ENT,

        RESET,          KC_MUTE,        KC_BRID,        KC_BRIU,        KC_TRNS,
        KC_0,           KC_1,           KC_2,           KC_3,           OSL(_AV_NUMPAD_AUX),

        KC_TRNS,        TG(_AV_NUMPAD),
        TO(_NAV),       KC_TRNS
    ),
    [_AV_NUMPAD_AUX] = LAYOUT(
        KC_TRNS,        KC_F7,          KC_F8,          KC_F9,          KC_F12,
        KC_TRNS,        KC_MINS,        KC_SLSH,        KC_COMM,        KC_TRNS,

        KC_TRNS,        KC_F4,          KC_F5,          KC_F6,          KC_F11,
        KC_TRNS,        KC_PLUS,        KC_ASTR,        KC_DOT,         KC_TRNS,

        KC_TRNS,        KC_F1,          KC_F2,          KC_F3,          KC_F10,
        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_NO,

        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS
    ),
    // Navigation Layer
    [_NAV] = LAYOUT(
        KC_GESC,        KC_BTN2,        KC_MS_U,        KC_BTN1,        KC_TRNS,
        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RGHT,        KC_BSPC,

        KC_TAB,         KC_MS_L,        KC_MS_D,        KC_MS_R,        KC_TRNS,
        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RGHT,        KC_ENT,

        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        MO(_NAV_AUX),
        MO(_NAV_AUX)    ,KC_ACL0,       KC_ACL1,        KC_ACL2,        KC_TRNS,

        KC_TRNS,        TG(_NAV),
        TO(_SPECIAL),   KC_TRNS
    ),
    [_NAV_AUX] = LAYOUT(
        KC_TRNS,        KC_TRNS,        KC_WH_U,        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,

        KC_TRNS,        KC_WH_L,        KC_WH_D,        KC_WH_R,        KC_TRNS,
        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,

        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,

        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS
    )
};
