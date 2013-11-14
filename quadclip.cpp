#include "quadclip.h"
#include "bezier_curve.h"
#include "Coef.h"

#include <QtGui/qopengl.h>
#include <QDebug>

QuadClip::QuadClip(BezierCurve* pBezier)
{
    m_pBezierCurve = pBezier;
    m_nOrder = pBezier->order();
}

QuadClip::~QuadClip()
{

}

void QuadClip::findroot()
{
    if( m_nOrder<2 )
    {
        return;
    }

    init();

    if( m_lInterval.size()!=0 )
    {
        m_lInterval.clear();
    }

    m_lInterval.push_back( m_pBezierCurve->control_points() );

    while( !(m_lInterval.size()==0) )
    {
        updateInterval( m_lInterval.front() );
        m_lInterval.pop_front();
    }
}

void QuadClip::updateInterval(conPoints &inConPoint)
{
    conPoints ctrlPoints(m_nOrder);

    for(int i=0; i<m_nOrder; i++)
    {
        ctrlPoints[i].x = i*1.0/(m_nOrder-1);
        ctrlPoints[i].y = inConPoint[i].y;
    }

    qDebug()<<"here1";
    conPoints reducedPoints(3);
    conPoints raisedPoints(m_nOrder);

    changeOrder(ctrlPoints, m_mReduce, reducedPoints);
    changeOrder(reducedPoints, m_mRaise, raisedPoints);

    qDebug()<<"here2";
    double dmax=0;
    double dtmp;

    for(int i=0; i<m_nOrder; i++)
    {
        dtmp = abs(ctrlPoints[i].y-raisedPoints[i].y);
        dmax = dtmp > dmax ? dtmp : dmax;
    }

    double dleft = inConPoint.front().x;
    double dright = inConPoint.back().x;
    double dFirstL, dFirstR, dSecL, dSecR;

    int nRoot = paraClip(raisedPoints, dmax, dleft, dright, dFirstL, dFirstR, dSecL, dSecR);
    qDebug()<<"root"<<nRoot;
    if (nRoot == 0)
    {
        return;
    }
    else
    {
        dtmp = (dFirstR - dFirstL > dSecR - dSecL) ? (dFirstR - dFirstL) : (dSecR - dSecL);
        if (dtmp < (dright-dleft)/2.0)
        {
            conPoints front1;
            conPoints front2;
            conPoints back;
            conPoints outConPoint;

            deCasteljau((dFirstR - dleft)/(dright - dleft), inConPoint, front1, back);
            deCasteljau((dFirstL - dleft)/(dFirstR - dleft), front1, front2, outConPoint);

            double delta = abs( outConPoint.front().x-outConPoint.back().x );
            if( delta<0.1 )
            {
                m_vRoot.push_back( (outConPoint.front().x+outConPoint.back().x)/2 );
            }
            else
            {
                m_lInterval.push_back(outConPoint);
            }

            if( nRoot==2 )
            {
                deCasteljau((dSecR - dleft)/(dright - dleft), inConPoint, front1, back);
                deCasteljau((dSecL - dleft)/(dSecR - dleft), front1, front2, outConPoint);

                delta = abs( outConPoint.front().x-outConPoint.back().x );

                if( delta<0.1 )
                {
                    m_vRoot.push_back( (outConPoint.front().x+outConPoint.back().x)/2 );
                }
                else
                {
                    m_lInterval.push_back(outConPoint);
                }
            }
        }
        else
        {
            conPoints front;
            conPoints back;
            deCasteljau(0.5, inConPoint, front, back);
            m_lInterval.push_back( front );
            m_lInterval.push_back( back );
        }
    }

}

void QuadClip::changeOrder(conPoints& origin, mat& m, conPoints& result)
{
    qDebug()<<"origin"<<origin.size();
    qDebug()<<"result"<<result.size();
    qDebug()<<"m"<<m.size();
    for(size_t i=0; i<result.size(); i++)
    {
        result[i].x = 0;
        result[i].y = 0;
        for(size_t j=0; j<origin.size(); j++)
        {
            result[i] = result[i] + origin[j]*m[j][i];
        }
    }
}

void QuadClip::init()
{
    CCoef coe1(m_nOrder-1, 2);
    coe1.GetMatrix(m_mReduce);

    CCoef coe2(2, m_nOrder-1);
    coe2.GetMatrix(m_mRaise);
}

int QuadClip::solveParabola(conPoints &ctrlPoints, double dleft, double dright, double &r1, double r2)
{
    double delta = ctrlPoints[1].y * ctrlPoints[1].y - ctrlPoints[0].y*ctrlPoints[2].y;
    double frac = ctrlPoints[0].y + ctrlPoints[2].y - 2 * ctrlPoints[1].y;
    double tmp;

    if (frac == 0)
    {
        r1 = r2 = 0.5 * ctrlPoints[0].y / (ctrlPoints[0].y - ctrlPoints[1].y);
        return 2;
    }
    if (delta < 0)
    {
        return 0;
    }
    delta = sqrt(delta);

    r1 = (ctrlPoints[0].y - ctrlPoints[1].y - delta)/frac;
    r2 = (ctrlPoints[0].y - ctrlPoints[1].y + delta)/frac;

    r1 = (1 - r1) * dleft + r1 * dright;
    r2 = (1 - r2) * dleft + r2 * dright;

    if (r1 > r2)
    {
        tmp = r1;
        r1 = r2;
        r2 = tmp;
    }
    return 2;
}

int QuadClip::paraClip(conPoints& paraPoints, double dmax, double lastleft, double lastright, double& rleft1, double& rright1, double& rleft2, double& rright2)
{
    conPoints vCtrl1(paraPoints);
    conPoints vCtrl2(paraPoints);

    for(size_t i=0; i<paraPoints.size(); i++)
    {
        vCtrl1[i].y = paraPoints[i].y+dmax;
        vCtrl2[i].y = paraPoints[i].y-dmax;
    }

    double left1, left2, right1, right2;
    int nRoot1 = solveParabola(vCtrl1, lastleft, lastright, left1, right1);
    int nRoot2 = solveParabola(vCtrl2, lastleft, lastleft, left2, right2);

    if ( (nRoot1 == 0) && (nRoot2 == 0) )
    {
        return 0;
    }
    else if ( (nRoot1 == 0) && (0 != nRoot2) )
    {
        if (left2 > lastright || right2 < lastleft)
        {
            return 0;
        }
        rleft1 = rleft2 = left2 > lastleft ? left2 : lastright;
        rright1 = rright2 = right2 < lastright ? right2 : lastright;

        return 1;
    }
    else if( (nRoot1 != 0) || (nRoot2 == 0) )
    {
        if (left1 > lastright || right1 < lastleft)
        {
            return 0;
        }
        rleft1 = rleft2 = left1 > lastleft ? left1 : lastleft;
        rright1 = rright2 = right1 < lastright ? right1 : lastright;

        return 1;
    }
    else
    {
        if (left1 > left2)
        {
            double tmp = left1;
            left1 = left2;
            left2 = tmp;

            tmp = right1;
            right1 = right2;
            right2 = tmp;
        }

        if ( (left2 < lastleft && right2 > lastright) || (right1 < lastleft) || (left1>lastright) )
        {
            return 0;
        }
        else if (left2 < lastleft && right2 < lastright)
        {
            rleft1 = rleft2 = right2 > lastleft ? right2 : lastleft;
            rright1 = rright2 = right1 < lastright ? right1 : lastright;
            return 1;
        }
        else if ( left2 < lastleft && right2 > lastright)
        {
            rleft1 = rleft2 = left1 > lastleft ? left1 : lastleft;
            rright1 = rright2 = left2 < lastright ? left2 : lastright;
            return 1;
        }
        else if ( left2 > lastleft && right2 < lastright)
        {
            rleft1 = left1 > lastleft ? left1 : lastleft;
            rright1 = left2;
            rleft2 = right2;
            rright2 = right1 < lastright ? right1 : lastright;
            return 2;
        }
        else
        {
            return 0;
        }
    }
}

void QuadClip::deCasteljau(double scale, conPoints& in,
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

void QuadClip::drawRoots()
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
