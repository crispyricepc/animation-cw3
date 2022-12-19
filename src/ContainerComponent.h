#pragma once

#include <QVector2D>
#include <Qt3DCore/QComponent>

namespace animation_cw3 {
class Animation;

class ContainerComponent : public Qt3DCore::QComponent {
    Q_OBJECT
private:
    QVector2D m_Dimensions;

public:
    explicit ContainerComponent(const Animation* animation,
        Qt3DCore::QNode* parent = nullptr);

    /**
     * @brief Get a direction vector that is perpendicular to the surface of the rigid component
     */
    [[nodiscard]] QVector2D collideWith(const QVector2D& point) const;

public slots:
    void onDimensionsChanged(const QVector2D& dimensions);
};
} // namespace animation_cw3
