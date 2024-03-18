#include "worm.h"
#include "game.h"

worm::worm()
{
    Game::worms.push_back(this);
}

void worm:: init(short x, const char* path, float sp, float pw ,short fr, short ms , short num ,short slmt)
{
    while(x--)
    {
        listBullet.push_back(new Bullet);
        Game::wormBullet.push_back(listBullet.back());
        listBullet.back()->SetAni(path,fr,ms,num);
        listBullet.back()->SetSpeed(sp);
        listBullet.back()->SetPower(pw);
        listBullet.back()->SetNumAtack(slmt);

    }
}

void worm:: input()
{
    timerAttack = Game::timer;
    if(Window::event.type == SDL_MOUSEMOTION)
    {
        if(isTake == true)
        {
            SetDest_x(Window::event.motion.x - width/2);
            SetDest_y(Window::event.motion.y - height/2);
        }
        if(isFree == true)
        {
            if(_Collision(GetDest(),{Window::event.button.x,Window::event.button.y,1,1}))SetStop(false);
            else SetStop(true);
        }

    }

    if(Window::event.type == SDL_MOUSEBUTTONDOWN)
    {
        short x = Window::event.button.x ;
        short y = Window::event.button.y;
        short j = (x - 80) / 60;
        short k = (800 - y) / 64;
        x = 80 + j*60 + (60 - width)/2;
        y = 800 - (k+1)*64 + (64 - height)/2;
        if(isTake == true)
        {
            if(x >= 140 && y > 32 && y < 800-64 )
            {
                if(Game::wormMap[j-1][k-1]==0)
                {
                    Col = j-1;
                    Row = k-1;
                    Game::wormMap[Col][Row]++;
                    SetDest_x(x);
                    SetDest_y(y);
                    isTake = false;
                    isFree = false;
                    SetStop(false);
                    lastAttack = timerAttack;
                }
            }
            else
            {
                Game::money += Cost;
                Erase();
            }
        }
    }

    if(Window::event.type == SDL_KEYDOWN)
    {
        switch(Window::event.key.keysym.sym)
        {
        case SDLK_e:
            Erase();
            break;
        default:
            break;
        }
    }

}

void worm:: update(short x,short y)
{
    if(isFree == true)return;
    if(listBullet.size() == 0)
    {

        if((1000.0/Game::FPS)*(timerAttack - lastAttack) >= ASP)
        {
            SetAct(1);
            Game::money+=Cost;
            timerSpawn = timerAttack;
            lastAttack = timerAttack;
        }
        else if((1000.0/Game::FPS)*(timerAttack - timerSpawn) >= 1000)
        {
            SetAct(0);
        }

    }
    else if(Game::onGround[Col] > 0 && Game::onGround[Col] < (GetDest().y) &&/// has enemy on lane
       (1000.0/Game::FPS)*(timerAttack - lastAttack) >= ASP)/// ready bullet
    {
        auto it = listBullet.begin();
        while (it != listBullet.end())
        {
            if ((*it)-> IsExist() == false)
            {
                delete (*it);
                it = listBullet.erase(it);
            }
            else it++;
        }
        bool ok = false;
        for(auto& b : listBullet)if(!b->isCreated())
        {
            b->spawn(GetDest().x + (GetDest().w - b->GetDest().w)/2, GetDest().y - b->GetDest().h);
            break;
        }

        lastAttack = timerAttack;
    }
    for(auto& b : listBullet)if(b->isCreated())b->update(x,y);

}

void worm:: render()
{
    Draw();
   // for(auto& b : listBullet)b->render();
}

void worm:: SetASP(short x)
{
    ASP = x;
}

void worm:: SetHp(short x)
{
    Hp = x;
}

std::vector<Bullet*>& worm:: GetBullet()
{
    return listBullet;
}

void worm:: SetPos(short x, short y)
{
    SetDest_x(x);
    SetDest_y(y);
}

void worm::beAtacked(short dame)
{
    Hp-=dame;
    if(Hp<0)Erase();
}


bool worm:: Erase()
{
    isExist = false;
    Game::wormMap[Col][Row]--;
    for(auto& b:listBullet)b->Erase();
    listBullet.clear();
}

bool worm::GetFree()
{
    return isFree;
}
