#include <boost/di.hpp>
#include "game.hpp"
#include "physics/drawer.hpp"
#include <bullet/LinearMath/btIDebugDraw.h>
#include "debugmode.cpp"

namespace di = boost::di;

bool DEBUG_MODE = true;

void disableDebugMode() {
    PHYSICS_DEBUG = false;
    P4_CAMERA_DEBUG = false;
    ONSCREEN_DEBUG = false;
    SHOW_FPS = false;
}

int main() {
    if (DEBUG_MODE) {
        PHYSICS_DEBUG = true;
        P4_CAMERA_DEBUG = true;
        ONSCREEN_DEBUG = false;
        SHOW_FPS = true;
    }
    else {
        disableDebugMode();
    }

    auto injector = di::make_injector(
        di::bind<btIDebugDraw>().to<DebugDrawer>()
    );

    auto game = injector.create<SomewhereToEscapeGame>();
    game.start();
}
