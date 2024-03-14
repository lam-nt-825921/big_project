#include "worm.h"
#include "game.h"

void worm:: init(int x, const char* path,int fr, int ms , int num )
{
    while(x--)
    {
        listBullet.push_back(new Bullet);
        listBullet.back()->SetAni(path,fr,ms,num);
    }
}

void worm:: input()
{
    SDL_PollEvent(&Window::event);

    if(Window::event.type == SDL_MOUSEMOTION)
    {
        if(isTake == true)
        {

            SetDest_x(Window::event.motion.x - width/2);
            SetDest_y(Window::event.motion.y - height/2);
        }
    }

    if(Window::event.type == SDL_MOUSEBUTTONDOWN)
    {
        if(isTake == true)
        {
            isTake = false;
            isFree = false;
            lastAttack = timerAttack;
        }
        else if(isFree == true && _Collision(GetDest(),{Window::event.button.x,Window::event.button.y,1,1}))
        {
            isTake = true;
        }
    }

}

void worm:: update(int x,int y)
{
    if(isFree == true)return;
    if(timerAttack - lastAttack >= ASP)
    {
        for(auto& b : listBullet)if(!b->isCreated())
        {
            b->spawn(GetDest().x + (GetDest().w - b->GetDest().w)/2, GetDest().y);
            break;
        }
        lastAttack = timerAttack;
    }
    for(auto& b : listBullet)if(b->isCreated())b->update(x,y);

}

void worm:: render()
{
    for(auto& b : listBullet)b->render();
    Draw();
}

void worm:: GetTimer()
{
    timerAttack = SetTimer();
    for(auto& b : listBullet)b->SetTimer();
}

void worm:: SetASP(int x)
{
    ASP = x;
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
