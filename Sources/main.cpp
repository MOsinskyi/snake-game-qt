#include "Headers/gamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    GameWindow window;
    window.show();
    return application.exec();
}
