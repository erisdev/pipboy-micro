#pragma once
#include <pebble.h>

void atlas_load(uint32_t resource_id, GBitmap **atlas, GBitmap **items, uint8_t item_count, GSize item_size);
void atlas_destroy(GBitmap *atlas, GBitmap **items, uint8_t item_count);