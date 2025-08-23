#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdarg.h>
typedef struct Text{
    SDL_Texture* texture;
    SDL_Rect dest;
}Text;

void Text_Init(SDL_Renderer* renderer, TTF_Font *font, Text *t, const char *format, ...);

void Text_Draw(SDL_Renderer* renderer, Text *t, int dx, int dy);

void Text_Modify(SDL_Renderer* renderer, TTF_Font* font, Text *text, const char *format, ...);
void Text_DestroyTexture(Text *t);