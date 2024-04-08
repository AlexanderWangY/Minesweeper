#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

bool isClicked(sf::Sprite &sprite, int x, int y) {
  sf::FloatRect bounds = sprite.getGlobalBounds();

  return bounds.contains(x, y);
}
