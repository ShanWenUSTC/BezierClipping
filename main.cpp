#include <QApplication>
#include "myMainWindow.h"
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myMainWindow w;

    w.show();

    return a.exec();
}
