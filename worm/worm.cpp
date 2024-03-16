#include "worm.h"
#include "game.h"

worm::worm()
{
    Game::worms.push_back(this);
}

void worm:: init(int x, const char* path, double sp, double pw ,int fr, int ms , int num )
{
    while(x--)
    {
        listBullet.push_back(new Bullet);
        Game::wormBullet.push_back(listBullet.back());
        listBullet.back()->SetAni(path,fr,ms,num);
        listBullet.back()->SetSpeed(sp);
        listBullet.back()->SetPower(pw);

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
        int x = Window::event.button.x ;
        int y = Window::event.button.y;
        int j = (x - 80) / 60;
        int k = (800 - y) / 64;
        x = 80 + j*60 + (60 - width)/2;
        y = 800 - (k+1)*64 + (64 - height)/2;
        if(isTake == true)
        {
            if(x >= 140)
            {
                Col = (x - 140)/60;
                SetDest_x(x);
                SetDest_y(y);
                isTake = false;
                isFree = false;
                SetStop(false);
                lastAttack = timerAttack;
            }
            else Erase();
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

void worm:: update(int x,int y)
{
    if(isFree == true)return;
    if(Game::onGround[Col] > 0 && Game::onGround[Col] < (GetDest().y) &&/// has enemy on lane
       (1000.0/Game::FPS)*(timerAttack - lastAttack) >= ASP)/// ready bullet
    {
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

void worm:: SetASP(int x)
{
    ASP = x;
}

void worm:: SetHp(int x)
{
    Hp = x;
}

std::vector<Bullet*>& worm:: GetBullet()
{
    return listBullet;
}

void worm:: SetPos(int x, int y)
{
    SetDest_x(x);
    SetDest_y(y);
}

void worm::beAtacked(int dame)
{
    Hp-=dame;
    if(Hp<0)Erase();
}


bool worm:: Erase()
{
    isExist = false;
    for(auto& b:listBullet)b->Erase();
    listBullet.clear();
}

bool worm::GetFree()
{
    return isFree;
}
