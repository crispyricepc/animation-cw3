#pragma once

#include "../Scene.h"

#include <QOpenGLWidget>

namespace animation_cw3::qobject::renderer {
class RendererWidget : public QOpenGLWidget {
    Q_OBJECT

private:
    Scene* m_Scene;

public:
    RendererWidget(QWidget* parent = nullptr);

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

}