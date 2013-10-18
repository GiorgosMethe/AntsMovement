/**
    Movement of Ants

    @author Georgios Methenitis @mailto: giorgosmethe@gmail.com
    @version 1.0 18/10/2013
*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
