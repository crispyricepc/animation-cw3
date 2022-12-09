#pragma once

#include "AnimationParameters.h"

#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>

namespace animation_cw3 {
class Animation : public Qt3DCore::QEntity {
    Q_OBJECT
private:
    Qt3DCore::QEntity* p_Container;

public:
    Animation(Qt3DExtras::Qt3DWindow* window);

public slots:
    void onAnimationParametersChanged(const AnimationParameters& params);
};
}