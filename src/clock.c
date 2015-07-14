#include <pebble.h>
#include "atlas.h"

#define CLOCK_CHAR_COUNT  10
#define CLOCK_CHAR_WIDTH  12
#define CLOCK_CHAR_HEIGHT 24

static GBitmap *clock_atlas;
static GBitmap *clock_chars[CLOCK_CHAR_COUNT];

static uint8_t hour, minute;

void clock_init() {
  atlas_load(RESOURCE_ID_IMG_CLOCK, &clock_atlas, clock_chars,
    CLOCK_CHAR_COUNT, GSize(CLOCK_CHAR_HEIGHT, CLOCK_CHAR_WIDTH));
}

void clock_fin() {
  atlas_destroy(clock_atlas, clock_chars, CLOCK_CHAR_COUNT);
}

void clock_set_time(struct tm *tick_time) {
  hour = tick_time->tm_hour;
  minute = tick_time->tm_min;
}

static inline GBitmap *get_digit(uint8_t n) {
  return clock_chars[n > 9 ? 9 : n];
}

void clock_draw_cb(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
  graphics_draw_bitmap_in_rect(ctx, get_digit(hour   / 10), GRect(0,  0, 24, 12));
  graphics_draw_bitmap_in_rect(ctx, get_digit(hour   % 10), GRect(0, 12, 24, 12));
  graphics_draw_bitmap_in_rect(ctx, get_digit(minute / 10), GRect(0, 28, 24, 12));
  graphics_draw_bitmap_in_rect(ctx, get_digit(minute % 10), GRect(0, 40, 24, 12));
}