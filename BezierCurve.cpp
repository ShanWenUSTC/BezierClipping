#include "BezierCurve.h"
#include "graham.h"

#include <QtGui/qopengl.h>
#include <QDebug>
BezierCurve::BezierCurve()
{

}

BezierCurve::~BezierCurve()
{

}

float BezierCurve::base(double t)
{
    return t;
}

void BezierCurve::addPoint(double x, double y)
{
    point v(x, y);
    m_vConPoint.push_back( v );
}

void BezierCurve::drawConPoint()
{
    if( m_vConPoint.size()==0 )
    {
        return;
    }

    glColor3f( 0.0, 0.0, 1.0 );
    glPointSize(5);

    glBegin(GL_POINTS);
    for(size_t i=0; i<m_vConPoint.size(); i++)
    {
        glVertex2d(m_vConPoint[i].x, m_vConPoint[i].y);
    }
    glEnd();
}

void BezierCurve::drawConPoly()
{
    if(m_vConPoint.size()==0 || m_vConPoint.size()==1)
    {
        return;
    }

    glColor3f( 0.0f, 1.0f, 0.0f );

    glBegin(GL_LINES);
        for(size_t i=0; i<m_vConPoint.size(); i++)
        {
            if(m_vConPoint.size()-1 == i)
            {
                break;
            }

            glVertex2d(m_vConPoint[i].x, m_vConPoint[i].y);
            glVertex2d(m_vConPoint[i+1].x, m_vConPoint[i+1].y);
        }
    glEnd();
}

void BezierCurve::drawCurve()
{
    std::vector<point> drawPoint;
    std::vector<point> tempPoint;

    if( (m_vConPoint.size()==0)||(m_vConPoint.size()==1)||(m_vConPoint.size()==2) )
    {
        return;
    }

    double dx = 1.0/(m_vConPoint.size()-1)/20;
    double t = dx;

    drawPoint.push_back( m_vConPoint[0] );
    while(t<1)
    {
        drawPoint.push_back( deCasteljau(t) );
        t += dx;
    }
    drawPoint.push_back( m_vConPoint.back() );

    glColor3f( 1.0f, 0.0f, 0.0f );
    glBegin(GL_LINES);
        for(size_t i=0; i<drawPoint.size()-1; i++)
        {
            glVertex2d(drawPoint[i].x, drawPoint[i].y);
            glVertex2d(drawPoint[i+1].x, drawPoint[i+1].y);
        }
    glEnd();
}

point BezierCurve::deCasteljau(double t)
{
    point ptmp;
    std::vector<point> currentPoint(m_vConPoint);
    std::vector<point> lastPoint;

    while(currentPoint.size() != 1)
    {
        lastPoint = currentPoint;
        currentPoint.resize(0);

        for(size_t i=0; i<lastPoint.size()-1; i++)
        {
            ptmp = lastPoint[i]*(1-t) + lastPoint[i+1]*t;
            currentPoint.push_back(ptmp);
        }
    }

    return currentPoint[0];
}

int BezierCurve::searchNearPoint(double x, double y)
{
    float ftmp;
    float fmin = 100000000;
    int index = 0;

    for(size_t i=0; i<m_vConPoint.size(); i++)
    {
        ftmp = (m_vConPoint[i].x-x)*(m_vConPoint[i].x-x)
                +(m_vConPoint[i].y-y)*(m_vConPoint[i].y-y);
        if(ftmp<fmin)
        {
            index = i;
            fmin = ftmp;
        }
    }

    if( fmin>0.1 )
    {
        return -1;
    }
    return index;
}

void BezierCurve::updatePoint(int index, double x, double y)
{
    m_vConPoint[index].x = x;
    m_vConPoint[index].y = y;
}

void BezierCurve::clear()
{
    m_vConPoint.clear();
}

int BezierCurve::order()
{
    return m_vConPoint.size();
}

std::vector<point> BezierCurve::controlPoint()
{
    return m_vConPoint;
}
