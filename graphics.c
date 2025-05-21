#include "graphics.h"

void draw_sierpinski(
    SDL_Renderer* renderer,
    int x1, int y1,
    int x2, int y2,
    int x3, int y3,
    int depth
) 
{
    if (depth <= 0) 
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
        SDL_RenderDrawLine(renderer, x3, y3, x1, y1);
        return;
    }

    int x12 = (x1 + x2) / 2;
    int y12 = (y1 + y2) / 2;
    int x23 = (x2 + x3) / 2;
    int y23 = (y2 + y3) / 2;
    int x31 = (x3 + x1) / 2;
    int y31 = (y3 + y1) / 2;

    draw_sierpinski(renderer, x1, y1, x12, y12, x31, y31, depth - 1);
    draw_sierpinski(renderer, x12, y12, x2, y2, x23, y23, depth - 1);
    draw_sierpinski(renderer, x31, y31, x23, y23, x3, y3, depth - 1);
}