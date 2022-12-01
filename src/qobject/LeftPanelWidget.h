#pragma once

#include <QPushButton>
#include <QVBoxLayout>
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

    QVBoxLayout* m_Layout;
    QPushButton* m_StartButton;
    QPushButton* m_PauseButton;
    QPushButton* m_ResetButton;

public:
    LeftPanelWidget(class MainWindow* parent = nullptr);

    inline const AnimationParameters& animationParameters() { return m_Params; }

signals:
    void startAnimation();
    void pauseAnimation();
    void resetAnimation();
};
}