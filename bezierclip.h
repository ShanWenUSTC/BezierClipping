#ifndef BEZIERCLIP_H
#define BEZIERCLIP_H

#include <list>
#include <vector>
#include "ClassDef.h"

typedef Point2 point;
typedef std::vector<point> conPoints;

class BezierCurve;
class BezierClip
{
public:
    BezierClip(BezierCurve* pBezier);
    ~BezierClip();

    void findroot();
    void drawRoots();
    void drawConvexhull(conPoints& p1, conPoints& p2);

private:
    void calConvexHull(std::vector<double> x, std::vector<double> y,
                       std::vector<double>& hullx, std::vector<double>& hully);
    void deCasteljau(double scale, conPoints& in,
                     conPoints& outfront, conPoints& outback);
    void updateInterval(conPoints& inConPoint);

private:
    BezierCurve* m_pBezierClip;
    std::vector<double> m_vRoot;
    std::list< conPoints > m_lInterval;
    std::vector< double > m_vConvexhull;
    int m_nOrder;
};

#endif // BEZIERCLIP_H
