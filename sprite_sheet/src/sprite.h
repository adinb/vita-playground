#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Texture *texture;
    int w;
    int h;
    int frameCount;
    int frameRate;
    int currentFrame;
    double waitTime;
} Sprite;

Sprite load_sprite(SDL_Renderer *renderer, char *image_path, char *data_path);

void next_frame(Sprite *sprite, double delta_t);

void render_sprite(SDL_Renderer *renderer, Sprite *sprite, int x, int y);

#endif
