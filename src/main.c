#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Entity.h"
#include "Text.h"

int main(int argc, char* argv[]){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("\033[31mERROR: %s\033[0m\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() < 0){
        printf("\033[31mTTF ERROR: %s\033[0m\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("MOVEMENT", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        640, 480, 
        SDL_WINDOW_SHOWN);
    if (!window){
        printf("\033[31mERROR: %s\033[0m\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        printf("\033[31mERROR: %s\033[0m\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font* main_font = TTF_OpenFont("assets/font/PressStart2P-Regular.ttf", 20);
    if (!main_font){
        printf("\033[31mTTF ERROR: %s\033[0m\n", TTF_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    srand(time(NULL));

    Entity Player;
    Entity_Init(&Player, 320, 240, 20, 20);

    Entity Coin;
    Entity_Init(&Coin, rand() % (640-20), rand() % (480-20), 20, 20);

    int score = 0;

    int isRunning = 1;
    SDL_Event event;
    while (isRunning){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                isRunning = 0;
            }
        }
        Entity_MoveBy_UIN(&Player, 5, 640, 480);
        
        if (SDL_HasIntersection(&Player.body, &Coin.body)){
            score++;
            Coin.body.x = rand() % (640-20);
            Coin.body.y = rand() % (480-20);
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        Entity_Draw(renderer, &Player, 0, 255, 0);
        Entity_Draw(renderer, &Coin, 255, 255, 0);

        
        Text Tscore;
        Text_Init(renderer, main_font, &Tscore, "Score: %d", score);
        Text_Draw(renderer, &Tscore, 10, 10);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    TTF_CloseFont(main_font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
    return 0;
}