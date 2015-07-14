#include <pebble.h>
#include "font_small.h"
#include "atlas.h"

#define FONT_FIRST_CHAR ' '

#define FONT_CHAR_COUNT  96
#define FONT_CHAR_WIDTH   9
#define FONT_CHAR_HEIGHT  9

#define INVALID_CHAR (FONT_CHAR_COUNT - 1)

typedef struct charset_entry CharsetEntry;
struct charset_entry {
  char code;
  uint8_t width;
  GBitmap *bitmap;
};
  
struct bitmap_font {
  Atlas *atlas;
  GSize char_size;
  int nchars;
  CharsetEntry charset[];
};

BitmapFont *bfont_create(uint32_t resource_id, GSize char_size, const char *repertoire, uint8_t widths[]) {
  Atlas *atlas = atlas_create(resource_id, char_size);
  
  int nchars = strlen(repertoire);
  
  BitmapFont *font = malloc(sizeof(BitmapFont) + nchars * sizeof(CharsetEntry));
  font->atlas = atlas;
  font->char_size = char_size;
  font->nchars = nchars;
  
  for (int i = 0; i < nchars; ++i) {
    font->charset[i] = (CharsetEntry){ repertoire[i], widths[i], atlas_get_tile(atlas, i) };
  }
  
  return font;
}

void bfont_destroy(BitmapFont *font) {
  atlas_destroy(font->atlas);
  free(font);
}

static inline CharsetEntry *get_char(BitmapFont *font, char ch) {
  for (int i = 0; i < font->nchars; ++i) {
    CharsetEntry *info = font->charset + i;
    if (info->code == ch) return info;
  }
  return NULL;
}

uint8_t bfont_width(BitmapFont *font, const char *str) {
  uint8_t w = 0;
  while (*str) {
    w += get_char(font, *str)->width;
    ++str;
  }
  return w;
}

void bfont_draw(BitmapFont *font, GContext *ctx, const char *str, GPoint origin) {
  int x = origin.x;
  
  while (*str) {
    CharsetEntry *info = get_char(font, *str);
    graphics_draw_bitmap_in_rect(ctx, info->bitmap, GRect(x, origin.y, info->width, font->char_size.h));
    x += info->width;
    ++str;
  }
}
