#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QGLWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>

class BezierCurve;
class myOpenGL : public QGLWidget
{
    Q_OBJECT

public:
    myOpenGL(QWidget *parent = 0);
    ~myOpenGL();

    void clear();
    void convexhull();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent *);

private:
    void drawAxis();

private:
    BezierCurve* m_pBezierCurve;
    GLdouble x_max;
    GLdouble y_max;
    int m_status;
};

#endif // MYOPENGL_H