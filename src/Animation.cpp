#include "Animation.h"

#include "ContainerComponent.h"
#include "MainWindow.h"

#include <QTimer>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMesh>

namespace animation_cw3 {
const static float FOV = 45;
const static float ASPECT_W = 16;
const static float ASPECT_H = 9;
const static float NEAR_PLANE = .1;
const static float FAR_PLANE = 1000;
const static float CAMERA_DISTANCE = 30;
const static float CAMERA_SPEED = 50;

QList<Particle*>& translateParticles(QList<Particle*>& particles, const AnimationParameters& params)
{
    for (int i = 0; i < particles.size(); i++) {
        auto* particle = particles[i];
        auto* transform = particle->componentsOfType<Qt3DCore::QTransform>()[0];

        // Get the 2D index of the particle
        int x = i % int(params.fluidDimensions.x() * params.fluidDensity);
        int y = i / int(params.fluidDimensions.x() * params.fluidDensity);

        // Get the translation
        float xTranslation = x / params.fluidDensity;
        float yTranslation = y / params.fluidDensity;

        // Translate the particle
        transform->setTranslation(QVector3D(
            QVector2D(
                xTranslation,
                yTranslation)
                + (params.initialWaterPosition - params.fluidDimensions / 2),
            0));
    }

    return particles;
}

QList<Particle*>& addParticlesToScene(Qt3DCore::QEntity* sceneEntity, QList<Particle*>& particles,
    const AnimationParameters& params)
{
    qInfo() << "Deleting" << particles.size() << "particles...";
    for (auto* particle : particles) {
        particle->deleteLater();
    }
    particles.clear();
    int fluidWidth = int(params.fluidDimensions.x() * params.fluidDensity);
    int fluidHeight = int(params.fluidDimensions.y() * params.fluidDensity);
    qInfo() << "Creating" << fluidWidth * fluidHeight << "particles...";
    particles.reserve(fluidWidth * fluidHeight);

    // Create the particles
    for (int i = 0; i < fluidWidth; ++i) {
        for (int j = 0; j < fluidHeight; ++j) {
            auto* particle = new Particle(sceneEntity,
                params,
                { 0, 0 },
                QVector2D(1 / params.fluidDensity, 1 / params.fluidDensity));
            particles.append(particle);
        }
    }

    return particles;
}

Animation::Animation(Qt3DExtras::Qt3DWindow* window)
    : p_Container(new Qt3DCore::QEntity(this))
{
    // Load the container 2D model
    auto* meshLoader = new Qt3DRender::QMesh(p_Container);
    auto* material = new Qt3DExtras::QPhongMaterial(p_Container);
    auto* transform = new Qt3DCore::QTransform(p_Container);
    auto* containerComponent = new ContainerComponent(this, p_Container);
    meshLoader->setSource(QUrl("qrc:/objects/container.obj"));
    transform->setTranslation(QVector3D(0, 0, 0));
    p_Container->addComponent(meshLoader);
    p_Container->addComponent(material);
    p_Container->addComponent(transform);
    p_Container->addComponent(containerComponent);

    // Camera
    Qt3DRender::QCamera* camera = window->camera();
    camera->lens()->setPerspectiveProjection(FOV, ASPECT_H / ASPECT_W, NEAR_PLANE, FAR_PLANE);
    camera->setPosition(QVector3D(0, 0, CAMERA_DISTANCE));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // Camera controls
    auto* cameraController = new Qt3DExtras::QOrbitCameraController(this);
    cameraController->setLinearSpeed(CAMERA_SPEED);
    cameraController->setCamera(camera);

    window->setRootEntity(this);
}

QVector2D Animation::rigidForce(const QVector2D& position) const
{
}

void Animation::simulate()
{
    for (const auto& particle : m_Particles) {
        particle->simulate();
    }
}

void Animation::resetAnimation()
{
    translateParticles(m_Particles, m_AnimationParametersDelta);
}

void Animation::onAnimationParametersChanged(const AnimationParameters& params)
{
    if (params.tankDimensions != m_AnimationParametersDelta.tankDimensions) {
        emit containerDimensionsChanged(params.tankDimensions);
    }

    if (params.isRunning) {
        return;
    }

    bool needsRegen = m_AnimationParametersDelta.fluidDimensions != params.fluidDimensions
        || m_AnimationParametersDelta.fluidDensity != params.fluidDensity;
    if (needsRegen) {
        addParticlesToScene(this, m_Particles, params);
    }

    if (m_AnimationParametersDelta.initialWaterPosition != params.initialWaterPosition
        || needsRegen) {
        translateParticles(m_Particles, params);
    }

    m_AnimationParametersDelta = params;
}
} // namespace animation_cw3