#include <pebble.h>

void atlas_load(uint32_t resource_id, GBitmap **atlas, GBitmap **tiles, uint8_t tile_count, GSize tile_size) {
  *atlas = gbitmap_create_with_resource(resource_id);
  GSize atlas_size = (*atlas)->bounds.size;
  
  int nrows = atlas_size.h / tile_size.h;
  
  for (int i = 0; i < tile_count; ++i) {
    tiles[i] = gbitmap_create_as_sub_bitmap(*atlas, GRect(
      atlas_size.w - (i / nrows + 1) * tile_size.w,
      i * tile_size.h % atlas_size.h,
      tile_size.w,
      tile_size.h));
  }
}

void atlas_destroy(GBitmap *atlas, GBitmap **tiles, uint8_t tile_count) {
  for (int i = 0; i < tile_count; ++i)
    gbitmap_destroy(tiles[i]);
  gbitmap_destroy(atlas);

}