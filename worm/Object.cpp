#include "Object.h"
#include "TextureManager.h"

Object:: Object(const char* path)
{
    SetAni(path);
}
Object::~Object()
{
    SDL_DestroyTexture(texture);
}


SDL_Rect Object:: GetDest()
{
    return dest;
}

SDL_Rect Object:: GetSrc()
{
    return src;
}

SDL_Texture* Object:: GetTex()
{
    return texture;
}

void Object:: SetDest(SDL_Rect _dest,bool t)
{
    if(t)
    {
        dest.x += _dest.x;
        dest.y += _dest.y;
        dest.w += _dest.w;
        dest.h += _dest.h;
    }
    else dest = _dest;
}

void  Object:: SetDest_x(short x)
{
    dest.x = x;
}

void Object:: SetDest_y(short y)
{
    dest.y = y;
}

void Object:: SetSrc(SDL_Rect _src)
{

    src = _src;
}

void Object:: SetTex(const char* path)
{
    texture = TextureManager::LoadTexture(path,width,height,frames,numA);
    dest = src = {0,0,width,height};
}

void Object:: Draw(bool x)
{
    timer_change = Game::timer;
    if(x)
    {
    }
    if((1000.0/Game::FPS)*(timer_change - last_change) >= msPF*60.0/Game::FPS)
    {
        last_change = timer_change;
        phase = (phase + 1)%frames;
        src.x = phase * width;
        src.y = Act * height;
    }
    if(Stop)src.x = 0;
    TextureManager::DrawTexture(texture,src,dest);
}

void Object::SetAni(const char* path,short _fr, short mpf, short num )
{

    frames = _fr;
    msPF = mpf;
    numA = num;
    SetTex(path);

}

void Object:: SetAct(short x)
{
    Act = x;
}

bool Object:: _Collision(SDL_Rect A, SDL_Rect B)
{
    return !(A.x > B.x + B.w||
             A.y > B.y + B.h||
             B.x > A.x + A.w||
             B.y > A.y + A.h);
}

bool Object:: Collision(SDL_Rect A)
{
    return _Collision(dest,A);
}

void Object:: SetStop(bool x)
{
    Stop = x;
}
