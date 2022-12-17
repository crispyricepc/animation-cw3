#include "Animation.h"

#include "MainWindow.h"

#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QMesh>

namespace animation_cw3 {
QList<Particle*>& translateParticles(QList<Particle*>& particles, const AnimationParameters& params)
{
    for (uint i = 0; i < particles.size(); i++) {
        auto particle = particles[i];
        auto transform = particle->componentsOfType<Qt3DCore::QTransform>()[0];

        // Get the 2D index of the particle
        uint x = i % uint(params.fluidDimensions.x() * params.fluidDensity);
        uint y = i / (params.fluidDimensions.x() * params.fluidDensity);

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
    qInfo() << "Recreating particles...";

    // Setup the list
    qInfo() << "Deleting" << particles.size() << "particles...";
    for (auto particle : particles) {
        particle->deleteLater();
    }
    particles.clear();
    uint fluidWidth = params.fluidDimensions.x() * params.fluidDensity;
    uint fluidHeight = params.fluidDimensions.y() * params.fluidDensity;
    qInfo() << "Creating" << fluidWidth * fluidHeight << "particles...";
    particles.reserve(fluidWidth * fluidHeight);

    // Create the particles
    for (uint i = 0; i < fluidWidth; ++i) {
        for (uint j = 0; j < fluidHeight; ++j) {
            auto particle = new Particle(sceneEntity,
                params,
                { 0, 0 },
                QVector2D(1 / params.fluidDensity, 1 / params.fluidDensity));
            particles.append(particle);
        }
    }

    return particles;
}

Animation::Animation(Qt3DExtras::Qt3DWindow* window)
    : Qt3DCore::QEntity()
    , p_Container(new Qt3DCore::QEntity(this))
{
    // Load the container 2D model
    auto meshLoader = new Qt3DRender::QMesh(p_Container);
    auto material = new Qt3DExtras::QPhongMaterial(p_Container);
    auto transform = new Qt3DCore::QTransform(p_Container);
    meshLoader->setSource(QUrl("qrc:/objects/container.obj"));
    transform->setTranslation(QVector3D(0, 0, 0));
    p_Container->addComponent(meshLoader);
    p_Container->addComponent(material);
    p_Container->addComponent(transform);

    // Camera
    Qt3DRender::QCamera* camera = window->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 20));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // Camera controls
    auto cameraController = new Qt3DExtras::QOrbitCameraController(this);
    cameraController->setLinearSpeed(50.0f);
    cameraController->setLookSpeed(180.0f);
    cameraController->setCamera(camera);

    window->setRootEntity(this);
}

void Animation::onAnimationParametersChanged(const AnimationParameters& params)
{
    if (params.tankDimensions != m_AnimationParametersDelta.tankDimensions) {
        auto containerTransform = p_Container->componentsOfType<Qt3DCore::QTransform>()[0];
        containerTransform->setScale3D(QVector3D(
            params.tankDimensions.x(),
            params.tankDimensions.y(),
            1));
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
}