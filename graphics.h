#pragma once

#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600 
#define MAX_DEPTH 5  

void draw_sierpinski(
    SDL_Renderer* renderer,
    int x1, int y1,
    int x2, int y2,
    int x3, int y3,
    int depth
);