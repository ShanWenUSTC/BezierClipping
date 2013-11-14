#include "myMainWindow.h"
#include <iostream>
#include <string>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include "CPolynomial.h"

#include <QDebug>

myMainWindow::myMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //design size and position of mainwindow
    setGeometry(400, 100, 700, 500);

    //design menubar
    setWindowTitle(tr("Bezier Clipping"));
  //  std::cout<<"test";

    design_action();
    design_menubar();
    design_toolbar();
    design_statusbar();


    //design openGL window
    pGL = new myOpenGL (this);
    pGL->move(0, menuBar()->height()+pToolBar->height());
}

myMainWindow::~myMainWindow()
{
    delete pGL;
}

void myMainWindow::resizeEvent(QResizeEvent *e)
{
    pGL->resize( e->size().width(), e->size().height()-menuBar()->height()-pToolBar->height()-statusBar()->height() );
}

void myMainWindow::open()
{
    CPolynomial p;

    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt") );


    if(!path.isEmpty())
    {
        std::string str = path.toStdString();
        const char* filename = str.c_str();
        p.ReadFromFile( filename );
    }
    else
    {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
 //   p.ReadFromFile("P1.txt");
    qDebug()<<p(4.2f);
}

void myMainWindow::clear()
{
    pGL->clear();
}

void myMainWindow::convexhull()
{
    pGL->convexhull();
}

void myMainWindow::findRoot()
{
    pGL->findRoot();
}

void myMainWindow::design_menubar()
{
    pMenuBar = menuBar();
//    QMenu *menufile = pMenuBar->addMenu(tr("&File"));
//    menufile->addAction(openAction);

    QMenu *menuedit = pMenuBar->addMenu(tr("Edit"));
    menuedit->addAction(clearAction);

    QMenu *menushow = pMenuBar->addMenu(tr("TestShow"));
    menushow->addAction(chAction);
}

void myMainWindow::design_toolbar()
{
    pToolBar = addToolBar(tr("&File"));
 //   pToolBar->addAction(openAction);
    pToolBar->addAction(clearAction);
    pToolBar->addAction(findRootAction);
}

void myMainWindow::design_statusbar()
{
    pStatusBar = statusBar() ;
 //   pStatusBar->addAction(openAction);
    pStatusBar->addAction(clearAction);
    pStatusBar->addAction(chAction);
}

void myMainWindow::design_action()
{
//    openAction = new QAction(QIcon(":/images/doc-open"), tr("&Open..."),this);
//    openAction->setShortcut(QKeySequence::Open);
//    openAction->setStatusTip(tr("Open an existing file"));
//    connect(openAction, &QAction::triggered, this, &myMainWindow::open);

    clearAction = new QAction(QIcon(":/images/clear"), tr("&Clear"), this);
    clearAction->setStatusTip(tr("Clear screen"));
    connect(clearAction, &QAction::triggered, this, &myMainWindow::clear);

    chAction = new QAction(QIcon(":/images/doc-open"), tr("&Convex Hull"), this);
    chAction->setStatusTip(tr("Show Convex Hull of control points"));
    connect(chAction, &QAction::triggered, this, &myMainWindow::convexhull);

    findRootAction = new QAction(QIcon(":/images/doc-open"), tr("&Convex Hull"), this);
    connect(findRootAction, &QAction::triggered, this, &myMainWindow::findRoot);
}
