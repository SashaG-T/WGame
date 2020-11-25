#ifndef ENGINE_H_
    #define ENGINE_H_

#define H_FLIP(T) (T+e_hBaseTile)
#define V_FLIP(T) (T+e_vBaseTile)
#define HV_FLIP(T) (T+e_hvBaseTile)

typedef unsigned int e_TILE;
extern e_TILE e_hBaseTile;
extern e_TILE e_vBaseTile;
extern e_TILE e_hvBaseTile;
extern e_TILE e_maxTile;

typedef union _e_Input {
    unsigned char state;
    struct Button {
        unsigned char up:1;
        unsigned char down:1;
        unsigned char left:1;
        unsigned char right:1;
        unsigned char a:1;
        unsigned char b:1;
        unsigned char start:1;
        unsigned char select:1;
    } button;
} e_Input;

extern e_Input e_input;

typedef struct _e_Output {
    char screen[360];
} e_Output;

extern e_Output e_output;

typedef struct _e_GameState {
    void (*init)();
    void (*update)(unsigned int);
    void (*cleanup)();
    struct _e_GameState* previousGameState;
} e_GameState;

void e_initGameState(e_GameState* gameState, void (*init)(), void (*update)(unsigned int), void (*cleanup)());
void e_startGameState(e_GameState* gameState);
void e_exitGameState();
void e_exitAllGameStates();
int e_init(const char* title, const char* tilesetFilename);
void e_gameLoop();
void e_cleanup();

void e_draw(e_TILE tile, int dx, int dy);
void e_clearScreen();
void e_renderScreen();

#endif