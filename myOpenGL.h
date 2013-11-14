#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QEvent>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>

class Clip;
class myOpenGL : public QGLWidget
{
    Q_OBJECT

public:
    myOpenGL(QWidget *parent = 0);
    ~myOpenGL();

    void clear();
    void convexhull();
    void findRoot();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent *);

private:
    void drawAxis();

private:
    Clip* clip_pointor_;

    GLdouble x_max;
    GLdouble y_max;
    int m_status;
};

#endif // MYOPENGL_H
