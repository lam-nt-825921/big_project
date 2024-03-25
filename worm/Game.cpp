#include "Game.h"
#include "Vector2D.h"
#include <string>
#include "Block.h"
#include <fstream>
#include <random>
#include <time.h>
#include "Menu.h"
#include <SDL_image.h>


///static declare
int Game:: FPS = 60;
short Game:: money = 150;
int Game::timer = 0;
short Game::onGround[6];
worm* Game:: wormMap[6][11];
bool Game:: isRunning = false;
bool Game::Win = false;
std::vector<Bullet*> Game:: wormBullet;
std::vector<worm*> Game:: worms;
std::vector<enemy*> Game:: enemys;
//-------------------------------------

Menu* blocks;

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
    for(short i=0;i<6;i++)onGround[i] = 0;
    for(short i=0;i<6;i++)
        for(short j= 0; j< 11;j ++)wormMap[i][j]=0;

    {/// load level
        last_spawn = 0;

        std::ifstream getEnemys("text/level2.txt"); // Open file for reading

        getEnemys>>numEnemys;
        spawn.resize(numEnemys);
        for(short i=numEnemys ;i--;)
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
        blocks = new Menu;
        blocks->AddTag(true,"n_worm 75$","spawn n_worm","image/n_wormBoard.bmp");
        blocks->tags.back()->SetPos(65,700);

        blocks->AddTag(true,"g_worm 175$","spawn g_worm","image/g_wormBoard.bmp");
        blocks->tags.back()->SetPos(65,600);

        blocks->AddTag(true,"m_worm 25$","spawn m_worm","image/m_wormBoard.bmp");
        blocks->tags.back()->SetPos(65,500);

        blocks->AddTag(true,"d_worm 50$","spawn d_worm","image/d_wormBoard.bmp");
        blocks->tags.back()->SetPos(65,400);

        blocks->AddTag(true,"e_worm 0$","spawn e_worm","image/e_wormBoard.bmp");
        blocks->tags.back()->SetPos(65,200);

        blocks->AddTag(false,"Money : "+ std::to_string(money)+"$","game money",NULL,12);
        blocks->tags.back()->SetPos(65,50);

        TimeStart = SDL_GetTicks();
        Time = (SDL_GetTicks() - TimeStart)/1000;
        blocks->AddTag(false,"Time : "+std::to_string(Time)+" s","game time",NULL,12);
        blocks->tags.back()->SetPos(65, 150);
    }
//---- Game Start --------
    isRunning = true;
    return isRunning;
}

void Game::Input()
{
    SDL_PollEvent(&Window::event);
    Frame++;
    timer = Frame;
    Time = (SDL_GetTicks() - TimeStart)/1000;

    if(Frame % 1500 == 0)money += 25;

    {///spawn enemys
        if(numEnemys > 0 && (1000/FPS)*(timer - last_spawn) >= spawn.back().first)
        {
            last_spawn = timer;
            switch(spawn.back().second)
            {
            case 1:
                {
                    enemy* e = new enemy;
                    e->SetAni("image/enemy_1.bmp",6,120,2);//frames, msPF, num Act
                    e ->init(800,0.2,100,60,1000);//hp,speed,strong,armo,Atack Speed
                    e -> SetCol(rand()%6);
                }
                break;
            case 2:
                {
                    enemy* e = new enemy;
                    e->SetAni("image/enemy_2.bmp",6,120,2);//frames, msPF, num Act
                    e ->init(1000,0.1,50,200,1000);//hp,speed,strong,armo,Atack Speed
                    e -> SetCol(rand()%6);
                }
                break;
            case 3:
                {
                    enemy* e = new enemy;
                    e->SetAni("image/enemy_3.bmp",6,120,2);//frames, msPF, num Act
                    e ->init(500,0.6,150,60,800);//hp,speed,strong,armo,Atack Speed
                    e -> SetCol(rand()%6);
                }
                break;
            default:
                break;
            }
            spawn.pop_back();
            numEnemys--;
        }

    }


    {/// input for enemys
        for(short i = 0; i<6; i++)onGround[i] = 0;
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
                short c = (*it)->inCollum;
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


    {/// update blocks

        blocks->update();
        for(auto&b : blocks->tags)
        {
            if(b->type == "spawn n_worm")///spawn worm type 1
            {
                if(b->isChosed && money >= 75)
                {
                    if(worms.empty() ||worms.back()->GetFree()==false)
                    {
                        worm* w = new worm;
                        money -= 75;
                        w->Cost = 75;
                        w->type = 1;
                        w->SetAni("image/n_worm.bmp",4,120);
                        w->init(2,"image/bullet.bmp",0.2,100,3,150,1,1);//num bullet, path,bullet speed, bullet dame, bullet frames, bullet ms Per Frames
                        w->SetPos(Window::event.button.x, Window::event.button.y);
                        w->SetASP(2000);
                        w->SetHp(1000);
                    }
                }
            }
            else if(b->type == "spawn g_worm")///spawn worm type 2
            {
                if(b->isChosed && money >= 175)
                {
                    if(worms.empty() ||worms.back()->GetFree()==false)
                    {
                        worm* w = new worm;
                        money -= 175;
                        w->Cost = 175;
                        w->type = 2;
                        w->SetAni("image/Green_worm.bmp",6,120);//frames, msPF
                        w->init(4,"image/burn_bullet.bmp",0.15,2,5,80,1,3);//num bullet, path,bullet speed, bullet dame, bullet frames, bullet ms Per Frames
                        w->SetPos(Window::event.button.x, Window::event.button.y);
                        w->SetASP(1500);
                        w->SetHp(1000);
                    }
                }
            }
            else if(b->type == "spawn m_worm")///spawn worm type 3
            {
                if(b->isChosed && money >= 25)
                {
                    if(worms.empty() ||worms.back()->GetFree()==false)
                    {
                        worm* w = new worm;
                        money -= 25;
                        w->Cost = 25;
                        w->type = 3;
                        w->SetAni("image/m_worm.bmp",6,120,2);//frames, msPF
                        //w->init(4,"image/burn_bullet.bmp",0.15,5,5,80,1,3);//num bullet, path,bullet speed, bullet dame, bullet frames, bullet ms Per Frames
                        w->SetPos(Window::event.button.x, Window::event.button.y);
                        w->SetASP(10000);
                        w->SetHp(1000);
                    }
                }
            }
            else if(b->type == "spawn d_worm")///spawn worm type 4
            {
                if(b->isChosed && money >= 50)
                {
                    if(worms.empty() ||worms.back()->GetFree()==false)
                    {
                        worm* w = new worm;
                        money -= 50;
                        w->Cost = 50;
                        w->type = 4;
                        w->SetAni("image/d_worm.bmp",6,120,2);//frames, msPF
                        //w->init(4,"image/burn_bullet.bmp",0.15,5,5,80,1,3);//num bullet, path,bullet speed, bullet dame, bullet frames, bullet ms Per Frames
                        w->SetPos(Window::event.button.x, Window::event.button.y);
                        w->SetASP(0);
                        w->SetHp(8000);
                    }
                }
            }
            else if(b->type == "spawn e_worm")///spawn worm type 5
            {
                if(b->isChosed)
                {
                    if(worms.empty() ||worms.back()->GetFree()==false)
                    {
                        worm* w = new worm;
                        w->Cost = 0;
                        w->type = 5;
                        w->SetAni("image/e_worm.bmp",6,120,1);//frames, msPF
                        //w->init(4,"image/burn_bullet.bmp",0.15,5,5,80,1,3);//num bullet, path,bullet speed, bullet dame, bullet frames, bullet ms Per Frames
                        w->SetPos(Window::event.button.x, Window::event.button.y);
                        w->SetASP(0);
                        w->SetHp(1);
                    }
                }
            }
            else if(b->type == "game money")///update money
            {
                if(money < 1000)b->SetText("Money : " + std::to_string(money),12);
                else b->SetText("Money : 999+",12);
            }
            else if(b->type == "game time")///update time
            {
                b->SetText("Time : "+std::to_string(Time)+" s",18);

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

                ///collision with worms
                short cnt = (*it) -> GetNumAtack();
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
    {/// update bullet
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
                if((*it)->isCreated())
                {
                    ///collision with worms
                    short cnt = (*it) -> GetNumAtack();
                    for(auto& e : enemys)if(e->Collision((*it)->GetDest()))
                    {
                        e->SetDameTaken((*it)->GetPower());
                        cnt--;
                        if(cnt <= 0)break;
                    }
                    if(cnt <= 0)(*it)->del();
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
        for(short y = 1;y<=12; y++)
        {
            if(SDL_RenderDrawLine(Window::renderer,140,800 - y*64,500,800-y*64)!=0)std::cout<<SDL_GetError()<<'\n';
        }
        for(short y = 1; y<=6; y++)
        {
            if(SDL_RenderDrawLine(Window::renderer,80+y*60,32,80+y*60,800-64)!=0)std::cout<<SDL_GetError()<<'\n';
        }
    }

    {/// render block spawn worms
        blocks->render();

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


    for(auto& e: enemys)delete e;
    for(auto& w: worms)delete w;
    for(auto& b: wormBullet)delete b;
    for(auto& b: blocks->tags)delete b;
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


