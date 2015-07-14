#include <pebble.h>
#include "font_small.h"

static Layer *root_layer;

static BitmapLayer *logo_layer;
static GBitmap *logo_bitmap;

static Layer *time_layer;
static char time_text_buffer[6];

static Layer *date_layer;
static char date_text_buffer[13];

static void tick_cb(struct tm *tick_time, TimeUnits units_changed) {
  if (units_changed & MINUTE_UNIT) {
    strftime(time_text_buffer, sizeof(time_text_buffer), "%H:%M", tick_time);
    layer_mark_dirty(time_layer);
  }
  if (units_changed & DAY_UNIT) {
    strftime(date_text_buffer, sizeof(date_text_buffer), "%d %b. %Y", tick_time);
    layer_mark_dirty(date_layer);
  }
}

static void time_draw_cb(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
  
  bfont_draw(clock_font, ctx, time_text_buffer, GPoint(0, 0));
}

static void date_draw_cb(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  int x = (bounds.size.w - bfont_width(small_font, date_text_buffer)) / 2;
  
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  
  bfont_draw(small_font, ctx, date_text_buffer, GPoint(x, 0));
}

void show_clock(Window *window) {
  root_layer = layer_create(GRect(0, 0, 144, 168));
  layer_add_child(window_get_root_layer(window), root_layer);
  
  logo_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMG_LOGO_VAULTTEC);
  logo_layer = bitmap_layer_create(GRect(4, 24, 136, 63));
  bitmap_layer_set_bitmap(logo_layer, logo_bitmap);
  layer_add_child(root_layer, bitmap_layer_get_layer(logo_layer));
  
  time_layer = layer_create(GRect(46, 98, 52, 24));
  layer_set_update_proc(time_layer, time_draw_cb);
  layer_add_child(root_layer, time_layer);
  
  date_layer = layer_create(GRect(24, 134, 96, 8));
  layer_set_update_proc(date_layer, date_draw_cb);
  layer_add_child(root_layer, date_layer);
  
  time_t tmp = time(NULL);
  struct tm *tick_time = localtime(&tmp);
  tick_cb(tick_time, MINUTE_UNIT | DAY_UNIT);
  
  tick_timer_service_subscribe(MINUTE_UNIT | DAY_UNIT, tick_cb);
}

void hide_clock() {
  tick_timer_service_unsubscribe();
  
  layer_remove_child_layers(root_layer);
  layer_destroy(root_layer);

  bitmap_layer_destroy(logo_layer);
  layer_destroy(time_layer);
  layer_destroy(date_layer);
  
  gbitmap_destroy(logo_bitmap);
}