#include <boost/di.hpp>
#include "game.hpp"
#include "physics/drawer.hpp"
#include <bullet/LinearMath/btIDebugDraw.h>

namespace di = boost::di;

int main() {
    auto injector = di::make_injector(
        di::bind<btIDebugDraw>().to<DebugDrawer>()
    );

    auto game = injector.create<SomewhereToEscapeGame>();
    game.start();
}
