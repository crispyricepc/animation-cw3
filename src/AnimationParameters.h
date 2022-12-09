#pragma once

#include <QVector2D>

namespace animation_cw3 {
struct AnimationParameters {
    QVector2D tankDimensions; // Dimensions of the tank in meters
    QVector2D waterDimensions; // Initial dimensions of the water in the tank in meters
    QVector2D initialWaterPosition; // Initial position of the water in the tank in meters
    bool isRunning; // Is the animation currently running
};
}