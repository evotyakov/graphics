#pragma once

#include <SDL.h>

#define WIDTH  800  
#define HEIGHT 700  
#define MAX_DEPTH 5  

void draw_sierpinski(
    SDL_Renderer* renderer,
    int x1, int y1,
    int x2, int y2,
    int x3, int y3,
    int depth
);