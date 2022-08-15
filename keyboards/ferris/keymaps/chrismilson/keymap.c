#include QMK_KEYBOARD_H


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

    // EPHEMERAL LAYERS
    // The following layers are not in the same spirit as the rest of the board,
    // and thus are more difficult to access in everyday use.
    // The EPHEMERAL_HOME layer can be reached from the normal layers, and the
    // other ephemeral layers can be reached from there.
    _EPHEMERAL_HOME,
    // A layer to allow the smooth play of sudoku with a single (Either) hand.
    _SUDOKU,
    _SUDOKU_AUX,
    // A layer for computer games that use the left hand on the keyboard.
    _WASD,
    _WASD_AUX,
};

#define TO_BASE TO(_QWERTY)
#define TO_SPEC TO(_SPECIAL)
#define TO_NUMS TO(_NUMBERS)
#define TG_ARRW TG(_ARROWS)
#define EP_HOME TO(_EPHEMERAL_HOME)
#define OS_NUMX OSL(_NUMBERS_AUX)

#define CTL_SLS LCTL_T(KC_SLSH)
#define CTL_Z LCTL_T(KC_Z)
#define ALT_X LALT_T(KC_X)
#define ALT_DOT LALT_T(KC_DOT)

#define KC_CLN 

// The keys in the middle of the board stay in the same orientation, but the
// inside and outside columns are mirrored.
#define MATCHING_LAYOUT( \
    L01, L02, L03, L04, L05, \
    L06, L07, L08, L09, L10, \
    L11, L12, L13, L14, L15, \
                   L16, L17 \
) LAYOUT( \
    L01, L02, L03, L04, L05, L05, L02, L03, L04, L01, \
    L06, L07, L08, L09, L10, L10, L07, L08, L09, L06, \
    L11, L12, L13, L14, L15, L15, L12, L13, L14, L11, \
                   L16, L17, L17, L16 \
)

// Defines a layout for auxiliary layers; the layout will be common on the
// different layers, so it is better to only define it once.
#define LAYOUT_SUPER( \
    L01, L02, L03, L04, L05, R01, R02, R03, R04, R05, \
    L06, L07, L08, L09, L10, R06, R07, R08, R09, R10, \
    L11, L12, L13, L14, L15, R11, R12, R13, R14, R15, \
                   L16, L17, R16, R17 \
) LAYOUT( \
    KC_ESC,  L02, L03, L04, L05, R01, R02, R03, R04, KC_BSPC, \
    KC_TAB,  L07, L08, L09, L10, R06, R07, R08, R09, KC_ENT, \
    KC_BTN1, L12, L13, L14, L15, R11, R12, R13, R14, R15, \
               KC_LCTL, TO_BASE, R16, KC_LSFT \
)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        CTL_Z,   ALT_X,   KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, ALT_DOT, CTL_SLS,
                                   KC_LGUI, KC_SPC,    TO_SPEC, KC_LSFT
    ),

	[_SPECIAL] = LAYOUT_SUPER(
        _______, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_TILD, _______,
        _______, KC_EXLM, KC_EQL,  KC_MINS, KC_QUOT,   KC_GRV,  KC_BSLS, KC_LCBR, KC_RCBR, _______,
        _______, _______, KC_PLUS, KC_UNDS, KC_DQUO,   KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, TG_ARRW,
                                   _______, _______,   TO_NUMS, _______
    ),

    [_ARROWS] = LAYOUT_SUPER(
        _______, KC_WH_D, KC_MS_U, KC_WH_U, RESET,     _______, _______, _______, _______, _______,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
        _______, KC_BTN2, _______, _______, EP_HOME,   _______, _______, _______, _______, _______,
                                   _______, _______,   _______, _______
    ),

    [_NUMBERS] = LAYOUT_SUPER(
        _______, KC_MSTP, KC_MPRV, KC_MNXT, _______,   KC_UNDS, KC_7,    KC_8,    KC_9,    KC_BSPC,
        _______, KC_VOLD, KC_VOLU, KC_MPLY, _______,   KC_SPC,  KC_4,    KC_5,    KC_6,    KC_ENT,
        _______, KC_BRID, KC_BRIU, KC_MUTE, _______,   KC_0,    KC_1,    KC_2,    KC_3,    OS_NUMX,
                                   _______, _______,   TO_SPEC, _______
    ),

    [_NUMBERS_AUX] = LAYOUT_SUPER(
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F12,    _______, _______, _______, _______, _______,
        _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,    _______, KC_PLUS, KC_ASTR, KC_DOT,  _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F10,    KC_COLN, KC_MINS, KC_SLSH, KC_COMM, KC_NO,
                                   _______, _______,   _______, _______
    ),

    [_EPHEMERAL_HOME] = LAYOUT(
        TO(_SUDOKU),    TO(_WASD),      _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,

        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,

        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,

        _______,        TO(_QWERTY),
        TO_SPECIAL,     _______
    ),

    [_SUDOKU] = MATCHING_LAYOUT(
        KC_BSPC,        KC_7,           KC_8,           KC_9,           TO(_QWERTY),
        TO(_QWERTY),    KC_4,           KC_5,           KC_6,           KC_SPC,
        TO(_QWERTY),    KC_1,           KC_2,           KC_3,           _______,
        KC_LSFT,        KC_LCTL
    ),

    [_WASD] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,      KC_H,    KC_J,    LALT_K,  KC_L,    KC_SCLN,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          MO(_WASD_AUX),    KC_SPC,    TO_SPEC, KC_LSFT
    ),

    [_WASD_AUX] = LAYOUT(
        KC_ESC,  KC_7,    KC_8,    KC_9,    KC_WH_U,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_LSFT, KC_4,    KC_5,    KC_6,    KC_WH_D,   KC_H,    KC_J,    LALT_K,  KC_L,    KC_SCLN,
        KC_LCTL, KC_1,    KC_2,    KC_3,    KC_V,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                   _______, KC_SPC,    TO_SPEC, KC_LSFT
    )
};
