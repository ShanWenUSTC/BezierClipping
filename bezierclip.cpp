#include "bezierclip.h"
#include "BezierCurve.h"
#include "graham.h"

#include <QtGui/qopengl.h>
#include <math.h>
#include <qDebug>

BezierClip::BezierClip(BezierCurve* pBezier)
{
    m_pBezierClip = pBezier;
    m_nOrder = pBezier->order();
}

BezierClip::~BezierClip()
{
    if( !(NULL==m_pBezierClip) )
    {
        delete m_pBezierClip;
    }
}

void BezierClip::findroot()
{
    if( m_lInterval.size()!=0 )
    {
        m_lInterval.clear();
    }

    m_vConvexhull.clear();
    m_lInterval.push_back( m_pBezierClip->controlPoint() );

    while( !(m_lInterval.size()==0) )
    {
        updateInterval( m_lInterval.front() );
        m_lInterval.pop_front();
    }
}

void BezierClip::updateInterval(conPoints& inConPoint)
{
    std::vector<double> t(m_nOrder);
    std::vector<double> y(m_nOrder);
    std::vector<double> hullt;
    std::vector<double> hully;

    for(int i=0; i<m_nOrder; i++)
    {
        t[i] = i*1.0/(m_nOrder-1);
        y[i] = inConPoint[i].y;
    }

    // convexhull of control polygon
    CGraham graham;
    graham.convex_hull(t, y, hullt, hully);

    std::vector<double> vtmp;
    for(size_t i=0; i<hullt.size()-1; i++)
    {
        if(hully[i]*hully[i+1]<0)
        {
            double scale = abs( hully[i+1]/( abs(hully[i+1])+abs(hully[i]) ) );
            vtmp.push_back( hullt[i]*scale+hullt[i+1]*(1-scale) );
        }
    }

    if(vtmp.size() == 0)
    {
        return;
    }
    else
    {
        conPoints front1;
        conPoints front2;
        conPoints back;
        conPoints outConPoint;

        deCasteljau(vtmp[1], inConPoint, front1, back);
        deCasteljau(vtmp[0]/vtmp[1], front1, front2, outConPoint);

        double delta = abs( outConPoint.front().x-outConPoint.back().x );

        if( delta<0.00001 )
        {
            m_vRoot.push_back(outConPoint.front().x);
        }
        else if( delta>abs( inConPoint.front().x-inConPoint.back().x )/2 )
        {
            deCasteljau(0.5, inConPoint, front1, back);
            m_lInterval.push_back( front1 );
            m_lInterval.push_back( back );
        }
        else
        {
            m_lInterval.push_back( outConPoint );
        }
    }
}

void BezierClip::deCasteljau(double scale, conPoints& in,
                             conPoints& outfront, conPoints& outback)
{
    conPoints current(in);
    conPoints last;

    if( !(outfront.size()==0) )
    {
        outfront.clear();
    }

    if( !(outback.size()==0) )
    {
        outback.clear();
    }

    outfront.resize( m_nOrder );
    outback.resize( m_nOrder );

    int index=1;
    outfront[0] = in[0];
    outback[ m_nOrder-1 ] = in.back();

    while(current.size() != 1)
    {
        last = current;
        current.resize(0);

        for(size_t i=0; i<last.size()-1; i++)
        {
            point ptmp = last[i]*(1-scale) + last[i+1]*scale;
            current.push_back(ptmp);
        }

        outfront[index] = current[0];
        outback[m_nOrder-1-index] = current.back();
        index++;
    }
}

void BezierClip::drawRoots()
{
    glColor3f(0.0f, 1.0f, 1.0f);
    qDebug()<<"rootsize: "<<m_vRoot.size();
    glBegin(GL_POINTS);
    for(size_t i= 0; i<m_vRoot.size(); i++)
    {
        glVertex2d(m_vRoot[i], 0.0);
        qDebug()<<m_vRoot[i];
    }

//    glColor3f(0.6, 0.7, 0.4);
//    for(size_t i=0; i<m_vConvexhull.size(); i++)
//    {
//        glVertex2d(m_vConvexhull[i], 0.0);
//    }
    glEnd();
}


