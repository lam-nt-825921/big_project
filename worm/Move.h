#pragma once
#include <bits/stdc++.h>
#include "Vector2D.h"

using namespace std;


class Move
{
public:

    static double MoveR,Movea,Movel;
    static Vector2D MoveButton, MoveI, MoveHand;


    static void MoveInit(Vector2D IPos, double r, Vector2D ButtonPos);

    static Vector2D GetVel();

    static double GetAng();
};
