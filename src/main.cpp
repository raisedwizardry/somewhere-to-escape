#include <boost/di.hpp>
#include "game.hpp"
#include <libdragon.h>

namespace di = boost::di;

int main() {
    auto injector = di::make_injector();
    auto game = injector.create<SomewhereToEscapeGame>();
    game.start();
}
