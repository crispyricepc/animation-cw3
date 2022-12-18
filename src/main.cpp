#include "MainWindow.h"

#include <QApplication>

using namespace animation_cw3;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    auto* mainWindow = new MainWindow();
    QApplication::setActiveWindow(mainWindow);
    mainWindow->show();
    QApplication::exec();
    return 0;
}
