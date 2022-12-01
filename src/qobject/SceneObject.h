#pragma once

#include "renderer/RendererMesh.h"

#include <QMatrix4x4>
#include <QObject>

namespace animation_cw3::qobject {
class SceneObject : public QObject {
    Q_OBJECT

private:
    const renderer::RendererMesh* m_Mesh;
    QMatrix4x4 m_Transform;

public:
    SceneObject(class Scene* parent);

    inline const renderer::RendererMesh* mesh() const { return m_Mesh; }
    inline void setMesh(renderer::RendererMesh* mesh) { m_Mesh = mesh; }
    inline const QMatrix4x4& transform() const { return m_Transform; }
    inline QVector4D position() const { return m_Transform.column(3); }
    inline QVector3D scale() const { return QVector3D(m_Transform.column(0).length(), m_Transform.column(1).length(), m_Transform.column(2).length()); }
    inline QQuaternion rotation() const { return QQuaternion::fromRotationMatrix(m_Transform.normalMatrix()); }
};
}