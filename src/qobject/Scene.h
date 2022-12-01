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

private:
};
}