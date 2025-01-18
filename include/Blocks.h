#ifndef BLOCKS_H
#define BLOCKS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;

class Blocks : public sf::Sprite {
 private:
  void initVertex();
  void initBuffer();
  void initTexture(float x, float y);

 public:
  float nBlocks = 10;
  float height;
  float width;
  float heightBlock;
  float widthBlock;

  struct COUNTERS {
    long long int swaps = 0;
    long long int reads = 0;
  } counter;

  sf::Color WHITE = sf::Color::White;
  sf::Color GREEN = sf::Color::Green;

  sf::RenderTexture texture;
  vector<sf::Vertex> vertices;
  sf::VertexBuffer vBuff;

  Blocks(float h, float w, float x, float y);
  void render();
  void reset_counter();
  void increaseBlocks();
  void decreaseBlocks();
  void shuffleBlocks();
  int cmp(int i, int j);
  void swapBlocks(int i, int j);
  float getValueY(int i);
  void assignValue(int i, int value);
  void resetColor();
  void mark(int i);
  void unmark(int i);
};

#endif // BLOCKS_H