#include "Vector2D.h"
#include <algorithm>
#include <math.h>
Vector2D::Vector2D()
{
    x=0.0f;
    y=0.0f;
}

Vector2D:: Vector2D(float x,float y)
{
    this->x=x;
    this->y=y;
}

Vector2D& Vector2D:: Add(const Vector2D& vec)
{
    this->x+=vec.x;
    this->y+=vec.y;
    return *this;
}

Vector2D& Vector2D:: Subtract(const Vector2D& vec)
{
    this->x-=vec.x;
    this->y-=vec.y;
    return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
    this->x*=vec.x;
    this->y*=vec.y;
    return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec)
{
    this->x/=vec.x;
    this->y/=vec.y;
    return *this;
}

//Vector2D& Vector2D::Rotate(const Vector2D& vec,float angle)
//{
//    Vector2D tmp = vec.Divide(*this);
//    float x=tmp.x;
//    float y=tmp.y;
//    tmp=Vector2D( x*std::cos(angle) - y*std::sin(angle)  , x*std::sin(x) + y*std::cos(x) );
//
//    this->x+=tmp.x;
//    this->y+=tmp.y;
//
//    return *this;
//
//}


double Vector2D::Val(const Vector2D &a)const
{
    return sqrt(a.x*a.x + a.y*a.y);
}

double Vector2D::Length(const Vector2D& a, const Vector2D& b)const
{
    Vector2D c = b;
    c -=a;
    return Val(c);
}

Vector2D& operator +(Vector2D& v1,const Vector2D& v2)
{
    return v1.Add(v2);
}

Vector2D& operator -(Vector2D& v1,const Vector2D& v2)
{
    return v1.Subtract(v2);
}

Vector2D& operator *(Vector2D& v1,const Vector2D& v2)
{
    return v1.Multiply(v2);
}

Vector2D& operator /(Vector2D& v1,const Vector2D& v2)
{
    return v1.Divide(v2);
}

Vector2D& Vector2D:: operator *(const int &i)
{
    this->x*=i;
    this->y*=i;
    return *this;
}



Vector2D& Vector2D:: Zero()
{
    this->x=0;
    this->y=0;
    return *this;
}

Vector2D& Vector2D::  operator +=(const Vector2D& vec)
{
    return this->Add(vec);
}

Vector2D& Vector2D:: operator -=(const Vector2D& vec)
{
    return this->Subtract(vec);
}

Vector2D& Vector2D:: operator *=(const Vector2D& vec)
{
    return this->Multiply(vec);
}

Vector2D& Vector2D:: operator /=(const Vector2D& vec)
{
    return this->Divide(vec);
}



