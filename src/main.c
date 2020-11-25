#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

#include "TitlescreenState.h"

int main(int argc, char* argv[]) {

    if(e_init("🎮 WGame Engine", "Resources/Tileset.png")) {
        e_startGameState(TitlescreenState());
        emscripten_set_main_loop(e_gameLoop, 60, 1);
    } else {
        puts("Error: Failed to initialize engine!");
    }
    e_cleanup();

    return 0;
}