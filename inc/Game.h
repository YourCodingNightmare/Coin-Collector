#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include "Entity.h"
#include "Text.h"

extern bool isRunning;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* main_font;
extern Entity player;
extern Entity coin;
extern int coins;
extern Text scoretext;
bool Game_Init();
void Game_Run();
void Game_End();
void Game_GetInput();
void Game_Update();
void Game_Render();
