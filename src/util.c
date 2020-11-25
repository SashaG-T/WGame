#include "util.h"
#include "engine.h"

void drawWindow(int x, int y, int w, int h) {
    e_draw(129, x * 8, y * 8);
    e_draw(130, (x + w) * 8, y * 8);
    e_draw(131, x * 8, (y + h) * 8);
    e_draw(132, (x + w) * 8, (y + h) * 8);
    for(int i = 1; i < w; i++) {
        e_draw(133, (x + i) * 8, y * 8);
        e_draw(133, (x + i) * 8, (y + h) * 8);
    }
    for(int j = 1; j < h; j++) {
        e_draw(134, x * 8, (y + j) * 8);
        e_draw(134, (x + w) * 8, (y + j) * 8);
    }
    for(int j = 1; j < h; j++) {
        for(int i = 1; i < w; i++) {
            e_draw(135, (x + i) * 8, (y + j) * 8);
        }
    }
}

void print(int x, int y, const char* text) {
    const char* c = text;
    y *= 8;
    while(*c) {
        e_draw(*c++ + 128, x++ * 8, y);
    }
}