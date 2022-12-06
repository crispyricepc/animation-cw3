#pragma once

#include <QSlider>
#include <QVector2D>
#include <QWidget>

namespace animation_cw3 {
class LeftPanelWidget : public QWidget {
    Q_OBJECT
public:
    struct AnimationParameters {
        QVector2D tankDimensions; // Dimensions of the tank in meters
        QVector2D waterDimensions; // Initial dimensions of the water in the tank in meters
        QVector2D initialWaterPosition; // Initial position of the water in the tank in meters
        bool isRunning; // Is the animation currently running
    };

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

signals:
    void startAnimation();
    void pauseAnimation();
    void resetAnimation();

    void animationParametersChanged(const AnimationParameters& params);
};
}