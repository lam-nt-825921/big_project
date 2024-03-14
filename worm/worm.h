#pragma once
#include "Object.h"
#include "bullet.h"
#include <vector>

class worm: public Object
{
private:
    int ASP = 1000;
    int lastAttack = 0;
    int timerAttack = 0;
    std::vector<Bullet*>listBullet;

public:

    void init(int x, const char* path, int fr = 1,int ms = 100, int num = 1);
    void update(int x = 0,int y = 0);
    void render();

    void SetTimer();
    void SetASP(int x);
    void SetPos(int x, int y);

    std::vector<Bullet*>& GetBullet();
};
