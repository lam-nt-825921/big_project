#include "bullet.h"

void Bullet:: spawn(int x,int y)
{
    if( x > -100 ) x_spawn = x;
    if( y > -100 ) y_spawn = y;
    SetDest_x(x_spawn);
    SetDest_y(y_spawn);
    isSpawn = true;
}

void Bullet:: update(int x, int y)
{
    if(isSpawn)SetDest({int(speed*x),int(speed*y),0,0},true);
    SDL_Rect pos = GetDest();
    if(pos.x > 500 || pos.x < 0 ||
       pos.y > 800 || pos.y < 0)del();
}

void Bullet:: del()
{
    SetDest_x(x_spawn);
    SetDest_y(y_spawn);
    isSpawn = false;
}

void Bullet:: render()
{
    if(isSpawn)Draw();
}

bool Bullet:: isCreated()
{
    return isSpawn;
}
