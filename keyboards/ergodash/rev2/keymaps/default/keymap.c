#include QMK_KEYBOARD_H
#include <time.h>

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,

  YMD,
};

#define EISU LALT(KC_GRV)
#define CLALDL LCTL(LALT(KC_DEL))  // Crrl+Alt+Del
#define CTL_1 LCTL(KC_1)           // Crrl+1
#define CTL_2 LCTL(KC_2)           // Crrl+2
#define CTL_3 LCTL(KC_3)           // Crrl+3
#define CTL_4 LCTL(KC_4)           // Crrl+4
#define CTL_5 LCTL(KC_5)           // Crrl+5
#define CTL_6 LCTL(KC_6)           // Crrl+6
#define CTL_7 LCTL(KC_7)           // Crrl+7
#define CTL_8 LCTL(KC_8)           // Crrl+8
#define CTL_9 LCTL(KC_9)           // Crrl+9
#define CTL_W LCTL(KC_W)           // Crrl+W
#define CTLTAB LCTL(KC_TAB)        // Crrl+TAB
#define CTLSTB LCTL(LSFT(KC_TAB))  // Crrl+Shift+TAB
#define ALTTAB LALT(KC_TAB)        // Alt+TAB
#define ALTSTB LALT(LSFT(KC_TAB))  // Alt+Shift+TAB

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,----------------------------------------------------------------------------------------------------------------------.
     * | ESC  |   1  |   2  |   3  |   4  |   5  |   [  |                    |   ]  |   6  |   7  |   8  |   9  |   0  |Pscree|
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * |  `   |   Q  |   W  |   E  |   R  |   T  |   -  |                    |   =  |   Y  |   U  |   I  |   O  |   P  |  \   |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * | Tab  |   A  |   S  |   D  |   F  |   G  |  Del |                    | Bksp |   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |      |ClAlDl|      | YMD  |      |   N  |   M  |   ,  |   .  |   /  | Shift|
     * |-------------+------+------+------+------| Space|------+------+------+ Enter|------+------+------+------+-------------|
     * | Ctrl |  GUI |  ALt | EISU |||||||| Lower|      |  Del |||||||| Bksp |      | Raise|||||||| Home |PageDn|PageUp|  End |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
    [_QWERTY] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LBRC,                        KC_RBRC, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PSCR, \
      KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS,                        KC_EQL , KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
      KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_DEL ,                        KC_BSPC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             CLALDL,       YMD    ,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, EISU,             LOWER,   KC_SPC , KC_DEL,       KC_BSPC, KC_ENT , RAISE,            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
    ),

    /* Lower
     * ,----------------------------------------------------------------------------------------------------------------------.
     * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |   {  |                    |   }  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * |  ~   |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |  |   |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * | Tab  | CTL_1| CTL_2| CTL_3| CTL_4| CTL_5|  Del |                    | Bksp | Left | Down |  Up  | Right| Home | End  |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * | Shift| CTL_6| CTL_7| CTL_8| CTL_9| CTL_W|      | Space|      | Enter|      |CTLTAB|CTLSTB|ATLTAB|ATLSTB|   ?  | Shift|
     * |-------------+------+------+------+------| Space|------+------+------+ Enter|------+------+------+------+-------------|
     * | Ctrl |  GUI |  ALt | EISU |||||||| Lower|      |  Del |||||||| Bksp |      | Raise|||||||| Home |PageDn|PageUp|  End |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
    [_LOWER] = LAYOUT(
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LCBR,                        KC_RCBR, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_UNDS,                        KC_PLUS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
      KC_TAB,  CTL_1,   CTL_2,   CTL_3,   CTL_4,   CTL_5,   KC_DEL ,                        KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_HOME, KC_END,  \
      KC_LSFT, CTL_6,   CTL_7,   CTL_8,   CTL_9,   CTL_W ,           KC_SPC,       KC_ENT ,          CTLTAB,  CTLSTB,  ATLTAB,  ATLSTB,  KC_QUES, KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, EISU,             LOWER,   KC_SPC , KC_DEL,       KC_BSPC, KC_ENT , RAISE,            KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
    ),

    /* Raise
     * ,----------------------------------------------------------------------------------------------------------------------.
     * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |   {  |                    |   }  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * |  ~   |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |  |   |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * | Tab  |   1  |   2  |   3  |   4  |   5  |  Del |                    | Bksp |MsLeft|MsDown| MsUp |MsRght|MsBtn1|MsBtn2|
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * | Shift|   6  |   7  |   8  |   9  |   0  |      | Space|      | Enter|      |   N  |   M  |   <  |   >  |   ?  | Shift|
     * |-------------+------+------+------+------| Space|------+------+------+ Enter|------+------+------+------+-------------|
     * | Ctrl |  GUI |  ALt | EISU |||||||| Lower|      |  Del |||||||| Bksp |      | Raise|||||||| Home |PageDn|PageUp|  End |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
    [_RAISE] = LAYOUT(
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LCBR,                        KC_RCBR, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_UNDS,                        KC_PLUS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
      KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_DEL ,                        KC_BSPC, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, KC_BTN2, \
      KC_LSFT, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,             KC_SPC,       KC_ENT ,          KC_N,    KC_M,    KC_LT,   KC_GT,   KC_QUES, KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, EISU,             LOWER,   KC_SPC , KC_DEL,       KC_BSPC, KC_ENT , RAISE,            KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
    ),

    /* Adjust
     * ,----------------------------------------------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+|      |      |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |                    |      |WhLeft|WhDown| WhUp |WhRght|MsBtn4|MsBtn5|
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
     * |-------------+------+------+------+------|      +------+------+------+      |------+------+------+------+-------------|
     * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______, _______, \
      _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, _______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
      _______, _______, BL_TOGG, BL_BRTG, BL_INC , BL_DEC , _______,                       _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN4, KC_BTN5, \
      _______, _______, _______, RGB_MOD, _______, _______,          _______,     _______,          _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______,          _______, _______, _______,     _______, _______, _______,          _______, _______, _______, _______  \
    )
  };

#ifdef AUDIO_ENABLE
float tone_qwerty[][2] = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case YMD:
      if (record->event.pressed) {
        // when keycode YMD is pressed
        char       s[256] = {'\0'};
        time_t     timer;
        struct tm *timeptr;

        timer   = time(NULL);
        timeptr = localtime(&timer);
        strftime(s, 256, "%Y%m%d", timeptr);
        send_string(s);
      } else {
        // when keycode YMD is pressed
      }
      return false;
      break;
  }
  return true;
}
