#pragma once
#include <SDL2/SDL.h>

typedef struct Entity {
    SDL_Rect body;
} Entity;

void Entity_Init(Entity *e, int x, int y, int w, int h);
void Entity_Draw(SDL_Renderer* renderer, Entity *e, int r, int g, int b);
void Entity_MoveBy_UIN(Entity *e, int s, int ww, int wh);