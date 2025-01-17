#include<iostream>
#include<vector>
#include <SFML/Graphics.hpp>

// float sizeX=10;
// float sizeY=10;


void updateRender(sf::VertexBuffer& vBuff, sf::RenderWindow& window, sf::Text& text) {
  // clear the window with black color
  window.clear(sf::Color::Black);

  window.draw(vBuff);

  window.draw(text);
  

  

  // window.draw(text);
  // end the current frame
  window.display();
}
