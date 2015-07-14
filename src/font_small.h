#pragma once
#include <pebble.h>

void font_small_init();
void font_small_fin();

uint8_t font_width(const char *str);
void font_small_draw(GContext *ctx, const char *str, GPoint origin);
