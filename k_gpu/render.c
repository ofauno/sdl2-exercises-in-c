// Copyright 2016 fauno

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

typedef SDL_Event s_event;
typedef SDL_Surface s_surface;
typedef SDL_Window s_window;
typedef SDL_Texture s_texture;

enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

int load_media();
int is_window_created();
int game_update();
s_surface * load_image(char * path);
s_texture * load_texture(char * path);


// s_surface* g_key_images[KEY_PRESS_SURFACE_TOTAL];
s_texture* g_key_images[KEY_PRESS_SURFACE_TOTAL];
// s_surface* g_current_image = 0;
s_texture* g_current_image = 0;
// s_surface* g_screen_surface = 0;
s_window* g_window = 0;
SDL_Renderer* g_render = 0;
s_texture* g_texture = 0;

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

int main(int argc, char* args[]) {
    if ( is_window_created() ) {
        // sdl2_image
        int image_flags = IMG_INIT_PNG;
        if ( !(IMG_Init(image_flags) & image_flags) ) {
            printf("sdl2_image err: %s\n", IMG_GetError() );
        }
        // else {
        //     g_screen_surface = SDL_GetWindowSurface(g_window);
        // }

        int user_quit = 0;
        s_event event;

        if ( !load_media() ) {
            user_quit = 1;
        }

        g_current_image =
            g_key_images[KEY_PRESS_SURFACE_DEFAULT];

        // the LOOP
        while  ( !user_quit ) {
            // getting events
            while ( SDL_PollEvent(&event) != 0 ) {
                // handling events
                // user_quit
                if ( event.type == SDL_QUIT ) {
                    user_quit = 1;
                } else if (event.type == SDL_KEYDOWN) {
                    printf("key!\n");
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                        g_current_image =
                        g_key_images[KEY_PRESS_SURFACE_UP];
                        break;

                        case SDLK_DOWN:
                        g_current_image =
                        g_key_images[KEY_PRESS_SURFACE_DOWN];
                        break;

                        case SDLK_LEFT:
                        g_current_image =
                        g_key_images[KEY_PRESS_SURFACE_LEFT];
                        break;

                        case SDLK_RIGHT:
                        g_current_image =
                        g_key_images[KEY_PRESS_SURFACE_RIGHT];
                        break;

                        default:
                        g_current_image =
                        g_key_images[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                    }
                }  // end handling events
            }

            game_update();
        }
    }

    // closing...
    // Deallocate textures
    for ( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i ) {
        SDL_DestroyTexture(g_key_images[ i ]);
        g_key_images[ i ] = 0;
    }

    SDL_DestroyTexture(g_texture);
    SDL_DestroyTexture(g_current_image);
    g_texture = 0;
    g_current_image = 0;

    SDL_DestroyRenderer(g_render);
    SDL_DestroyWindow(g_window);
    g_window = 0;
    g_render = 0;

    IMG_Quit();
    SDL_Quit();
    return 0;
}

int load_media() {
    int success = 1;

    // $ mogrify -format bmp *.jpg

    // load key images
    g_key_images[ KEY_PRESS_SURFACE_DEFAULT ] =
    // load_image("default.jpeg");
    load_texture("../events/default.jpeg");
    if (g_key_images[ KEY_PRESS_SURFACE_DEFAULT ] == 0) {
        printf("cannot load %s image\n", "default");
        success = 0;
    }

    g_key_images[ KEY_PRESS_SURFACE_UP ] =
    // load_image("up.jpg");
    load_texture("../events/up.jpg");
    if (g_key_images[ KEY_PRESS_SURFACE_UP ] == 0) {
        printf("cannot load %s image\n", "up");
        success = 0;
    }

    g_key_images[ KEY_PRESS_SURFACE_DOWN ] =
    // load_image("down.jpg");
    load_texture("../events/down.jpg");
    if (g_key_images[ KEY_PRESS_SURFACE_DOWN ] == 0) {
        printf("cannot load %s image\n", "down");
        success = 0;
    }

    g_key_images[ KEY_PRESS_SURFACE_LEFT ] =
    // load_image("left.jpg");
    load_texture("../events/left.jpg");
    if (g_key_images[ KEY_PRESS_SURFACE_LEFT ] == 0) {
        printf("cannot load %s image\n", "left");
        success = 0;
    }

    g_key_images[ KEY_PRESS_SURFACE_RIGHT ] =
    // load_image("right.jpg");
    load_texture("../events/right.jpg");
    if (g_key_images[ KEY_PRESS_SURFACE_RIGHT ] == 0) {
        printf("cannot load %s image\n", "right");
        success = 0;
    }

    g_texture = load_texture("../events/default.jpeg");

    if ( !g_texture ) {
        printf("texture err\n");
        success = 0;
    }

    return success;
}

// s_surface* load_image(char * path) {
//     s_surface* post_processed_image = 0;

//     // s_surface* loaded_image = SDL_LoadBMP(path);

//     // support BMP, GIF, JPEG, LBM, PCX, PNG, PNM,
//     // TGA, TIFF, WEBP, XCF, XPM, XV
//     s_surface* loaded_image = IMG_Load(path);

//     if (loaded_image == 0) {
//         // printf("%s err : %s\n", path, SDL_GetError());
//         printf("%s err : %s\n", path, IMG_GetError());
//     } else {
//         // optimized for blitting
//         // http://wiki.libsdl.org/SDL_ConvertSurface
//         // returns a new image in memory
//         post_processed_image = SDL_ConvertSurface(
//             loaded_image,
//             g_screen_surface->format,
//             0);

//         SDL_FreeSurface(loaded_image);
//     }

//     return post_processed_image;
// }

s_texture* load_texture(char* path) {
    // The final texture
    s_texture* newTexture = 0;

    // Load image at specified path
    s_surface* loadedSurface = IMG_Load(path);
    if ( !loadedSurface ) {
        printf("Unable to load %s! Error: %s\n", path, IMG_GetError());
    } else {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(g_render, loadedSurface);
        if ( !newTexture ) {
            printf("texture %s! Error: %s\n", path, SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

int is_window_created() {
    int success = 1;
    // init
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("err %s\n", SDL_GetError());
        success = 0;
    } else {
        // Set texture filtering to linear
        if ( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") ) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        g_window = SDL_CreateWindow(
         "sdl key",
         SDL_WINDOWPOS_UNDEFINED,
         SDL_WINDOWPOS_UNDEFINED,
         SCREEN_WIDTH,
         SCREEN_HEIGHT,
         SDL_WINDOW_SHOWN);

        if ( !g_window ) {
            printf("err %s\n", SDL_GetError());
            success = 0;
        } else {
            g_render = SDL_CreateRenderer(
                g_window,
                -1,
                SDL_RENDERER_ACCELERATED);

            if ( !g_render ) {
                printf("err render: %s\n", SDL_GetError());
                success = 0;
            } else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(
                    g_render, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }

    return success;
}

int game_update() {
    // Clear screen
    SDL_RenderClear(g_render);

    // Render texture to screen
    SDL_RenderCopy(g_render, g_current_image, 0, 0);

    // Update screen
    SDL_RenderPresent(g_render);

    // SDL_FillRect(
    //     g_screen_surface,
    //     0,
    //     SDL_MapRGB(
    //         g_screen_surface->format,
    //         0xff,
    //         0xff,
    //         0xff));

    // SDL_Rect screen_rectangle;
    // screen_rectangle.x = 0;
    // screen_rectangle.y = 0;
    // screen_rectangle.w = SCREEN_WIDTH;
    // screen_rectangle.h = SCREEN_HEIGHT;

    // SDL_BlitScaled(
    //     g_current_image,  // src
    //     0,  // copy the entire surface
    //     g_screen_surface,
    //     &screen_rectangle);

    // // SDL_BlitSurface(
    // //     g_current_image,
    // //     0,
    // //     screen_surface,
    // //     0
    // // );

    // SDL_UpdateWindowSurface(g_window);
    return 0;
}
