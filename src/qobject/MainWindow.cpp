#include "MainWindow.h"

namespace animation_cw3::qobject {
MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , m_Layout(new QHBoxLayout(this))
    , m_LeftPanel(new LeftPanelWidget(this))
    , m_RendererWidget(new renderer::RendererWidget(m_LeftPanel->animationParameters(), this))
{
    setWindowTitle("Animation CW3");
    setMinimumSize(800, 600);

    setLayout(m_Layout);
    m_Layout->addWidget(m_LeftPanel);
    m_Layout->addWidget(m_RendererWidget);

    connect(m_LeftPanel, &LeftPanelWidget::animationParametersChanged, this, [this]() {
        m_RendererWidget->update();
    });
}
}