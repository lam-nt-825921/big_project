
#include <iostream>
#include "TextureManager.h"


SDL_Window* window;
SDL_Surface* surface;
SDL_Renderer* renderer;
SDL_Texture* texture;

SDL_Rect src,dest;


int main( int argc, char* args[] )
{
    if(SDL_Init( SDL_INIT_VIDEO ) == 0)
    {
        std:: cout<<"started\n";
        SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
        window = SDL_CreateWindow("worm",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,500,500,false);

        if(window)
        {
            std::cout<<"window is created\n";

            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


            if(renderer)
            {
                std:: cout<<"renderer is created";
            }
            SDL_SetRenderDrawColor(renderer,255,20,255,255);

        }

    }

    TextureManager::init();

    bool quit = false;

    SDL_Event e;

    while( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else
            {




                texture = TextureManager::LoadTextTexture(renderer," ",src);
                dest = src;
                dest.x = 50;
                dest.y = 50;
                SDL_RenderClear(renderer);
                TextureManager::DrawTexture(renderer,texture,src,dest);
                SDL_RenderPresent(renderer);
            }
        }


    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();




    return 0;
}
