#pragma once

#include "LeftPanelWidget.h"
#include "renderer/RendererWidget.h"

#include <QHBoxLayout>
#include <QWidget>

namespace animation_cw3::qobject {
class MainWindow : public QWidget {
    Q_OBJECT
private:
    QHBoxLayout* m_Layout;
    LeftPanelWidget* m_LeftPanel;
    renderer::RendererWidget* m_RendererWidget;

public:
    MainWindow(QWidget* parent = nullptr);

private:
};
}