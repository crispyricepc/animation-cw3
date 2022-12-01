#include "Scene.h"

#include "renderer/RendererWidget.h"

namespace animation_cw3::qobject {
Scene::Scene(renderer::RendererWidget* parent)
    : QObject(parent)
{
}
}