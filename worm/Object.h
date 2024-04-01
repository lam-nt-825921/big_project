#pragma once

#include <SDL.h>

class Object
{
private:
    SDL_Rect dest,src;
    SDL_Texture* texture;

    short  Act = 0;
    int last_change = 0;
    int timer_change = 0;
    bool Stop = true;

public:

    short phase = 0,frames, msPF, numA;
    short height, width;

    Object() = default;
    Object(const char* path);
    ~Object();


    SDL_Rect GetDest();
    SDL_Rect GetSrc();
    SDL_Texture* GetTex();

    void SetDest(SDL_Rect _dest,bool t = false);
    void SetDest_x(short x);
    void SetDest_y(short y);
    void SetSrc(SDL_Rect _src);
    void SetTex(const char* path);
    void SetAni(const char* path,short _fr= 1, short mpf = 100, short num = 1);
    void SetAct(short x);
    void SetStop(bool x);

    void Draw(bool x = false);

    bool _Collision(SDL_Rect A, SDL_Rect B);
    bool Collision(SDL_Rect A);

};
