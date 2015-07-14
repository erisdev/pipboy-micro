#pragma once
#include <pebble.h>

typedef struct atlas Atlas;
  
Atlas *atlas_create(uint32_t resource_id, GSize tile_size);
void atlas_destroy(Atlas *atlas);

GBitmap *atlas_get_tile(Atlas *atlas, uint8_t index);