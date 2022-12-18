#include "LeftPanelWidget.h"

#include "MainWindow.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

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

    QObject::connect(slider, &QSlider::valueChanged, parent, [slider, label, name]() {
        label->setText(QString("%1: %2")
                           .arg(name)
                           .arg(float(slider->value()) * SLIDER_INTERVAL));
    });

    sliderLayout->addWidget(label);
    sliderLayout->addWidget(slider);
    layout->addItem(sliderLayout);

    return slider;
}

LeftPanelWidget::LeftPanelWidget(MainWindow* parent)
    : QWidget(parent)
{
    setMaximumWidth(350);

    // Buttons
    auto buttonGroupBox = new QGroupBox("Animation Controls", this);
    auto startButton = new QPushButton("Start", buttonGroupBox);
    auto pauseButton = new QPushButton("Pause", buttonGroupBox);
    auto resetButton = new QPushButton("Reset", buttonGroupBox);
    connect(startButton, &QPushButton::clicked, this, [this, startButton, pauseButton, resetButton] {
        startButton->setEnabled(false);
        pauseButton->setEnabled(true);
        resetButton->setEnabled(true);
        m_Params.isRunning = true;
        emit startAnimation();
    });
    connect(pauseButton, &QPushButton::clicked, this, [this, pauseButton] {
        if (m_Params.isRunning) {
            pauseButton->setText("Resume");
            emit pauseAnimation();
        } else {
            pauseButton->setText("Pause");
            emit resumeAnimation();
        }
    });
    connect(resetButton, &QPushButton::clicked, this, [this, startButton, pauseButton, resetButton] {
        startButton->setEnabled(true);
        pauseButton->setEnabled(false);
        pauseButton->setText("Pause");
        resetButton->setEnabled(false);
        m_Params.isRunning = false;
        emit resetAnimation();
    });
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
    sliderGroupBox->layout()->addWidget(new QLabel("Fluid Dimensions", sliderGroupBox));
    p_FluidWidthSlider = createLabelledSlider("W", sliderGroupBox, sliderGroupBox->layout());
    p_FluidHeightSlider = createLabelledSlider("H", sliderGroupBox, sliderGroupBox->layout());
    sliderGroupBox->layout()->addWidget(new QLabel("Fluid Position", sliderGroupBox));
    p_FluidXSlider = createLabelledSlider("X", sliderGroupBox, sliderGroupBox->layout());
    p_FluidYSlider = createLabelledSlider("Y", sliderGroupBox, sliderGroupBox->layout());
    sliderGroupBox->layout()->addWidget(new QLabel("Fluid Properties", sliderGroupBox));
    p_FluidDensitySlider = createLabelledSlider("g", sliderGroupBox, sliderGroupBox->layout());
    p_ViscositySlider = createLabelledSlider("μ", sliderGroupBox, sliderGroupBox->layout());
    p_DeltaSlider = createLabelledSlider("Δ", sliderGroupBox, sliderGroupBox->layout());
    sliderGroupBox->layout()->addWidget(new QLabel("Gravity", sliderGroupBox));
    p_GravitySlider = createLabelledSlider("g", sliderGroupBox, sliderGroupBox->layout());

    connect(p_TankWidthSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.tankDimensions.setX(float(value) * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(p_TankHeightSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.tankDimensions.setY(float(value) * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(p_FluidWidthSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.fluidDimensions.setX(float(value) * SLIDER_INTERVAL);
    });
    connect(p_FluidWidthSlider, &QSlider::sliderReleased, this, [this]() {
        emit animationParametersChanged(animationParameters());
    });
    connect(p_FluidHeightSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.fluidDimensions.setY(float(value) * SLIDER_INTERVAL);
    });
    connect(p_FluidHeightSlider, &QSlider::sliderReleased, this, [this]() {
        emit animationParametersChanged(animationParameters());
    });
    connect(p_FluidXSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.initialWaterPosition.setX(float(value) * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(p_FluidYSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.initialWaterPosition.setY(float(value) * SLIDER_INTERVAL);
        emit animationParametersChanged(animationParameters());
    });
    connect(p_FluidDensitySlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.fluidDensity = float(value) * SLIDER_INTERVAL;
    });
    connect(p_FluidDensitySlider, &QSlider::sliderReleased, this, [this]() {
        emit animationParametersChanged(animationParameters());
    });
    connect(p_ViscositySlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.viscosity = float(value) * SLIDER_INTERVAL;
        emit animationParametersChanged(animationParameters());
    });
    connect(p_DeltaSlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.delta = float(value) * SLIDER_INTERVAL;
        emit animationParametersChanged(animationParameters());
    });
    connect(p_GravitySlider, &QSlider::valueChanged, this, [this](int value) {
        m_Params.gravity = float(value) * SLIDER_INTERVAL;
        emit animationParametersChanged(animationParameters());
    });

    // Layout
    setLayout(new QVBoxLayout(this));
    layout()->setAlignment(Qt::AlignTop);
    layout()->addWidget(buttonGroupBox);
    layout()->addWidget(sliderGroupBox);

    // Reset animation
    resetButton->click();
}

void LeftPanelWidget::setTankDimensionRange(const QVector2D& min, const QVector2D& max)
{
    p_TankWidthSlider->setRange(min.x() / SLIDER_INTERVAL, max.x() / SLIDER_INTERVAL);
    p_TankHeightSlider->setRange(min.y() / SLIDER_INTERVAL, max.y() / SLIDER_INTERVAL);
}

void LeftPanelWidget::setWaterDimensionRange(const QVector2D& min, const QVector2D& max)
{
    p_FluidWidthSlider->setRange(min.x() / SLIDER_INTERVAL, max.x() / SLIDER_INTERVAL);
    p_FluidHeightSlider->setRange(min.y() / SLIDER_INTERVAL, max.y() / SLIDER_INTERVAL);
}

void LeftPanelWidget::setWaterPositionRange(const QVector2D& min, const QVector2D& max)
{
    p_FluidXSlider->setRange(min.x() / SLIDER_INTERVAL, max.x() / SLIDER_INTERVAL);
    p_FluidYSlider->setRange(min.y() / SLIDER_INTERVAL, max.y() / SLIDER_INTERVAL);
}

void LeftPanelWidget::setFluidDensityRange(float min, float max)
{
    p_FluidDensitySlider->setRange(min / SLIDER_INTERVAL, max / SLIDER_INTERVAL);
}

void LeftPanelWidget::setViscosityRange(float min, float max)
{
    p_ViscositySlider->setRange(min / SLIDER_INTERVAL, max / SLIDER_INTERVAL);
}

void LeftPanelWidget::setDeltaRange(float min, float max)
{
    p_DeltaSlider->setRange(min / SLIDER_INTERVAL, max / SLIDER_INTERVAL);
}

void LeftPanelWidget::setGravityRange(float min, float max)
{
    p_GravitySlider->setRange(min / SLIDER_INTERVAL, max / SLIDER_INTERVAL);
}

void LeftPanelWidget::setTankDimensions(const QVector2D& dimensions)
{
    p_TankWidthSlider->setValue(dimensions.x() / SLIDER_INTERVAL);
    p_TankHeightSlider->setValue(dimensions.y() / SLIDER_INTERVAL);
}

void LeftPanelWidget::setWaterDimensions(const QVector2D& dimensions)
{
    p_FluidWidthSlider->setValue(dimensions.x() / SLIDER_INTERVAL);
    p_FluidHeightSlider->setValue(dimensions.y() / SLIDER_INTERVAL);
}

void LeftPanelWidget::setWaterPosition(const QVector2D& position)
{
    p_FluidXSlider->setValue(position.x() / SLIDER_INTERVAL);
    p_FluidYSlider->setValue(position.y() / SLIDER_INTERVAL);
}

void LeftPanelWidget::setFluidDensity(float density)
{
    p_FluidDensitySlider->setValue(density / SLIDER_INTERVAL);
}

void LeftPanelWidget::setViscosity(float viscosity)
{
    p_ViscositySlider->setValue(viscosity / SLIDER_INTERVAL);
}

void LeftPanelWidget::setDelta(float delta)
{
    p_DeltaSlider->setValue(delta / SLIDER_INTERVAL);
}
void LeftPanelWidget::setGravity(float gravity)
{
    p_GravitySlider->setValue(gravity / SLIDER_INTERVAL);
}
}