#include "../classes/Board.h"
#include "Screen.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

GameScreen::GameScreen(int _width, int _height, int _columns, int _rows,
                       int _bombCount) {
  width = _width;
  height = _height;
  columns = _columns;
  rows = _rows;
  bombCount = _bombCount;

  Board newBoard(columns, rows, bombCount);
  myBoard = &newBoard;
}

void GameScreen::handleEvent(sf::Event event) {}

void GameScreen::update() {}

void GameScreen::render(sf::RenderWindow &_window) {
  this->window = &_window;
  myBoard->render(*window);
}
