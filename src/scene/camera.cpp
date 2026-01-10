#include "camera.hpp"

#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <GL/glu.h>

void Camera::initCamera() {
    cameraPosition = {{0.0f, 25.0f, 70.0f}};
    cameraTarget = {{0.0f, 10.0f,0.0f}};
    cameraUp = {{0.0f, 1.0f,0.0f}};

    degreeOfFov = 55.0f;
    near = 10.0f;
    far = 150.0f;
}

void Camera::renderCamera() {
    t3dRender();
    openGlRender();
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