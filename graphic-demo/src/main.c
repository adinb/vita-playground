#include <psp2/kernel/processmgr.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

int main(int argc, char *argv[]) {
    if (SDL_Init( SDL_INIT_VIDEO ) < 0 ) { return -1; }
    if ((gWindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 544, SDL_WINDOW_SHOWN)) == NULL) { return -1; }
    if ((gRenderer = SDL_CreateRenderer(gWindow, -1, 0)) == NULL) { return -1; }

    SDL_Surface *imageSurface = IMG_Load("app0:/image.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    SDL_Rect dstRect;
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = 122;
    dstRect.h = 374;

    SDL_RenderCopy(gRenderer, texture, NULL, &dstRect);
    SDL_RenderPresent( gRenderer );

    SDL_Delay(4000);
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();
	sceKernelExitProcess(0);
	return 0;
}
