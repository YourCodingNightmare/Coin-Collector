#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include "Entity.h"
#include "Text.h"
#include "Timer.h"

extern bool isRunning;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* main_font;
extern Entity player;
extern Entity coin;
extern int coins;
extern Text CoinsStat;

extern Timer countdown;
extern Text countdownText;
extern int timeLeft;

extern Text gameoverText;
extern Text finalScore;
extern Text restartText;
bool Game_Init();
void Game_Run();
void Game_End();
void Game_GetInput();
void Game_Update();
void Game_Render();
