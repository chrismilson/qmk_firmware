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

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_TAP,
    TD_HOLD,
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

#define TC_MBTN TC_MOUSE_BUTTON_TAP_LEFT_HOLD_RIGHT
// Tap dance enums
enum {
    TC_MOUSE_BUTTON_TAP_LEFT_HOLD_RIGHT
};

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

        TC_MBTN,        _______,        _______,        _______,        _______,
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
        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,

        _______,        _______,        _______,        RESET,          _______,
        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RGHT,        _______,

        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,

        _______,        _______,
        _______,        _______
    ),

    [_NUMBERS] = LAYOUT(
        _______,        KC_MSTP,        KC_MPRV,        KC_MNXT,        _______,
        _______,        KC_7,           KC_8,           KC_9,           KC_BSPC,

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

td_state_t current_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_HOLD;
    }

    return TD_UNKNOWN;
}

static td_tap_t mbtn_tap = {
    .is_press_action = true,
    .state = TD_NONE
};

void mbtn_finished(qk_tap_dance_state_t *state, void *user_data) {
    mbtn_tap.state = current_dance(state);

    switch (mbtn_tap.state) {
        case TD_TAP: register_code(KC_BTN1); break;
        case TD_HOLD: register_code(KC_BTN2); break;
        default: break;
    }
}

void mbtn_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (mbtn_tap.state) {
        case TD_TAP: unregister_code(KC_BTN1); break;
        case TD_HOLD: unregister_code(KC_BTN2); break;
        default: break;
    }
    mbtn_tap.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TC_MBTN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mbtn_finished, mbtn_reset)
};
