#include <pebble.h>
#include "atlas.h"
#include "bfont.h"
#include "useful.h"

static Window *face;

static Atlas *battery_icons;
static Atlas *bluetooth_icons;

static BitmapLayer *battery_icon_layer;
static BitmapLayer *bluetooth_icon_layer;

static BitmapLayer *background_layer;
static GBitmap *background_bitmap;

void show_clock(Window *window);
void hide_clock();

static void battery_cb(BatteryChargeState battery) {
  GBitmap *icon = atlas_get_tile(battery_icons,
    min(9, battery.charge_percent / 10) + (battery.is_charging ? 10 : 0));
  bitmap_layer_set_bitmap(battery_icon_layer, icon);
}

static void bluetooth_cb(bool connected) {
  GBitmap *icon = atlas_get_tile(bluetooth_icons, connected ? 1 : 0);
  bitmap_layer_set_bitmap(bluetooth_icon_layer, icon);
}

static void face_load(Window *face) {
  bfonts_init();

  battery_icons = atlas_create(RESOURCE_ID_IMG_BATTERY, GSize(13, 8));
  bluetooth_icons = atlas_create(RESOURCE_ID_IMG_BLUETOOTH, GSize(8, 7));
  
  background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMG_BACKGROUND);
  background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(background_layer, background_bitmap);
  layer_add_child(
    window_get_root_layer(face),
    bitmap_layer_get_layer(background_layer));

  battery_icon_layer = bitmap_layer_create(GRect(126, 4, 12, 7));
  layer_add_child(
    window_get_root_layer(face),
    bitmap_layer_get_layer(battery_icon_layer));

  bluetooth_icon_layer = bitmap_layer_create(GRect(87, 4, 7, 7));
  layer_add_child(
    window_get_root_layer(face),
    bitmap_layer_get_layer(bluetooth_icon_layer));
  
  // why do these need to be called manually?
  // event services please send initialization events
  battery_cb(battery_state_service_peek());
  bluetooth_cb(bluetooth_connection_service_peek());
  
  battery_state_service_subscribe(battery_cb);
  bluetooth_connection_service_subscribe(bluetooth_cb);

  show_clock(face);
}

static void face_unload(Window *face) {
  hide_clock();
  
  battery_state_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();

  layer_remove_child_layers(window_get_root_layer(face));
  bitmap_layer_destroy(battery_icon_layer);
  bitmap_layer_destroy(bluetooth_icon_layer);
  bitmap_layer_destroy(background_layer);

  gbitmap_destroy(background_bitmap);
  atlas_destroy(battery_icons);
  atlas_destroy(bluetooth_icons);

  bfonts_fin();
}

int main(void) {
  face = window_create();
  window_set_window_handlers(face, (WindowHandlers) {
    .load = face_load,
    .unload = face_unload
  });
  window_stack_push(face, false);

  app_event_loop();

  window_destroy(face);

  return 0;
}
