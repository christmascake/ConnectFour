#ifndef CONNECTFOUR_INCLUDE_ASSETS_H_
#define CONNECTFOUR_INCLUDE_ASSETS_H_

#include <SFML/Graphics.hpp>

namespace connect_four {
namespace engine {

constexpr auto window_icon_size = 32;
constexpr auto checker_radius = 50;

const sf::Image windowIcon = [] {
  sf::Image t;
  t.loadFromFile("../assets/icon.png");
  return t;
}();

const sf::CircleShape checker_circle = [] {
  sf::CircleShape t(checker_radius);
  t.setFillColor(sf::Color::Red);
  return t;
}();

const sf::RectangleShape background_rect = [] {
  sf::RectangleShape t(sf::Vector2f(700, 600));
  t.setFillColor(sf::Color::Cyan);
  return t;
}();

const sf::Texture board_texture = [] {
  sf::Texture t;
  t.loadFromFile("../assets/cfour.png");
  return t;
}();

const sf::Font consola_font = [] {
  sf::Font t;
  t.loadFromFile("../assets/consola.ttf");
  return t;
}();

const sf::Text consola_text = [] {
  sf::Text t;
  t.setFont(consola_font);
  t.setOutlineThickness(1);
  t.setString("TEXT_STRING_NOT_SET");
  t.setOutlineColor(sf::Color::Black);
  t.setFillColor(sf::Color::White);
  return t;
}();

const sf::Sprite board_sprite(board_texture);

}  // namespace engine
}  // namespace connect_four

#endif  // !CONNECTFOUR_INCLUDE_ASSETS_H_