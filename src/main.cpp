#include "engine.h"

int main() {
  while (connect_four::engine::get_window_is_open()) {
    connect_four::engine::update();
    connect_four::engine::render();
  }

  return 0;
}