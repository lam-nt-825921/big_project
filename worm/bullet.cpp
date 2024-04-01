#include "bullet.h"
#include "Game.h"

void Bullet:: spawn(short x,short y)
{
    if( x > -100 ) x_spawn = x;
    if( y > -100 ) y_spawn = y;
    SetDest_x(x_spawn);
    SetDest_y(y_spawn);
    isSpawn = true;
    isDesAni = false;
    SetStop(false);
}

void Bullet:: update(short x, short y)
{
    if(isDesAni && (1000.0/Game::FPS)*(Game::timer - timerDes) >= msDes*60.0/Game::FPS)del(true);
    if(!isSpawn)return;

    SetDest({short(speed*x),short(speed*y),0,0},true);
    if(isDesAni)return;
    SDL_Rect pos = GetDest();
    if(WasDealDame.size() == numDealDame)del();
    else if(pos.x > 500 || pos.x < 0 ||
       pos.y > 800 || pos.y < 0)del();
       if(isDesAni)return;
}

void Bullet:: del(bool t)
{
    if(t)
    {
        isSpawn = false;
        isDesAni = false;
        SetDest_x(x_spawn);
        SetDest_y(y_spawn);
        WasDealDame.clear();
        speed = rSpeed;

        msPF = rMsPF;
        SetAct(0);
        return;
    }

    if(msDes > 0)
    {
        if(isDesAni == false)
        {
            timerDes = Game::timer;
            isDesAni = true;
            phase = 0;
            speed = 0.1;
            SetAct(ActDes);
            msPF = msDes/frames;
            return;
        }
    }
    else del(true);
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
    rSpeed = speed;
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

void Bullet:: setDesAni(short ms, short Act)
{
    rMsPF = msPF;

    msDes = ms;
    ActDes = Act;
}
