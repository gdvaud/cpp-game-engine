#pragma once

#include <glm/glm.hpp>

#include "Neon/Core/TimeStep.h"
#include "Neon/Event/ApplicationEvent.h"
#include "Neon/Event/MouseEvent.h"
#include "Neon/Renderer/OrthographicCamera.h"

namespace Neon {
    class OrthographicCameraController {
    public:
        OrthographicCameraController(float aspectRatio, float cameraMoveSpeed = 5.0f);
        OrthographicCameraController(float aspectRatio, float cameraMoveSpeed = 5.0f,
                                     float cameraRotationSpeed = 180.0f);

        void OnUpdate(TimeStep timeStep);
        void OnEvent(Event& e);

        const Ref<OrthographicCamera>& GetCamera() const { return m_Camera; }

    private:
        bool OnWindowScrolled(MouseScrolledEvent& event);
        bool OnWindowResized(WindowResizedEvent& event);

    private:
        float m_ZoomLevel = 1.0f;
        float m_AspectRatio;
        Ref<OrthographicCamera> m_Camera;

        bool m_Rotating;

        glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
        float m_CameraRotation = 0.0f;  // In radians

        float m_CameraZoomMin = 0.25f;
        float m_CameraZoomSpeed;
        float m_CameraMoveSpeed;
        float m_CameraRotationSpeed;
    };
}  // namespace Neon
