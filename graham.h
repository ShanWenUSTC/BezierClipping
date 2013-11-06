#ifndef GRAHAM_H
#define GRAHAM_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
        double x, y;

        bool operator <(const Point &p) const {
                return x < p.x || (x == p.x && y < p.y);
        }
};

class CGraham
{
public:
    CGraham();
    ~CGraham();
public:
    double cross(const Point &O, const Point &A, const Point &B);
    void convex_hull(vector<double> x, vector<double> y, vector<double> &m_hull_x, vector<double> &m_hull_y);
};
#endif
