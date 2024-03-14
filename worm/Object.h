#pragma once

#include <SDL.h>

class Object
{
private:
    SDL_Rect dest,src;
    SDL_Texture* texture;
    int height, width;
    int frames, msPF, numA;
    int phase = 0, Act = 0;
    int last_change = 0;
    int timer_change = 0;

public:



    Object() = default;
    Object(const char* path);

    SDL_Rect GetDest();
    SDL_Rect GetSrc();
    SDL_Texture* GetTex();

    void SetDest(SDL_Rect _dest,bool t = false);
    void SetDest_x(int x);
    void SetDest_y(int y);
    void SetSrc(SDL_Rect _src);
    void SetTex(const char* path);
    void SetAni(const char* path,int _fr= 1, int mpf = 100, int num = 1);
    void SetTimer();
    void SetAct(int x);

    void Draw();

    bool Collision(SDL_Rect A, SDL_Rect B);

};
