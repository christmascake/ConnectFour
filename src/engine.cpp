#include "engine.h"

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "assets.h"

namespace connect_four {
namespace engine {
namespace {

constexpr auto window_width = 1000;
constexpr auto window_height = 600;
constexpr auto window_title = "Connect Four";
constexpr auto window_style = sf::Style::Titlebar | sf::Style::Close;
constexpr auto window_fps_limit = 30;

std::unique_ptr<ConnectFour> current_game = std::make_unique<ConnectFour>();

sf::Event ev;

std::array<std::array<sf::CircleShape, ConnectFour::board_cols>,
           ConnectFour::board_rows>
    circle_render_board;

const std::unique_ptr<sf::RenderWindow> window = [] {
  auto t = std::make_unique<sf::RenderWindow>(
      sf::VideoMode(window_width, window_height), window_title, window_style);
  t->setFramerateLimit(window_fps_limit);
  t->setIcon(window_icon_size, window_icon_size, windowIcon.getPixelsPtr());
  return t;
}();

sf::Text side_to_move_text = [] {
  auto t = consola_text;
  t.setPosition(750, 10);
  t.setString("Red Move");
  t.setFillColor(sf::Color::Red);
  return t;
}();

std::vector<sf::Text*> text_to_render = {&side_to_move_text};

void reset() {
  current_game.reset();
  current_game = std::make_unique<ConnectFour>();
}

void update_checkers() {
  for (auto i = 0; i < ConnectFour::board_rows; i++) {
    for (auto j = 0; j < ConnectFour::board_cols; j++) {
      auto& circle_at_ij = circle_render_board.at(i).at(j);
      const auto& checker_at_ij = current_game->getSideAt(i, j);
      if (checker_at_ij != ConnectFour::Side::none) {
        circle_at_ij = checker_circle;

        circle_at_ij.setPosition(j * 100, i * 100);

        if (checker_at_ij == ConnectFour::Side::red) {
          circle_at_ij.setFillColor(sf::Color::Red);
        } else if (checker_at_ij == ConnectFour::Side::yellow) {
          circle_at_ij.setFillColor(sf::Color::Yellow);
        }
      }
    }
  }
}

void update_side_to_move_text() {
  if (current_game->get_is_red_turn()) {
    side_to_move_text.setString("Red Move");
    side_to_move_text.setFillColor(sf::Color::Red);
  } else {
    side_to_move_text.setString("Yellow Move");
    side_to_move_text.setFillColor(sf::Color::Yellow);
  }
}

void handle_keyboard() {
  if (ev.type == sf::Event::KeyPressed) {
    switch (ev.key.code) {
      case sf::Keyboard::Escape:
        window->close();
        break;
      case sf::Keyboard::BackSpace:
        reset();
        break;
      default:
        break;
    }
  }
}

void handle_mouse() {
  if (ev.type == sf::Event::MouseButtonPressed) {
    if (ev.mouseButton.button == sf::Mouse::Left) {
      auto row = ev.mouseButton.y / 100;
      auto col = ev.mouseButton.x / 100;

      try {
        if (current_game->make_move(row, col)) {
          update_checkers();
          update_side_to_move_text();
        }
      } catch (...) {
      }
    }
  }
}

void poll_event() {
  while (window->pollEvent(ev)) {
    switch (ev.type) {
      case sf::Event::KeyPressed:
      case sf::Event::KeyReleased:
        handle_keyboard();
        break;
      case sf::Event::MouseButtonPressed:
      case sf::Event::MouseButtonReleased:
        handle_mouse();
        break;
      case sf::Event::Closed:
        window->close();
        break;
      default:
        break;
    }
  }
}

void draw_checkers() {
  for (auto i = 0; i < ConnectFour::board_rows; i++) {
    for (auto j = 0; j < ConnectFour::board_cols; j++) {
      window->draw(circle_render_board.at(i).at(j));
    }
  }
}

void draw_text() {
  for (auto&& i : text_to_render) {
    window->draw(*i);
  }
}

}  // namespace

void update() { poll_event(); }

void render() {
  window->clear(sf::Color(25, 25, 25));

  window->draw(background_rect);

  draw_checkers();

  window->draw(board_sprite);

  draw_text();

  window->display();
}

bool get_window_is_open() { return window->isOpen(); }

}  // namespace engine
}  // namespace connect_four