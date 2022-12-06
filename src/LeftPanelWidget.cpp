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
    m_TankWidthSlider = createLabelledSlider("W", sliderGroupBox, sliderGroupBox->layout());
    m_TankHeightSlider = createLabelledSlider("H", sliderGroupBox, sliderGroupBox->layout());
    sliderGroupBox->layout()->addWidget(new QLabel("Water Dimensions", sliderGroupBox));
    m_WaterWidthSlider = createLabelledSlider("W", sliderGroupBox, sliderGroupBox->layout());
    m_WaterHeightSlider = createLabelledSlider("H", sliderGroupBox, sliderGroupBox->layout());
    sliderGroupBox->layout()->addWidget(new QLabel("Water Position", sliderGroupBox));
    m_WaterXSlider = createLabelledSlider("X", sliderGroupBox, sliderGroupBox->layout());
    m_WaterYSlider = createLabelledSlider("Y", sliderGroupBox, sliderGroupBox->layout());
    connect(m_TankWidthSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.tankDimensions.setX(value * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(m_TankHeightSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.tankDimensions.setY(value * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(m_WaterWidthSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.waterDimensions.setX(value * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(m_WaterHeightSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.waterDimensions.setY(value * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(m_WaterXSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.initialWaterPosition.setX(value * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(m_WaterYSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.initialWaterPosition.setY(value * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });

    // Layout
    setLayout(new QVBoxLayout(this));
    layout()->setAlignment(Qt::AlignTop);
    layout()->addWidget(buttonGroupBox);
    layout()->addWidget(sliderGroupBox);
}
}