#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include "myOpenGL.h"

class myMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit myMainWindow(QWidget* parent = 0);
    ~myMainWindow();

    void resizeEvent(QResizeEvent*);

private:
    void open();
    void clear();
    void convexhull();

    void design_menubar();
    void design_toolbar();
    void design_statusbar();
    void design_action();

private:
    //user interface
    myOpenGL *pGL;      //openGL window
    QAction *openAction;
    QAction *clearAction;
    QAction *chAction;
    QMenuBar *pMenuBar;
    QToolBar *pToolBar;
    QStatusBar *pStatusBar;
};

#endif // MYMAINWINDOW_H
