#include "MainWindow.h"

namespace animation_cw3::qobject {
MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("Animation CW3");
    setMinimumSize(800, 600);
}
}