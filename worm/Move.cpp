#include "Move.h"


double Move:: MoveR;
double Move:: Movea;
double Move:: Movel;

Vector2D Move:: MoveButton;
Vector2D Move:: MoveI;
Vector2D Move:: MoveHand;


void Move:: MoveInit(Vector2D IPos, double r, Vector2D ButtonPos)
{
    MoveI = IPos;
    MoveButton = ButtonPos;
    MoveR = r;
    double tmp = 1.0, X = MoveButton.x-MoveI.x, Y = MoveButton.y-MoveI.y;
    if(Y < 0) tmp = -1.0;
    Movel = sqrt(X*X + Y*Y);
    Movea = acos(tmp*X/Movel) + acos(tmp);
    MoveHand = {X*MoveR/Movel, Y*MoveR/Movel};
}

Vector2D Move::GetVel()
{

    return (MoveHand - MoveI);
}

double Move::GetAng()
{
    return Movea;
}
