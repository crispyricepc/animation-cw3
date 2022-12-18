#pragma once

#include "LeftPanelWidget.h"

#include "Animation.h"

#include <QHBoxLayout>
#include <QTimer>
#include <QWidget>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>

namespace animation_cw3 {
class MainWindow : public QWidget {
    Q_OBJECT
private:
    LeftPanelWidget* p_LeftPanel;
    Qt3DExtras::Qt3DWindow* p_3DWindow;
    QTimer* p_Timer;

    Animation* p_Animation;

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void onStartAnimation();
    void onPauseAnimation();
    void onResumeAnimation();
    void onResetAnimation();
};
}