#include <pebble.h>
#include "battery_icon.h"
#include "atlas.h"
#include "useful.h"

#define BATTERY_ICON_WIDTH  13
#define BATTERY_ICON_HEIGHT  8

#define BLUETOOTH_ICON_WIDTH  8
#define BLUETOOTH_ICON_HEIGHT 7

static Atlas *battery_icons;
static Atlas *bluetooth_icons;
  
void status_icons_init() {
  battery_icons = atlas_create(RESOURCE_ID_IMG_BATTERY,
    GSize(BATTERY_ICON_WIDTH, BATTERY_ICON_HEIGHT));
  bluetooth_icons = atlas_create(RESOURCE_ID_IMG_BLUETOOTH,
    GSize(BLUETOOTH_ICON_WIDTH, BLUETOOTH_ICON_HEIGHT));
}

void status_icons_fin() {
  atlas_destroy(battery_icons);
  atlas_destroy(bluetooth_icons);
}

GBitmap *battery_icon_get(BatteryChargeState battery) {
  return atlas_get_tile(battery_icons,
    min(9, battery.charge_percent / 10)
    + (battery.is_charging ? 10 : 0));
}

GBitmap *bluetooth_icon_get(bool connected) {
  return atlas_get_tile(bluetooth_icons, connected ? 1 : 0);
}