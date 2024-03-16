#pragma once

#include "Object.h"


class enemy: public Object
{
private:
    int ASP = 1000;
    int lastAttack = 0;
    int timerAttack = 0;
    int lastTakeDame = 0;
    int timerTakeDame = 0;
    bool isLive = true;
    bool isAtack = false;
    int inCollum = 0;
    bool isDealDame = false;

    double yPos = 0;

    int Hp = 1000;
    double speed = 0.2;
    int strong = 2;
    int armo = 1;
    int res = 1;

    int rHp;
    double rSpeed;
    int rStrong;
    int rArmo;
    int rRes;
    int rASP;

    double DameTaken = 0;

public:

    enemy();

    void init(int hp, double sp, int str, int ar, int re, int AtSP);
    void input();
    void update();
    void render();

    bool GetIsLive();
    bool GetIsAtack();
    int GetHp();
    int GetStrong();
    void GetTimer();

    void SetDameTaken(double x);
    void SetPos(int x, int y);
    void SetCol(int j);
    void SetIsAtack(bool a);

    bool DealAtack();
    void Kill();
};
