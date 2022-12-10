#pragma once

#include <QVector2D>

namespace animation_cw3 {
namespace kernel {
    QVector2D poly6(const QVector2D& position, float radius);
    QVector2D spiky(const QVector2D& position, float radius);
    QVector2D viscosity(const QVector2D& position, float radius);

    /**
     * @brief A kernel function that takes a position @c r
     * and a radius @c h and returns a vector.
     */
    typedef QVector2D (*KernelFunction)(const QVector2D&, float);
}
}