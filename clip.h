//copyright 2013 GCL
//  Shan Wen    sw09001@mail.ustc.edu.cn    shanwenn@gmail.com

//class clip inherits class BezierCurve, it can find roots of bezier curve, and
//  draw them in openGL window.   Sample usage:
//  Clip* pClip = new Clip();
//  (user inputs control points)
//  pClip->FindRoots;
//  (in openGL window) pClip->DrawRoots;

#ifndef CLIP_H
#define CLIP_H

#include <list>
#include <vector>
#include "bezier_curve.h"
#include "classdef.h"

typedef Point2 Point;
typedef std::vector<Point> ControlPoint;

class Clip : public BezierCurve
{
public:
    Clip();

    virtual void FindRoots();
    void DrawRoots();

protected:
    virtual void UpdateInterval(ControlPoint& last_points);
    std::vector<double> roots_;
    std::list<ControlPoint> interval_;
};

#endif // CLIP_H
