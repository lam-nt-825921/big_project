#pragma once;
#include "Game.h"
#include "Move.h"


class Player
{
public:
    short  Act = 0;
    int last_change = 0;
    int timer_change = 0;
    short phase = 0,frames, msPF, numA,height, width;

    SDL_Texture* skin;
    SDL_Rect src;
    SDL_FRect dest;
    SDL_FRect Button;
    double speed = 1;

    Player();
    ~Player();

    double ang = 0;
    Vector2D I, velocity = {0,0};
    double R = 1;
    double bAng = 0;

    void update();
//    void update(Vector2D B);

    void SetAni(const char* path,short _fr= 1, short mpf = 100, short num = 1);
    void SetTex(const char* path);
    void Draw();
    bool Collision(SDL_FRect A);

};

struct Body
{
    SDL_Rect src;
    SDL_FRect dest;
    double ang;
    bool operator < (const Body& b)
    {
        return ((dest.x-b.dest.x)*(dest.x-b.dest.x) + (dest.y - b.dest.y)*(dest.y - b.dest.y) <=(dest.w + b.dest.w)*(dest.w + b.dest.w));
    }
};


class Snake
{
public:
    std::deque<Body> body;
    Player* head;
    int length = 0;
    double speed = 2.5;
    int space = 1;
    double cnt = 0;

    void init();
    void update();
    void render();
    void clean();
};
