#include "graham.h"

CGraham::CGraham()
{

}

CGraham::~CGraham()
{

}

double CGraham::cross(const Point_ &O, const Point_ &A, const Point_ &B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

void CGraham::convex_hull(vector<double> x, vector<double> y, vector<double> &m_hull_x, vector<double> &m_hull_y)
{
    if(!m_hull_x.empty())
    {
        m_hull_x.clear();
        m_hull_y.clear();
    }
    int n = x.size();
    int k = 0;
    vector<Point_> P;
    vector<Point_> H(2*n);
    for(int i = 0; i != n; i++)
    {
        Point_ p;
        p.x = x[i];
        p.y = y[i];
        P.push_back(p);
    }
    sort(P.begin(), P.end());
    for (int i = 0; i < n; i++)
    {
        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0)
        {
            k--;
        }
        H[k++] = P[i];
    }
    for (int i = n-2, t = k+1; i >= 0; i--)
    {
        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0)
        {
            k--;
        }
        H[k++] = P[i];
    }
    H.resize(k);
    for(int i = 0; i != H.size(); i++)
    {
        double x, y;
        x = H[i].x;
        y = H[i].y;
        m_hull_x.push_back(x);
        m_hull_y.push_back(y);
    }
}
