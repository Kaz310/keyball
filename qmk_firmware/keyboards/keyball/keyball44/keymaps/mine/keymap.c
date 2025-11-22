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
enum layer_number
{
  /** Layer number for Qwerty */
  _QWERTY = 0,
  /** Layer number for Number and Function keys */
  _NUM,
  /** Layer number for Numpad and Function keys */
  _HALF_NUM,
  /** Layer number for Sing keys */
  _SIGN,
  /** Layer number for Arrow and Mouse keys */
  _ARROW_MOUSE
};

/** Define custom keycodes */
enum custom_keycodes
{
  /** Change language */
  CTRL_LANG = KEYBALL_SAFE_RANGE
};

/** Change language to English */
#define CTL_LNG_EN MT(MOD_LCTL, KC_LNG2)
/** Change language to Japanese */
#define CTL_LNG_JP MT(MOD_LCTL, KC_LNG1)
/** Space key and Change layer to sing keys */
#define SIGN_SPC LT(_SIGN, KC_SPC)
/** Minus key and Change layer to arrows and mouse keys */
#define MOUSE_MINS LT(_ARROW_MOUSE, KC_MINS)
/** Enter key and Change layer to number and function keys */
#define NUM_ENT LT(_NUM, KC_ENT)
/** Backspace key and Change layer to numpad and function keys */
#define SFT_BS LT(_HALF_NUM, KC_BSPC)
/** Z key and Left shift */
#define SFT_Z MT(MOD_LSFT, KC_Z)
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
/** Change layer to qwerty keys */
#define TO_QWER TO(_QWERTY)

/*************************************************************
 * Settings for keymaps, keycodes and layer states.
 *************************************************************/
// clang-format off
/** Custom keymap settings */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Qwerty (default)
  [_QWERTY] = LAYOUT_right_ball(
    KC_ESC    , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T      ,      KC_Y      , KC_U      , KC_I      , KC_O      , KC_P      , KC_DEL    ,
    KC_TAB    , KC_A      , KC_S      , KC_D      , KC_F      , KC_G      ,      KC_H      , KC_J      , KC_K      , KC_L      , KC_SCLN   , KC_BSLS   ,
    KC_LSFT   , SFT_Z     , KC_X      , KC_C      , KC_V      , KC_B      ,      KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_QUOT   , KC_SLSH   ,
                KC_LALT   , KC_LGUI   , CTL_LNG_EN, SIGN_SPC  , MOUSE_MINS,      SFT_BS    , NUM_ENT                           , KC_CAPS
  ),
  // Number and Function keys
  [_NUM] = LAYOUT_right_ball(
    _______   , KC_1      , KC_2      , KC_3      , KC_4      , KC_5      ,      KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , _______   ,
    _______   , KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     ,      COLON     , KC_4      , KC_5      , KC_6      , KC_COMM   , XXXXXXX   ,
    _______   , KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    ,      KC_0      , KC_1      , KC_2      , KC_3      , KC_DOT    , XXXXXXX   ,
                _______   , _______   , CTL_LNG_JP, _______   , _______   ,      _______   , _______                           , XXXXXXX
  ),
  // Half number and Function keys
  [_HALF_NUM] = LAYOUT_right_ball(
    _______   , KC_P1     , KC_P2     , KC_P3     , KC_P4     , KC_P5     ,      KC_P6     , KC_P7     , KC_P8     , KC_P9     , KC_P0     , _______   ,
    _______   , KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     ,      COLON     , KC_P4     , KC_P5     , KC_P6     , KC_COMM   , XXXXXXX   ,
    _______   , KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    ,      KC_P0     , KC_P1     , KC_P2     , KC_P3     , KC_DOT    , XXXXXXX   ,
                _______   , _______   , CTL_LNG_JP, _______   , _______   ,      _______   , _______                           , XXXXXXX
  ),
  // Sing keys
  [_SIGN] = LAYOUT_right_ball(
    KC_GRV    , EXCLAM    , AT        , HASH      , DOLLAR    , PERCENT   ,      HAT       , AND       , STAR      , LPAREN    , RPAREN    , _______   ,
    TILDE     , KC_COMM   , KC_DOT    , KC_MINS   , KC_EQL    , KC_SLSH   ,      KC_BSLS   , KC_QUOT   , KC_SCLN   , KC_LBRC   , KC_RBRC   , XXXXXXX   ,
    _______   , LANGBRC   , RANGBRC   , UNDRSCR   , PLUS      , QUEST     ,      PIPE      , DQUOT     , COLON     , LCRLYBRC  , RCRLYBRC  , XXXXXXX   ,
                _______   , _______   , _______   , _______   , _______   ,      _______   , _______                           , KC_PSCR
  ),
  // Arrow and Mouse keys
  [_ARROW_MOUSE] = LAYOUT_right_ball(
    _______   , KC_WH_U   , KC_HOME   , KC_UP     , KC_END    , KC_PGUP   ,      UNDO      , CUT       , COPY      , PASTE     , KC_INS    , SCRL_TO   ,
    XXXXXXX   , KC_WH_D   , KC_LEFT   , KC_DOWN   , KC_RGHT   , KC_PGDN   ,      SCRL_DVI  , KC_BTN1   , KC_WH_U   , KC_BTN2   , KC_BTN3   , CNG_WIN   ,
    KC_LALT   , KC_LGUI   , SFTED_TAB , KC_TAB    , PREV_PG   , NEXT_PG   ,      SCRL_DVD  , KC_WH_L   , KC_WH_D   , KC_WH_R   , KC_BTN4   , KC_BTN5   ,
                _______   , _______   , _______   , _______   , _______   ,      KC_LSFT   , KC_LCTL                           , TO_QWER
  ),
};
// clang-format on

/** Key state for custom keycodes */
enum key_state
{
  _RELEASED,
  _PRESSED,
  _HOLDEN
};

/** Key state for Ctrl/Lang keycode */
enum key_state ctrl_lang_state = _RELEASED;

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
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
    // For Ctrl/Lang
  case CTRL_LANG:
    if (record->event.pressed)
    {
      ctrl_lang_state = _PRESSED;
    }
    else
    {
      switch (ctrl_lang_state)
      {
      case _PRESSED:
        register_code(KC_RALT);
        tap_code(KC_GRV);
        unregister_code(KC_RALT);
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
  default:
    // For Ctrl/Lang
    if (ctrl_lang_state == _PRESSED)
    {
      register_code(KC_LCTL);
      ctrl_lang_state = _HOLDEN;
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
layer_state_t layer_state_set_user(layer_state_t state)
{
  // Auto enable scroll mode when the highest layer is _SIGN
  keyball_set_scroll_mode(get_highest_layer(state) == _SIGN);
  return state;
}

/**************************************************************
 * Settings for OLED.
 **************************************************************/
#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void)
{
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
combo_t key_combos[COMBO_COUNT] = {
    COMBO(comb_keys_TO_MOUSE, TO(_ARROW_MOUSE)),
    COMBO(comb_keys_F11, KC_F11),
    COMBO(comb_keys_F12, KC_F12),
    COMBO(comb_keys_F13, KC_F13),
    COMBO(comb_keys_F14, KC_F14),
    COMBO(comb_keys_F15, KC_F15),
    COMBO(comb_keys_F16, KC_F16),
    COMBO(comb_keys_F17, KC_F17),
    COMBO(comb_keys_F18, KC_F18),
    COMBO(comb_keys_F19, KC_F19),
};
#endif