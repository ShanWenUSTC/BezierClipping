#include <QtGui/qopengl.h>

#include "bezier_curve.h"
#include "graham.h"

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

void BezierCurve::AddPoint(double x, double y)
{
    point v(x, y);
    control_points_.push_back( v );
}

void BezierCurve::DrawControlPoint()
{
    if( control_points_.size()==0 )
    {
        return;
    }

    glColor3f( 0.0, 0.0, 1.0 );
    glPointSize(5);

    glBegin(GL_POINTS);
    for(size_t i=0; i<control_points_.size(); i++)
    {
        glVertex2d(control_points_[i].x, control_points_[i].y);
    }
    glEnd();
}

void BezierCurve::DrawControlPolygon()
{
    if(control_points_.size()==0 || control_points_.size()==1)
    {
        return;
    }

    glColor3f( 0.0f, 1.0f, 0.0f );

    glBegin(GL_LINES);
        for(size_t i=0; i<control_points_.size(); i++)
        {
            if(control_points_.size()-1 == i)
            {
                break;
            }

            glVertex2d(control_points_[i].x, control_points_[i].y);
            glVertex2d(control_points_[i+1].x, control_points_[i+1].y);
        }
    glEnd();
}

void BezierCurve::DrawCurve()
{
    std::vector<point> drawPoint;
    std::vector<point> tempPoint;

    if( (control_points_.size()==0)||(control_points_.size()==1)||(control_points_.size()==2) )
    {
        return;
    }

    double dx = 1.0/(control_points_.size()-1)/20;
    double t = dx;

    drawPoint.push_back( control_points_[0] );
    while(t<1)
    {
        drawPoint.push_back( deCasteljau(t) );
        t += dx;
    }
    drawPoint.push_back( control_points_.back() );

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
    std::vector<point> currentPoint(control_points_);
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

int BezierCurve::SearchNearPoint(double x, double y)
{
    float ftmp;
    float fmin = 100000000;
    int index = 0;

    for(size_t i=0; i<control_points_.size(); i++)
    {
        ftmp = (control_points_[i].x-x)*(control_points_[i].x-x)
                +(control_points_[i].y-y)*(control_points_[i].y-y);
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

void BezierCurve::UpdatePoint(int index, double x, double y)
{
    control_points_[index].x = x;
    control_points_[index].y = y;
}

void BezierCurve::Clear()
{
    control_points_.clear();
}

int BezierCurve::order()
{
    return control_points_.size();
}

std::vector<point> BezierCurve::control_points()
{
    return control_points_;
}
