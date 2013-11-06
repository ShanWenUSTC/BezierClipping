#ifndef BEZIERCLIP_H
#define BEZIERCLIP_H

#include <list>
#include <vector>

struct interval
{
    double left;
    double right;
    std::vector<double> x;
    std::vector<double> y;
};

class BezierCurve;
class BezierClip
{
public:
    BezierClip(BezierCurve* pBezier);
    ~BezierClip();

    void findroot(std::list<interval>& root,
                  std::list<interval>::iterator iter);

private:
    void calConvexHull(std::vector<double> x, std::vector<double> y,
                       std::vector<double>& hullx, std::vector<double>& hully);
    void deCasteljau(double scale, std::vector<double>& in, std::vector<double>& out);

private:
    BezierCurve* m_pBezierClip;
    std::list<interval> m_vRootInterval;
    std::vector<double> m_vRoot;
    int m_nOrder;
};

#endif // BEZIERCLIP_H
