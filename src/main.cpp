#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works!");
  window.setVerticalSyncEnabled(true);
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Red);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      std::cout << "D" << std::endl;
    }

    window.clear();
    window.draw(shape);
    window.display();
  }
  return 0;
}
