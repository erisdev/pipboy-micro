#include <pebble.h>
#include "font_small.h"
#include "atlas.h"

#define FONT_FIRST_CHAR ' '

#define FONT_CHAR_COUNT  96
#define FONT_CHAR_WIDTH   9
#define FONT_CHAR_HEIGHT  9

GBitmap *font_atlas;
GBitmap *font_chars[FONT_CHAR_COUNT];

/* yuck that these are hardcoded but who wants to do image analysis */
uint8_t font_widths[FONT_CHAR_COUNT] = {
  4, 3, 6, 8, 7, 9, 8, 4, 5, 5, 8, 7, 4, 7, 4, 8,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 4, 6, 7, 6, 7,
  8, 9, 8, 7, 8, 7, 7, 8, 8, 3, 8, 8, 7, 8, 8, 8,
  8, 8, 8, 8, 7, 8, 9, 8, 9, 9, 8, 5, 8, 5, 8, 7,
  4, 7, 7, 6, 7, 7, 6, 7, 7, 3, 6, 7, 3, 8, 7, 7,
  7, 7, 6, 7, 7, 7, 8, 8, 7, 7, 7, 6, 0, 6, 7, 9
};

void font_small_init() {
  atlas_load(RESOURCE_ID_IMG_FONT_SMALL, &font_atlas, font_chars,
    FONT_CHAR_COUNT, GSize(FONT_CHAR_HEIGHT, FONT_CHAR_WIDTH));
}

void font_small_fin() {
  atlas_destroy(font_atlas, font_chars, FONT_CHAR_COUNT);
}

static inline GBitmap *get_char(char ch) {
  uint8_t i = ch - (uint8_t)FONT_FIRST_CHAR;
  return font_chars[i >= FONT_CHAR_COUNT ? FONT_CHAR_COUNT - 1 : i];
}

static inline uint8_t char_width(char ch) {
  uint8_t i = ch - (uint8_t)FONT_FIRST_CHAR;
  return font_widths[i >= FONT_CHAR_COUNT ? FONT_CHAR_COUNT - 1 : i];
}

uint8_t font_width(const char *str) {
  uint8_t w = 0;
  while (*str) {
    w += char_width(*str);
    ++str;
  }
  return w;
}

void font_small_draw(GContext *ctx, const char *str, GPoint origin) {
  int x = origin.x, y = origin.y;
  
  while (*str) {
    int w = char_width(*str);
    graphics_draw_bitmap_in_rect(ctx, get_char(*str), GRect(x, y, FONT_CHAR_HEIGHT, w));
    y += w;
    ++str;
  }
}
