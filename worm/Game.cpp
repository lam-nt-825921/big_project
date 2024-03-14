#include "Game.h"
#include "Vector2D.h"
#include "Block.h"
#include "worm.h"

bool Game:: isRunning = false;

worm *bullet;


Game::Game()
{

}

Game::~Game()
{

}

bool Game::Init()
{

    bullet = new worm;
    bullet->SetAni("image/n_worm.bmp",4,100);
    bullet->init(2,"image/bullet.bmp",3,150);
    bullet->SetPos(50,700);
    bullet->SetASP(2000);

    isRunning = true;
    return isRunning;
}

void Game::Input()
{
    bullet->GetTimer();
    bullet->input();

    SDL_PollEvent(&Window::event);

    switch(Window::event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch(Window::event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            isRunning = false;
            break;
        case SDLK_DOWN:
            //bullet.spawn(50,700);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

}

void Game::Update()
{

    bullet->update(0, -25);

}

void Game::Render()
{
    SDL_RenderClear(Window::renderer);

    bullet->render();
    SDL_RenderPresent(Window::renderer);
}

void Game::Close()
{
    delete bullet;

}

bool Collision(const SDL_Rect &A,const SDL_Rect &B)
{
    return !(A.x > B.x + B.w ||
            A.y > B.y + B.h ||
            B.x > A.x + A.w ||
            B.y > A.y + A.h);
}


