#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    TTF_Font* main_font = TTF_OpenFont("font/PressStart2P-Regular.ttf", 20);
    if (!main_font){
        printf("\033[31mTTF ERROR: %s\033[0m\n", TTF_GetError());
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    srand(time(NULL));
    SDL_Rect player = {320, 240, 20, 20};
    SDL_Rect coin = {rand() % (640-20), rand() % (480-20), 20, 20};

    int score = 0;

    SDL_Color white = {255, 255, 255, 255};

    int isRunning = 1;
    SDL_Event event;
    while (isRunning){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                isRunning = 0;
            }
        }
        const Uint8* keyboard = SDL_GetKeyboardState(NULL);
        if (keyboard[SDL_SCANCODE_W] && player.y > 0)player.y -= 5;
        if (keyboard[SDL_SCANCODE_S] &&  player.y + player.h < 480) player.y += 5;
        if (keyboard[SDL_SCANCODE_A] && player.x > 0) player.x -= 5;
        if (keyboard[SDL_SCANCODE_D] && player.x + player.w < 640) player.x += 5;

        if (SDL_HasIntersection(&player, &coin)){
            score++;
            coin.x = rand() % (640-20);
            coin.y = rand() % (480-20);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &player);

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &coin);
        
        char TextBuffer[64];
        sprintf(TextBuffer, "Score: %d", score);

        SDL_Surface* textSurface = TTF_RenderText_Solid(main_font, TextBuffer, white);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect textdest = {10, 10, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, NULL, &textdest);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

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