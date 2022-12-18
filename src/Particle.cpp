#include "Particle.h"

#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QMesh>

namespace animation_cw3 {
Particle::Particle(
    Qt3DCore::QEntity* parent,
    const AnimationParameters& animationParameters,
    const QVector2D& initialPosition,
    const QVector2D& scale)
    : Qt3DCore::QEntity(parent)
    , m_AnimationParameters(animationParameters)
{
    auto transform = new Qt3DCore::QTransform(this);
    transform->setTranslation(QVector3D(initialPosition, 0));
    transform->setScale3D(QVector3D(scale / 3., 1));
    addComponent(transform);

    auto material = new Qt3DExtras::QPhongMaterial(this);
    addComponent(material);

    auto meshLoader
        = new Qt3DRender::QMesh(this);
    meshLoader->setSource(QUrl("qrc:/objects/particle.obj"));
    addComponent(meshLoader);
}
void Particle::simulate(kernel::KernelFunction kernelFunction)
{
    qDebug() << "Particle::simulate()";

    auto transform = componentsOfType<Qt3DCore::QTransform>()[0];
    auto position = transform->translation();

    auto newPosition = kernelFunction(position.toVector2D(), 10.f);
    transform->setTranslation(QVector3D(newPosition, 0));
}
}