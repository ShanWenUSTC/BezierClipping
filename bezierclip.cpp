#include "bezierclip.h"
#include "BezierCurve.h"
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

void BezierClip::findroot(std::list<interval>& root,
                          std::list<interval>::iterator iter)
{
    std::vector<double> t(m_nOrder);
    std::vector<double> hullt;
    std::vector<double> hully;

    for(size_t i=0; i<m_nOrder; i++)
    {
        t[i] = i*1.0/(m_nOrder-1);
    }

    CGraham graham;
    graham.convex_hull(t, (*iter).y, hullx, hully);

    std::vector<double> vtmp;
    for(size_t i=0; i<hullx.size()-1; i++)
    {
        if(hully[i]*hull[i+1]<0)
        {
            double scale = abs( hully[i+1]/hully[i] );
            vtmp.push_back( hullx[i]*scale+hullx[i+1]*(1-scale) );
        }
    }

    qDebug()<<"size of vtmp: "<<tmp.size();
    if(vtmp.size() == 0)
    {
        erase(iter);
    }
    else
    {
       double tmp;
       if(vtmp[0]>vtmp[1])
       {
           tmp = vtmp[0];
           vtmp[0] = vtmp[1];
           vtmp[1] = tmp;
       }
    }

    if( vtmp[1]-vtmp[0]<0.001 )
    {
        m_vRoot.push_back(vtmp[0]);
        erase(iter);
    }
    else
    {
        std::vector<double> conx;
        std::vector<double> cony;

        deCasteljau(vtmp[1], )
    }
}

void BezierClip::deCasteljau(double scale, std::vector<double>& in,
                             std::vector<double>& outfront, std::vector<double>& outback)
{
    std::vector<double> current(in);
    std::vector<double> last;

    if( !(out.size()==0) )
    {
        out.resize(0);
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
            ptmp = last[i]*(1-t) + last[i+1]*t;
            current.push_back(ptmp);
        }

        outfront[index] = current[0];
        outback[m_nOrder-1-index] = current.back();
        intdex++;
    }
}
