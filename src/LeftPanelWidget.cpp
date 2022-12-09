#include "LeftPanelWidget.h"

#include "MainWindow.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>

namespace animation_cw3 {
const float SLIDER_INTERVAL = .01;

QSlider* createLabelledSlider(
    const QString& name,
    QWidget* parent,
    QLayout* layout)
{
    QLayout* sliderLayout = new QHBoxLayout();
    auto label = new QLabel(name, parent);
    label->setMinimumWidth(55);
    auto slider = new QSlider(Qt::Orientation::Horizontal, parent);

    QObject::connect(slider, &QSlider::valueChanged, [slider, label, name]() {
        label->setText(QString("%1: %2")
                           .arg(name)
                           .arg(slider->value() * SLIDER_INTERVAL));
    });

    sliderLayout->addWidget(label);
    sliderLayout->addWidget(slider);
    layout->addItem(sliderLayout);

    return slider;
}

LeftPanelWidget::LeftPanelWidget(MainWindow* parent)
    : QWidget(parent)
    , m_Params({
          .tankDimensions = { 5, 5 },
          .waterDimensions = { 2, 3 },
          .initialWaterPosition = { 0, 4 },
          .isRunning = false,
      })
{
    setMaximumWidth(350);

    // Buttons
    auto buttonGroupBox = new QGroupBox("Animation Controls", this);
    auto startButton = new QPushButton("Start", buttonGroupBox);
    auto pauseButton = new QPushButton("Pause", buttonGroupBox);
    auto resetButton = new QPushButton("Reset", buttonGroupBox);
    connect(startButton, &QPushButton::clicked, this, &LeftPanelWidget::startAnimation);
    connect(pauseButton, &QPushButton::clicked, this, &LeftPanelWidget::pauseAnimation);
    connect(resetButton, &QPushButton::clicked, this, &LeftPanelWidget::resetAnimation);
    buttonGroupBox->setLayout(new QHBoxLayout(buttonGroupBox));
    buttonGroupBox->layout()->addWidget(startButton);
    buttonGroupBox->layout()->addWidget(pauseButton);
    buttonGroupBox->layout()->addWidget(resetButton);

    // Sliders
    auto sliderGroupBox = new QGroupBox("Animation Parameters", this);
    sliderGroupBox->setLayout(new QVBoxLayout(sliderGroupBox));
    sliderGroupBox->layout()->addWidget(new QLabel("Tank Dimensions", sliderGroupBox));
    p_TankWidthSlider = createLabelledSlider("W", sliderGroupBox, sliderGroupBox->layout());
    p_TankHeightSlider = createLabelledSlider("H", sliderGroupBox, sliderGroupBox->layout());
    sliderGroupBox->layout()->addWidget(new QLabel("Water Dimensions", sliderGroupBox));
    p_WaterWidthSlider = createLabelledSlider("W", sliderGroupBox, sliderGroupBox->layout());
    p_WaterHeightSlider = createLabelledSlider("H", sliderGroupBox, sliderGroupBox->layout());
    sliderGroupBox->layout()->addWidget(new QLabel("Water Position", sliderGroupBox));
    p_WaterXSlider = createLabelledSlider("X", sliderGroupBox, sliderGroupBox->layout());
    p_WaterYSlider = createLabelledSlider("Y", sliderGroupBox, sliderGroupBox->layout());
    connect(p_TankWidthSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.tankDimensions.setX(value * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(p_TankHeightSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.tankDimensions.setY(value * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(p_WaterWidthSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.waterDimensions.setX(value * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(p_WaterHeightSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.waterDimensions.setY(value * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(p_WaterXSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.initialWaterPosition.setX(value * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(p_WaterYSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.initialWaterPosition.setY(value * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });

    // Layout
    setLayout(new QVBoxLayout(this));
    layout()->setAlignment(Qt::AlignTop);
    layout()->addWidget(buttonGroupBox);
    layout()->addWidget(sliderGroupBox);
}

void LeftPanelWidget::setTankDimensionRange(const QVector2D& min, const QVector2D& max)
{
    p_TankWidthSlider->setRange(min.x() / SLIDER_INTERVAL, max.x() / SLIDER_INTERVAL);
    p_TankHeightSlider->setRange(min.y() / SLIDER_INTERVAL, max.y() / SLIDER_INTERVAL);
}

void LeftPanelWidget::setWaterDimensionRange(const QVector2D& min, const QVector2D& max)
{
    p_WaterWidthSlider->setRange(min.x() / SLIDER_INTERVAL, max.x() / SLIDER_INTERVAL);
    p_WaterHeightSlider->setRange(min.y() / SLIDER_INTERVAL, max.y() / SLIDER_INTERVAL);
}

void LeftPanelWidget::setWaterPositionRange(const QVector2D& min, const QVector2D& max)
{
    p_WaterXSlider->setRange(min.x() / SLIDER_INTERVAL, max.x() / SLIDER_INTERVAL);
    p_WaterYSlider->setRange(min.y() / SLIDER_INTERVAL, max.y() / SLIDER_INTERVAL);
}

void LeftPanelWidget::setTankDimensions(const QVector2D& dimensions)
{
    p_TankWidthSlider->setValue(dimensions.x() / SLIDER_INTERVAL);
    p_TankHeightSlider->setValue(dimensions.y() / SLIDER_INTERVAL);
}

void LeftPanelWidget::setWaterDimensions(const QVector2D& dimensions)
{
    p_WaterWidthSlider->setValue(dimensions.x() / SLIDER_INTERVAL);
    p_WaterHeightSlider->setValue(dimensions.y() / SLIDER_INTERVAL);
}

void LeftPanelWidget::setWaterPosition(const QVector2D& position)
{
    p_WaterXSlider->setValue(position.x() / SLIDER_INTERVAL);
    p_WaterYSlider->setValue(position.y() / SLIDER_INTERVAL);
}
}