#pragma once
#include "Object.h"
#include "Vector2D.h"
#include "enemy.h"
#include <vector>

class Bullet: public Object
{
private:
    short x_spawn,y_spawn;
    bool isSpawn = false;
    float power = 20;
    float speed = 0.2;
    bool isExist = true;
    short numDealDame = 1;
    std::vector<enemy*>WasDealDame;

public:
    void spawn(short x = -100,short y = -100);
    void update(short x = 0, short y = 0);
    void del();
    void render();
    bool isCreated();
    bool Erase();

    void SetPower(float pw);
    void SetSpeed(float sp);
    void SetNumAtack(short x);

    float GetPower();
    short GetNumAtack();

    bool CheckEnemy(enemy* p);
    bool IsExist();
};
