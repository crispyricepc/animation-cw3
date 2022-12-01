#include "Scene.h"

#include "renderer/RendererWidget.h"

namespace animation_cw3::qobject {
Scene::Scene(const LeftPanelWidget::AnimationParameters& params,
    renderer::RendererWidget* parent)
    : QObject(parent)
    , m_Params(params)
{
}
}