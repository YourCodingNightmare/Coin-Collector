#include <SDL2/SDL.h>
#include "Timer.h"
#include <stdio.h>

Timer Timer_Start(int duration){
    Timer t;
    t.startingTick = SDL_GetTicks();
    t.duration = duration;
    return t;
}

int Timer_Left(Timer *t){
    Uint32 elapsed = (SDL_GetTicks() - t->startingTick) / 1000;
    int left = t->duration - elapsed;
    return (left > 0) ? left : 0;
}

int Timer_IsFinished(Timer *t){
    return Timer_Left <= 0;
}