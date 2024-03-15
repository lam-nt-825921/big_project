#include "Game.h"
#include "Vector2D.h"
#include "worm.h"

bool Game:: isRunning = false;
std::vector<Bullet*> Game:: wormBullet;
std::vector<worm*> Game:: worms;

worm *bullet;
worm *bullet1;
worm *bullet2;

Object *BG;


Game::Game()
{

}

Game::~Game()
{

}

bool Game::Init()
{
    BG = new Object;
    BG -> SetAni("image/Game_BG.bmp");

    bullet = new worm;
    bullet->SetAni("image/n_worm.bmp",4,100);
    bullet->init(2,"image/bullet.bmp",3,150);
    bullet->SetPos(50,700);
    bullet->SetASP(2000);

    bullet1 = new worm;
    bullet1->SetAni("image/n_worm.bmp",4,100);
    bullet1->init(2,"image/bullet.bmp",3,150);
    bullet1->SetPos(50,600);
    bullet1->SetASP(2000);

    bullet2 = new worm;
    bullet2->SetAni("image/n_worm.bmp",4,100);
    bullet2->init(2,"image/bullet.bmp",3,150);
    bullet2->SetPos(50,500);
    bullet2->SetASP(2000);


    isRunning = true;
    return isRunning;
}

void Game::Input()
{
    SDL_PollEvent(&Window::event);
    auto it = worms.begin();
    while (it != worms.end())
    {
        if ((*it)-> isExist == false)
        {
            delete (*it);
            it = worms.erase(it);
        }
        else
        {
            (*it) -> GetTimer();
            (*it) -> input();
            ++it;
        }
    }


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

    auto it = worms.begin();
    while (it != worms.end())
    {
        if ((*it)-> isExist == false)
        {
            delete (*it);
            it = worms.erase(it);
        }
        else
        {
            (*it) -> update(0, -25);
            ++it;
        }
    }
}

void Game::Render()
{

    SDL_RenderClear(Window::renderer);

    BG->Draw();
    for(int y = 1;y<=12; y++)
    {
        if(SDL_RenderDrawLine(Window::renderer,0,800 - y*64,500,800-y*64)!=0)std::cout<<SDL_GetError()<<'\n';
    }
    for(int y = 1; y<=6; y++)
    {
        if(SDL_RenderDrawLine(Window::renderer,80+y*60,0,80+y*60,800)!=0)std::cout<<SDL_GetError()<<'\n';
    }
    auto it = worms.begin();
    while (it != worms.end())
    {
        if ((*it)-> isExist == false)
        {
            delete (*it);
            it = worms.erase(it);
        }
        else
        {
            (*it) -> render();
            ++it;
        }
    }
    SDL_RenderPresent(Window::renderer);
}

void Game::Close()
{
    for(auto& w: worms)delete w;
    for(auto& b: wormBullet)delete b;
    wormBullet.clear();
    worms.clear();
}

bool Collision(const SDL_Rect &A,const SDL_Rect &B)
{
    return !(A.x > B.x + B.w ||
            A.y > B.y + B.h ||
            B.x > A.x + A.w ||
            B.y > A.y + A.h);
}


