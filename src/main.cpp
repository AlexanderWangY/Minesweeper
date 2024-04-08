#include "classes/Board.h"
#include "classes/Cell.h"
#include "screens/Screen.h"
#include "utils/RandomHelper.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <fstream>
#include <iostream>
#include <string>

struct Config {
  unsigned int columns;
  unsigned int rows;
  unsigned int bombCount;
};

int main() {
  Config config;

  std::ifstream file("./files/config.cfg");
  std::string line;

  if (file.is_open()) {
    std::getline(file, line);
    config.columns = std::stoi(line);
    std::getline(file, line);
    config.rows = std::stoi(line);
    std::getline(file, line);
    config.bombCount = std::stoi(line);
  } else {
    std::cerr << "An error occured while trying to open config files\n";
    return 1;
  }

  int screenWidth = config.columns * 32;
  int screenHeight = (config.rows * 32) + 100;

  sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight),
                          "Minesweeper", sf::Style::Close);

  GameScreen gamescreen(screenWidth, screenHeight, config.columns, config.rows,
                        config.bombCount);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      gamescreen.handleEvent(event);
    }

    window.clear();
    gamescreen.render(window);
    window.display();
  }

  // Now rendering the main pages
  // int screenWidth = config.columns * 32;
  // int screenHeight = (config.rows * 32) + 100;

  // sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight),
  //                         "Minesweeper", sf::Style::Close);

  // TitleScreen titlescreen(screenWidth, screenHeight);

  // while (window.isOpen()) {
  //   sf::Event event;
  //   while (window.pollEvent(event)) {
  //     if (event.type == sf::Event::Closed) {
  //       window.close();
  //     } else {
  //       titlescreen.handleEvent(event);
  //     }
  //   }

  //   titlescreen.update();
  //   window.clear();
  //   titlescreen.render(window);
  //   window.display();
  // }

  // std::string username = titlescreen.getUsername();

  // std::cout << "Username: " << username << std::endl;

  return 0;
}
