#include <pebble.h>
#include "date.h"
#include "font_small.h"

static char text_buffer[33];

void date_init() {
  
}

void date_fin() {
  
}

void date_set_time(struct tm *tick_time) {
  strftime(text_buffer, sizeof(text_buffer), "%d %b. %Y", tick_time);
}

void date_draw_cb(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
  font_small_draw(ctx, text_buffer, GPoint(0, 0));
}
