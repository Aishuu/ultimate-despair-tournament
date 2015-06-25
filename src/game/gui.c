#include <SDL2/SDL.h>

#include "include.h"

#include "game/gui.h"

#define BPP     4
#define DEPTH   32

struct MyColor {
    Uint8 r;
    Uint8 g;
    Uint8 b;
};

struct MyColor colors [9] = {
    {.r=255, .g=255, .b=255},
    {.r=255, .g=255, .b=255},
    {.r=255, .g=255, .b=255},
    {.r=255, .g=0,   .b=0},
    {.r=155, .g=0,  .b=0},
    {.r=55, .g=0, .b=0},
    {.r=0,   .g=0,   .b=255},
    {.r=0,  .g=0,  .b=155},
    {.r=0, .g=0, .b=55}
};

SDL_Surface* screen;
SDL_Window* window;

void setpixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) {
    Uint32 *pixmem32;
    Uint32 colour;  
    Uint8 o_r, o_g, o_b;
  
    pixmem32 = (Uint32*) screen->pixels  + y + x;
    SDL_GetRGB(*pixmem32, screen->format, &o_r, &o_g, &o_b);

    if (o_r+o_g+o_b == 0 || r+g+b > o_r+o_g+o_b) {
        colour = SDL_MapRGB( screen->format, r, g, b );
        *pixmem32 = colour;
    }
}

void draw (Game game) { 
    int x, y, ytimesw;
  
    if(SDL_MUSTLOCK(screen)) 
    {
        if(SDL_LockSurface(screen) < 0) return;
    }

    for(y = 0; y < screen->h; y++ ) {
        ytimesw = y*screen->pitch/BPP;
        for( x = 0; x < screen->w; x++ )
           if (game->cases[x][y] != 0)
            {
                setpixel(x, ytimesw, colors[3*game->cases[x][y]].r, colors[3*game->cases[x][y]].g, colors[3*game->cases[x][y]].b);
                if (x > 0) {
                    setpixel(x-1, ytimesw, colors[3*game->cases[x][y]+1].r, colors[3*game->cases[x][y]+1].g, colors[3*game->cases[x][y]+1].b);
                    if (y > 0)
                        setpixel(x-1, ytimesw-screen->pitch/BPP, colors[3*game->cases[x][y]+2].r, colors[3*game->cases[x][y]+2].g, colors[3*game->cases[x][y]+2].b);
                    if (y < screen->h-1)
                        setpixel(x-1, ytimesw+screen->pitch/BPP, colors[3*game->cases[x][y]+2].r, colors[3*game->cases[x][y]+2].g, colors[3*game->cases[x][y]+2].b);
                }
                if (x < screen->w-1) {
                    setpixel(x+1, ytimesw, colors[3*game->cases[x][y]+1].r, colors[3*game->cases[x][y]+1].g, colors[3*game->cases[x][y]+1].b);
                    if (y > 0)
                        setpixel(x+1, ytimesw-screen->pitch/BPP, colors[3*game->cases[x][y]+2].r, colors[3*game->cases[x][y]+2].g, colors[3*game->cases[x][y]+2].b);
                    if (y < screen->h-1)
                        setpixel(x+1, ytimesw+screen->pitch/BPP, colors[3*game->cases[x][y]+2].r, colors[3*game->cases[x][y]+2].g, colors[3*game->cases[x][y]+2].b);
                }
                if (y > 0)
                    setpixel(x, ytimesw-screen->pitch/BPP, colors[3*game->cases[x][y]+1].r, colors[3*game->cases[x][y]+1].g, colors[3*game->cases[x][y]+1].b);
                if (y < screen->h-1)
                    setpixel(x, ytimesw+screen->pitch/BPP, colors[3*game->cases[x][y]+1].r, colors[3*game->cases[x][y]+1].g, colors[3*game->cases[x][y]+1].b);
            }
    }

    if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  
    SDL_UpdateWindowSurface(window);
}

void initGUI () {
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf (stderr, "Error when initializing SDL.\n");
        exit (1);
    }

    window = SDL_CreateWindow(
        "Ultimate Despair Tournament",     // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        WIDTH,                             // width, in pixels
        HEIGHT,                            // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    if (window == NULL) {
        SDL_Quit();
        fprintf (stderr, "Error when initializing SDL.\n");
        exit (1);
    }

    screen = SDL_GetWindowSurface(window);
}

int getEvent () {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {      
        switch (event.type) {
        case SDL_QUIT:
            return -1;
            break;
        case SDL_KEYDOWN:
            return 1;
            break;
        }
    }

    return 0;
}

void quitGUI () {
    SDL_Quit ();
}
