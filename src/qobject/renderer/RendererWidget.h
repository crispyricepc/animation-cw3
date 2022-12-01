#pragma once

#include "../Scene.h"

#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLWidget>

namespace animation_cw3::qobject::renderer {
class RendererWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core {
    Q_OBJECT

private:
    Scene* m_Scene;

public:
    RendererWidget(
        const LeftPanelWidget::AnimationParameters& params,
        QWidget* parent = nullptr);

    inline const Scene* scene() { return m_Scene; }

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

}