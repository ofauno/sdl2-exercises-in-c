// window.c
#include "SDL2/SDL.h"
// #include "SDL_opengl.h"
#include "stdio.h"

int main(int argc, char* args[])
{
    int SCREEN_WIDTH = 600;
    int SCREEN_HEIGHT = 400;

    SDL_Window* window = 0;
    SDL_Surface* screen_surface = 0;
    SDL_Surface* background = 0;

    // init
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {   
        printf("err %s\n", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow(
           "sdl first", 
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        );

        if (!window)
        {
            printf("err %s\n", SDL_GetError());
        }
        else
        {
            screen_surface = SDL_GetWindowSurface( window );

            SDL_FillRect( 
                screen_surface,
                0,
                SDL_MapRGB( 
                    screen_surface->format,
                    0xff,
                    0xff,
                    0xff
                )
            );

            // mogrify -format bmp *.jpg 
            background = SDL_LoadBMP("apo.bmp");

            if (!background)
            {
                printf("err %s\n", SDL_GetError());
            }
            else
            {
                SDL_BlitSurface(
                    background,
                    0,
                    screen_surface,
                    0
                );
            }

            SDL_UpdateWindowSurface( window );

            SDL_Delay( 2000 );
        }
    }

    SDL_FreeSurface( background );
    background = 0;
    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}
