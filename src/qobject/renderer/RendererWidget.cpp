#include "RendererWidget.h"

namespace animation_cw3::qobject::renderer {
RendererWidget::RendererWidget(
    const LeftPanelWidget::AnimationParameters& params,
    QWidget* parent)
    : QOpenGLWidget(parent)
    , m_Scene(new Scene(params, this))
{
}

void RendererWidget::initializeGL()
{
    initializeOpenGLFunctions();
}
void RendererWidget::resizeGL(int, int)
{
}
void RendererWidget::paintGL()
{
    glClearColor(
        scene()->animationParameters().tankDimensions.x(),
        scene()->animationParameters().tankDimensions.y(),
        scene()->animationParameters().waterDimensions.x(),
        1.0f);
}
}