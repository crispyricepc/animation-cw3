#pragma once

#include <QSlider>
#include <QVector2D>
#include <QWidget>

namespace animation_cw3::qobject {
class LeftPanelWidget : public QWidget {
    Q_OBJECT
private:
    struct AnimationParameters {
        QVector2D tankDimensions; // Dimensions of the tank in meters
        QVector2D waterDimensions; // Initial dimensions of the water in the tank in meters
        QVector2D initialWaterPosition; // Initial position of the water in the tank in meters
        bool isRunning;
    } m_Params;

    QSlider* m_TankWidthSlider;
    QSlider* m_TankHeightSlider;
    QSlider* m_WaterWidthSlider;
    QSlider* m_WaterHeightSlider;
    QSlider* m_WaterXSlider;
    QSlider* m_WaterYSlider;

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
};
}