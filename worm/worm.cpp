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

void worm:: SetDesAniForBullet(short ms, short Act)
{
    for(auto& b : listBullet)b->setDesAni(ms,Act);
}

void worm:: input()
{
    timerAttack = Game::timer;
    if(type == 0)return;
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
                if(Game::wormMap[j-1][k-1]==nullptr)
                {
                    if(type == 5)
                    {
                        Erase();
                    }
                    else
                    {
                        Col = j-1;
                        Row = k-1;
                        Game::wormMap[Col][Row] = this;
                        SetDest_x(x);
                        SetDest_y(y);
                        isTake = false;
                        isFree = false;
                        SetStop(false);
                        lastAttack = timerAttack;
                    }
                }
                else if(type == 4 && Game::wormMap[j-1][k-1]->type == 4)
                {
                    Game::wormMap[j-1][k-1]->SetHp(rHp);
                    Erase();
                }
                else if(type == 5)
                {
                    Game::wormMap[j-1][k-1]->Erase();
                    Erase();
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

    if(type == 0)
    {
        if(GetDest().y < -64)Erase();
        else if(isFree == true)
        {
            SetAct(1);
            SetDest({0,-10,0,0},true);
        }
        return;
    }
    if(isFree == true)return;

    if(type == 3 || type == 6)///change face before atack
    {
        if((1000.0/Game::FPS)*(timerAttack - lastAttack) >= 0.75*ASP*60.0/Game::FPS)
        {
            SetAct(1);
        }
        else if((1000.0/Game::FPS)*(timerAttack - timerSpawn) >= 1000*60.0/Game::FPS)
        {
            SetAct(0);
        }
    }

    if(type == 3 || type == 4)///none spawn bullet
    {

        if(type == 4)
        {

            if(Hp<rHp/2)SetAct(1);
            else SetAct(0);
            return;
        }
        if(type == 3)
        {
            if((1000.0/Game::FPS)*(timerAttack - lastAttack) >= ASP*60.0/Game::FPS)
            {
                Game::money+=Cost;
                lastAttack = timerAttack;
            }
        }

        return;
    }


    if(Game::onGround[Col] > 0 && Game::onGround[Col] < (GetDest().y) &&/// has enemy on lane
       (1000.0/Game::FPS)*(timerAttack - lastAttack) >= ASP*60.0/Game::FPS)/// ready bullet
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
    Hp = rHp = x;
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

void worm::SetFree(bool x)
{
    if(type == 0)isTake = false;
    isFree = x;
}

void worm::beAtacked(short dame)
{
    Hp-=dame;
    if(Hp<0)Erase();
}


bool worm:: Erase()
{
    isExist = false;
    if(Col<10 && Row<10)Game::wormMap[Col][Row]=nullptr;
    for(auto& b:listBullet)b->Erase();
    listBullet.clear();
}

bool worm::GetFree()
{
    return isFree;
}
