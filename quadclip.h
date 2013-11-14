#ifndef QUADCLIP_H
#define QUADCLIP_H

#include <list>
#include <vector>
#include "classdef.h"

typedef Point2 point;
typedef std::vector<point> conPoints;
typedef std::vector< std::vector<double> > mat;

class BezierCurve;
class QuadClip
{
public:
    QuadClip(BezierCurve* pBezier);
    ~QuadClip();

    void findroot();
    void drawRoots();

private:
    void updateInterval(conPoints& inConPoint);
    void changeOrder(conPoints& origin, mat& m, conPoints& result);
    void deCasteljau(double scale, conPoints& in,
                     conPoints& outfront, conPoints& outback);
    void init();
    int solveParabola(conPoints& ctrlPoints, double dleft, double dright, double& r1, double r2);
    int paraClip(conPoints& paraPoints, double dmax, double lastleft, double lastright, double& rleft1, double& rright1, double& rleft2, double& rright2);

private:
    BezierCurve* m_pBezierCurve;
    std::vector<double> m_vRoot;
    std::list< conPoints > m_lInterval;
    int m_nOrder;
    mat m_mReduce;
    mat m_mRaise;


};

#endif // QUADCLIP_H
