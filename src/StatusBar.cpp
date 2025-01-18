#include "../include/StatusBar.h"

using namespace std;

void Statusbar::initTexture() {
  texture.create(width, height);
  this->setTexture(texture.getTexture());
}

Statusbar::Statusbar(Blocks* blocks, Algorithms* algo, float h, float w) {
  this->width = w;
  this->height = h;
  this->blocks = blocks;
  this->algo = algo;

  initTexture();

  font.loadFromFile("Arial.ttf");
  text.setFont(font);

  text.setCharacterSize(15);
  text.setFillColor(sf::Color::White);
}

void Statusbar::render() {
  stringstream sstr;

  sstr << "Select Alg: " << algo->nameAlgo[algo->selectedAlgo]
       << " | Elements: " << blocks->nBlocks
       << " | Swap count: " << blocks->counter.swaps << " | Speed: x"
       << algo->speed << " | isSorted: " << (algo->isSorted ? "YES" : "NO")
       << " | isSorting: " << (algo->isSorting ? "YES" : "NO");

  text.setString(sstr.str());
  texture.clear();
  texture.draw(text);
  texture.display();
}
