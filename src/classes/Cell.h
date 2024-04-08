#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

struct Position {
  int x;
  int y;
};

struct State {
  bool revealed;
  bool flagged;
  bool disabled;
};

class Cell {
private:
  std::vector<Cell *> nearbyCells;
  sf::Sprite tile;
  sf::Sprite under;
  sf::Sprite value;
  sf::Sprite flag;
  int type; // 0 - Nothing, 1, 2, 3, -1 - BOMB
  Position pos;
  State state;

public:
  Cell(int _type, int _x, int _y, sf::Texture &_value, sf::Texture &_tile,
       sf::Texture &_under, sf::Texture &_flag) {
    tile.setTexture(_tile);
    under.setTexture(_under);
    flag.setTexture(_flag);
    value.setTexture(_value);
    pos.x = _x;
    pos.y = _y;
    state.disabled = false;
    state.flagged = false;
    state.revealed = false;

    tile.setPosition(32.f * pos.x, 32.f * pos.y);
    under.setPosition(pos.x * 32.f, pos.y * 32.f);
    value.setPosition(pos.x * 32.f, pos.y * 32.f);
    flag.setPosition(pos.x * 32.f, pos.y * 32.f);
  }

  bool withinBounds(int x, int y) {
    return tile.getGlobalBounds().contains(x, y);
  }

  int Click() {
    std::cout << pos.x << ", " << pos.y << " cell was clicked!\n";
    if (state.flagged) {
      return 1;
    }

    if (type == -1) {
      state.revealed = true;
      return -1;
    }

    state.revealed = true;
    return 0;
  }

  int Flag() {
    if (state.revealed != true) {
      state.flagged = !state.flagged;
      return 0;
    } else {
      return 1;
    }
  }

  void Reveal() {
    if (type == 0) {
      // Reveal and reveal pointers
    } else {
      // Reveal but stop
    }
  }

  void render(sf::RenderWindow &window) {
    window.draw(under);
    window.draw(value);

    if (!state.revealed) {
      window.draw(tile);
    }

    if (state.flagged) {
      window.draw(flag);
    }
  }
};
