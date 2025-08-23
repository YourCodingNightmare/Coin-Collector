#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Text.h"
void Text_Init(SDL_Renderer* renderer, TTF_Font *font, Text *t, const char *format, ...){
    char tbuffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(tbuffer, sizeof(tbuffer), format, args);
    va_end(args);

    SDL_Color dfcol = {255, 255, 255, 255};

    SDL_Surface *surface = TTF_RenderText_Solid(font, tbuffer, dfcol);
    if (!surface){
        printf("\033[31mTEXT ERROR: %s\n\033[0m", TTF_GetError());
        return;
    }
    t->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!t->texture){
        printf("\033[31mTEXT ERROR: %s\n\033[0m", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    t->dest.x = 0;
    t->dest.y = 0;
    t->dest.w = surface->w;
    t->dest.h = surface->h;

    SDL_FreeSurface(surface);
}

void Text_Draw(SDL_Renderer* renderer, Text *t, int dx, int dy){
    t->dest.x = dx;
    t->dest.y = dy;

    SDL_RenderCopy(renderer, t->texture, NULL, &t->dest);
}

void Text_DestroyTexture(Text *t){
    SDL_DestroyTexture(t->texture);
    t->texture = NULL;
}