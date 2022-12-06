#include "MainWindow.h"

namespace animation_cw3 {
MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , p_LeftPanel(new LeftPanelWidget(this))
    , p_3DWindow(new Qt3DExtras::Qt3DWindow())
{
    setWindowTitle("Animation CW3");

    auto layout = new QHBoxLayout(this);
    setLayout(layout);
    layout->addWidget(p_LeftPanel);
    layout->addWidget(QWidget::createWindowContainer(p_3DWindow));

    connect(p_LeftPanel, &LeftPanelWidget::animationParametersChanged, this, []() {
        qDebug() << "Animation parameters changed";
    });
}
}