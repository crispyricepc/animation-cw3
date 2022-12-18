#include "MainWindow.h"

#include <QCoreApplication>
#include <QTimer>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMesh>

namespace animation_cw3 {
MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , p_LeftPanel(new LeftPanelWidget(this))
    , p_3DWindow(new Qt3DExtras::Qt3DWindow())
    , p_Timer(new QTimer(this))
    , p_Animation(new Animation(p_3DWindow))
{
    connect(p_LeftPanel, &LeftPanelWidget::animationParametersChanged,
        p_Animation, &Animation::onAnimationParametersChanged);
    connect(p_Timer, &QTimer::timeout, p_Animation, &Animation::simulate);
    connect(p_LeftPanel, &LeftPanelWidget::startAnimation, this, &MainWindow::onStartAnimation);
    connect(p_LeftPanel, &LeftPanelWidget::pauseAnimation, this, &MainWindow::onPauseAnimation);
    connect(p_LeftPanel, &LeftPanelWidget::resumeAnimation, this, &MainWindow::onResumeAnimation);
    connect(p_LeftPanel, &LeftPanelWidget::resetAnimation, this, &MainWindow::onResetAnimation);

    setWindowTitle("Animation CW3");

    p_LeftPanel->setTankDimensionRange({ .5, .5 }, { 10, 10 });
    p_LeftPanel->setWaterDimensionRange({ .3, .3 }, { 8, 8 });
    p_LeftPanel->setWaterPositionRange({ -4, -4 }, { 4, 4 });
    p_LeftPanel->setFluidDensityRange(1, 10);
    p_LeftPanel->setViscosityRange(0.1, 10);
    p_LeftPanel->setDeltaRange(0.1, 10);
    p_LeftPanel->setGravityRange(.01, 1);
    p_LeftPanel->setTankDimensions({ 5, 5 });
    p_LeftPanel->setWaterDimensions({ 2, 3 });
    p_LeftPanel->setWaterPosition({ -1, 2 });
    p_LeftPanel->setFluidDensity(5);
    p_LeftPanel->setViscosity(1);
    p_LeftPanel->setDelta(1);
    p_LeftPanel->setGravity(.1);

    auto layout = new QHBoxLayout(this);
    setLayout(layout);
    layout->addWidget(p_LeftPanel);
    layout->addWidget(QWidget::createWindowContainer(p_3DWindow));
}

void MainWindow::onStartAnimation()
{
    p_Timer->start(1000 / 60);
}

void MainWindow::onPauseAnimation()
{
    p_Timer->stop();
}

void MainWindow::onResumeAnimation()
{
    p_Timer->start();
}

void MainWindow::onResetAnimation()
{
    p_Timer->stop();
    p_Animation->resetAnimation();
}
}