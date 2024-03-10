
#include <iostream>
#include "TextureManager.h"
#include <string>
#include <cstring>


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

    bool quit = false, writing = false;
    char* write = new char;
    *write = '-';

    SDL_Event e;

    while( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            switch (e.type)
            {
            case SDL_QUIT:
                quit = false;
                std::cout<<quit<<'\n';
                SDL_Quit();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(!writing)
                {
                    writing = true;
                    delete write;
                    write = new char;
                    *write = '-';
                }
                break;
            case SDL_TEXTINPUT:
                if(writing)
                {
                    char* text = e.text.text;
                    char* tmp = write;
                    int len= std::strlen(tmp);
                    write = new char[len + 1];
                    std::strcpy(write,tmp);
                    delete tmp;
                    write[len]=*text;
                    delete text;

                }
                break;
            case SDL_KEYDOWN:
                if(e.key.keysym.sym == SDLK_TAB)
                {
                    std::cout<<writing<<'\n';
                    if(writing)
                    {
                        writing = false;
                    }
                    std::cout<<'-'<<writing<<'\n';
                }

                break;
            default:
                break;
            }
            if(write)
            {
                    texture = TextureManager::LoadTextTexture(renderer,write,src);
                    dest = src;
                    dest.x = 50;
                    dest.y = 50;
            }



            SDL_RenderClear(renderer);
            TextureManager::DrawTexture(renderer,texture,src,dest);
            SDL_RenderPresent(renderer);

        }


    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();




    return 0;
}

