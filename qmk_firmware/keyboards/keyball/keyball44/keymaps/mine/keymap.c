/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

/**************************************************************
 * Define parameters.
 **************************************************************/
/** Define layer numbers */
enum layer_number {
    /** Layer number for Qwerty */
    _QWERTY = 0,
    /** Layer number for Matogi */
    _MATOGI,
    /** Layer number for Matogi-Shift */
    _MATOGI_SHIFT,
    /** Layer number for Number and Function keys */
    _NUMBER_FUNCTION,
    /** Layer number for Sing keys */
    _SIGN,
    /** Layer number for Arrow and Mouse keys */
    _ARROW_MOUSE
};

/** Define custom keycodes (Max 32 keys) */
enum custom_keycodes {
    /** Change language to EN and layer to Qwerty */
    MO_QWERTY = QK_USER_0,
    /** Change language to JP and layer to MATO */
    MO_MATO,
    /** CTRL and Change language */
    CTL_LANG,
    /** CTRL and Change language to EN and layer to Qwerty */
    CTL_QWERTY,
    /** CTRL and Change language to JP and layer to Matogi */
    CTL_MATO,
    /** Tap: Space and Hold: Sings */
    SIGN_SPC,
    /** Tap: Minus and Hold: Arrow and Mouse */
    MOUSE_MINS,
    /** Tap: Enter and Hold: Number and Function */
    NUM_ENT,
    /** Tap: Enter and Hold: Matogi-Shift */
    MT_S_ENT,
    /** Send string "ん" */
    SEND_NN,
    /** tap "y" + "a" */
    KC_YA,
    /** tap "y" + "u" */
    KC_YU,
    /** tap "y" + "o" */
    KC_YO
};

/** Key state for custom keycodes */
enum key_state {
    /** key is released */
    _RELEASED = 0,
    /** key is pressed */
    _PRESSED,
    /** key is holden */
    _HOLDEN
};

/** Key state for Ctrl/Lang keycode */
enum key_state ctrl_lang_state = _RELEASED;
/** Key state for Ctrl/Qwerty keycode */
enum key_state ctrl_qwerty_state = _RELEASED;
/** Key state for Ctrl/Matogi keycode */
enum key_state ctrl_mato_state = _RELEASED;

/** Sign / Space key */
#define SIGN_SPC LT(_SIGN, KC_SPC)
/** Arrow and Mouse / Minus key */
#define MOUSE_MINS LT(_ARROW_MOUSE, KC_MINS)
/** Number and Function / Enter key */
#define NUM_ENT LT(_NUMBER_FUNCTION, KC_ENT)
/** Matogi-Shift / Enter key */
#define MT_SFT_ENT LT(_MATOGI_SHIFT, KC_ENT)
/** Mod shift and space */
#define SPC_SFT MT(MOD_LSFT, KC_SPC)
/** Z key and Left shift */
#define SFT_Z MT(MOD_LSFT, KC_Z)
/** Slash key and Left shift */
#define SFT_SLSH MT(MOD_LSFT, KC_SLSH)
/** Quotation key and Left shift */
#define SFT_QUOT MT(MOD_LSFT, KC_QUOT)
/** Tilde key: '~' */
#define TILDE LSFT(KC_GRV)
/** Exclamation key: '!' */
#define EXCLAM LSFT(KC_1)
/** At key: '@' */
#define AT LSFT(KC_2)
/** Hash key: '#' */
#define HASH LSFT(KC_3)
/** Dollar key: '$' */
#define DOLLAR LSFT(KC_4)
/** Percent key: '%' */
#define PERCENT LSFT(KC_5)
/** Hat key: '^' */
#define HAT LSFT(KC_6)
/** Amapsand key: '&' */
#define AND LSFT(KC_7)
/** Star key: '*' */
#define STAR LSFT(KC_8)
/** Left paren key: '(' */
#define LPAREN LSFT(KC_9)
/** Right paren key: ')' */
#define RPAREN LSFT(KC_0)
/** Left angle bracket key: '<' */
#define LANGBRC LSFT(KC_COMM)
/** Right angle bracket key: '>' */
#define RANGBRC LSFT(KC_DOT)
/** Underscore key: '_' */
#define UNDRSCR LSFT(KC_MINS)
/** Plus key: '+' */
#define PLUS LSFT(KC_EQL)
/** Question key: '?' */
#define QUEST LSFT(KC_SLSH)
/** Pipe key: '|' */
#define PIPE LSFT(KC_BSLS)
/** Double quotation key: '"' */
#define DQUOT LSFT(KC_QUOT)
/** Colon key: ':' */
#define COLON LSFT(KC_SCLN)
/** Left curly bracket key: '{' */
#define LCRLYBRC LSFT(KC_LBRC)
/** Right curly bracket key: '}' */
#define RCRLYBRC LSFT(KC_RBRC)
/** Undo: ctrl + Z */
#define UNDO LCTL(KC_Z)
/** Cut: ctrl + X */
#define CUT LCTL(KC_X)
/** Copy: ctrl + C */
#define COPY LCTL(KC_C)
/** Paste: ctrl + V */
#define PASTE LCTL(KC_V)
/** Show windows: win + tab */
#define CNG_WIN LGUI(KC_TAB)
/** Next page (tab): ctrl + tab */
#define NEXT_PG LCTL(KC_TAB)
/** Previous page (tab): ctrl + shift + tab */
#define PREV_PG LSFT(LCTL(KC_TAB))
/** Reverse tab: shift + tab */
#define SFTED_TAB LSFT(KC_TAB)

/*************************************************************
 * Settings for keymaps, keycodes and layer states.
 *************************************************************/
// clang-format off
/** Custom keymap settings */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Qwerty (default)
    [_QWERTY] = LAYOUT_right_ball(
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        KC_ESC    , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T      ,                                         KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , KC_DEL    ,
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        KC_TAB    , KC_A      , KC_S      , KC_D      , KC_F      , KC_G      ,                                         KC_H      , KC_J      , KC_K      , KC_L      , KC_SCLN   , KC_BSLS   ,
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        KC_LSFT   , SFT_Z     , KC_X      , KC_C      , KC_V      , KC_B      ,                                         KC_N      , KC_M      , KC_COMM   , KC_DOT    , SFT_QUOT  , SFT_SLSH  ,
    //+-----------+-----------+-----------+----+------+----+-----------+------+----+-----------+     +-----------+----+------+----+-----------+-----------+-----------+-----------+-----------+
                                KC_LALT   , KC_LGUI   ,      CTL_LANG  , SIGN_SPC  , MOUSE_MINS,       KC_BSPC   , NUM_ENT   ,                                          KC_CAPS
    //                        +-----------+-----------+    +-----------+-----------+-----------+     +-----------+-----------+                                        +-----------+
    ),
    // Matogi
    [_MATOGI] = LAYOUT_right_ball(
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        KC_ESC    , KC_L      , KC_W      , KC_K      , KC_R      , KC_F      ,                                         XXXXXXX   , KC_I      , KC_E      , KC_Y      , KC_MINS   , KC_DEL    ,
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        KC_TAB    , KC_M      , KC_S      , KC_T      , KC_N      , KC_H      ,                                         XXXXXXX   , KC_A      , KC_U      , KC_O      , KC_COMM   , XXXXXXX   ,
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        KC_LSFT   , UNDO      , CUT       , COPY      , PASTE     , XXXXXXX   ,                                         XXXXXXX   , KC_YA     , KC_YU     , KC_YO     , XXXXXXX   , KC_RSFT   ,
    //+-----------+-----------+-----------+----+------+----+-----------+------+----+-----------+     +-----------+----+------+----+-----------+-----------+-----------+-----------+-----------+
                                KC_LALT   , KC_LGUI   ,      CTL_LANG  , SIGN_SPC  , MOUSE_MINS,       KC_BSPC   , MT_SFT_ENT,                                          KC_CAPS
    //                        +-----------+-----------+    +-----------+-----------+-----------+     +-----------+-----------+                                        +-----------+
    ),
    // Matogi-Shift
    [_MATOGI_SHIFT] = LAYOUT_right_ball(
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        _______   , KC_X      , KC_J      , KC_G      , KC_C      , KC_P      ,                                         _______   , _______   , _______   , SEND_NN   , KC_EQL    , _______   ,
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        _______   , KC_Q      , KC_Z      , KC_D      , KC_V      , KC_B      ,                                         _______   , _______   , _______   , _______   , KC_DOT    , _______   ,
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        _______   , _______   , _______   , _______   , _______   , _______   ,                                         _______   , _______   , _______   , _______   , _______   , _______   ,
    //+-----------+-----------+-----------+----+------+----+-----------+------+----+-----------+     +-----------+----+------+----+-----------+-----------+-----------+-----------+-----------+
                                _______   , _______   ,      CTL_QWERTY, _______   , SPC_SFT   ,       _______   , _______   ,                                          _______
    //                        +-----------+-----------+    +-----------+-----------+-----------+     +-----------+-----------+                                        +-----------+
    ),
    // Number and Function keys
    [_NUMBER_FUNCTION] = LAYOUT_right_ball(
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        _______   , KC_1      , KC_2      , KC_3      , KC_4      , KC_5      ,                                         KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , _______   ,
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        _______   , KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     ,                                         COLON     , KC_4      , KC_5      , KC_6      , KC_COMM   , XXXXXXX   ,
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        _______   , KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    ,                                         KC_0      , KC_1      , KC_2      , KC_3      , KC_DOT    , KC_RSFT   ,
    //+-----------+-----------+-----------+----+------+----+-----------+------+----+-----------+     +-----------+----+------+----+-----------+-----------+-----------+-----------+-----------+
                                _______   , _______   ,      CTL_MATO  , _______   , _______   ,       _______   , _______   ,                                          XXXXXXX
    //                        +-----------+-----------+    +-----------+-----------+-----------+     +-----------+-----------+                                        +-----------+
    ),
    // Sing keys
    [_SIGN] = LAYOUT_right_ball(
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        KC_GRV    , EXCLAM    , AT        , HASH      , DOLLAR    , PERCENT   ,                                         HAT       , AND       , STAR      , LPAREN    , RPAREN    , _______   ,
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        TILDE     , KC_COMM   , KC_DOT    , KC_MINS   , KC_EQL    , KC_SLSH   ,                                         KC_BSLS   , KC_QUOT   , KC_SCLN   , KC_LBRC   , KC_RBRC   , XXXXXXX   ,
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        _______   , LANGBRC   , RANGBRC   , UNDRSCR   , PLUS      , QUEST     ,                                         PIPE      , DQUOT     , COLON     , LCRLYBRC  , RCRLYBRC  , KC_RSFT   ,
    //+-----------+-----------+-----------+----+------+----+-----------+------+----+-----------+     +-----------+----+------+----+-----------+-----------+-----------+-----------+-----------+
                                _______   , _______   ,      _______   , _______   , _______   ,       _______   , _______   ,                                          KC_PSCR
    //                        +-----------+-----------+    +-----------+-----------+-----------+     +-----------+-----------+                                        +-----------+
    ),
    // Arrow and Mouse keys
    [_ARROW_MOUSE] = LAYOUT_right_ball(
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        _______   , KC_WH_U   , KC_HOME   , KC_UP     , KC_END    , KC_PGUP   ,                                         UNDO      , CUT       , COPY      , PASTE     , KC_INS    , SCRL_TO   ,
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        _______   , KC_WH_D   , KC_LEFT   , KC_DOWN   , KC_RGHT   , KC_PGDN   ,                                         SCRL_DVI  , KC_BTN1   , KC_WH_U   , KC_BTN2   , KC_BTN3   , CNG_WIN   ,
    //+-----------+-----------+-----------+-----------+-----------+-----------+                                       +-----------+-----------+-----------+-----------+-----------+-----------+
        KC_LALT   , KC_LGUI   , SFTED_TAB , KC_TAB    , PREV_PG   , NEXT_PG   ,                                         SCRL_DVD  , KC_WH_L   , KC_WH_D   , KC_WH_R   , KC_BTN4   , KC_BTN5   ,
    //+-----------+-----------+-----------+----+------+----+-----------+------+----+-----------+     +-----------+----+------+----+-----------+-----------+-----------+-----------+-----------+
                                _______   , _______   ,      _______   , _______   , _______   ,       KC_LSFT   , KC_LCTL   ,                                          MO_QWERTY
    //                        +-----------+-----------+    +-----------+-----------+-----------+     +-----------+-----------+                                        +-----------+
    )
};
// clang-format on

/**
 * Change language and layer.
 *
 * <parameter>
 * language : uint16_t          - KC_LNG1 or KC_LNG2
 * layer    : enum layer_number - _QWERTY or _MATOGI
 */
void changeLangAndLayer(uint16_t language, enum layer_number layer) {
    tap_code(language);
    layer_move(layer);
}

/**
 * Tap key with modifier.
 *
 * <parameter>
 * keycode  : uint16_t - Tap key
 * modifier : uint16_t - Modifier key
 */
void tapWithMod(uint16_t keycode, uint16_t modifier) {
    register_code(modifier);
    tap_code(keycode);
    unregister_code(modifier);
}

/**
 * Do double tap.
 *
 * <parameter>
 * firstTap  : uint16_t - First tap keycode
 * secondTap : uint16_t - Second tap keycode
 */
void doubleTap(uint16_t firstTap, uint16_t SecondTap) {
    tap_code(firstTap);
    tap_code(SecondTap);
}

/**
 * Set behavior for custom keycodes.
 *
 * <parameter>
 * keycode: uint16_t     - Pressed keycode
 * record : keyrecord_t* - Record of key order
 *
 * <return>
 * bool -> Whether to override super
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO_QWERTY:
            if (record->event.pressed) {
                changeLangAndLayer(KC_LNG2, _QWERTY);
            }
            break;
        case MO_MATO:
            if (record->event.pressed) {
                changeLangAndLayer(KC_LNG1, _MATOGI);
            }
            break;
        case CTL_LANG:
            if (record->event.pressed) {
                ctrl_lang_state = _PRESSED;
            } else {
                switch (ctrl_lang_state) {
                    case _PRESSED:
                        tapWithMod(KC_GRV, KC_RALT);
                        break;
                    case _HOLDEN:
                        unregister_code(KC_LCTL);
                        break;
                    case _RELEASED:
                        break;
                }
                ctrl_lang_state = _RELEASED;
            }
            break;
        case CTL_QWERTY:
            if (record->event.pressed) {
                ctrl_qwerty_state = _PRESSED;
            } else {
                switch (ctrl_qwerty_state) {
                    case _PRESSED:
                        changeLangAndLayer(KC_LNG2, _QWERTY);
                        break;
                    case _HOLDEN:
                        unregister_code(KC_LCTL);
                        break;
                    case _RELEASED:
                        break;
                }
                ctrl_qwerty_state = _RELEASED;
            }
            break;
        case CTL_MATO:
            if (record->event.pressed) {
                ctrl_mato_state = _PRESSED;
            } else {
                switch (ctrl_mato_state) {
                    case _PRESSED:
                        changeLangAndLayer(KC_LNG1, _MATOGI);
                        break;
                    case _HOLDEN:
                        unregister_code(KC_LCTL);
                        break;
                    case _RELEASED:
                        break;
                }
                ctrl_mato_state = _RELEASED;
            }
            break;
        case SEND_NN:
            if (record->event.pressed) {
                doubleTap(KC_N, KC_N);
            }
            break;
        case KC_YA:
            if (record->event.pressed) {
                doubleTap(KC_Y, KC_A);
            }
            break;
        case KC_YU:
            if (record->event.pressed) {
                doubleTap(KC_Y, KC_U);
            }
            break;
        case KC_YO:
            if (record->event.pressed) {
                doubleTap(KC_Y, KC_O);
            }
            break;
        default:
            // For Ctrl/Lang
            if (ctrl_lang_state == _PRESSED) {
                register_code(KC_LCTL);
                ctrl_lang_state = _HOLDEN;
            }
            // For Ctrl/Qwerty
            if (ctrl_qwerty_state == _PRESSED) {
                register_code(KC_LCTL);
                ctrl_qwerty_state = _HOLDEN;
            }
            // For Ctrl/Matogi
            if (ctrl_mato_state == _PRESSED) {
                register_code(KC_LCTL);
                ctrl_mato_state = _HOLDEN;
            }
            break;
    }

    return true;
}

/**
 * Customize layer state.
 *
 * <parameter>
 * state: layer_state_t - Layer state
 *
 * <return>
 * layer_state_t -> Layer state
 */
layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is _SIGN
    keyball_set_scroll_mode(get_highest_layer(state) == _SIGN);
    return state;
}

/**************************************************************
 * Settings for OLED.
 **************************************************************/
#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

/**************************************************************
 * Settings for combos.
 **************************************************************/
#ifdef COMBO_ENABLE
typedef const uint16_t comb_keys_t[];

/** Change layer to arrow and mouse keys */
static PROGMEM comb_keys_t comb_keys_TO_MOUSE = {KC_J, KC_L, COMBO_END};
/** Change layer to Matogi arrow and mouse keys */
static PROGMEM comb_keys_t comb_keys_matogi_TO_MOUSE = {KC_A, KC_I, COMBO_END};
/** Function 11 key */
static PROGMEM comb_keys_t comb_keys_F11 = {KC_F10, KC_F1, COMBO_END};
/** Function 12 key */
static PROGMEM comb_keys_t comb_keys_F12 = {KC_F10, KC_F2, COMBO_END};
/** Function 13 key */
static PROGMEM comb_keys_t comb_keys_F13 = {KC_F10, KC_F3, COMBO_END};
/** Function 14 key */
static PROGMEM comb_keys_t comb_keys_F14 = {KC_F10, KC_F4, COMBO_END};
/** Function 15 key */
static PROGMEM comb_keys_t comb_keys_F15 = {KC_F10, KC_F5, COMBO_END};
/** Function 16 key */
static PROGMEM comb_keys_t comb_keys_F16 = {KC_F10, KC_F6, COMBO_END};
/** Function 17 key */
static PROGMEM comb_keys_t comb_keys_F17 = {KC_F10, KC_F7, COMBO_END};
/** Function 18 key */
static PROGMEM comb_keys_t comb_keys_F18 = {KC_F10, KC_F8, COMBO_END};
/** Function 19 key */
static PROGMEM comb_keys_t comb_keys_F19 = {KC_F10, KC_F9, COMBO_END};

/** Set behavior for combos */
combo_t key_combos[COMBO_COUNT] = {COMBO(comb_keys_TO_MOUSE, TO(_ARROW_MOUSE)), COMBO(comb_keys_matogi_TO_MOUSE, TO(_ARROW_MOUSE)), COMBO(comb_keys_F11, KC_F11), COMBO(comb_keys_F12, KC_F12), COMBO(comb_keys_F13, KC_F13), COMBO(comb_keys_F14, KC_F14), COMBO(comb_keys_F15, KC_F15), COMBO(comb_keys_F16, KC_F16), COMBO(comb_keys_F17, KC_F17), COMBO(comb_keys_F18, KC_F18), COMBO(comb_keys_F19, KC_F19)};
#endif
