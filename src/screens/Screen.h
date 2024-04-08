#pragma once
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

  // For window sizing

  int width;
  int height;

public:
  TitleScreen(int _width, int _height);
  ~TitleScreen(){};
  void handleEvent(sf::Event event) override;
  void update() override;
  void render(sf::RenderWindow &window) override;
};
