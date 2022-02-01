#ifndef CONNECTFOUR_INCLUDE_ENGINE_H_
#define CONNECTFOUR_INCLUDE_ENGINE_H_

#include "game.h"

namespace connect_four {
namespace engine {

void update();
void render();

bool get_window_is_open();

}  // namespace engine
}  // namespace connect_four

#endif  // !CONNECTFOUR_INCLUDE_ENGINE_H_