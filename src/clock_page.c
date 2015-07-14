#include <pebble.h>
#include "font_small.h"
#include "clock.h"
#include "date.h"

static Layer *root_layer;

static BitmapLayer *logo_layer;
static GBitmap *logo_bitmap;

static Layer *time_layer;
static Layer *date_layer;

static void tick_cb(struct tm *tick_time, TimeUnits units_changed) {
  if (units_changed & MINUTE_UNIT) {
    time_set_time(tick_time);
    layer_mark_dirty(time_layer);
  }
  if (units_changed & DAY_UNIT) {
    date_set_time(tick_time);
    layer_mark_dirty(date_layer);
  }
}

void show_clock(Window *window) {
  clock_init();
  date_init();

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
  time_set_time(tick_time);
  date_set_time(tick_time);

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
  
  clock_fin();
  date_fin();
}