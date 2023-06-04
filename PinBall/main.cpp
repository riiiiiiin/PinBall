
#include "Headers/mmainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MMainWindow w;
    w.show();
    return a.exec();
}
