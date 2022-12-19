#include "ContainerComponent.h"

#include "Animation.h"

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

namespace animation_cw3 {
ContainerComponent::ContainerComponent(const Animation* animation, Qt3DCore::QNode* parent)
    : Qt3DCore::QComponent(parent)
{
    connect(animation, &Animation::containerDimensionsChanged, this, &ContainerComponent::onDimensionsChanged);
}

QVector2D ContainerComponent::collideWith(const QVector2D& point) const
{
    auto* transform = dynamic_cast<Qt3DCore::QEntity*>(parentNode())->componentsOfType<Qt3DCore::QTransform>()[0];
    auto position = transform->translation().toVector2D();
    auto halfDimensions = m_Dimensions / 2.;
    auto relativePosition = point - position;
    if (relativePosition.x() < -halfDimensions.x()) {
        return { 1, 0 };
    }
    if (relativePosition.x() > halfDimensions.x()) {
        return { -1, 0 };
    }
    if (relativePosition.y() < -halfDimensions.y()) {
        return { 0, 1 };
    }

    return point;
}

void ContainerComponent::onDimensionsChanged(const QVector2D& dimensions)
{
    m_Dimensions = dimensions;

    // Update transform
    auto* transform = dynamic_cast<Qt3DCore::QEntity*>(parentNode())->componentsOfType<Qt3DCore::QTransform>()[0];
    transform->setScale3D(QVector3D(m_Dimensions, 1));
}
} // namespace animation_cw3