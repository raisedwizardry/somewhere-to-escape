#include <boost/di.hpp>
#include "game.hpp"

namespace di = boost::di;

extern "C" {
    #include "../../minigame.h"
    #include "physics/drawer.hpp"
    #include <bullet/btBulletDynamicsCommon.h>


    MinigameDef minigame_def = {
        .gamename = "somewheretoescape",
        .developername = "nicetoknow",
        .description = "abc",
        .instructions = "def"
    };

    void minigame_init() {

        auto injector = di::make_injector(
            di::bind<btIDebugDraw>().to<DebugDrawer>()
        );
        auto game = injector.create<SomewhereToEscapeGame>();
        game.start();
    }
}
