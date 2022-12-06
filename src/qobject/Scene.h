#pragma once

#include "LeftPanelWidget.h"
#include "SceneObject.h"

#include <QObject>

namespace animation_cw3::qobject {
namespace renderer {
    class RendererWidget;
}
class Scene : public QObject {
    Q_OBJECT

private:
    const LeftPanelWidget::AnimationParameters& m_Params;
    std::vector<SceneObject*> m_Objects;

public:
    Scene(
        const LeftPanelWidget::AnimationParameters& params,
        renderer::RendererWidget* parent);

    inline const LeftPanelWidget::AnimationParameters& animationParameters() const { return m_Params; }

    inline const std::vector<SceneObject*>& objects() const { return m_Objects; }

signals:
    /**
     * @brief Called at a regular interval
     *
     * @param deltaTime The amount of time that has passed since
     *                  the last update in seconds
     */
    void tick(float deltaTime);
};
}