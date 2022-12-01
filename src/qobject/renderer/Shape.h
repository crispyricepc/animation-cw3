#pragma once

#include <QObject>

namespace animation_cw3::qobject::renderer {
class Shape : public QObject {
    Q_OBJECT
public:
    Shape(class Scene* parent);

private:
};
}