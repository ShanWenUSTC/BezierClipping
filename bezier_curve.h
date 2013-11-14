//copyright 2013 GCL
//  Shan Wen    sw09001@mail.ustc.edu.cn    shanwenn@gmail.com

//class BezierCurve implement Bezier curve, it accepts user input control
//  points by left button in the window, and draw its control polygon, control
//  points and curve, user can also click to control point by right button and
//  move mouse, see how curve changes with control point changes.
//  Sample useage:
//  BezierCurve pBezierCurve = new BezierCurve();
//  (in right button response function)pBezierCurve->AddPoint();
//  (in left button response function)pBezierCurve->SearchNearPoint(x, y)
//      pBezierCurve->UpdatePoint(index, x, y);
//  (in openGL window)pBezierCurve->DrawControlPolygon();
//      pBezierCurve->DrawCurve();
//      pBezierCurve->DrawControlPoint();
//  You'd better draw curve like the order shown above, so your points
//      wouldn't be covered by polygon and curve.

#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <vector>
#include "classdef.h"

typedef Point2 point;

class BezierCurve
{
public:
    BezierCurve();
    ~BezierCurve();

    void DrawControlPoint();
    void DrawControlPolygon();
    void DrawCurve();

    void AddPoint(double x, double y);
    int SearchNearPoint(double x, double y);
    void UpdatePoint(int index, double x, double y);
    void Clear();
    int order();
    std::vector<point> control_points();

private:
    float base(double t);         // Bernstein base function
    point deCasteljau(double t);

    std::vector<point> control_points_;
};

#endif // BEZIERCURVE_H
