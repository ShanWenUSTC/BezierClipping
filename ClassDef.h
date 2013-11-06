#ifndef CLASSDEF_H
#define CLASSDEF_H

class Point2
{
public:
    Point2();
    Point2(int, int);
    Point2(float, float);
    Point2(double, double);
    ~Point2();

    Point2      operator + ( Point2& v );
    Point2      operator - ( Point2& v );
    double       operator * ( Point2& v );
    Point2      operator * ( int k );
    Point2      operator * ( float k );
    Point2      operator * ( double k );
    Point2      operator / ( double k );
    //Point2      operator = ();

public:
    double x;
    double y;
};



#endif // CLASSDEF_H
