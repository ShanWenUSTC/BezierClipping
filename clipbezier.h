#ifndef ClipBezier_H
#define ClipBezier_H

#include <list>
#include <vector>
#include "classdef.h"
#include "clip.h"

class ClipBezier : public Clip
{
public:
    ClipBezier();
    ~ClipBezier();

    void FindRoots();

private:
    void deCasteljau(double scale, ControlPoint& in,
                     ControlPoint& outfront, ControlPoint& outback);
    void UpdateInterval(ControlPoint& inConPoint);
};

#endif // ClipBezier_H
