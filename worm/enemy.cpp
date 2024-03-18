#include "enemy.h"
#include "Game.h"

enemy::enemy()
{
    Game::enemys.push_back(this);
}

void enemy::init(short hp, float sp, short str, short ar, short AtSP)
{
    Hp = hp;
    speed = sp;
    strong = str;
    armo = ar;
    ASP = AtSP;

    rHp = Hp;
    rSpeed = speed;
    rStrong = strong;
    rArmo = armo;
    rASP = ASP;

    SetStop(false);
}

void enemy::input()
{

}

void enemy::update()
{
    timerAttack = Game::timer;
    if(isLive == false)return;
    if(isAtack)
    {
        if((1000.0/Game::FPS)*(timerAttack - lastAttack) >= ASP)
        {
            SetAct(1);
            isDealDame = true;
            lastAttack = timerAttack;
        }
        else isDealDame = false;
    }
    else
    {
        SetAct(0);
        yPos += rSpeed;
        SetDest_y(yPos);
        if(yPos >= 800)Game::isRunning = false;

    }
    if(DameTaken > 0 )
    {

        rHp -= DameTaken;
        DameTaken = 0;
        if(rHp < 0)Kill();
    }

}

void enemy::render()
{
    if(isLive == false)return;
    Draw();
}



bool enemy::GetIsLive()
{
    return isLive;
}

bool enemy::GetIsAtack()
{
    return isAtack;
}

short enemy::enemy::GetHp()
{
    return rHp;
}

short enemy::GetStrong()
{
    return rStrong;
}

short enemy::GetNumAtack()
{
    return numAtack;
}

void enemy::SetDameTaken(float x)
{
    if(armo>=0) DameTaken += x*(100.0/(100+armo));
    if(armo<0) DameTaken += x*(2.0- 100.0/(100-armo));
}

void enemy::SetPos(short x, short y)
{
    SetDest_x(x);
    SetDest_y(y);
    yPos = y;
}

void enemy::SetCol(short j)
{
    inCollum = j;
    SetPos(140 + j*60 + (60- GetDest().w)/2, 0);
}

bool enemy::GetDealAtack()
{
    return isDealDame;
}

void enemy::SetIsAtack(bool a)
{
    isAtack = a;
}

void enemy::SetNumAtack(short a)
{
    numAtack = a;
}

void enemy::Kill()
{
    Game::money += 25;
    Game::onGround[inCollum] = -1;
    isLive = false;
    return;
}
