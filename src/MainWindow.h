#pragma once

#include "LeftPanelWidget.h"

#include <QHBoxLayout>
#include <QWidget>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>

namespace animation_cw3 {
class MainWindow : public QWidget {
    Q_OBJECT
private:
    LeftPanelWidget* p_LeftPanel;
    Qt3DExtras::Qt3DWindow* p_3DWindow;

    Qt3DCore::QEntity* p_SceneRoot;

public:
    MainWindow(QWidget* parent = nullptr);

private:
};
}