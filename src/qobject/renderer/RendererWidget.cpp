#include "RendererWidget.h"

namespace animation_cw3::qobject::renderer {
RendererWidget::RendererWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , m_Scene(new Scene(this))
{
}

void RendererWidget::initializeGL()
{
}
void RendererWidget::resizeGL(int w, int h)
{
}
void RendererWidget::paintGL()
{
}
}