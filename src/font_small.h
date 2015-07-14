#pragma once
#include <pebble.h>

void font_small_init();
void font_small_fin();

void font_small_draw(GContext *ctx, const char *str, GPoint origin);
