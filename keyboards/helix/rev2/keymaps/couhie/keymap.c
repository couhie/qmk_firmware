#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _FN1,
    _FN2,
    _FN3
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  FN1,
  FN2,
  FN3,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#define KC_SGUI GUI_T(KC_SPACE)
#define KC_ENT3 LT(_FN3, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  -   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * | Fn2  | Alt  | GUI  | Caps | Fn1  | Ctrl |Space |Space | Enter| Fn1  | Bksp | GUI  | Alt  | Fn2  |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
      KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT , \
      FN2,     KC_LALT, KC_LGUI, KC_CAPS, FN1,     KC_LCTL, KC_SGUI, KC_SGUI, KC_ENT3, FN1,     KC_BSPC, KC_RGUI, KC_RALT, FN2 \
      ),

  /* Fn1
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |  +   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |   \  |   |  |      |   [  |   ]  |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_FN1] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL, \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS, \
      _______, _______, _______, _______, _______, _______,                   KC_BSLS, KC_PIPE, _______, KC_LBRC, KC_RBRC, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
      ),

  /* Fn2
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |RGBRST|RGB ON| HUE+ | SAT+ | VAL+ | Reset|             |      | Home | End  |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | MODE | HUE- | SAT- | VAL- |      |             | Left | Down |  Up  | Right|      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Play | Next |      |      |      |             |      |PageDn|PageUp|      |      |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_FN2] = LAYOUT( \
      RGBRST,  RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RESET,                     _______, KC_HOME, KC_END,  _______, _______, _______, \
      _______, RGB_SMOD,RGB_HUD, RGB_SAD, RGB_VAD, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
      _______, KC_MPLY, KC_MNXT, _______, _______, _______,                   _______, KC_PGDN, KC_PGUP, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
      ),

  /* Fn3
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |   7  |   8  |   9  |   0  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |   4  |   5  |   6  |   ,  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |   1  |   2  |   3  |   .  |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_FN3] = LAYOUT( \
      _______, _______, _______, _______, _______, _______,                   _______, KC_7,    KC_8,    KC_9,    KC_0,    _______, \
      _______, _______, _______, _______, _______, _______,                   _______, KC_4,    KC_5,    KC_6,    KC_COMM, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, KC_1,    KC_2,    KC_3,    KC_DOT,  _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
      )
};


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

struct keybuf {
  char col, row;
  char frame;
};
struct keybuf keybufs[256];
unsigned char keybuf_begin, keybuf_end;

#define COLOR_FRAME_SOLID 12
#define COLOR_FRAME_ERASE 24

#define COLOR_MAX 255
#define COLOR_DEFAULT 24
//#define COLOR_FN1_R 40
//#define COLOR_FN1_G 72
//#define COLOR_FN1_B 96
#define COLOR_FN1_R 0xFF
#define COLOR_FN1_G 0xFE
#define COLOR_FN1_B 0x3B
#define COLOR_FN2_R 48
#define COLOR_FN2_G 96
#define COLOR_FN2_B 32
#define COLOR_FN3_R 91
#define COLOR_FN3_G 83
#define COLOR_FN3_B 16

int global_color_r = COLOR_DEFAULT;
int global_color_g = COLOR_DEFAULT;
int global_color_b = COLOR_DEFAULT;

#define COLOR_DEFAULT_HUE 0
#define COLOR_DEFAULT_SAT 0
#define COLOR_DEFAULT_VAL 255
#define COLOR_ACCENT_HUE 0
#define COLOR_ACCENT_SAT 255
#define COLOR_ACCENT_VAL 255
#define COLOR_FN1_HUE 187
#define COLOR_FN1_SAT 255
#define COLOR_FN1_VAL 255
#define COLOR_FN2_HUE 54
#define COLOR_FN2_SAT 255
#define COLOR_FN2_VAL 255
#define COLOR_FN3_HUE 88
#define COLOR_FN3_SAT 255
#define COLOR_FN3_VAL 255

uint16_t global_hue = COLOR_DEFAULT_HUE;
uint8_t global_sat = COLOR_DEFAULT_SAT;
uint8_t global_val = COLOR_DEFAULT_VAL;

void change_global_color(uint16_t hue, uint8_t sat, uint8_t val) {
    global_hue = hue;
    global_sat = sat;
    global_val = val;
    //global_color_r = tmp_color_r;
    //global_color_g = tmp_color_g;
    //global_color_b = tmp_color_b;
    //rgblight_setrgb(tmp_color_r, tmp_color_g, tmp_color_b);
    rgblight_sethsv_noeeprom(hue, sat, val);
    //rgblight_set();
}

int col, row;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  col = record->event.key.col;
  row = record->event.key.row;
  if (record->event.pressed && ((row < 4 && is_master) || (row >= 4 && !is_master))) {
    int end = keybuf_end;
    keybufs[end].col = col;
    keybufs[end].row = row % 4;
    keybufs[end].frame = 0;
    keybuf_end ++;
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case FN1:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(16);
            change_global_color(COLOR_FN1_HUE, COLOR_FN1_SAT, COLOR_FN1_VAL);
          #endif
        }
        layer_on(_FN1);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
          change_global_color(COLOR_DEFAULT_HUE, COLOR_DEFAULT_SAT, COLOR_DEFAULT_VAL);
        #endif
        TOG_STATUS = false;
        layer_off(_FN1);
      }
      return false;
      break;
    case FN2:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(15);
            change_global_color(COLOR_FN2_HUE, COLOR_FN2_SAT, COLOR_FN2_VAL);
          #endif
        }
        layer_on(_FN2);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
          change_global_color(COLOR_DEFAULT_HUE, COLOR_DEFAULT_SAT, COLOR_DEFAULT_VAL);
        #endif
        layer_off(_FN2);
        TOG_STATUS = false;
      }
      return false;
      break;
    case FN3:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(15);
            change_global_color(COLOR_FN3_HUE, COLOR_FN3_SAT, COLOR_FN3_VAL);
          #endif
        }
        layer_on(_FN3);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
          change_global_color(COLOR_DEFAULT_HUE, COLOR_DEFAULT_SAT, COLOR_DEFAULT_VAL);
        #endif
        layer_off(_FN3);
        TOG_STATUS = false;
      }
      return false;
      break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
          change_global_color(COLOR_DEFAULT_HUE, COLOR_DEFAULT_SAT, COLOR_DEFAULT_VAL);
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// hook point for 'led_test' keymap
//   'default' keymap's led_test_init() is empty function, do nothing
//   'led_test' keymap's led_test_init() force rgblight_mode_noeeprom(35);
__attribute__ ((weak))
void led_test_init(void) {}

void led_custom_init(void) {
    static int scan_count = -16;
    if (scan_count == -1) {
      rgblight_enable_noeeprom();
      rgblight_mode(0);
      change_global_color(COLOR_DEFAULT_HUE, COLOR_DEFAULT_SAT, COLOR_DEFAULT_VAL);
    } else if (scan_count == 0) {
      for (unsigned char c=keybuf_begin; c!=keybuf_end; c++) {
        int i = c;
        int at = keybufs[i].row*6 + keybufs[i].col;

        LED_TYPE global_led;
        sethsv(global_hue, global_sat, global_val, &global_led);

        LED_TYPE accent_led;
        sethsv(COLOR_ACCENT_HUE, COLOR_ACCENT_SAT, COLOR_ACCENT_VAL, &accent_led);

        uint8_t color_r = accent_led.r;
        uint8_t color_g = accent_led.g;
        uint8_t color_b = accent_led.b;

        if ((keybufs[i].row & 1) == 0) {
            at += 5 - keybufs[i].col * 2;
        }

        if (keybufs[i].frame < COLOR_FRAME_SOLID + COLOR_FRAME_ERASE) {
          if (COLOR_FRAME_SOLID < keybufs[i].frame) {
            float step = ((float) (keybufs[i].frame - COLOR_FRAME_SOLID)) / COLOR_FRAME_ERASE;
            color_r -= (color_r - global_led.r) * step;
            color_g -= (color_g - global_led.g) * step;
            color_b -= (color_b - global_led.b) * step;
          }

          keybufs[i].frame ++;
        } else {
          color_r = global_led.r;
          color_g = global_led.g;
          color_b = global_led.b;
          keybuf_begin ++;
        }

        rgblight_setrgb_at((uint8_t) color_r, (uint8_t) color_g, (uint8_t) color_b, at);
      }
    }

    scan_count++;
    if (scan_count >= 16) { scan_count = 0; }
}

void matrix_scan_user(void) {
     //led_test_init();
     led_custom_init();
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_FN1 (1<<_FN1)
#define L_FN2 (1<<_FN2)
#define L_FN3 (1<<_FN3)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_FN1:
           matrix_write_P(matrix, PSTR("Fn1"));
           break;
        case L_FN2:
           matrix_write_P(matrix, PSTR("Fn2"));
           break;
        case L_FN3:
           matrix_write_P(matrix, PSTR("Fn3"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
