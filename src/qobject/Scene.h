#pragma once

#include <QObject>

namespace animation_cw3::qobject {
namespace renderer {
    class RendererWidget;
}
class Scene : public QObject {
    Q_OBJECT
public:
    Scene(renderer::RendererWidget* parent);

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