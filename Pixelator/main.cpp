#include "pixelator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pixelator w;
    w.show();
    return a.exec();
}
