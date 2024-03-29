#include "Particle.h"

#include "Forces.h"

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
    auto* transform = new Qt3DCore::QTransform(this);
    transform->setTranslation(QVector3D(initialPosition, 0));
    transform->setScale3D(QVector3D(scale, 1));
    addComponent(transform);

    auto* material = new Qt3DExtras::QPhongMaterial(this);
    addComponent(material);

    auto* meshLoader
        = new Qt3DRender::QMesh(this);
    meshLoader->setSource(QUrl("qrc:/objects/particle.obj"));
    addComponent(meshLoader);
}
void Particle::simulate(const ContainerComponent* container)
{
    auto* transform = componentsOfType<Qt3DCore::QTransform>()[0];
    auto oldPos = transform->translation().toVector2D();

    auto newPos = container->collideWith(oldPos);
    if (newPos != oldPos) {
        transform->setTranslation(QVector3D(newPos, 0));
        return;
    }

    auto gravity = forces::gravity(m_AnimationParameters.gravity);
    transform->setTranslation(transform->translation() + QVector3D(gravity, 0));
}
} // namespace animation_cw3