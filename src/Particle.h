#pragma once

#include "AnimationParameters.h"
#include "ContainerComponent.h"
#include "Kernel.h"

#include <Qt3DCore/QEntity>

namespace animation_cw3 {
class Particle : public Qt3DCore::QEntity {
    Q_OBJECT

private:
    const AnimationParameters& m_AnimationParameters;

public:
    Particle(
        Qt3DCore::QEntity* parent,
        const AnimationParameters& animationParameters,
        const QVector2D& initialPosition = { 0, 0 },
        const QVector2D& scale = { .5, .5 });

    [[nodiscard]] inline const AnimationParameters& animationParameters() const { return m_AnimationParameters; }

    void simulate(const ContainerComponent* container);
};
} // namespace animation_cw3