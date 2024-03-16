#include "Game.h"
#include "Vector2D.h"

#include "Block.h"


bool Game:: isRunning = false;
std::vector<Bullet*> Game:: wormBullet;
std::vector<worm*> Game:: worms;
std::vector<enemy*> Game:: enemys;

Block *n_worms;

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

    enemy* a = new enemy;
    a->SetAni("image/Green_worm.bmp",6,50,1);
    a ->init(1000,0.2,1,60,1,1000);
    a -> SetCol(0);

    n_worms = new Block;
    n_worms->init("image/Board.bmp", "normal worm",10);
    n_worms->SetPos(65,702);

    isRunning = true;
    return isRunning;
}

void Game::Input()
{
    SDL_PollEvent(&Window::event);

    {/// Get time for enemys
        auto it = enemys.begin();
        while (it != enemys.end())
        {
            if ((*it)-> GetIsLive() == false)
            {
                delete (*it);
                it = enemys.erase(it);
            }
            else
            {
                (*it) -> GetTimer();
                ++it;
            }
        }
    }

    {/// Get time and input for worms
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
    }


/// == Game handle event ==
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



    {/// update block spawn worms
        n_worms->update();
        if(n_worms->isChosed == true)
        {

            if(worms.empty()||worms.back()->GetFree()==false)
            {
                worm* w = new worm;
                w->SetAni("image/n_worm.bmp",4,120);
                w->init(2,"image/bullet.bmp",0.2,100,3,150);
                w->SetPos(Window::event.button.x, Window::event.button.y);
                w->SetASP(2000);
            }
            n_worms->isChosed = false;
        }
    }

    {/// update worms
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

    {/// update enemys
        auto it = enemys.begin();
        while (it != enemys.end())
        {
            if ((*it)-> GetIsLive() == false)
            {
                delete (*it);
                it = enemys.erase(it);
            }
            else
            {

                (*it) -> update();
                ///collision with bullet
                for(auto& b : wormBullet)if(b->isCreated()&&b->Collision((*it)->GetDest()))
                {
                    (*it)->SetDameTaken(b->GetPower());
                    b->del();
                }
                ///collision with worms
                for(auto& w : worms)if(w->Collision((*it)->GetDest()))
                {
                    (*it)->SetIsAtack(true);

                }
                ++it;
            }
        }
    }
}

void Game::Render()
{
    SDL_RenderClear(Window::renderer);

    {/// render background
        BG->Draw();
        for(int y = 1;y<=12; y++)
        {
            if(SDL_RenderDrawLine(Window::renderer,0,800 - y*64,500,800-y*64)!=0)std::cout<<SDL_GetError()<<'\n';
        }
        for(int y = 1; y<=6; y++)
        {
            if(SDL_RenderDrawLine(Window::renderer,80+y*60,0,80+y*60,800)!=0)std::cout<<SDL_GetError()<<'\n';
        }
    }

    {/// render block spawn worms
        n_worms->render();
    }

    {/// render worms
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
    }

    {/// render enemys
        auto it = enemys.begin();
        while (it != enemys.end())
        {
            if ((*it)-> GetIsLive() == false)
            {
                delete (*it);
                it = enemys.erase(it);
            }
            else
            {
                (*it) -> render();
                ++it;
            }
        }
    }

    {/// render worms bullets
        auto it = wormBullet.begin();
        while (it != wormBullet.end())
        {
            if ((*it)-> IsExist() == false)
            {
                delete (*it);
                it = wormBullet.erase(it);
            }
            else
            {
                (*it) -> render();
                ++it;
            }
        }
    }

    SDL_RenderPresent(Window::renderer);
}

void Game::Close()
{
    delete n_worms;
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


