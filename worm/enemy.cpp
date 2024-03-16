#include "enemy.h"
#include "Game.h"

enemy::enemy()
{
    Game::enemys.push_back(this);
}

void enemy::init(int hp, double sp, int str, int ar, int re, int AtSP)
{
    Hp = hp;
    speed = sp;
    strong = str;
    armo = ar;
    res = re;
    ASP = AtSP;

    rHp = Hp;
    rSpeed = speed;
    rStrong = strong;
    rArmo = armo;
    rRes = res;
    rASP = ASP;

    SetStop(false);
}

void enemy::input()
{

}

void enemy::update()
{
    if(isLive == false)return;
    if(isAtack)
    {
        if(timerAttack - lastAttack >= ASP)
        {
            SetAct(0);
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
    }
    if(DameTaken > 0 )
    {

        rHp -= DameTaken;
        std::cout<<rHp<<" auchi!\n";
        DameTaken = 0;
        if(rHp < 0)Kill();
    }
}

void enemy::render()
{
    if(isLive == false)return;
    Draw();
}

void enemy::GetTimer()
{
    timerAttack = SetTimer();
  //  timerTakeDame = timerAttack;
}

bool enemy::GetIsLive()
{
    return isLive;
}

bool enemy::GetIsAtack()
{
    return isAtack;
}

int enemy::enemy::GetHp()
{
    return rHp;
}

int enemy::GetStrong()
{
    return rStrong;
}

void enemy::SetDameTaken(double x)
{
    if(armo>=0) DameTaken += x*(100.0/(100+armo));
    if(armo<0) DameTaken += x*(2.0- 100.0/(100-armo));
}

void enemy::SetPos(int x, int y)
{
    SetDest_x(x);
    SetDest_y(y);
    yPos = y;
}

void enemy::SetCol(int j)
{
    inCollum = j;
    SetPos(140 + j*64 + (64- GetDest().w)/2, 0);
}

bool enemy::DealAtack()
{
    return isAtack;
}

void enemy::SetIsAtack(bool a)
{
    isAtack = a;
}

void enemy::Kill()
{
    isLive = false;
    return;
}
