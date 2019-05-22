#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

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
};

#define EISU LALT(KC_GRV)
#define CLALDL LCTL(LALT(KC_DEL))  // Crrl+Alt+Del
#define CTL_W LCTL(KC_W)           // Crrl+W
#define CTLTAB LCTL(KC_TAB)        // Crrl+TAB
#define CTLSTB LCTL(LSFT(KC_TAB))  // Crrl+Shift+TAB
#define WWW_BK KC_WWW_BACK	       // Browser Back (Windows)
#define WWW_FW KC_WWW_FORWARD      // Browser Forward (Windows)
#define GUI_RT LGUI(KC_RGHT)       // Windows+Right
#define GUI_UP LGUI(KC_UP)         // Windows+Up
#define ALT2F  KC_RALT             // Alt -> F
#define ESCx2  KC_ESC              // ESC
#define SD_PRN KC_LPRN             // ( -> ) -> Left (Surround)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,----------------------------------------------------------------------------------------------------------------------.
     * | ESC  |   1  |   2  |   3  |   4  |   5  |   [  |                    |   ]  |   6  |   7  |   8  |   9  |   0  |  `   |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |   -  |                    |   =  |   Y  |   U  |   I  |   O  |   P  |  \   |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * | Ctrl |   A  |   S  |   D  |   F  |   G  |  Del |                    | ALT_F|   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |      |ClAlDl|      |K8SCTL|      |   N  |   M  |   ,  |   .  |   /  | Shift|
     * |-------------+------+------+------+------| Space|------+------+------+ Enter|------+------+------+------+-------------|
     * |      |  GUI |  ALt |ALT_TB|||||||| Lower|      |  Del |||||||| Bksp |      | Raise|||||||| EISU |GUI_RT|GUI_UP| Ctrl |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
    [_QWERTY] = LAYOUT( \
      ESCx2,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LBRC,                        KC_RBRC, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS,                        KC_EQL , KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_DEL ,                        ALT2F,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             CLALDL,       K8SCTL ,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      _______, KC_LGUI, KC_LALT, ALT_TB,           LOWER,   KC_SPC , KC_DEL,       KC_BSPC, KC_ENT , RAISE,            EISU,    GUI_RT,  GUI_UP,  KC_RCTL  \
    ),

    /* Lower
     * ,----------------------------------------------------------------------------------------------------------------------.
     * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |   {  |                    |   }  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * |  ~   |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |  ()  |   )  |  |   |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * | Ctrl |      |      |      | EISU |      |      |                    |      | Left | Down |  Up  | Right| Home | End  |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * | Shift|      |      |      |      |      |      | Space|      | Enter|      |      |      |      |      |      |      |
     * |-------------+------+------+------+------| Space|------+------+------+ Enter|------+------+------+------+-------------|
     * |      |  GUI |  ALt | EISU |||||||| Lower|      |  Del |||||||| Bksp |      | Raise|||||||| EISU |GUI_RT|GUI_UP|      |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
    [_LOWER] = LAYOUT(
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LCBR,                        KC_RCBR, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_UNDS,                        KC_PLUS, KC_CIRC, KC_AMPR, KC_ASTR, SD_PRN , KC_RPRN, KC_PIPE, \
      KC_LCTL, _______, _______, _______, EISU,    _______, _______,                        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_HOME, KC_END,  \
      KC_LSFT, _______, _______, _______, _______, _______,          KC_SPC,       KC_ENT ,          _______, _______, _______, _______, _______, _______, \
      _______, KC_LGUI, KC_LALT, EISU,             LOWER,   KC_SPC , KC_DEL,       KC_BSPC, KC_ENT , RAISE,            EISU,    GUI_RT,  GUI_UP,  _______  \
    ),

    /* Raise
     * ,----------------------------------------------------------------------------------------------------------------------.
     * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |   {  |                    |   }  |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * |  ~   |   !  |   @  |   #  |   $  |   %  |   _  |                    |      |WhLeft|WhDown| WhUp |WhRght|      |      |
     * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
     * | Ctrl |      |      |      |      |      |      |                    |CTL_W |MsLeft|MsDown| MsUp |MsRght|MsBtn1|MsBtn2|
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * | Shift|      |      |      |      |      |      | Space|      | Enter|      |CTLSTB|CTLTAB|WWW_BK|WWW_FW|      |      |
     * |-------------+------+------+------+------| Space|------+------+------+ Enter|------+------+------+------+-------------|
     * |      |  GUI |  ALt | EISU |||||||| Lower|      |  Del |||||||| Bksp |      | Raise|||||||| EISU |GUI_RT|GUI_UP|      |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
    [_RAISE] = LAYOUT(
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LCBR,                        KC_RCBR, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,  \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_UNDS,                        _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______, \
      KC_LCTL, _______, _______, _______, _______, _______, KC_DEL ,                        CTL_W,   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, KC_BTN2, \
      KC_LSFT, _______, _______, _______, _______, _______,          KC_SPC,       KC_ENT ,          CTLSTB,  CTLTAB,  WWW_BK,  WWW_FW,  _______, _______, \
      _______, KC_LGUI, KC_LALT, EISU,             LOWER,   KC_SPC , KC_DEL,       KC_BSPC, KC_ENT , RAISE,            EISU,    GUI_RT,  GUI_UP,  _______  \
    ),

    /* Adjust
     * ,----------------------------------------------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+|      |      |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * | Ctrl |      |      |      |      |      |      |                    |      | Left | Down |  Up  | Right| Home | End  |
     * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
     * | Shift|      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
     * |-------------+------+------+------+------|      +------+------+------+      |------+------+------+------+-------------|
     * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______, _______, \
      _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, _______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
      KC_LCTL, _______, BL_TOGG, BL_BRTG, BL_INC , BL_DEC , _______,                       _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_HOME, KC_END , \
      KC_LSFT, _______, _______, RGB_MOD, _______, _______,          _______,     _______,          _______, _______, _______, _______, _______, _______, \
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
     case SD_PRN:
      if (record->event.pressed) {
        // when keycode ( is pressed to surround ()
        SEND_STRING("(");
        SEND_STRING(")");
        SEND_STRING(SS_TAP(X_RIGHT));
      } else {
        // when keycode ESC is pressed two times 
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
    case ALT2F:
      if (record->event.pressed) {
        // when keycode ALT -> F is pressed
        SEND_STRING(SS_TAP(X_RALT));
        SEND_STRING(SS_TAP(X_F));
      } else {
        // released
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