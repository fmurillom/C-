#include "c_ide.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    C_IDE w;
    w.show();

    return a.exec();
}

