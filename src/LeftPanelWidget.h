#pragma once

#include "AnimationParameters.h"

#include <QSlider>
#include <QWidget>

namespace animation_cw3 {
class LeftPanelWidget : public QWidget {
    Q_OBJECT
public:
private:
    AnimationParameters m_Params;

    QSlider* p_TankWidthSlider;
    QSlider* p_TankHeightSlider;
    QSlider* p_FluidWidthSlider;
    QSlider* p_FluidHeightSlider;
    QSlider* p_FluidXSlider;
    QSlider* p_FluidYSlider;

    QSlider* p_FluidDensitySlider;
    QSlider* p_ViscositySlider;
    QSlider* p_DeltaSlider;

public:
    LeftPanelWidget(class MainWindow* parent = nullptr);

    inline const AnimationParameters& animationParameters() { return m_Params; }

    void setTankDimensionRange(const QVector2D& min, const QVector2D& max);
    void setWaterDimensionRange(const QVector2D& min, const QVector2D& max);
    void setWaterPositionRange(const QVector2D& min, const QVector2D& max);
    void setFluidDensityRange(float min, float max);
    void setViscosityRange(float min, float max);
    void setDeltaRange(float min, float max);

    void setTankDimensions(const QVector2D& dimensions);
    void setWaterDimensions(const QVector2D& dimensions);
    void setWaterPosition(const QVector2D& position);
    void setFluidDensity(float density);
    void setViscosity(float viscosity);
    void setDelta(float delta);

signals:
    void startAnimation();
    void pauseAnimation();
    void resumeAnimation();
    void resetAnimation();

    void animationParametersChanged(const AnimationParameters& params);
};
}