#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <ostream>

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

    type = _type;

    tile.setPosition(32.f * pos.x, 32.f * pos.y);
    under.setPosition(pos.x * 32.f, pos.y * 32.f);
    value.setPosition(pos.x * 32.f, pos.y * 32.f);
    flag.setPosition(pos.x * 32.f, pos.y * 32.f);
  }

  bool withinBounds(int x, int y) {
    return tile.getGlobalBounds().contains(x, y);
  }

  int Click() {
    if (state.flagged) {
      return 1;
    }

    if (type == -1) {
      state.revealed = true;
      return -1;
    }

    this->Reveal();
    return 0;
  }

  int Flag() {
    if (state.revealed != true) {
      int result = (state.flagged) ? 2 : 0;
      state.flagged = !state.flagged;
      return result;
    } else {
      return 1;
    }
  }

  void Reveal() {
    if (type == 0 && !state.revealed) {
      state.revealed = true;

      for (Cell *c : nearbyCells) {
        c->Reveal();
      }
    } else {
      state.revealed = true;
    }
  }

  void setNearbyCells(std::vector<std::vector<Cell>> &board) {

    for (int dy = -1; dy <= 1; ++dy) {
      for (int dx = -1; dx <= 1; ++dx) {
        // Skip the current cell itself
        if (dx == 0 && dy == 0)
          continue;

        // Calculate coordinates of the neighboring cell
        int nx = pos.x + dx;
        int ny = pos.y + dy;

        // Check if the neighboring cell is within the bounds of the board
        if (nx >= 0 && nx < board[0].size() && ny >= 0 && ny < board.size()) {
          nearbyCells.push_back(&board[ny][nx]);
        }
      }
    }
  }

  void render(sf::RenderWindow &window, bool debug) {
    window.draw(under);
    window.draw(value);

    if (debug) {
      if (type != -1 && !state.revealed) {
        window.draw(tile);
      }
    } else {

      if (!state.revealed) {
        window.draw(tile);
      }
    }

    if (state.flagged) {
      window.draw(flag);
    }
  }

  bool isFlagged() { return state.flagged; }

  int getType() { return type; }
};
