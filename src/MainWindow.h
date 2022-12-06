#pragma once

#include "LeftPanelWidget.h"

#include <QHBoxLayout>
#include <QWidget>

namespace animation_cw3 {
class MainWindow : public QWidget {
    Q_OBJECT
private:
    QHBoxLayout* m_Layout;
    LeftPanelWidget* m_LeftPanel;

public:
    MainWindow(QWidget* parent = nullptr);

private:
};
}