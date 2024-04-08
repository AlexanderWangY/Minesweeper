#include "../classes/Board.h"
#include "Screen.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

GameScreen::GameScreen(int _width, int _height, int _columns, int _rows,
                       int _bombCount) {
  width = _width;
  height = _height;
  columns = _columns;
  rows = _rows;
  bombCount = _bombCount;

  myBoard.loadBoard(columns, rows, bombCount);
}

void GameScreen::handleEvent(sf::Event event) {
  if (event.type == sf::Event::Closed) {
    window->close();
  }

  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      int x = event.mouseButton.x;
      int y = event.mouseButton.y;

      // Now check every cell to see if I click on anything!
      myBoard.handleClick(x, y);
    } else if (event.mouseButton.button == sf::Mouse::Right) {
      int x = event.mouseButton.x;
      int y = event.mouseButton.y;

      // Now check every cell to see if I click on anything!
      myBoard.handleFlag(x, y);
    }
  }
}

void GameScreen::update() { std::cout << "hi!" << std::endl; }

void GameScreen::render(sf::RenderWindow &_window) {
  this->window = &_window;
  myBoard.render(*window);
}
