#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    fuzzylite::setDebug(true);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
