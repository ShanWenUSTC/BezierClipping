#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "ClassDef.h"
#include <vector>

typedef Point2 point;

class BezierCurve
{
public:
    BezierCurve();
    ~BezierCurve();

    void drawConPoint();
    void drawConPoly();
    void drawCurve();

    void addPoint(double x, double y);
    int searchNearPoint(double x, double y);
    void updatePoint(int index, double x, double y);
    void clear();
    void calConvexHull(std::vector<double> x, std::vector<double> y, 
                       std::vector<double>& hullx, std::vector<double>& hully);
    int order();

private:
    float base(double t);         // Bernstein base function
    point deCasteljau(double t);

public:

private:
    std::vector<point> m_vConPoint;
    std::vector<double> m_vy;
    std::vector<double> m_inter;
};

#endif // BEZIERCURVE_H
