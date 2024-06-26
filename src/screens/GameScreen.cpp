#include "../classes/Board.h"
#include "../utils/LeaderboardHelper.h"
#include "../utils/SpriteHelper.h"
#include "Screen.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cstdlib>
#include <iostream>

GameScreen::GameScreen(int _width, int _height, int _columns, int _rows,
                       int _bombCount, std::string _username) {
  width = _width;
  height = _height;
  columns = _columns;
  rows = _rows;
  bombCount = _bombCount;
  flagsLeft = bombCount;
  username = _username;

  myBoard.loadBoard(columns, rows, bombCount);

  buttonTextures["happy"].loadFromFile("./files/images/face_happy.png");
  buttonTextures["win"].loadFromFile("./files/images/face_win.png");
  buttonTextures["lose"].loadFromFile("./files/images/face_lose.png");
  buttonTextures["debug"].loadFromFile("./files/images/debug.png");
  buttonTextures["pause"].loadFromFile("./files/images/pause.png");
  buttonTextures["play"].loadFromFile("./files/images/play.png");
  buttonTextures["leader"].loadFromFile("./files/images/leaderboard.png");

  // Numbered textures
  for (int x = 0; x < 12; ++x) {
    sf::IntRect textureRect(21 * x, 0, 21, 32);
    sf::Texture texture;
    texture.loadFromFile("./files/images/digits.png");
    texture.loadFromImage(texture.copyToImage(), textureRect);
    numberTextures[x] = texture;
  }
  // Set number textures and positions
  hundreth.setTexture(numberTextures[0]);
  tens.setTexture(numberTextures[5]);
  ones.setTexture(numberTextures[0]);

  minuteTen.setTexture(numberTextures[0]);
  minute.setTexture(numberTextures[0]);
  secondTen.setTexture(numberTextures[0]);
  second.setTexture(numberTextures[0]);

  // Number positions

  minuteTen.setPosition((columns * 32) - 97, 32 * (rows + 0.5) + 16);
  minute.setPosition((columns * 32) - 76, 32 * (rows + 0.5) + 16);
  secondTen.setPosition((columns * 32) - 54, 32 * (rows + 0.5) + 16);
  second.setPosition((columns * 32) - 33, 32 * (rows + 0.5) + 16);

  hundreth.setPosition(33, 32 * (rows + 0.5) + 16);
  tens.setPosition(54, 32 * (rows + 0.5) + 16);
  ones.setPosition(75, 32 * (rows + 0.5) + 16);

  happy.setTexture(buttonTextures["happy"]);
  win.setTexture(buttonTextures["win"]);
  lose.setTexture(buttonTextures["lose"]);
  debug.setTexture(buttonTextures["debug"]);
  pause.setTexture(buttonTextures["pause"]);
  play.setTexture(buttonTextures["play"]);
  leader.setTexture(buttonTextures["leader"]);

  // Set positions

  happy.setPosition(columns / 2.0 * 32.f - 32, 32 * (rows + 0.5));
  win.setPosition(columns / 2.0 * 32.f - 32, 32 * (rows + 0.5));
  lose.setPosition(columns / 2.0 * 32.f - 32, 32 * (rows + 0.5));
  debug.setPosition(columns * 32.f - 304, 32 * (rows + 0.5));
  pause.setPosition(columns * 32.f - 240, 32 * (rows + 0.5));
  play.setPosition(columns * 32.f - 240, 32 * (rows + 0.5));
  leader.setPosition(columns * 32.f - 176, 32 * (rows + 0.5));

  // Start timer!
  timer.start();
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
      int result = myBoard.handleClick(x, y);

      if (result == -1) {
        winner = false;
        gameOver = true;
        myBoard.toggleDisable();
      } else if (result == 1) {
        std::cout << "You can't reveal a flag.\n";
      } else if (result == 404) {
        std::cout << "Did not click within bounds\n";
      } else if (result == 500) {
        std::cout << "Board is disabled.\n";
      }

      if (isClicked(debug, x, y) && !gameOver) {
        std::cout << "Toggling debug\n";
        debugMode = !debugMode;
      } else if (isClicked(happy, x, y)) {
        std::cout << "resetting game\n";
        this->reset();
      } else if (isClicked(leader, x, y)) {
        std::cout << "Opening leaderboard\n";
        timer.pause();
        paused = true;
        myBoard.Disable();

        int screenHeight = rows * 16 + 50;
        int screenWidth = columns * 16;

        sf::RenderWindow nWindow(sf::VideoMode(screenWidth, screenHeight),
                                 "Leaderboard", sf::Style::Close);

        Leaderboard leader(screenWidth, screenHeight);

        while (nWindow.isOpen()) {
          sf::Event event;
          while (nWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
              nWindow.close();
            }
          }

          nWindow.clear(sf::Color::Blue);
          leader.render(nWindow);
          nWindow.display();
        }

        if (!gameOver) {
          timer.start();
          paused = false;
          myBoard.toggleDisable();
        }
      } else if (isClicked(pause, x, y) && !gameOver) {
        if (timer.running()) {
          timer.pause();
        } else {
          timer.start();
        }
        debugMode = false;
        paused = !paused;
        myBoard.toggleDisable();
      }

    } else if (event.mouseButton.button == sf::Mouse::Right && !gameOver) {
      int x = event.mouseButton.x;
      int y = event.mouseButton.y;

      // Now check every cell to see if I click on anything!
      int result = myBoard.handleFlag(x, y);

      if (result == 0) {
        flagsLeft--;
      } else if (result == 2) {
        flagsLeft++;
      } else if (result == 1) {
        std::cout << "Can't place flag over a revealed element!\n";
      } else if (result == 404) {
        // Nothing
      }

      if (myBoard.checkForWin()) {
        gameOver = true;
        winner = true;
        timeTaken = timer.getElapsedTime();
        paused = true;
        timer.pause();
        myBoard.Disable();
        setScore(username, timeTaken);
      }
    }
  }
}

void GameScreen::update() {
  // Calculate how many flags left
  if (flagsLeft >= 0) {
    int hundred = flagsLeft / 100;
    int ten = (flagsLeft % 100) / 10;
    int one = (flagsLeft % 10);
    hundreth.setTexture(numberTextures[hundred]);
    tens.setTexture(numberTextures[ten]);
    ones.setTexture(numberTextures[one]);
  } else if (flagsLeft < 0) {
    hundreth.setTexture(numberTextures[10]);
    int flags = abs(flagsLeft);
    int ten = flags / 10;
    int one = (flags % 10);
    tens.setTexture(numberTextures[ten]);
    ones.setTexture(numberTextures[one]);
  }

  // Calculate timer times
  /*
  10 minute == 600 seconds
  1 minute = 60 seconds
  */
  int elapsedTime = timer.getElapsedTime();
  timeElapsed = elapsedTime;
  int tenMinutes = elapsedTime / 600;
  elapsedTime = elapsedTime % 600;
  int minutes = elapsedTime / 60;
  elapsedTime = elapsedTime % 60;
  int tenSeconds = elapsedTime / 10;
  int seconds = elapsedTime % 10;

  minuteTen.setTexture(numberTextures[tenMinutes]);
  minute.setTexture(numberTextures[minutes]);
  secondTen.setTexture(numberTextures[tenSeconds]);
  second.setTexture(numberTextures[seconds]);
}

void GameScreen::render(sf::RenderWindow &_window) {
  this->window = &_window;
  window->clear(sf::Color::White);
  myBoard.render(*window, debugMode);

  window->draw(hundreth);
  window->draw(tens);
  window->draw(ones);
  window->draw(minuteTen);
  window->draw(minute);
  window->draw(secondTen);
  window->draw(second);

  if (gameOver) {
    if (winner) {
      window->draw(win);
    } else {
      window->draw(lose);
    }
  } else {
    window->draw(happy);
  }

  if (paused) {
    window->draw(play);
  } else {
    window->draw(pause);
  }

  window->draw(leader);
  window->draw(debug);
}

void GameScreen::reset() {
  flagsLeft = bombCount;
  winner = false;
  gameOver = false;
  debugMode = false;
  paused = false;

  myBoard.loadBoard(columns, rows, bombCount);

  buttonTextures["happy"].loadFromFile("./files/images/face_happy.png");
  buttonTextures["win"].loadFromFile("./files/images/face_win.png");
  buttonTextures["lose"].loadFromFile("./files/images/face_lose.png");
  buttonTextures["debug"].loadFromFile("./files/images/debug.png");
  buttonTextures["pause"].loadFromFile("./files/images/pause.png");
  buttonTextures["play"].loadFromFile("./files/images/play.png");
  buttonTextures["leader"].loadFromFile("./files/images/leaderboard.png");

  happy.setTexture(buttonTextures["happy"]);
  win.setTexture(buttonTextures["win"]);
  lose.setTexture(buttonTextures["lose"]);
  debug.setTexture(buttonTextures["debug"]);
  pause.setTexture(buttonTextures["pause"]);
  play.setTexture(buttonTextures["play"]);
  leader.setTexture(buttonTextures["leader"]);

  // Set positions

  happy.setPosition(columns / 2.0 * 32.f - 32, 32 * (rows + 0.5));
  win.setPosition(columns / 2.0 * 32.f - 32, 32 * (rows + 0.5));
  lose.setPosition(columns / 2.0 * 32.f - 32, 32 * (rows + 0.5));
  debug.setPosition(columns * 32.f - 304, 32 * (rows + 0.5));
  pause.setPosition(columns * 32.f - 240, 32 * (rows + 0.5));
  play.setPosition(columns * 32.f - 240, 32 * (rows + 0.5));
  leader.setPosition(columns * 32.f - 176, 32 * (rows + 0.5));

  timer.reset();
  timer.start();
}
