#pragma once

#include <t3d/t3d.h>

#define DEGREE_OF_ROTATION 0.125f

class Camera {
    public:

        void initCamera();
        void renderCamera();
        void updateControls(joypad_inputs_t joypadInput);
        bool isWorldCamera = false;

        T3DViewport viewport;
        T3DVec3 cameraPosition = {{0.0f, 0.0f, 0.0f}};
        T3DVec3 cameraTarget = {{0.0f, 0.0f,0.0f}};
        T3DVec3 cameraUp = {{0.0f, 0.0f,0.0f}};
        float degreeOfFov = 0.0f;
        float near = 0.0f;
        float far = 0.0f;
    private:
        bool isHoldingLAndR = false;
        void t3dRender();
        void openGlRender();

        static float getPositionalXByDegree(float x, float z, float degree);
        float getPositionalZByDegree(float x, float z, float degree);

};
