#include "mainwindow.h"
#include <QApplication>
#include "register.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Register* r=new Register;
    MainWindow w(r);
    w.show();

    return a.exec();
}
