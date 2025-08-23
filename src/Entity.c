#include <SDL2/SDL.h>
#include "Entity.h"

void Entity_Init(Entity *e, int x, int y, int w, int h){
    e->body.x = x, e->body.y = y, e->body.w = w, e->body.h = h;
}
void Entity_Draw(SDL_Renderer* renderer, Entity *e, int r, int g, int b){
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &e->body);
}

void Entity_MoveBy_UIN(Entity *e, int s, int ww, int wh){
    const Uint8* keyboardstate = SDL_GetKeyboardState(NULL);
    if (keyboardstate[SDL_SCANCODE_W] && e->body.y > 0) e->body.y -= s;
    if (keyboardstate[SDL_SCANCODE_S] && e->body.y + e->body.h < wh) e->body.y += s;
    if (keyboardstate[SDL_SCANCODE_A] && e->body.x > 0) e->body.x -= s;
    if (keyboardstate[SDL_SCANCODE_D] && e->body.x + e->body.w < ww) e->body.x += s;
}