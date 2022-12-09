#include "Animation.h"

#include "MainWindow.h"

#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QMesh>

namespace animation_cw3 {
Animation::Animation(Qt3DExtras::Qt3DWindow* window)
    : Qt3DCore::QEntity()
    , p_Container(new Qt3DCore::QEntity(this))
{
    // Load the container 2D model
    auto meshLoader = new Qt3DRender::QMesh(p_Container);
    auto material = new Qt3DExtras::QPhongMaterial(this);
    auto transform = new Qt3DCore::QTransform(p_Container);
    meshLoader->setSource(QUrl("qrc:/objects/container.obj"));
    transform->setTranslation(QVector3D(0, 0, 0));
    p_Container->addComponent(meshLoader);
    p_Container->addComponent(material);
    p_Container->addComponent(transform);

    // Camera
    Qt3DRender::QCamera* camera = window->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 20));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // Camera controls
    auto cameraController = new Qt3DExtras::QOrbitCameraController(this);
    cameraController->setLinearSpeed(50.0f);
    cameraController->setLookSpeed(180.0f);
    cameraController->setCamera(camera);

    window->setRootEntity(this);
}

void Animation::onAnimationParametersChanged(const AnimationParameters& params)
{
    auto transform = p_Container->componentsOfType<Qt3DCore::QTransform>()[0];
    transform->setScale3D(QVector3D(
        params.tankDimensions.x(),
        params.tankDimensions.y(),
        1));
}
}