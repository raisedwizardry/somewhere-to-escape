#pragma once

class DebugMode {
    public:
        DebugMode() {
            //setDebugModeFlags();
        }
        void setDebugModeFlags();
        bool PHYSICS_DEBUG = false;
        bool P4_CAMERA_DEBUG = false;
        bool ONSCREEN_DEBUG = false;
        bool SHOW_FPS = false;
};
