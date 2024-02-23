#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow win{sf::VideoMode{500, 500}, "TIC++"};
  win.setFramerateLimit(60);

  while (win.isOpen()) {
    sf::Event e;
    while (win.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        win.close();
      }
    }
    win.clear();


    win.display();
  }
}
