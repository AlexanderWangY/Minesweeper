#pragma once
#include "../classes/Board.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>

class Screen {
public:
  virtual void handleEvent(sf::Event event) = 0;
  virtual void update() = 0;
  virtual void render(sf::RenderWindow &window) = 0;
  virtual ~Screen(){};
};

class TitleScreen : public Screen {
private:
  sf::Font font;
  sf::Text titleText;
  sf::Text inputPromptText;
  sf::Text userInputText;
  sf::String userInput;
  sf::RenderWindow *window;

  // For window sizing

  int width;
  int height;

public:
  TitleScreen(int _width, int _height);
  ~TitleScreen(){};

  std::string getUsername();
  void handleEvent(sf::Event event) override;
  void update() override;
  void render(sf::RenderWindow &_window) override;
};

class GameScreen : public Screen {
private:
  sf::RenderWindow *window;
  Board *myBoard;

  // For window sizing
  int width;
  int height;
  int columns;
  int rows;
  int bombCount;

public:
  GameScreen(int _width, int _height, int _columns, int _rows, int _bombCount);
  ~GameScreen(){};

  void handleEvent(sf::Event event) override;
  void update() override;
  void render(sf::RenderWindow &_window) override;
};
