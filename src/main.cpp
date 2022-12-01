#include "qobject/MainWindow.h"

#include <QApplication>

using namespace animation_cw3;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    qobject::MainWindow* mainWindow = new qobject::MainWindow();
    app.setActiveWindow(mainWindow);
    mainWindow->show();
    app.exec();
    return 0;
}
