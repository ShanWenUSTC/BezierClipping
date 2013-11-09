#include "myOpenGL.h"
#include "BezierCurve.h"
#include "bezierclip.h"

#include <QDebug>
#define DRAG_POINT 1
#define ADD_POINT 0

myOpenGL::myOpenGL(QWidget *parent)
    :QGLWidget(parent)
{
    m_pBezierCurve = new BezierCurve();
    m_status = 0;
    m_pClip = NULL;
}

myOpenGL::~myOpenGL()
{

}

void myOpenGL::initializeGL()
{
    // 启用smooth shading
    glShadeModel( GL_SMOOTH );

    // 设置清屏颜色
    glClearColor( 0.5f, 0.5f, 0.5f, 0.0 );

    // 设置深度缓存
    glClearDepth( GL_DEPTH_TEST );
}

void myOpenGL::resizeGL(int width, int height)
{
    if( height == 0 )
    {
        height = 1;
    }

    //    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);


    //    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    //    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

   // 重置当前视口
   glViewport( 0, 0, (GLint)width, (GLint)height );

   // 选择投影矩阵
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();

   if (width <= height)
   {
       x_max = 5.0;
       y_max = 5.0*(GLfloat)height/(GLfloat)width;
       glOrtho(-x_max, x_max, -y_max, y_max, -1.0, 1.0);
   }
   else
   {
       x_max = 5.0*(GLfloat)width/(GLfloat)height;
       y_max = 5.0;
       glOrtho(-x_max, x_max, -y_max, y_max, -1.0, 1.0);
   }
}

void myOpenGL::paintGL()
{
    // 清除屏幕和深度缓存
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    drawAxis();

    m_pBezierCurve->drawConPoly();
    m_pBezierCurve->drawCurve();
    m_pBezierCurve->drawConPoint();

    if( !(m_pClip==NULL) )
    {
        m_pClip->drawRoots();
    }

//    test code
//    if(m_status)
//    {
//        m_pBezierCurve->drawConvexHull();
//    }
}

void myOpenGL::mousePressEvent(QMouseEvent *e)
{
    double x, y;

    switch(e->button())
    {
    case Qt::LeftButton:
        x = 2.0*x_max*e->pos().x()/width() - x_max;
        y = y_max - 2.0*y_max*e->pos().y()/height();
        m_pBezierCurve->addPoint( x, y );
        updateGL();

        break;

    case Qt::RightButton:

        break;

    default:
        break;
    }
}

void myOpenGL::mouseMoveEvent(QMouseEvent *e)
{
    double x, y;
    int index;

    switch(e->buttons())
    {
    case Qt::RightButton:
        x = 2.0*x_max*e->pos().x()/width() - x_max;
        y = y_max - 2.0*y_max*e->pos().y()/height();

        index = m_pBezierCurve->searchNearPoint(x, y);

        if( index<0 )
        {
            return;
        }
        else
        {
            m_pBezierCurve->updatePoint(index, x, y);
        }
        updateGL();

        break;

    default:
        break;
    }
}

void myOpenGL::clear()
{
    m_pBezierCurve->clear();
    updateGL();
}

void myOpenGL::convexhull()
{
  //  m_status = 1;
    updateGL();
}

void myOpenGL::drawAxis()
{
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(0.5);
    glBegin(GL_LINES);
        glVertex2f(-6.0, 0);
        glVertex2f(6.0, 0);
        glVertex2f(0, 6.0);
        glVertex2f(0, -6.0);
    glEnd();
}

void myOpenGL::findRoot()
{
    m_pClip = new BezierClip (m_pBezierCurve);
    m_pClip->findroot();
    updateGL();
}

