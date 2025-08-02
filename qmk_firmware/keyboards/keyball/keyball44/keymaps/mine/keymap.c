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

enum layer_number
{
  _QWERTY = 0,
  _NUM,
  _SIGN,
  _ARROW_MOUSE
};

enum custom_keycodes
{
  CTRL_LANG = SAFE_RANGE
};

void tap_mod_key(uint16_t modifier, uint16_t keycode)
{
  register_code(modifier);
  tap_code(keycode);
  unregister_code(modifier);
}

enum key_state
{
  RELEASED,
  PRESSED,
  HOLDEN
};

enum key_state ctrl_lang_state = RELEASED;

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  if (keycode == CTRL_LANG)
  {
    if (record->event.pressed)
    {
      ctrl_lang_state = PRESSED;
    }
    else
    {
      switch (ctrl_lang_state)
      {
      case PRESSED:
        tap_mod_key(KC_RALT, KC_GRV);
        break;
      case HOLDEN:
        unregister_code(KC_RCTL);
        break;
      case RELEASED:
        break;
      }
      ctrl_lang_state = RELEASED;
    }
  }
  else
  {
    if (ctrl_lang_state == PRESSED)
    {
      register_code(KC_RCTL);
      ctrl_lang_state = HOLDEN;
    }
  }

  return true;
}

// custom key codes
#define LYR_SPC LT(_SIGN, KC_SPC)
#define LYR_MINS LT(_ARROW_MOUSE, KC_MINS)
#define LYR_ENT LT(_NUM, KC_ENT)
#define SFT_BS LSFT(KC_BSPC)
#define SFT_Z LSFT(KC_Z)
#define TILDE LSFT(KC_GRV)
#define EXCLAM LSFT(KC_1)
#define AT LSFT(KC_2)
#define HASH LSFT(KC_3)
#define DOLLAR LSFT(KC_4)
#define PERCENT LSFT(KC_5)
#define HAT LSFT(KC_6)
#define AND LSFT(KC_7)
#define STAR LSFT(KC_8)
#define LPAREN LSFT(KC_9)
#define RPAREN LSFT(KC_0)
#define LANGBRC LSFT(KC_COMM)
#define RANGBRC LSFT(KC_DOT)
#define UNDRSCR LSFT(KC_MINS)
#define PLUS LSFT(KC_EQL)
#define QUEST LSFT(KC_SLSH)
#define PIPE LSFT(KC_BSLS)
#define DQUOT LSFT(KC_QUOT)
#define COLON LSFT(KC_SCLN)
#define LCRLYBRC LSFT(KC_LBRC)
#define RCRLYBRC LSFT(KC_RBRC)
#define UNDO LCTL(KC_Z)
#define CUT LCTL(KC_X)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)
#define CNG_WIN LGUI(KC_TAB)
#define TO_QWER TO(_QWERTY)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [_QWERTY] = LAYOUT_right_ball(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,      KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,      KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_BSLS  ,
    KC_LSFT  , SFT_Z    , KC_X     , KC_C     , KC_V     , KC_B     ,      KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_QUOT  , KC_SLSH  ,
               KC_LALT  , KC_LGUI  , CTRL_LANG, LYR_SPC  , LYR_MINS ,      SFT_BS   , LYR_ENT                        , KC_CAPS
  ),

  [_NUM] = LAYOUT_right_ball(
    XXXXXXX  , XXXXXXX  , KC_7     , KC_8     , KC_9     , COLON    ,      XXXXXXX  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_DEL   ,
    PLUS     , KC_MINS  , KC_4     , KC_5     , KC_6     , KC_COMM  ,      XXXXXXX  , KC_F5    , KC_F6    , KC_F7    , KC_F8    , XXXXXXX  ,
    STAR     , KC_SLSH  , KC_1     , KC_2     , KC_3     , RANGBRC  ,      XXXXXXX  , KC_F9    , KC_F10   , KC_F11   , KC_F12   , XXXXXXX  ,
               KC_0     , KC_EQL   , _______  , _______  , _______  ,      _______  , _______                        , KC_PSCR
  ),

  [_SIGN] = LAYOUT_right_ball(
    KC_GRV   , EXCLAM   , AT       , HASH     , DOLLAR   , PERCENT  ,      HAT      , AND      , STAR     , LPAREN   , RPAREN   , KC_DEL   ,
    TILDE    , KC_COMM  , KC_DOT   , KC_MINS  , KC_EQL   , KC_SLSH  ,      KC_BSLS  , KC_QUOT  , KC_SCLN  , KC_LBRC  , KC_RBRC  , XXXXXXX  ,
    _______  , LANGBRC  , RANGBRC  , UNDRSCR  , PLUS     , QUEST    ,      PIPE     , DQUOT    , COLON    , LCRLYBRC , RCRLYBRC , XXXXXXX  ,
               _______  , _______  , _______  , _______  , _______  ,      _______  , _______                        , KC_PSCR
  ),

  [_ARROW_MOUSE] = LAYOUT_right_ball(
    _______  , XXXXXXX  , KC_HOME  , KC_UP    , KC_END   , KC_PGUP  ,      UNDO     , CUT      , COPY     , PASTE    , KC_INS   , SCRL_TO  ,
    _______  , XXXXXXX  , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_PGDN  ,      SCRL_DVI , KC_BTN1  , KC_WH_U  , KC_BTN2  , KC_BTN3  , CNG_WIN  ,
    _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,      SCRL_DVD , KC_WH_L  , KC_WH_D  , KC_WH_R  , KC_BTN4  , KC_BTN5  ,
               _______  , _______  , _______  , _______  , _______  ,      KC_LSFT  , KC_LCTL                        , TO_QWER
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state)
{
  // Auto enable scroll mode when the highest layer is 3
  keyball_set_scroll_mode(get_highest_layer(state) == 10);
  return state;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void)
{
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
  keyball_oled_render_layerinfo();
}
#endif

#ifdef COMBO_ENABLE
typedef const uint16_t comb_keys_t[];
static PROGMEM comb_keys_t
    my_jl = {KC_J, KC_L, COMBO_END},
    my_pgud = {KC_PAGE_UP, KC_PAGE_DOWN, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(my_jl, TO(_ARROW_MOUSE)),
    COMBO(my_pgud, TO(_QWERTY)),
};
#endif