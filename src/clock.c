#include <pebble.h>
#include "atlas.h"

#define CLOCK_CHAR_WIDTH  12
#define CLOCK_CHAR_HEIGHT 24

static Atlas *clock_chars;

static uint8_t hour, minute;

void clock_init() {
  clock_chars = atlas_create(RESOURCE_ID_IMG_CLOCK,
    GSize(CLOCK_CHAR_WIDTH, CLOCK_CHAR_HEIGHT));
}

void clock_fin() {
  atlas_destroy(clock_chars);
}

void time_set_time(struct tm *tick_time) {
  hour = tick_time->tm_hour;
  minute = tick_time->tm_min;
}

static inline GBitmap *get_digit(uint8_t n) {
  return atlas_get_tile(clock_chars, n);
}

void time_draw_cb(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
  graphics_draw_bitmap_in_rect(ctx, get_digit(hour   / 10), GRect( 0, 0, 12, 24));
  graphics_draw_bitmap_in_rect(ctx, get_digit(hour   % 10), GRect(12, 0, 12, 24));
  graphics_draw_bitmap_in_rect(ctx, get_digit(10),          GRect(24, 0,  4, 24));
  graphics_draw_bitmap_in_rect(ctx, get_digit(minute / 10), GRect(28, 0, 12, 24));
  graphics_draw_bitmap_in_rect(ctx, get_digit(minute % 10), GRect(40, 0, 12, 24));
}