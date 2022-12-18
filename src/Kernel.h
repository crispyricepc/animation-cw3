#pragma once

#include <QVector2D>

namespace animation_cw3::kernel {
QVector2D poly6(const QVector2D& position, float radius);
QVector2D spiky(const QVector2D& position, float radius);
QVector2D viscosity(const QVector2D& position, float radius);

/**
 * @brief A kernel function that takes a position @c r
 * and a radius @c h and returns a vector.
 */
using KernelFunction = QVector2D (*)(const QVector2D&, float);
} // namespace animation_cw3::kernel