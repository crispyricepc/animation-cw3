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
    QSlider* p_WaterWidthSlider;
    QSlider* p_WaterHeightSlider;
    QSlider* p_WaterXSlider;
    QSlider* p_WaterYSlider;

public:
    LeftPanelWidget(class MainWindow* parent = nullptr);

    inline const AnimationParameters& animationParameters() { return m_Params; }

    void setTankDimensionRange(const QVector2D& min, const QVector2D& max);
    void setWaterDimensionRange(const QVector2D& min, const QVector2D& max);
    void setWaterPositionRange(const QVector2D& min, const QVector2D& max);

    void setTankDimensions(const QVector2D& dimensions);
    void setWaterDimensions(const QVector2D& dimensions);
    void setWaterPosition(const QVector2D& position);

signals:
    void startAnimation();
    void pauseAnimation();
    void resetAnimation();

    void animationParametersChanged(const AnimationParameters& params);
};
}