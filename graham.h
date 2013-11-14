#ifndef GRAHAM_H
#define GRAHAM_H

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Point_ {
        double x, y;

        bool operator <(const Point_ &p) const {
                return x < p.x || (x == p.x && y < p.y);
        }
};

class CGraham
{
public:
    CGraham();
    ~CGraham();
public:
    double cross(const Point_ &O, const Point_ &A, const Point_ &B);
    void convex_hull(vector<double> x, vector<double> y, vector<double> &m_hull_x, vector<double> &m_hull_y);
};
#endif
