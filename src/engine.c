#include "engine.h"

#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* tilesetTexture;
unsigned int tilesPerRow;
unsigned int tilesPerCol;

e_TILE e_hBaseTile;
e_TILE e_vBaseTile;
e_TILE e_hvBaseTile;
e_TILE e_maxTile;

e_Input e_input;
e_GameState *currGameState;

void e_initGameState(e_GameState* gameState, void (*init)(), void (*update)(unsigned int), void (*cleanup)()) {
    assert(update != 0);
    gameState->init = init;
    gameState->update = update;
    gameState->cleanup = cleanup;
    gameState->previousGameState = 0;
}

void e_startGameState(e_GameState* gameState) {
    assert(gameState != 0);
    gameState->previousGameState = currGameState;
    currGameState = gameState;
    if(currGameState->init) {
        currGameState->init();
    }
}

void e_exitGameState() {
    if(currGameState->cleanup) {
        currGameState->cleanup();
    }
    currGameState = currGameState->previousGameState;
}

void e_exitAllGameStates() {
    while(currGameState) {
        e_exitGameState();
    }
}

int e_init(const char* title, const char* tilesetFilename) {
    int success = 1;
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Failed to init SDL: %s\n", SDL_GetError());
        success = 0;
    } else {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 576, 0);
        if(window == 0) {
            printf("Failed to create window: %s\n", SDL_GetError());
            success = 0;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == 0) {
                printf("Failed to create renderer: %s\n", SDL_GetError());
                success = 0;
            } else {
                SDL_RenderSetLogicalSize(renderer, 160, 144);
                SDL_Surface* surface = IMG_Load(tilesetFilename);
                if(surface == 0) {
                    printf("Failed to load tileset: %s\n", IMG_GetError());
                    success = 0;
                } else {
                    tilesPerRow = surface->w / 8;
                    tilesPerCol = surface->h / 8;
                    e_hBaseTile = tilesPerRow * tilesPerCol;
                    e_vBaseTile = e_hBaseTile * 2;
                    e_hvBaseTile = e_hBaseTile * 3;
                    e_maxTile = e_hBaseTile * 4;

                    printf("Tileset Flip Offsets: %u - %u - %u - %u\n", e_hBaseTile, e_vBaseTile, e_hvBaseTile, e_maxTile);
                    tilesetTexture = SDL_CreateTextureFromSurface(renderer, surface);
                    if(tilesetTexture == 0) {
                        printf("Failed to create tileset texture: %s\n", SDL_GetError());
                        success = 0;
                    }
                    SDL_FreeSurface(surface);
                    e_input.state = 0x00;

                }
            }
        }
    }
    return success;
}

void e_cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void e_draw(e_TILE tile, int x, int y) {
    tile %= e_maxTile;
    SDL_RendererFlip flip = 0;
    if(tile < e_hBaseTile) {
        flip = SDL_FLIP_NONE;
    } else if(tile < e_vBaseTile) {
        flip |= SDL_FLIP_HORIZONTAL;
    } else if(tile < e_hvBaseTile) {
        flip |= SDL_FLIP_VERTICAL;
    } else {
        flip |= SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
    }
    tile %= e_hBaseTile;
    SDL_Rect src = {(tile % tilesPerRow) * 8, (tile / tilesPerRow) * 8, 8, 8};
    SDL_Rect dst = {x, y, 8, 8};
    SDL_RenderCopyEx(renderer, tilesetTexture, &src, &dst, 0.0, 0, flip);
}

void e_clearScreen() {
    SDL_RenderClear(renderer);
}

void e_renderScreen() {
    SDL_RenderPresent(renderer);
}

void e_handleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT: {
                e_exitAllGameStates();
                break;
            }
            case SDL_KEYDOWN: {
                if(!event.key.repeat) {
                    switch(event.key.keysym.sym) {
                        case SDLK_UP: {
                            e_input.button.up = 1;
                            break;
                        }
                        case SDLK_DOWN: {
                            e_input.button.down = 1;
                            break;
                        }
                        case SDLK_LEFT: {
                            e_input.button.left = 1;
                            break;
                        }
                        case SDLK_RIGHT: {
                            e_input.button.right = 1;
                            break;
                        }
                        case SDLK_z: {
                            e_input.button.a = 1;
                            break;
                        }
                        case SDLK_x: {
                            e_input.button.b = 1;
                            break;
                        }
                        case SDLK_RETURN: {
                            e_input.button.start = 1;
                            break;
                        }
                        case SDLK_ESCAPE: {
                            e_input.button.select = 1;
                            break;
                        }
                    }
                }
                break;
            }
            case SDL_KEYUP: {
                switch(event.key.keysym.sym) {
                        case SDLK_UP: {
                            e_input.button.up = 0;
                            break;
                        }
                        case SDLK_DOWN: {
                            e_input.button.down = 0;
                            break;
                        }
                        case SDLK_LEFT: {
                            e_input.button.left = 0;
                            break;
                        }
                        case SDLK_RIGHT: {
                            e_input.button.right = 0;
                            break;
                        }
                        case SDLK_z: {
                            e_input.button.a = 0;
                            break;
                        }
                        case SDLK_x: {
                            e_input.button.b = 0;
                            break;
                        }
                        case SDLK_RETURN: {
                            e_input.button.start = 0;
                            break;
                        }
                        case SDLK_ESCAPE: {
                            e_input.button.select = 0;
                            break;
                        }
                }
                break;
            }
        }
    }
}

void e_gameLoop() {
    static unsigned int t1 = 0;
    static unsigned int t2 = 0;
    currGameState->update(t2 - t1);
    e_handleEvents();
    t1 = t2;
    t2 = SDL_GetTicks();
}