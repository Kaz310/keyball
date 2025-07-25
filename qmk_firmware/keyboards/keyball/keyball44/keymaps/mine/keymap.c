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

// custom keys
#define LYR_SPC LT(3, KC_SPC)
#define LYR_MINS LT(2, KC_MINS)
#define LYR_ENT LT(1, KC_ENT)
#define SFT_Z SFT_T(KC_Z)
#define SFT_GRV SFT_T(KC_GRV)
#define SFT_1 SFT_T(KC_1)
#define SFT_2 SFT_T(KC_2)
#define SFT_3 SFT_T(KC_3)
#define SFT_4 SFT_T(KC_4)
#define SFT_5 SFT_T(KC_5)
#define SFT_6 SFT_T(KC_6)
#define SFT_7 SFT_T(KC_7)
#define SFT_8 SFT_T(KC_8)
#define SFT_9 SFT_T(KC_9)
#define SFT_0 SFT_T(KC_0)
#define SFT_COMM SFT_T(KC_COMM)
#define SFT_DOT SFT_T(KC_DOT)
#define SFT_MINS SFT_T(KC_MINS)
#define SFT_EQL SFT_T(KC_EQL)
#define SFT_SLSH SFT_T(KC_SLSH)
#define SFT_BSLS SFT_T(KC_BSLS)
#define SFT_QUOT SFT_T(KC_QUOT)
#define SFT_SCLN SFT_T(KC_SCLN)
#define SFT_LBRC SFT_T(KC_LBRC)
#define SFT_RBRC SFT_T(KC_RBRC)
#define WIN_LOCK GUI_T(KC_L)
#define UNDO CTL_T(KC_Z)
#define CUT CTL_T(KC_X)
#define COPY CTL_T(KC_C)
#define PASTE CTL_T(KC_V)
#define CNG_WIN GUI_T(KC_TAB)
#define MO_QWER MO(0)

enum layer_number
{
  _QWERTY = 0,
  _NUM,
  _SFT_NUM,
  _ARROW_MOUSE,
  _MOUSE
};

enum custom_keycodes
{
  CTRL_LANG = SAFE_RANGE
};

enum key_state
{
  RELEASED,
  PRESSED,
  HOLDEN
};

void tap_mod_key(uint16_t modifier, uint16_t keycode)
{
  register_code(modifier);
  tap_code(keycode);
  unregister_code(modifier);
}

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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [_QWERTY] = LAYOUT_right_ball(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,      KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL  ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,      KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_BSLS ,
    KC_LSFT  , SFT_Z    , KC_X     , KC_C     , KC_V     , KC_B     ,      KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_QUOT  , KC_SLSH ,
               KC_LALT  , KC_LGUI  , CTRL_LANG, LYR_SPC  , LYR_MINS ,      KC_BSPC  , LYR_ENT                        , KC_CAPS
  ),

  [_NUM] = LAYOUT_right_ball(
    KC_GRV   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,      KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , _______ ,
    _______  , KC_COMM  , KC_DOT   , KC_MINS  , KC_EQL   , KC_SLSH  ,      KC_BSLS  , KC_QUOT  , KC_SCLN  , KC_LBRC  , KC_RBRC  , XXXXXXX ,
    _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,      XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX ,
               _______  , _______  , _______  , _______  , _______  ,      _______  , _______                        , XXXXXXX
  ),

  [_SFT_NUM] = LAYOUT_right_ball(
    SFT_GRV  , SFT_1    , SFT_2    , SFT_3    , SFT_4    , SFT_5    ,      SFT_6    , SFT_7    , SFT_8    , SFT_9    , SFT_0    , _______ ,
    KC_F1    , SFT_COMM , SFT_DOT  , SFT_MINS , SFT_EQL  , SFT_SLSH ,      SFT_BSLS , SFT_QUOT , SFT_SCLN , SFT_LBRC , SFT_RBRC , XXXXXXX ,
    _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,      XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX ,
               _______  , _______  , _______  , _______  , _______  ,      _______  , _______                        , XXXXXXX
  ),

  [_ARROW_MOUSE] = LAYOUT_right_ball(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    , KC_F6    ,      KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   , KC_F12   ,
    _______  , XXXXXXX  , XXXXXXX  , KC_UP    , XXXXXXX  , KC_HOME  ,      KC_PGUP  , KC_BTN1  , KC_WH_U  , KC_BTN2  , KC_BTN3  , SCRL_TO  ,
    _______  , XXXXXXX  , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_END   ,      KC_PGDN  , KC_WH_L  , KC_WH_D  , KC_WH_R  , KC_BTN4  , KC_BTN5  ,
               _______  , _______  , _______  , _______  , _______  ,      KC_LSFT  , KC_LCTL                        , CNG_WIN
  ),

  [_MOUSE] = LAYOUT_right_ball(
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,      UNDO     , CUT      , COPY     , PASTE    , SCRL_DVD , SCRL_DVI ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_UP    , XXXXXXX  , KC_HOME  ,      KC_PGUP  , KC_BTN1  , KC_WH_U  , KC_BTN2  , KC_BTN3  , SCRL_TO  ,
    XXXXXXX  , XXXXXXX  , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_END   ,      KC_PGDN  , KC_WH_L  , KC_WH_D  , KC_WH_R  , KC_BTN4  , KC_BTN5  ,
               XXXXXXX  , XXXXXXX  , MO_QWER  , MO_QWER  , MO_QWER  ,      KC_LSFT  , KC_LCTL                        , CNG_WIN
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
    COMBO(my_jl, TG(_MOUSE)),
    COMBO(my_pgud, TG(_QWERTY)),
};
#endif