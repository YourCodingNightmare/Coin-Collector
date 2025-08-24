#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>

typedef struct Timer {
    Uint32 startingTick;
    int duration;
} Timer;

Timer Timer_Start(int duration);

int Timer_Left(Timer *t);
int Timer_IsFinished(Timer *t);
