#pragma once

#include <QObject>

namespace animation_cw3::qobject::renderer {
class RendererMesh : public QObject {
    Q_OBJECT
public:
    RendererMesh(class RendererWidget* parent);

private:
};
}