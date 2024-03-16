#include "Game.h"
#include "Vector2D.h"
#include <string>
#include "Block.h"
#include <fstream>
#include <random>
#include <time.h>


///static declare
int Game:: FPS = 60;
int Game:: money = 150;
int Game::timer = 0;
int Game::onGround[6];
bool Game:: isRunning = false;
bool Game::Win = false;
std::vector<Bullet*> Game:: wormBullet;
std::vector<worm*> Game:: worms;
std::vector<enemy*> Game:: enemys;
//-------------------------------------

Block *n_worms;
Block *GameMoney;
Block *GameTime;

Object *BG;



Game::Game()
{

}

Game::~Game()
{

}

bool Game::Init()
{
    Frame = 0;
    money = 150;
    Win = false;
    srand(time(NULL));
    for(int i=0;i<6;i++)onGround[i] = 0;
    {/// load level
        last_spawn = 0;

        std::ifstream getEnemys("text/level1.txt"); // Open file for reading

        getEnemys>>numEnemys;
        spawn.resize(numEnemys);
        for(int i=numEnemys ;i--;)
        {
            getEnemys >> spawn[i].first;
            spawn[i].first*=1000;
            getEnemys >> spawn[i].second;
        }
        getEnemys.close(); // Close the file
    }

    {/// init back ground
        BG = new Object;
        BG -> SetAni("image/Game_BG.bmp");
    }



    {/// init Block
        n_worms = new Block;
        n_worms->init("image/Board.bmp", "normal worm",10);
        n_worms->SetPos(65,702);

        GameMoney = new Block;
        GameMoney->init("image/Board.bmp", "Money : " + std::to_string(money),10);
        GameMoney->SetPos(65,50);

        TimeStart = SDL_GetTicks();
        Time = (SDL_GetTicks() - TimeStart)/1000;
        GameTime = new Block;
        GameTime->init("image/Board.bmp","Time : "+std::to_string(Time)+" s",18);
        GameTime->SetPos(40, 150);


    }
///---- Game Start --------
    isRunning = true;
    return isRunning;
}

void Game::Input()
{
    SDL_PollEvent(&Window::event);
    Frame++;
    timer = Frame;
    Time = (SDL_GetTicks() - TimeStart)/1000;

    if(Frame % 150 == 0)money += 10;

    {///spawn enemys
        if(numEnemys > 0 && (1000/FPS)*(timer - last_spawn) >= spawn.back().first)
        {
            last_spawn = timer;
            switch(spawn.back().second)
            {
            case 1:
                {
                    enemy* e = new enemy;
                    e->SetAni("image/enemy_1.bmp",6,120,2);
                    e ->init(800,0.2,80,60,1,1000);//hp,speed,strong,armo,res,Atack Speed
                    e -> SetCol(rand()%6);
                }
                break;
            default:
                break;
            }
            spawn.pop_back();
            numEnemys--;
        }

        GameMoney->SetText("Money : " + std::to_string(money),10);
        GameTime->SetText("Time : "+std::to_string(Time)+" s",18);
    }


    {/// input for enemys
        for(int i = 0; i<6; i++)onGround[i] = 0;
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
                int c = (*it)->inCollum;
                if(onGround[c] <= 0 ||
                   onGround[c] > (*it)->GetDest().y)
                   onGround[c] = (*it)->GetDest().y;
                ++it;
            }
        }
    }

    {/// input for worms
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
        case SDLK_x:
            if(FPS == 60)FPS =120;
            else FPS = 60;
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
        if(n_worms->isChosed == true && money >= 100)
        {
            if(worms.empty()||worms.back()->GetFree()==false)
            {
                money -= 100;
                worm* w = new worm;
                w->SetAni("image/n_worm.bmp",4,120);
                w->init(2,"image/bullet.bmp",0.2,200,3,150);//num bullet, path,bullet speed, bullet dame, bullet frames, bullet ms Per Frames
                w->SetPos(Window::event.button.x, Window::event.button.y);
                w->SetASP(2000);
                w->SetHp(1000);
            }
            n_worms->isChosed = false;
        }
        GameMoney->update();
        GameTime->update();
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
                int cnt = (*it) -> GetNumAtack();
                bool IsAtack = (*it) ->GetDealAtack();
                (*it)->SetIsAtack(false);
                for(auto& w : worms)if(cnt > 0 && w->GetFree() == false && w->Collision((*it)->GetDest()))
                {
                    (*it)->SetIsAtack(true);
                    if(IsAtack)
                    {
                        w->beAtacked((*it)->GetStrong());
                        cnt--;
                    }
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
        GameMoney->render();
        GameTime->render();
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

    if(enemys.size() == 0 && numEnemys <= 0)
    {
        Win = true;
        isRunning = false;
    }
}

void Game::Close()
{
    delete n_worms;
    for(auto& e: enemys)delete e;
    for(auto& w: worms)delete w;
    for(auto& b: wormBullet)delete b;
    wormBullet.clear();
    worms.clear();
    enemys.clear();
}

bool Collision(const SDL_Rect &A,const SDL_Rect &B)
{
    return !(A.x > B.x + B.w ||
            A.y > B.y + B.h ||
            B.x > A.x + A.w ||
            B.y > A.y + A.h);
}


