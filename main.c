#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "graphics.h"

typedef struct {
    SDL_Rect rect;
    const char* label;
    bool hovered;
} Button;

Button btn_decrease;
Button btn_increase;
int current_depth = 3;

void init_buttons() {
    btn_decrease = (Button){ {50, HEIGHT - 80, 200, 50}, "-", false };
    btn_increase = (Button){ {WIDTH - 250, HEIGHT - 80, 200, 50}, "+", false };
}

void render_buttons(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, btn_decrease.hovered ? 100 : 70, 70, 70, 255);
    SDL_RenderFillRect(renderer, &btn_decrease.rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &btn_decrease.rect);

    SDL_SetRenderDrawColor(renderer, btn_increase.hovered ? 100 : 70, 70, 70, 255);
    SDL_RenderFillRect(renderer, &btn_increase.rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &btn_increase.rect);
}

void handle_click(int x, int y) {
    if (SDL_PointInRect(&(SDL_Point){x, y}, &btn_decrease.rect) && current_depth > 1) {
        current_depth--;
    } else if (SDL_PointInRect(&(SDL_Point){x, y}, &btn_increase.rect) && current_depth < MAX_DEPTH) {
        current_depth++;
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Sierpinski Triangle",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        printf("Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    init_buttons();

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        handle_click(event.button.x, event.button.y);
                    }
                    break;
                case SDL_MOUSEMOTION:
                    btn_decrease.hovered = SDL_PointInRect(
                        &(SDL_Point){event.motion.x, event.motion.y},
                        &btn_decrease.rect
                    );
                    btn_increase.hovered = SDL_PointInRect(
                        &(SDL_Point){event.motion.x, event.motion.y},
                        &btn_increase.rect
                    );
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        draw_sierpinski(
            renderer,
            WIDTH / 2, 100,
            100, HEIGHT - 100,
            WIDTH - 100, HEIGHT - 100,
            current_depth
        );

        render_buttons(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}