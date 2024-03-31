#include "bullet.h"

void Bullet:: spawn(short x,short y)
{
    if( x > -100 ) x_spawn = x;
    if( y > -100 ) y_spawn = y;
    SetDest_x(x_spawn);
    SetDest_y(y_spawn);
    isSpawn = true;
    SetStop(false);
}

void Bullet:: update(short x, short y)
{
    if(isSpawn)SetDest({short(speed*x),short(speed*y),0,0},true);
    SDL_Rect pos = GetDest();
    if(WasDealDame.size() == numDealDame)del();
    else if(pos.x > 500 || pos.x < 0 ||
       pos.y > 800 || pos.y < 0)del();
}

void Bullet:: del()
{
    SetDest_x(x_spawn);
    SetDest_y(y_spawn);
    isSpawn = false;
    WasDealDame.clear();
}

void Bullet:: render()
{
    if(isSpawn)Draw();
}

bool Bullet:: isCreated()
{
    return isSpawn;
}

bool Bullet:: Erase()
{
    isExist = false;
}

void Bullet::SetPower(float pw)
{
    power = pw;
}

void Bullet::SetSpeed(float sp)
{
    speed = sp;
}

void Bullet:: SetNumAtack(short x)
{
    numDealDame = x;
}

float Bullet::GetPower()
{
    return power;
}

short Bullet:: GetNumAtack()
{
    return numDealDame;
}

bool Bullet:: CheckEnemy(enemy* p)
{
    if(WasDealDame.size() == numDealDame)return false;
    for(auto& t : WasDealDame)if(t == p)return false;
    WasDealDame.push_back(p);
    return true;
}

bool Bullet:: IsExist()
{
    return isExist;
}
