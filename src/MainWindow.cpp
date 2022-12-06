#include "MainWindow.h"

namespace animation_cw3 {
MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , m_Layout(new QHBoxLayout(this))
    , m_LeftPanel(new LeftPanelWidget(this))
{
    setWindowTitle("Animation CW3");

    setLayout(m_Layout);
    m_Layout->addWidget(m_LeftPanel);

    connect(m_LeftPanel, &LeftPanelWidget::animationParametersChanged, this, []() {
        qDebug() << "Animation parameters changed";
    });
}
}