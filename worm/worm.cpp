#include "worm.h"

void worm:: init(int x, const char* path,int fr, int ms , int num )
{
    while(x--)
    {
        listBullet.push_back(new Bullet);
        listBullet.back()->SetAni(path,fr,ms,num);
    }
}

void worm:: update(int x,int y)
{
    if(timerAttack - lastAttack >= ASP)
    {
        for(auto& b : listBullet)if(!b->isCreated())
        {
            b->spawn(GetDest().x, GetDest().y);
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

void worm:: SetTimer()
{
    timerAttack = SDL_GetTicks();
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
