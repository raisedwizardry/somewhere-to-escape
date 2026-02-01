#include "camera.hpp"

#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <GL/glu.h>
#include "../utility/button.hpp"

void Camera::initCamera() {
    cameraPosition = {{0.0f, 25.0f, 70.0f}};
    cameraTarget = {{0.0f, 10.0f,0.0f}};
    cameraUp = {{0.0f, 1.0f,0.0f}};

    degreeOfFov = 55.0f;
    near = 10.0f;
    far = 500.0f;
}

void Camera::updateControls(joypad_inputs_t joypadInput) {
    if (joypadInput.stick_y > 20) {
        cameraPosition.z +=2.0f;
        cameraTarget.z += 2.0f;
    }
    if (joypadInput.stick_y < -20) {
        cameraPosition.z -=2.0f;
        cameraTarget.z -= 2.0f;
    }
    if (joypadInput.stick_x < -20) {
        cameraPosition.x += 2.0f;
        cameraTarget.x += 2.0f;
    }
    if (joypadInput.stick_x > 20) {
        cameraPosition.x -= 2.0f;
        cameraTarget.x -= 2.0f;
    }
    auto button = Button::PriorityButtonQuery(joypadInput.btn);
    switch (button) {
        case Button::BUTTON_D_UP:
            cameraPosition.y += 2.0f;
            cameraTarget.y += 2.0f;
            break;
        case Button::BUTTON_D_LEFT:
            cameraTarget.x = getPositionalXByDegree(cameraTarget.x, cameraTarget.z, -DEGREE_OF_ROTATION);
            cameraTarget.z = getPositionalZByDegree(cameraTarget.x, cameraTarget.z, -DEGREE_OF_ROTATION);
            break;
        case Button::BUTTON_D_DOWN:
            cameraPosition.y -= 2.0f;
            cameraTarget.y -= 2.0f;
            break;
        case Button::BUTTON_D_RIGHT:
            cameraTarget.x = getPositionalXByDegree(cameraTarget.x, cameraTarget.z, DEGREE_OF_ROTATION);
            cameraTarget.z = getPositionalZByDegree(cameraTarget.x, cameraTarget.z, DEGREE_OF_ROTATION);
            break;
        default:
            break;
    }
}

void Camera::renderCamera() {
    t3dRender();
    if (_debug.PHYSICS_DEBUG) {
        openGlRender();
    }
}

void Camera::t3dRender() {
    t3d_viewport_set_perspective(&viewport, T3D_DEG_TO_RAD(degreeOfFov),(float)display_get_width() / (float)display_get_height(), near, far);
    t3d_viewport_look_at(&viewport, &cameraPosition, &cameraTarget, &cameraUp);
}

void Camera::openGlRender() {
    gluPerspective(degreeOfFov, (float)display_get_width() / (float)display_get_height(), near, far);
    gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
            cameraTarget.x, cameraTarget.y, cameraTarget.z,
               cameraUp.x, cameraUp.y, cameraUp.z);
}

float Camera::getPositionalXByDegree(float x, float z, float degree) {
    return x * cos(degree) - z * sin(degree);
}

float Camera::getPositionalZByDegree(float x, float z, float degree) {
    return x * sin(degree) + z * cos(degree);
}