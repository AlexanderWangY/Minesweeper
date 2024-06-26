#include "../utils/TextHelper.h"
#include "Screen.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <cctype>
#include <iostream>
#include <ostream>
#include <string>

TitleScreen::TitleScreen(int _width, int _height) {
  font.loadFromFile("./files/font.ttf");
  userInput = "";
  width = _width;
  height = _height;

  // Setting up Title Text
  titleText.setFont(font);
  titleText.setString("WELCOME TO MINESWEEPER!");
  titleText.setCharacterSize(24);
  titleText.setFillColor(sf::Color::White);
  titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
  setText(titleText, width / 2, height / 2 - 150);

  // Setting up Input Prompt Text
  inputPromptText.setFont(font);
  inputPromptText.setString("Enter your name:");
  inputPromptText.setCharacterSize(20);
  inputPromptText.setFillColor(sf::Color::White);
  setText(inputPromptText, width / 2, height / 2 - 75);

  // Setting up empty User Input Text

  userInputText.setFont(font);
  userInputText.setString("Alexander");
  userInputText.setCharacterSize(18);
  userInputText.setFillColor(sf::Color::Yellow);
  userInputText.setStyle(sf::Text::Bold);
  setText(userInputText, width / 2, height / 2 - 45);
}

std::string TitleScreen::getUsername() {
  return this->userInputText.getString();
}

void TitleScreen::handleEvent(sf::Event event) {

  // Check if event is user entering text!

  if (event.type == sf::Event::TextEntered) {
    if (event.text.unicode < 128) {

      if (event.text.unicode == '\r' && userInput.getSize() > 0) {
        window->close();
      } else if (event.text.unicode == '\b' && !userInput.isEmpty()) {
        userInput.erase(userInput.getSize() - 1);
      } else if (userInput.getSize() < 10 && event.text.unicode != '\b' &&
                 event.text.unicode != '\r' &&
                 std::isalpha(static_cast<char>(event.text.unicode))) {
        if (userInput.getSize() == 0) {
          userInput += static_cast<char>(
              std::toupper(static_cast<char>(event.text.unicode)));
        } else {
          userInput += static_cast<char>(
              std::tolower(static_cast<char>(event.text.unicode)));
        }
      }
    }
  }
}

void TitleScreen::update() {
  // Updating something but not now!
  userInputText.setString(userInput);
}

void TitleScreen::render(sf::RenderWindow &_window) {
  this->window = &_window;
  window->clear(sf::Color::Blue);
  window->draw(titleText);
  window->draw(inputPromptText);
  window->draw(userInputText);
}
