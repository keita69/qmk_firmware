#include QMK_KEYBOARD_H
#include <stdio.h>

extern keymap_config_t keymap_config;

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

uint16_t key_tap_count = 0;
char key_tap_count_buf[11];

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,

  K8SCTL,
  ALT_TB,
  ESCx2,   // ESC x2
  SD_CBR,  // Surround {}
  SD_CRB,  // Surround []
  SD_PRN,  // Surround ()
  SD_SCLN, // Surround ""
  SD_QUOT, // Surround ''
  SD_GRV3, // Surround ``````
  TAP_CNT  // get key tap count
};

#define EISU   LALT(KC_GRV)
#define CLALDL LCTL(LALT(KC_DEL))  // Crrl+Alt+Del
#define CTL_W  LCTL(KC_W)          // Crrl+W
#define CTLTAB LCTL(KC_TAB)        // Crrl+TAB
#define CTLSTB LCTL(LSFT(KC_TAB))  // Crrl+Shift+TAB
#define WWW_BK KC_WWW_BACK	       // Browser Back (Windows)
#define WWW_FW KC_WWW_FORWARD      // Browser Forward (Windows)
#define GUI_RT LGUI(KC_RGHT)       // Windows+Right
#define GUI_UP LGUI(KC_UP)         // Windows+Up
#define ALTSUP LALT(LSFT(KC_UP))   // ALT+Shift+Up
#define ALTSDN LALT(LSFT(KC_DOWN)) // ALT+Shift+Down
#define ALT_SP LALT(KC_SPC)        // ALT+Space

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,----------------------------------------------------------------------------------------------------------------------.
     * | ESC  |   1  |   2  |   3  |   4  |   5  |   [  |                    |   ]  |   6  |   7  |   8  |   9  |   0  |  `   |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |   -  |                    |   =  |   Y  |   U  |   I  |   O  |   P  |  \   |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * | Ctrl |   A  |   S  |   D  |   F  |   G  |  Del |                    |ALT_SP|   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |      |ClAlDl||||||||K8SCTL|      |   N  |   M  |   ,  |   .  |   /  | Shift|
     * |-------------+------+------+------+------| Space|------+------+------+ Enter|------+------+------+------+-------------|
     * | Ctrl |  GUI |  ALt |ALT_TB|||||||| Lower|      |  Del |||||||| Bksp |      | Raise||||||||  GUI |GUI_RT|GUI_UP| Enter|
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
    [_QWERTY] = LAYOUT( \
      ESCx2,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LBRC,                        KC_RBRC, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS,                        KC_EQL , KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_DEL ,                        ALT_SP,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             CLALDL,       K8SCTL ,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, ALT_TB,           LOWER,   KC_SPC , KC_DEL,       KC_BSPC, KC_ENT , RAISE,            KC_RGUI, GUI_RT,  GUI_UP,  KC_ENT   \
    ),

    /* Lower
     * ,----------------------------------------------------------------------------------------------------------------------.
     * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |      |                    |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * |      |      |      |ALTSUP|ALTSDN|      |      |                    |      |``````|  {}  |  []  |  ()  |  ""  |  ''  |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * | Ctrl |      |      |      | EISU |      |      |                    |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * | EISU |      |      |      |      |      |      |      ||||||||      |      |CTLSTB|CTLTAB|WWW_BK|WWW_FW|      |      |
     * |-------------+------+------+------+------| Space|------+------+------+ Enter|------+------+------+------+-------------|
     * |      |      |      |      |||||||| Lower|      |  Del |||||||| Bksp |      | Raise|||||||| EISU |GUI_RT|GUI_UP|      |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
    [_LOWER] = LAYOUT(
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
      _______, _______, _______, ALTSUP , ALTSDN , _______, _______,                        _______, SD_GRV3, SD_CBR , SD_CRB , SD_PRN , SD_SCLN, SD_QUOT, \
      KC_LCTL, _______, _______, _______, EISU,    _______, _______,                        _______, _______, _______, _______, _______, _______, _______, \
      EISU   , _______, _______, _______, _______, _______,          _______,      _______,          CTLSTB,  CTLTAB,  WWW_BK,  WWW_FW,  _______, _______, \
      _______, _______, _______, _______,          LOWER,   KC_SPC , _______,      _______, KC_ENT , RAISE,            EISU,    GUI_RT,  GUI_UP,  _______  \
    ),

    /* Raise
     * ,----------------------------------------------------------------------------------------------------------------------.
     * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |   {  |                    |   }  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * |  ~   |   !  |   @  |   #  |   $  |   %  |   _  |                    |      |MsLeft|MsDown| MsUp |MsRght|MsBtn1|MsBtn2|
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * | Ctrl |      |      |      |      |      |      |                    |CTL_W | Left | Down |  Up  | Right|WinApp| Enter|
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * | Shift|      |      |      |      |      |      |      ||||||||      |      |WhLeft|WhDown| WhUp |WhRght| Home | End  |
     * |-------------+------+------+------+------| Space|------+------+------+ Enter|------+------+------+------+-------------|
     * |      |  GUI |  ALt | EISU |||||||| Lower|      |  Del |||||||| Bksp |      | Raise|||||||| EISU |GUI_RT|GUI_UP|      |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
    [_RAISE] = LAYOUT(
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LCBR,                        KC_RCBR, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12 , \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_UNDS,                        _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, KC_BTN2, \
      KC_LCTL, _______, _______, _______, _______, _______, KC_DEL ,                        CTL_W,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_APP	, KC_ENT , \
      KC_LSFT, _______, _______, _______, _______, _______,          _______,      _______,          KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_HOME, KC_END , \
      _______, KC_LGUI, KC_LALT, EISU,             LOWER,   KC_SPC , KC_DEL,       KC_BSPC, KC_ENT , RAISE,            EISU,    GUI_RT,  GUI_UP,  _______  \
    ),

    /* Adjust
     * ,----------------------------------------------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+|      |      |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * | Ctrl |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * | Shift|      |      |      |      |      |      |      ||||||||      |      |CTLSTB|CTLTAB|WWW_BK|WWW_FW|      |      |
     * |-------------+------+------+------+------|      +------+------+------+      |------+------+------+------+-------------|
     * |TAPCNT|      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______, _______, \
      _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, _______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
      KC_LCTL, _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______, _______, \
      KC_LSFT, _______, _______, _______, _______, _______,          _______,     _______,          CTLSTB,  CTLTAB,  WWW_BK,  WWW_FW,  _______, _______, \
      TAP_CNT, _______, _______, _______,          _______, _______, _______,     _______, _______, _______,          _______, _______, _______, _______  \
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

  if (record->event.pressed) {
    // tap is twice evnets. events are proessed and release event.
    key_tap_count++;
  }

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
    case SD_CBR:
      if (record->event.pressed) {
        // when keycode this is pressed to surround {}
        SEND_STRING("{");
        SEND_STRING("}");
        SEND_STRING(SS_TAP(X_LEFT));
      } else {
        // when keycode this is pressed
      }
      return false;
      break;
    case SD_CRB:
      if (record->event.pressed) {
        // when keycode this is pressed to surround []
        SEND_STRING("[");
        SEND_STRING("]");
        SEND_STRING(SS_TAP(X_LEFT));
      } else {
        // when keycode this is pressed
      }
      return false;
      break;
    case SD_PRN:
      if (record->event.pressed) {
        // when keycode this is pressed to surround ()
        SEND_STRING("(");
        SEND_STRING(")");
        SEND_STRING(SS_TAP(X_LEFT));
      } else {
        // when keycode this is pressed
      }
      return false;
      break;
    case SD_SCLN:
      if (record->event.pressed) {
        // when keycode this is pressed to surround ""
        SEND_STRING("\"");
        SEND_STRING("\"");
        SEND_STRING(SS_TAP(X_LEFT));
      } else {
        // when keycode this is pressed
      }
      return false;
      break;
    case SD_QUOT:
      if (record->event.pressed) {
        // when keycode this is pressed to surround ''
        SEND_STRING("'");
        SEND_STRING("'");
        SEND_STRING(SS_TAP(X_LEFT));
      } else {
        // when keycode this is pressed
      }
      return false;
      break;
    case SD_GRV3:
      if (record->event.pressed) {
        // when keycode this is pressed to surround ``````
        SEND_STRING(SS_TAP(X_ESCAPE)); // 無変換
        SEND_STRING("```");
        SEND_STRING(SS_TAP(X_ENTER));
        SEND_STRING(SS_TAP(X_ENTER));
        SEND_STRING("```");
        SEND_STRING(SS_TAP(X_UP));
      } else {
        // when keycode this is pressed
      }
      return false;
      break;
    case ESCx2:
      if (record->event.pressed) {
        // when keycode ESC is pressed two times 
        // https://qiita.com/chesscommands/items/ce2883ad0a0c6c27c8de#ss_tap
        // https://github.com/qmk/qmk_firmware/blob/6590f3c81155f5d5cfb59c5b8a28610d6f3207d0/quantum/send_string_keycodes.h
        SEND_STRING(SS_TAP(X_ESCAPE));
        SEND_STRING(SS_TAP(X_ESCAPE));
      } else {
        // when keycode ESC is pressed two times 
      }
      return false;
      break;
   case K8SCTL:
      if (record->event.pressed) {
        // when keycode K8SCTL is pressed
        SEND_STRING("kubectl ");
      } else {
        // when keycode K8SCTL is pressed
      }
      return false;
      break;
   case TAP_CNT:
      if (record->event.pressed) {
        // when keycode TAP_CNT is pressed
        SEND_STRING("Your key tap count is ");
        snprintf(key_tap_count_buf, 11, "%d", key_tap_count);
        send_string(key_tap_count_buf);
        SEND_STRING(SS_TAP(X_ENTER));
      } else {
        // when keycode TAP_CNT is pressed
      }
      return false;
      break;
    case ALT_TB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        } 
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

// Super ALT↯TAB
// https://docs.qmk.fm/#/feature_macros?id=super-alt%e2%86%aftab
void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 350) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

// Key Tap Counter
// char *get_key_tap_count(void) {
//   snprintf(key_tap_count_buf, 11, "%d", key_tap_count);
//   return key_tap_count_buf;
// }