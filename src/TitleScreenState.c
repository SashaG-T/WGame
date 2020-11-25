#include "TitlescreenState.h"
#include "MainGameState.h"
#include "util.h"
#include <stdio.h>

static void init() {
    puts("Titlescreen Init!");
}

static void update(unsigned int elapsedTime) {
    #define TRANSITION_TIME 500
    static int screen = 0;
    static unsigned int timer = TRANSITION_TIME;
    if((timer += elapsedTime) >= TRANSITION_TIME) {
        timer -= TRANSITION_TIME;
        switch(screen) { 
            case 0: {
                drawWindow(0, 0, 19, 17);
                print(4, 6, "WGame Engine");
                print(4, 8, "Ver. a.0.1.0");
                e_renderScreen();
                screen++;
                break;
            }
            case 6: {
                drawWindow(0, 0, 19, 17);
                print(5, 6, "A Game By:");
                print(7, 8, "Sasha");
                print(1, 9, "Gervais-Tourangeau");
                e_renderScreen();
                screen++;
                break;
            }
            case 12: 
            case 13: {
                drawWindow(0, 0, 19, 17);
                e_draw(64, 40, 48); //P
                e_draw(65, 48, 48); //I
                e_draw(66, 56, 48); //N
                e_draw(67, 64, 48); //K
                e_draw(68, 88, 48); //D
                e_draw(69, 96, 48); //U
                e_draw(68, 104, 48); //D
                e_draw(70, 112, 48); //E
                if(screen == 13) {
                    print(3, 12, "~ Press Enter ~");
                    screen--;
                } else {
                    screen++;
                }
                e_renderScreen();
                break;
            }
            default: {screen++;}
        }
    }
    if(e_input.button.start && screen >= 12) {
        e_exitGameState();
        e_startGameState(MainGameState());
    }
}

static void cleanup() {
    puts("Titlescreen Cleanup!");
}

e_GameState* TitlescreenState() {
    static e_GameState gameState;
    e_initGameState(&gameState, &init, &update, &cleanup);
    return &gameState;
}