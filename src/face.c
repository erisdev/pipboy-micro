#include <pebble.h>
#include "font_small.h"
#include "battery_icon.h"
#include "clock.h"
#include "date.h"

static Window *face;

static BitmapLayer *battery_icon_layer;
static BitmapLayer *bluetooth_icon_layer;

static BitmapLayer *background_layer;
static GBitmap *background_bitmap;

static Layer *clock_layer;
static Layer *date_layer;

static void tick_cb(struct tm *tick_time, TimeUnits units_changed) {
  if (units_changed & MINUTE_UNIT) {
    clock_set_time(tick_time);
    layer_mark_dirty(clock_layer);
  }
  if (units_changed & DAY_UNIT) {
    date_set_time(tick_time);
    layer_mark_dirty(date_layer);
  }
}

static void battery_cb(BatteryChargeState battery) {
  bitmap_layer_set_bitmap(battery_icon_layer, battery_icon_get(battery));
}

static void bluetooth_cb(bool connected) {
  bitmap_layer_set_bitmap(bluetooth_icon_layer, bluetooth_icon_get(connected));
}

static void face_load(Window *face) {
  background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMG_BACKGROUND);
  background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(background_layer, background_bitmap);
  layer_add_child(
    window_get_root_layer(face),
    bitmap_layer_get_layer(background_layer));

  battery_icon_layer = bitmap_layer_create(GRect(133, 151, 7, 13));
  layer_add_child(
    window_get_root_layer(face),
    bitmap_layer_get_layer(battery_icon_layer));

  bluetooth_icon_layer = bitmap_layer_create(GRect(133, 111, 7, 8));
  layer_add_child(
    window_get_root_layer(face),
    bitmap_layer_get_layer(bluetooth_icon_layer));
  
  clock_layer = layer_create(GRect(25, 58, 24, 52));
  layer_set_update_proc(clock_layer, clock_draw_cb);
  layer_add_child(
    window_get_root_layer(face),
    clock_layer);
  
  date_layer = layer_create(GRect(131, 5, 9, 74));
  layer_set_update_proc(date_layer, date_draw_cb);
  layer_add_child(
    window_get_root_layer(face),
    date_layer);
  
  time_t tmp = time(NULL);
  struct tm *tick_time = localtime(&tmp);
  clock_set_time(tick_time);
  date_set_time(tick_time);
  
  battery_cb(battery_state_service_peek());
  bluetooth_cb(bluetooth_connection_service_peek());
}

static void face_unload(Window *face) {
  layer_remove_child_layers(window_get_root_layer(face));
  bitmap_layer_destroy(battery_icon_layer);
  bitmap_layer_destroy(bluetooth_icon_layer);
  layer_destroy(clock_layer);
  layer_destroy(date_layer);
}

static void app_init() {
  face = window_create();
  window_set_window_handlers(face, (WindowHandlers) {
    .load = face_load,
    .unload = face_unload
  });

  window_stack_push(face, true);

  tick_timer_service_subscribe(MINUTE_UNIT | DAY_UNIT, tick_cb);
  battery_state_service_subscribe(battery_cb);
  bluetooth_connection_service_subscribe(bluetooth_cb);
}

static void app_fin() {
  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();

  bitmap_layer_destroy(background_layer);
  gbitmap_destroy(background_bitmap);

  window_destroy(face);
}

int main(void) {
  status_icons_init();
  clock_init();
  date_init();
  font_small_init();

  app_init();
  app_event_loop();
  app_fin();

  status_icons_fin();
  clock_fin();
  date_fin();
  font_small_fin();

  return 0;
}
