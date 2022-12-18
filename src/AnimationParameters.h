#pragma once

#include <QVector2D>

namespace animation_cw3 {
struct AnimationParameters {
    QVector2D tankDimensions; // Dimensions of the tank in meters
    QVector2D fluidDimensions; // Initial dimensions of the fluid in the tank in meters
    QVector2D initialWaterPosition; // Initial position of the fluid in the tank in meters

    float fluidDensity = 0; // External force density field
    float viscosity = 0; // Viscosity of the fluid
    float delta = 0; // Time step, increase or decrease to slow down or speed up the simulation

    float gravity = 0; // Gravity constant

    bool isRunning = false; // Is the animation currently running
};
}