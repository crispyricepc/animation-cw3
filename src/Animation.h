#pragma once

#include "AnimationParameters.h"
#include "Particle.h"

#include <QList>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>

namespace animation_cw3 {
class Animation : public Qt3DCore::QEntity {
    Q_OBJECT
private:
    Qt3DCore::QEntity* p_Container;
    QList<Particle*> m_Particles;

    // Old parameters to be compared with when the parameters change
    AnimationParameters m_AnimationParametersDelta;

public:
    explicit Animation(Qt3DExtras::Qt3DWindow* window);

public slots:
    void simulate();
    void resetAnimation();
    void onAnimationParametersChanged(const AnimationParameters& params);
};
}