#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

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
  Cell(int _type, int _x, int _y, sf::Texture _value, sf::Texture _tile,
       sf::Texture _under, sf::Texture _flag) {
    tile.setTexture(_tile);
    under.setTexture(_under);
    flag.setTexture(_flag);
    value.setTexture(_value);
    pos.x = _x;
    pos.y = _y;
    state.disabled = false;
    state.flagged = false;
    state.revealed = false;

    // Set sprite sizes

    tile.scale(.5, .5);
    under.scale(.5, .5);
    flag.scale(.5, .5);
    under.scale(.5, .5);
  }

  int Click() {
    if (type == -1) {
      // Reveal
      return -1;
    }

    return 0;
  }

  void Reveal() {
    if (type == 0) {
      // Reveal and reveal pointers
    } else {
      // Reveal but stop
    }
  }

  void render(sf::RenderWindow &window) {
    tile.setPosition(pos.x * 32.f, pos.y * 32.f);
    window.draw(tile);
  }
};
