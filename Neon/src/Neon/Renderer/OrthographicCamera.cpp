#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Neon {

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : _projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
          _viewMatrix(1.0f),
          _position(0.0f),
          _rotation(0.0f) {
        RecalculateViewMatrix();
    }

    void OrthographicCamera::RecalculateViewMatrix() {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position) * glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0, 0, 1));

        _viewMatrix = glm::inverse(transform);
        _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
    }
}  // namespace Neon
