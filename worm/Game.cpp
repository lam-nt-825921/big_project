#include "Game.h"
#include "Vector2D.h"
#include "Block.h"

SDL_Renderer* Game:: renderer = nullptr;
SDL_Window* Game:: window = nullptr;
SDL_Event Game:: event;
bool Game:: isRunning = false;



Game::Game()
{

}

Game::~Game()
{

}

bool Game::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        std::cout<<"init\n";
        window = SDL_CreateWindow("Game con sau",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Width=500,Height=800,false);
        if(window != nullptr)
        {
            std::cout<<"window\n";
            renderer = SDL_CreateRenderer(window,-1,0);
            if(renderer != nullptr)
            {
                std::cout<<"renderer\n";
                SDL_SetRenderDrawColor(renderer, 0, 20, 40, 255);
                if(TextureManager:: init())
                {
                    std::cout<<"texture manager\n";
                    isRunning = true;
                }
            }
        }
    }



    return isRunning;
}

void Game::Input()
{

    if(SDL_PollEvent(&event)!=0)
    {
        switch(event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

}

void Game::Update()
{


}

void Game::Render()
{
    SDL_RenderClear(renderer);


    SDL_RenderPresent(renderer);
}

void Game::Close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Collision(const SDL_Rect &A,const SDL_Rect &B)
{
    return !(A.x > B.x + B.w ||
            A.y > B.y + B.h ||
            B.x > A.x + A.w ||
            B.y > A.y + A.h);
}


