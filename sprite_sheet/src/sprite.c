#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sprite.h"

Sprite load_sprite(SDL_Renderer *renderer, char *image_path, char *data_path) {
    Sprite sprite;
    sprite.currentFrame = 0;

    FILE *fp = fopen(data_path, "r");
    assert(fp != NULL);
    char *line = malloc(sizeof(char)*40);
    fgets(line, sizeof(char)*40, fp);
    fclose(fp);

    sprite.w = atoi(strsep(&line, " "));
    sprite.h = atoi(strsep(&line, " "));
    sprite.frameCount = atoi(strsep(&line, " "));
    sprite.frameRate = atoi(strsep(&line, " "));
    free(line);

    SDL_Surface *image = IMG_Load(image_path);
    assert(image != NULL);
    sprite.texture = SDL_CreateTextureFromSurface(renderer, image);
    sprite.waitTime = 1.0f/sprite.frameRate;

    return sprite;
}

void next_frame(Sprite *sprite, double delta_t) {
    sprite->waitTime -= delta_t;
    if (sprite->waitTime <= 0) {
        sprite->currentFrame = (sprite->currentFrame + 1) % sprite->frameCount;
        sprite->waitTime = 1.0f/sprite->frameRate;
    }
}

void render_sprite(SDL_Renderer *renderer, Sprite *sprite, int x, int y) {
    SDL_Rect srcrect;
    srcrect.x = sprite->currentFrame * (sprite->w/sprite->frameCount);
    srcrect.y = 0;
    srcrect.w = (sprite->w/sprite->frameCount);
    srcrect.h = sprite->h;

    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = (sprite->w/sprite->frameCount)*4;
    dstrect.h = sprite->h*4;
    
    SDL_RenderCopy(renderer, sprite->texture, &srcrect, &dstrect);
}
