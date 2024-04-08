#pragma once
#include "../utils/RandomHelper.h"
#include "Cell.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Board {
private:
  std::vector<std::vector<int>> board;
  std::vector<std::vector<Cell>> cellBoard;
  std::unordered_map<int, sf::Texture> textureMap;
  int columns;
  int rows;
  int bombCount;

  // Game logiv

  bool disabled;

public:
  Board() {
    columns = 0;
    rows = 0;
    bombCount = 0;
  }

  void loadBoard(int _columns, int _rows, int _bombCount) {
    board.clear();
    cellBoard.clear();

    columns = _columns;
    rows = _rows;
    bombCount = _bombCount;
    disabled = false;
    // Fill with zeroes, prep for generation
    for (int r = 0; r < rows; ++r) {
      std::vector<int> entry;
      for (int c = 0; c < columns; ++c) {
        entry.push_back(0);
      }
      board.push_back(entry);
    }

    this->Generate();
    this->GenerateValues();

    // Populate map with textures
    try {
      textureMap[-3].loadFromFile("./files/images/flag.png");
      textureMap[-2].loadFromFile("./files/images/tile_hidden.png");
      textureMap[-1].loadFromFile("./files/images/mine.png");
      textureMap[0].loadFromFile("./files/images/tile_revealed.png");
      textureMap[1].loadFromFile("./files/images/number_1.png");
      textureMap[2].loadFromFile("./files/images/number_2.png");
      textureMap[3].loadFromFile("./files/images/number_3.png");
      textureMap[4].loadFromFile("./files/images/number_4.png");
      textureMap[5].loadFromFile("./files/images/number_5.png");
      textureMap[6].loadFromFile("./files/images/number_6.png");
      textureMap[7].loadFromFile("./files/images/number_7.png");
    } catch (...) {
      std::cerr << "Something went wrong loading images\n";
    }

    for (int y = 0; y < rows; ++y) {
      std::vector<Cell> entry;
      for (int x = 0; x < columns; ++x) {
        Cell cell(board[y][x], x, y, textureMap[board[y][x]], textureMap[-2],
                  textureMap[0], textureMap[-3]);

        entry.push_back(cell);
      }

      cellBoard.push_back(entry);
    }

    for (int y = 0; y < rows; ++y) {
      for (int x = 0; x < columns; ++x) {
        cellBoard[y][x].setNearbyCells(cellBoard);
      }
    }
  }

  bool checkForWin() {
    for (std::vector<Cell> &row : cellBoard) {
      for (Cell &c : row) {
        if (c.getType() == -1 && !c.isFlagged()) {
          return false;
        } else if (c.getType() != -1 && c.isFlagged()) {
          return false;
        }
      }
    }
    return true;
  }

  int handleClick(int x, int y) {
    if (disabled) {
      return 500;
    }
    bool cellFound = false;
    for (std::vector<Cell> &row : cellBoard) {
      for (Cell &c : row) {
        if (c.withinBounds(x, y)) {
          int result = c.Click();

          return result;
        }
      }
    }

    return 404;
  }

  int handleFlag(int x, int y) {
    if (disabled) {
      return 500;
    }
    bool cellFound = false;
    for (std::vector<Cell> &row : cellBoard) {
      for (Cell &c : row) {
        if (c.withinBounds(x, y)) {
          int result = c.Flag();
          return result;
        }
      }
    }
    return 404;
  }

  void Generate() {
    int generated = 0;

    while (generated != bombCount) {
      int y = getRandomNumber(0, columns - 1);
      int x = getRandomNumber(0, rows - 1);

      if (board[x][y] != -1) {
        board[x][y] = -1;
        ++generated;
      }
    }
  }

  void GenerateValues() {
    int xTransform[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int yTransform[] = {-1, -1, -1, 0, 0, 1, 1, 1};

    for (int y = 0; y < rows; ++y) {
      for (int x = 0; x < columns; ++x) {
        if (board[y][x] == -1) {
          continue;
        }

        int count = 0;

        for (int t = 0; t < 8; ++t) {
          int newX = x + xTransform[t];
          int newY = y + yTransform[t];

          if (newX < 0 || newY < 0 || newX > columns - 1 || newY > rows - 1) {
            continue;
          } else {
            if (board[newY][newX] == -1) {
              ++count;
            }
          }
        }

        board[y][x] = count;
      }
    }
  }

  void toggleDisable() {
    std::cout << "Toggle disable\n";
    disabled = !disabled;
  }

  void Display() {
    for (std::vector<int> x : board) {
      for (int val : x) {
        std::cout << val << " ";
      }
      std::cout << std::endl;
    }
  }

  void render(sf::RenderWindow &window, bool debug) {
    for (std::vector<Cell> row : cellBoard) {
      for (Cell cell : row) {
        cell.render(window, debug);
      }
    }
  }
};
