#include "MainWindow.h"

#include <QCoreApplication>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMesh>

namespace animation_cw3 {
MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , p_LeftPanel(new LeftPanelWidget(this))
    , p_3DWindow(new Qt3DExtras::Qt3DWindow())
    , p_Animation(new Animation(p_3DWindow))
{
    connect(p_LeftPanel, &LeftPanelWidget::animationParametersChanged,
        p_Animation, &Animation::onAnimationParametersChanged);

    setWindowTitle("Animation CW3");

    p_LeftPanel->setTankDimensionRange({ .5, .5 }, { 10, 10 });
    p_LeftPanel->setWaterDimensionRange({ .3, .3 }, { 8, 8 });
    p_LeftPanel->setWaterPositionRange({ -4, -4 }, { 4, 4 });
    p_LeftPanel->setFluidDensityRange(1, 10);
    p_LeftPanel->setViscosityRange(0.1, 10);
    p_LeftPanel->setDeltaRange(0.1, 10);
    p_LeftPanel->setTankDimensions({ 5, 5 });
    p_LeftPanel->setWaterDimensions({ 2, 3 });
    p_LeftPanel->setWaterPosition({ 4, -2 });
    p_LeftPanel->setFluidDensity(5);
    p_LeftPanel->setViscosity(1);
    p_LeftPanel->setDelta(1);

    auto layout = new QHBoxLayout(this);
    setLayout(layout);
    layout->addWidget(p_LeftPanel);
    layout->addWidget(QWidget::createWindowContainer(p_3DWindow));
}
}