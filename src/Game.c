#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "Entity.h"
#include "Text.h"
#include "Timer.h"

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
bool isRunning = false;
TTF_Font* main_font = NULL;
Entity player;
Entity coin;
int coins;
Text CoinsStat;

Timer countdown;
Text countdownText;
int timeLeft;

Text gameoverText;
Text finalScore;
Text restartText;

bool Game_Init(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL GAME INIT ERROR: %s\n", SDL_GetError());
        return false;
    }
    if (TTF_Init() < 0){
        printf("TTF INIT ERROR: %s\n", TTF_GetError());
        SDL_Quit();
        return false;
    }
    window = SDL_CreateWindow("COIN COLLECTOR",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, 
        SDL_WINDOW_SHOWN);
    if (!window){
        printf("SDL WINDOW INIT ERROR: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        SDL_DestroyWindow(window);
        printf("SDL RENDERER INIT ERROR: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    main_font = TTF_OpenFont("assets/font/PressStart2P-Regular.ttf", 20);
    if (!main_font){
        printf("TTF FONT INIT ERROR: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    srand(time(NULL));

    Entity_Init(&player, 320, 240, 20, 20);
    Entity_Init(&coin, rand() % (640-20), rand() % (480-20), 20, 20);

    coins = 0;
    Text_Init(renderer, main_font, &CoinsStat, "Coins: %d", coins);
    
    countdown = Timer_Start(5);
    timeLeft = Timer_Left(&countdown);
    Text_Init(renderer, main_font, &countdownText, "Time Left: %d", timeLeft);
    isRunning = true;

    Text_Init(renderer, main_font, &gameoverText, "Game Over!");
    Text_Init(renderer, main_font, &finalScore, "Final Coins: %d", coins);
    Text_Init(renderer, main_font, &restartText, "Press SPACE to restart");
    return true;
}
void Game_Run(){
    while (isRunning){
        Game_GetInput();
        Game_Update();
        Game_Render();
        SDL_Delay(16);
    }
}
void Game_End(){
    Text_DestroyTexture(&CoinsStat);
    TTF_CloseFont(main_font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
}
void Game_GetInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            isRunning = 0;
        }
        if (event.type == SDL_KEYDOWN){
            if (event.key.keysym.sym == SDLK_SPACE){
                if (timeLeft <= 0){
                    coins = 0;
                    Text_Modify(renderer, main_font, &CoinsStat, "Coins: %d", coins);
                    player.body.x = 320;
                    player.body.y = 240;
                    
                    coin.body.x = rand() % (640-20);
                    coin.body.y = rand() % (480-20);
                    countdown = Timer_Start(60);
                    timeLeft = Timer_Left(&countdown);
                }
            }
        }
    }
    Entity_MoveBy_UIN(&player, 5, 640, 480);
    
}
void Game_Update(){
    if (timeLeft > 0){
        timeLeft = Timer_Left(&countdown);
        Text_Modify(renderer, main_font, &countdownText, "Time Left: %d", timeLeft);
        if (SDL_HasIntersection(&player.body, &coin.body)){
            coins++;
            coin.body.x = rand() % (640-20);
            coin.body.y = rand() % (480-20);

            Text_Modify(renderer, main_font, &CoinsStat, "Coins: %d", coins);
        }
    }
} 
void Game_Render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (timeLeft > 0){
        Entity_Draw(renderer, &player, 0, 255, 0);
        Entity_Draw(renderer, &coin, 255, 255, 0);
        Text_Draw(renderer, &CoinsStat, 10, 10);

        Text_Draw(renderer, &countdownText, 370, 10);
    } else {
        Text_Draw(renderer, &gameoverText, 220, 160);
        Text_Modify(renderer, main_font, &finalScore, "Final Coins: %d", coins);
        Text_Draw(renderer, &finalScore, 180, 220);
        Text_Draw(renderer, &restartText, 120, 280);
    }
    
    SDL_RenderPresent(renderer);
}
