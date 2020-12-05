#include "OrthographicCameraController.h"

#include "Neon/Core/Base.h"
#include "Neon/Input/Input.h"
#include "Neon/Input/KeyCodes.h"

namespace Neon {

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, float cameraMoveSpeed)
        : m_AspectRatio(aspectRatio),
          m_Rotating(false),
          m_CameraMoveSpeed(cameraMoveSpeed),
          m_CameraRotationSpeed(0.0f),
          m_CameraZoomSpeed(0.25f) {
        m_Camera = CreateRef<OrthographicCamera>(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
                                                 -m_ZoomLevel, m_ZoomLevel);
    }

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, float cameraMoveSpeed,
                                                               float cameraRotationSpeed)
        : m_AspectRatio(aspectRatio),
          m_Rotating(true),
          m_CameraMoveSpeed(cameraMoveSpeed),
          m_CameraRotationSpeed(glm::radians(cameraRotationSpeed)),
          m_CameraZoomSpeed(0.25f) {
        m_Camera = CreateRef<OrthographicCamera>(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
                                                 -m_ZoomLevel, m_ZoomLevel);
    }

    void OrthographicCameraController::OnUpdate(TimeStep timeStep) {
        if (Input::IsKeyPressed(NEO_KEY_A)) {
            m_CameraPosition.x -= cos(m_CameraRotation) * m_CameraMoveSpeed * m_ZoomLevel * timeStep;
            m_CameraPosition.y -= sin(m_CameraRotation) * m_CameraMoveSpeed * m_ZoomLevel * timeStep;
        }
        if (Input::IsKeyPressed(NEO_KEY_D)) {
            m_CameraPosition.x += cos(m_CameraRotation) * m_CameraMoveSpeed * m_ZoomLevel * timeStep;
            m_CameraPosition.y += sin(m_CameraRotation) * m_CameraMoveSpeed * m_ZoomLevel * timeStep;
        }

        if (Input::IsKeyPressed(NEO_KEY_W)) {
            m_CameraPosition.x += -sin(m_CameraRotation) * m_CameraMoveSpeed * m_ZoomLevel * timeStep;
            m_CameraPosition.y += cos(m_CameraRotation) * m_CameraMoveSpeed * m_ZoomLevel * timeStep;
        }
        if (Input::IsKeyPressed(NEO_KEY_S)) {
            m_CameraPosition.x -= -sin(m_CameraRotation) * m_CameraMoveSpeed * m_ZoomLevel * timeStep;
            m_CameraPosition.y -= cos(m_CameraRotation) * m_CameraMoveSpeed * m_ZoomLevel * timeStep;
        }

        m_Camera->SetPosition(m_CameraPosition);

        if (m_Rotating) {
            if (Input::IsKeyPressed(NEO_KEY_Q)) m_CameraRotation -= m_CameraRotationSpeed * timeStep;
            if (Input::IsKeyPressed(NEO_KEY_E)) m_CameraRotation += m_CameraRotationSpeed * timeStep;

            m_Camera->SetRotation(m_CameraRotation);
        }
    }

    void OrthographicCameraController::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(NEO_BIND_EVENT_FN(OrthographicCameraController::OnWindowScrolled));
        dispatcher.Dispatch<WindowResizedEvent>(NEO_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnWindowScrolled(MouseScrolledEvent& event) {
        m_ZoomLevel -= event.GetYOffset() * m_CameraZoomSpeed;
        m_ZoomLevel = std::max(m_ZoomLevel, m_CameraZoomMin);
        m_Camera->SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
    bool OrthographicCameraController::OnWindowResized(WindowResizedEvent& event) {
        m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
        m_Camera->SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}  // namespace Neon
