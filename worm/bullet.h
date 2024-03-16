#pragma once
#include "Object.h"
#include "Vector2D.h"

class Bullet: public Object
{
private:
    int x_spawn,y_spawn;
    bool isSpawn = false;
    double power = 20;
    double speed = 0.2;
    bool isExist = true;
public:

    void spawn(int x = -100,int y = -100);
    void update(int x = 0, int y = 0);
    void del();
    void render();
    bool isCreated();
    bool Erase();

    void SetPower(double pw);
    void SetSpeed(double sp);

    double GetPower();

    bool IsExist();
};
