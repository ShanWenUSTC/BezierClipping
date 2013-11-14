#include <iostream>
#include <QApplication>
#include "myMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myMainWindow w;

    w.show();

    return a.exec();
}
