#pragma once
#include <pebble.h>

void clock_init();
void clock_fin();

void time_set_time(struct tm *tick_time);

void time_draw_cb(Layer *layer, GContext *ctx);
