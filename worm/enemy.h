#pragma once

#include "Object.h"


class enemy: public Object
{
private:
    short ASP = 1000;
    short lastAttack = 0;
    int timerAttack = 0;
    int lastTakeDame = 0;
    int timerTakeDame = 0;
    bool isLive = true;
    bool isAtack = false;
    bool isDealDame = false;

    float yPos = 0;

    short Hp = 1000;
    float speed = 0.2;
    short strong = 20;
    short armo = 1;
    short numAtack = 1;

    short rHp;
    float rSpeed;
    short rStrong;
    short rArmo;
    short rRes;
    short rASP;

    float DameTaken = 0;

public:
    short inCollum = 0;

    enemy();

    void init(short hp, float sp, short str, short ar, short AtSP);
    void input();
    void update();
    void render();

    bool GetIsLive();
    bool GetIsAtack();
    short GetHp();
    short GetStrong();

    short GetNumAtack();
    bool GetDealAtack();


    void SetDameTaken(float x);
    void SetPos(short x, short y);
    void SetCol(short j);
    void SetIsAtack(bool a);
    void SetNumAtack(short a);

    void Kill();
};
