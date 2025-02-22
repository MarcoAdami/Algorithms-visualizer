#include <SFML/Graphics.hpp>
#include <atomic>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

#include "../include/Algorithm.h"
#include "../include/Blocks.h"
#include "../include/StatusBar.h"
#include "../include/config.h"
using namespace std;

int main() {
  // create the window
  sf::RenderWindow window(sf::VideoMode(widthWindow, heightWindow),
                          "Show of algorithm");

  int positionBlocksX = 0;
  int positionBlocksY = 20;

  Blocks blocks(heightSort, widthSort, positionBlocksX, positionBlocksY);
  Algorithms algo(&blocks);
  Statusbar bar(&blocks, &algo, 20.0, widthSort);

  window.setFramerateLimit(30);

  // run the program as long as the window is open
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      // catch the resize events
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::Right:
            algo.increaseBlocks();
            break;
          case sf::Keyboard::Left:
            algo.decreaseBlocks();
            break;
          case sf::Keyboard::Up:
            algo.increaseSpeed();
            break;
          case sf::Keyboard::Down:
            algo.decreaseSpeed();
            break;
          case sf::Keyboard::S:
            algo.shuffleBlocks();
            break;
          case sf::Keyboard::Num1:
            algo.start(1);
            break;
          case sf::Keyboard::Num2:
            algo.start(2);
            break;
          case sf::Keyboard::Num3:
            algo.start(3);
            break;
          case sf::Keyboard::Num4:
            algo.start(4);
            break;
          case sf::Keyboard::Num5:
            algo.start(5);
            break;
          case sf::Keyboard::Num6:
            algo.start(6);
            break;
          default:
            break;
        }
      }
    }

    blocks.render();
    bar.render();
    window.clear(sf::Color::Black);

    window.draw(blocks);  // Draw the vertices
    window.draw(bar);     // Draw the text

    window.display();
  }

  return 0;
}