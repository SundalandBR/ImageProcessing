#include "Image_processing.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Image_processing w;
    w.show();
    return a.exec();
}
