#pragma once
#include <pebble.h>
  
void date_init();
void date_fin();

void date_set_time(struct tm *tick_time);

void date_draw_cb(Layer *layer, GContext *ctx);
