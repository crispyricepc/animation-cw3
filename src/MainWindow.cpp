#include "MainWindow.h"

#include <QCoreApplication>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMesh>

namespace animation_cw3 {
Qt3DCore::QEntity* setupScene()
{
    auto sceneRoot = new Qt3DCore::QEntity();
    Qt3DRender::QMaterial* material = new Qt3DExtras::QPhongMaterial(sceneRoot);

    // Load the container 2D model
    auto container = new Qt3DCore::QEntity(sceneRoot);
    auto meshLoader = new Qt3DRender::QMesh(container);
    auto transform = new Qt3DCore::QTransform(container);
    meshLoader->setSource(QUrl("qrc:/objects/container.obj"));
    transform->setTranslation(QVector3D(0, 0, 0));
    container->addComponent(meshLoader);
    container->addComponent(material);
    container->addComponent(transform);

    return sceneRoot;
}

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , p_LeftPanel(new LeftPanelWidget(this))
    , p_3DWindow(new Qt3DExtras::Qt3DWindow())
    , p_SceneRoot(setupScene())
{
    setWindowTitle("Animation CW3");

    connect(p_LeftPanel, &LeftPanelWidget::animationParametersChanged, this, []() {
        qDebug() << "Animation parameters changed";
    });

    // Camera
    Qt3DRender::QCamera* camera = p_3DWindow->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 20));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // Camera controls
    auto cameraController = new Qt3DExtras::QOrbitCameraController(p_SceneRoot);
    cameraController->setLinearSpeed(50.0f);
    cameraController->setLookSpeed(180.0f);
    cameraController->setCamera(camera);

    p_3DWindow->setRootEntity(p_SceneRoot);

    auto layout = new QHBoxLayout(this);
    setLayout(layout);
    layout->addWidget(p_LeftPanel);
    layout->addWidget(QWidget::createWindowContainer(p_3DWindow));
}
}