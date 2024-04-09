#include "classes/Board.h"
#include "classes/Cell.h"
#include "screens/Screen.h"
#include "utils/RandomHelper.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
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
  auto image = sf::Image{};

  image.loadFromFile("./files/images/mine.png");

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
  // Now rendering the main pages
  int screenWidth = config.columns * 32;
  int screenHeight = (config.rows * 32) + 100;

  sf::RenderWindow titlewindow(sf::VideoMode(screenWidth, screenHeight),
                               "Minesweeper", sf::Style::Close);

  TitleScreen titlescreen(screenWidth, screenHeight);

  while (titlewindow.isOpen()) {
    sf::Event event;
    while (titlewindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        titlewindow.close();
      } else {
        titlescreen.handleEvent(event);
      }
    }

    titlescreen.update();
    titlewindow.clear();
    titlescreen.render(titlewindow);
    titlewindow.display();
  }

  std::string username = titlescreen.getUsername();

  std::cout << "Username: " << username << std::endl;

  sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight),
                          "Minesweeper", sf::Style::Close);

  window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

  GameScreen gamescreen(screenWidth, screenHeight, config.columns, config.rows,
                        config.bombCount, username);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      gamescreen.handleEvent(event);
    }

    gamescreen.update();

    window.clear();
    gamescreen.render(window);
    window.display();
  }

  return 0;
}
