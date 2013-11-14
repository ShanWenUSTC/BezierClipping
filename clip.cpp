#include "clip.h"
#include <QtGui/qopengl.h>
#include <QDebug>

Clip::Clip()
{
}

void Clip::FindRoots()
{

}

void Clip::UpdateInterval(ControlPoint& last_points)
{

}

void Clip::DrawRoots()
{
    glColor3f(0.0f, 1.0f, 1.0f);
    qDebug()<<"rootsize: "<<roots_.size();
    glBegin(GL_POINTS);
    for (size_t i= 0; i<roots_.size(); i++)
    {
        glVertex2d(roots_[i], 0.0);
        qDebug()<<roots_[i];
    }
    glEnd();
}
