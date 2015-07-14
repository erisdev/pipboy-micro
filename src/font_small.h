#pragma once
#include <pebble.h>

typedef struct bitmap_font BitmapFont;

BitmapFont *bfont_create(uint32_t resource_id, GSize char_size, const char *charset, uint8_t char_widths[]);
void bfont_destroy(BitmapFont *font);

uint8_t bfont_width(BitmapFont *font, const char *str);
void bfont_draw(BitmapFont *font, GContext *ctx, const char *str, GPoint origin);

BitmapFont *small_font;
BitmapFont *clock_font;

static inline void bfonts_init() {
  static const char *small_font_repertoire =
    " !\"#$%&'()*+,-./"
    "0123456789:;<=>?"
    "@ABCDEFGHIJKLMNO"
    "PQRSTUVWXYZ[\\]^_"
    "`abcdefghijklmno"
    "pqrstuvwxyz{|}~";
  static uint8_t small_font_widths[] = {
    4, 3, 6, 8, 7, 9, 8, 4, 5, 5, 8, 7, 4, 7, 4, 8,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 4, 6, 7, 6, 7,
    8, 9, 8, 7, 8, 7, 7, 8, 8, 3, 8, 8, 7, 8, 8, 8,
    8, 8, 8, 8, 7, 8, 9, 8, 9, 9, 8, 5, 8, 5, 8, 7,
    4, 7, 7, 6, 7, 7, 6, 7, 7, 3, 6, 7, 3, 8, 7, 7,
    7, 7, 6, 7, 7, 7, 8, 8, 7, 7, 7, 6, 0, 6, 7, 9
  };
  
  static const char *clock_font_repertoire =
    "0123456789:";
  static uint8_t clock_font_widths[] = {
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 4};
    
  small_font = bfont_create(RESOURCE_ID_IMG_FONT_SMALL,
    GSize(9, 9), small_font_repertoire, small_font_widths);
  
  clock_font = bfont_create(RESOURCE_ID_IMG_CLOCK,
    GSize(12, 24), clock_font_repertoire, clock_font_widths);
}

static inline void bfonts_fin() {
  bfont_destroy(small_font);
  bfont_destroy(clock_font);
}