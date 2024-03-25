#pragma once
#include "Object.h"
#include "bullet.h"
#include <vector>

class worm: public Object
{
private:
    short ASP = 1000;
    short Hp = 1000;
    short rHp;
    short Col = 10;
    short Row = 10;

    int lastAttack = 0;
    int timerAttack = 0;
    int timerSpawn = 0;
    bool isTake = true;
    bool isFree = true;

    std::vector<Bullet*>listBullet;

public:

    short Cost = 100;
    short type;


    worm();

    bool isExist = true;

    void init(short x, const char* path, float sp, float pw, short fr = 1,short ms = 100, short num = 1,short slmt = 1);
    void input();
    void update(short x = 0,short y = 0);
    void render();

    bool GetFree();

    void SetASP(short x);
    void SetHp(short x);
    void SetPos(short x, short y);

    void beAtacked(short dame);

    std::vector<Bullet*>& GetBullet();

    bool Erase();
};
