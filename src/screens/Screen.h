#pragma once
#include "../classes/Board.h"
#include "../utils/TimerUtility.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
#include <unordered_map>

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
  Board myBoard;
  std::unordered_map<std::string, sf::Texture> buttonTextures;
  sf::Sprite win;
  sf::Sprite lose;
  sf::Sprite happy;
  sf::Sprite debug;
  sf::Sprite pause;
  sf::Sprite play;
  sf::Sprite leader;

  // For timer
  std::unordered_map<int, sf::Texture> numberTextures;
  int timeElapsed;
  sf::Sprite hundreth;
  sf::Sprite tens;
  sf::Sprite ones;

  sf::Sprite minuteTen;
  sf::Sprite minute;
  sf::Sprite secondTen;
  sf::Sprite second;

  // Actual Chrono Timer class
  Timer timer;
  int timeTaken;

  // For game logic
  bool gameOver = false;
  bool winner = false;
  bool paused = false;
  bool debugMode = false;
  bool enabled = true;

  int flagsLeft;

  // For window sizing
  int width;
  int height;
  int columns;
  int rows;
  int bombCount;

  // Other MISC.
  std::string username;

public:
  GameScreen(int _width, int _height, int _columns, int _rows, int _bombCount,
             std::string _username);
  ~GameScreen(){};

  void handleEvent(sf::Event event) override;
  void update() override;
  void render(sf::RenderWindow &_window) override;

  void reset();
};

class Leaderboard : public Screen {
private:
  sf::Font font;
  sf::Text titleText;
  sf::Text leaderboardText;
  sf::RenderWindow *window;

  // For window sizing

  int width;
  int height;

public:
  Leaderboard(int _width, int _height);

  void handleEvent(sf::Event event) override;
  void update() override;
  void render(sf::RenderWindow &_window) override;
};
