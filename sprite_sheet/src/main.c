#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <time.h>

#include "../common/debugScreen.h"
#include "sprite.h"

#define printf psvDebugScreenPrintf
#define PATH_MAX 1024
#define ROOT "app0:"

double get_delta_time(int old, int current) {
    return ((double)(current - old))/SDL_GetPerformanceFrequency();
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        return -1;
    }

    // Main SDL window
    SDL_Window* window = SDL_CreateWindow("sprite_sheet_demo", 0, 0, 960, 544, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        return -1;
    }

    // Main SDL renderer
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        return -1;
    }
    SDL_RenderSetLogicalSize(renderer, 960, 544);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    Sprite knight_idle = load_sprite(renderer, "app0:/assets/knight_idle.png", "app0:/assets/knight_idle.data");

    const double FRAME_RATE = 60.0f;
    const double TARGET_FRAME_TIME = 1.0f / FRAME_RATE;
    unsigned int last_frame_counter = 0;

    while (1) {
        if (get_delta_time(last_frame_counter, SDL_GetPerformanceCounter()) >= TARGET_FRAME_TIME) {
            SDL_RenderClear(renderer);
            next_frame(&knight_idle, TARGET_FRAME_TIME);
            render_sprite(renderer,&knight_idle,960/2-32,544/2-56);
            SDL_RenderPresent(renderer);
            last_frame_counter = SDL_GetPerformanceCounter();
        }
    }

    SDL_Quit();
    return 0;
}
