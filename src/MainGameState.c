#include "MainGameState.h"

static void update(unsigned int elapsedTime) {
    static unsigned int timer = 0;
    if((timer += elapsedTime) >= 25) {
        timer -= 100;
        static int x = 8;
        static int inc = 1;
        if(x >= 152) inc = -1;
        else if(x <= 8) inc = 1;
        e_clearScreen();
        e_draw(1 + (inc < 0 ? e_hBaseTile : 0), x += inc, 80);
        e_renderScreen();
    }
}

e_GameState* MainGameState() {
    static e_GameState gameState;
    e_initGameState(&gameState, 0, &update, 0);
    return &gameState;
}