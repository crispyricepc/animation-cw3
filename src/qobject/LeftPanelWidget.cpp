#include "LeftPanelWidget.h"

#include "MainWindow.h"

namespace animation_cw3::qobject {
LeftPanelWidget::LeftPanelWidget(MainWindow* parent)
    : QWidget(parent)
    , m_Params({
          .tankDimensions = { 5, 5 },
          .waterDimensions = { 2, 3 },
          .initialWaterPosition = { 0, 4 },
          .isRunning = false,
      })
    , m_Layout(new QVBoxLayout(this))
    , m_StartButton(new QPushButton("Start", this))
    , m_PauseButton(new QPushButton("Pause", this))
    , m_ResetButton(new QPushButton("Reset", this))
{
    setLayout(m_Layout);
    m_Layout->setAlignment(Qt::AlignTop);
    m_Layout->addWidget(m_StartButton);
    m_Layout->addWidget(m_PauseButton);
    m_Layout->addWidget(m_ResetButton);
}
}