#pragma once

#include <QWidget>

namespace animation_cw3::qobject {
class LeftPanelWidget : public QWidget {
    Q_OBJECT
public:
    LeftPanelWidget(class MainWindow* parent = nullptr);

signals:
};
}