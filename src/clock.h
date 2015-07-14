#pragma once
#include <pebble.h>

void clock_init();
void clock_fin();

void clock_set_time(struct tm *tick_time);

void clock_draw_cb(Layer *layer, GContext *ctx);
