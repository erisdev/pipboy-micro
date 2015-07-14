#include <pebble.h>
#include "battery_icon.h"
#include "atlas.h"

#define BATTERY_ICON_COUNT  10
#define BATTERY_ICON_WIDTH   7
#define BATTERY_ICON_HEIGHT 13

static GBitmap *battery_atlas;
static GBitmap *battery_icons[BATTERY_ICON_COUNT];

#define BLUETOOTH_ICON_COUNT  2
#define BLUETOOTH_ICON_WIDTH  7
#define BLUETOOTH_ICON_HEIGHT 8

static GBitmap *bluetooth_atlas;
static GBitmap *bluetooth_icons[BLUETOOTH_ICON_COUNT];
  
void status_icons_init() {
  atlas_load(RESOURCE_ID_IMG_BATTERY, &battery_atlas, battery_icons,
    BATTERY_ICON_COUNT, GSize(BATTERY_ICON_WIDTH, BATTERY_ICON_HEIGHT));
  atlas_load(RESOURCE_ID_IMG_BLUETOOTH, &bluetooth_atlas, bluetooth_icons,
    BLUETOOTH_ICON_COUNT, GSize(BLUETOOTH_ICON_WIDTH, BLUETOOTH_ICON_HEIGHT));
}

void status_icons_fin() {
  atlas_destroy(battery_atlas, battery_icons, BATTERY_ICON_COUNT);
  atlas_destroy(bluetooth_atlas, bluetooth_icons, BLUETOOTH_ICON_COUNT);
}

GBitmap *battery_icon_get(BatteryChargeState battery) {
  uint8_t i = battery.charge_percent / 10;
  return battery_icons[i < BATTERY_ICON_COUNT ? i : BATTERY_ICON_COUNT - 1];
}

GBitmap *bluetooth_icon_get(bool connected) {
  return bluetooth_icons[connected ? 1 : 0];
}