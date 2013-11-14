#include "clipbezier.h"

#include <math.h>
#include <QtGui/qopengl.h>
#include "bezier_curve.h"
#include "graham.h"

#include <QDebug>

ClipBezier::ClipBezier()
{

}

ClipBezier::~ClipBezier()
{

}

void ClipBezier::FindRoots()
{
    if( interval_.size()!=0 )
    {
        interval_.clear();
    }

    interval_.push_back( control_points() );

    while( !(interval_.size()==0) )
    {
        UpdateInterval( interval_.front() );
        interval_.pop_front();
    }
}

void ClipBezier::UpdateInterval(ControlPoint& inConPoint)
{
    std::vector<double> t(order());
    std::vector<double> y(order());
    std::vector<double> hullt;
    std::vector<double> hully;

    for(int i=0; i<order(); i++)
    {
        t[i] = i*1.0/(order()-1);
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
        ControlPoint front1;
        ControlPoint front2;
        ControlPoint back;
        ControlPoint outConPoint;

        deCasteljau(vtmp[1], inConPoint, front1, back);
        deCasteljau(vtmp[0]/vtmp[1], front1, front2, outConPoint);

        double delta = abs( outConPoint.front().x-outConPoint.back().x );

        if( delta<0.00001 )
        {
            roots_.push_back(outConPoint.front().x);
        }
        else if( delta>abs( inConPoint.front().x-inConPoint.back().x )/2 )
        {
            deCasteljau(0.5, inConPoint, front1, back);
            interval_.push_back( front1 );
            interval_.push_back( back );
        }
        else
        {
            interval_.push_back( outConPoint );
        }
    }
}

void ClipBezier::deCasteljau(double scale, ControlPoint& in,
                             ControlPoint& outfront, ControlPoint& outback)
{
    ControlPoint current(in);
    ControlPoint last;

    if( !(outfront.size()==0) )
    {
        outfront.clear();
    }

    if( !(outback.size()==0) )
    {
        outback.clear();
    }

    outfront.resize( order() );
    outback.resize( order() );

    int index=1;
    outfront[0] = in[0];
    outback[ order()-1 ] = in.back();

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
        outback[order()-1-index] = current.back();
        index++;
    }
}
