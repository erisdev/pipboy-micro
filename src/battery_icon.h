#pragma once
#include <pebble.h>

void status_icons_init();
void status_icons_fin();

GBitmap *battery_icon_get(BatteryChargeState battery);
GBitmap *bluetooth_icon_get(bool connected);
