#include <pebble.h>
#include "atlas.h"

struct atlas {
  uint8_t ntiles;
  GBitmap *parent_bitmap;
  GBitmap *tiles[];
};

Atlas *atlas_create(uint32_t resource_id, GSize tile_size) {
  GBitmap *bitmap = gbitmap_create_with_resource(resource_id);
  GSize bitmap_size = bitmap->bounds.size;
  
  int ncols = bitmap_size.w / tile_size.w;
  int nrows = bitmap_size.h / tile_size.h;
  int ntiles = ncols * nrows;

  Atlas *atlas = malloc(sizeof(Atlas) + ntiles * sizeof(GBitmap *));
  atlas->parent_bitmap = bitmap;
  atlas->ntiles = ntiles;

  for (int i = 0; i < ntiles; ++i) {
    atlas->tiles[i] = gbitmap_create_as_sub_bitmap(bitmap, GRect(
      tile_size.w * (i % ncols),
      tile_size.h * (i / ncols),
      tile_size.w, tile_size.h));
  }
  
  return atlas;
}

void atlas_destroy(Atlas *atlas) {
  for (int i = 0; i < atlas->ntiles; ++i)
    gbitmap_destroy(atlas->tiles[i]);
  gbitmap_destroy(atlas->parent_bitmap);
}

GBitmap *atlas_get_tile(Atlas *atlas, uint8_t index) {
  if (index < atlas->ntiles)
    return atlas->tiles[index];
  else
    return NULL;
}