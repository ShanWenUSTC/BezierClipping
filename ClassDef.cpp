#include "classdef.h"

/////////////////////////////////////
// class Point2
/////////////////////////////////////
//------------------------------
// constructor
//------------------------------
Point2::Point2()
{
    x = 0;
    y = 0;
}

Point2::Point2( int xx, int yy )
{
    x = (double)xx;
    y = (double)yy;
}

Point2::Point2( float xx, float yy )
{
    x = (double)xx;
    y = (double)yy;
}

Point2::Point2( double xx, double yy )
{
    x = xx;
    y = yy;
}

//------------------------------
// destructor
//------------------------------
Point2::~Point2()
{
}

//------------------------------
//
//------------------------------
double Point2::operator *(Point2& v)
{
    return (x*v.x+y*v.y);
}

Point2 Point2::operator +(Point2& v)
{
    Point2 r;

    r.x = x+v.x;
    r.y = y+v.y;

    return r;
}

Point2 Point2::operator -(Point2& v)
{
    Point2 r;

    r.x = x-v.x;
    r.y = y-v.y;

    return r;
}

Point2 Point2::operator *(int k)
{
    Point2 r;

    r.x = x*(double)k;
    r.y = y*(double)k;

    return r;
}

Point2 Point2::operator *(float k)
{
    Point2 r;

    r.x = x*k;
    r.y = y*k;

    return r;
}

Point2 Point2::operator *(double k)
{
    Point2 r;

    r.x = x*k;
    r.y = y*k;

    return r;
}

Point2 Point2::operator /(double k)
{
    Point2 r;

    r.x = x/k;
    r.y = y/k;

    return r;
}

//Point Point2::operator =()
//{

//}

















