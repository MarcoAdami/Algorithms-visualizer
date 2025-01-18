#include "../include/Blocks.h"

using namespace std;

void Blocks::initVertex() {
  heightBlock = height / nBlocks;
  widthBlock = width / nBlocks;
  vertices = vector<sf::Vertex>(nBlocks * 4);

  for (size_t i = 0; i < nBlocks; ++i) {
    // height_rect = sizeY * (i + 1);
    sf::Vector2f size((float)widthBlock, (float)(heightBlock * (i + 1)));
    sf::Vector2f position(widthBlock * i, 0);  // Adjust positioning

    size_t offset = i * 4;
    vertices[offset + 0].position = position;
    vertices[offset + 1].position = position + sf::Vector2f(size.x, 0);
    vertices[offset + 2].position = position + sf::Vector2f(size.x, size.y);
    vertices[offset + 3].position = position + sf::Vector2f(0, size.y);

    vertices[offset + 0].color = WHITE;
    vertices[offset + 1].color = WHITE;
    vertices[offset + 2].color = WHITE;
    vertices[offset + 3].color = WHITE;
  }
}

void Blocks::initBuffer() {
  vBuff = sf::VertexBuffer(sf::Quads);
  if (!vBuff.create(nBlocks * 4)) {
    cout << "It couldn't be possibile to create VertexBuffer" << endl;
  }
  vBuff.update(&vertices[0], vertices.size(), 0);
}

void Blocks::initTexture(float x, float y) {
  // Create and set textures
  texture.create(width, height);

  this->setTexture(texture.getTexture());
  this->setPosition({x, y});

  // Flip y axis
  sf::View flippedView = texture.getDefaultView();
  sf::Vector2f size = flippedView.getSize();
  flippedView.setSize(size.x, -size.y);
  texture.setView(flippedView);
}

Blocks::Blocks(float h, float w, float x, float y) {
  height = h;
  width = w;
  initVertex();
  initBuffer();
  initTexture(x, y);
}

void Blocks::render() {
  vBuff.update(&vertices[0], vertices.size(), 0);

  texture.clear();
  texture.draw(vBuff);
  texture.display();
  // cout<<"a"<<endl;
}

void Blocks::reset_counter() {
  counter.swaps = 0;
  counter.reads = 0;
}

void Blocks::increaseBlocks() {
  if (nBlocks * 10 < 10000000) {
    nBlocks *= 10;
  }
  initVertex();
  initBuffer();
}

void Blocks::decreaseBlocks() {
  if (nBlocks / 10 > 1) {
    nBlocks /= 10;
  }
  initVertex();
  initBuffer();
}

void Blocks::shuffleBlocks() {
  srand(time(NULL));
  int temp = 0;
  for (int i = 0; i < vertices.size(); i = i + 4) {
    int index_random = (rand() % vertices.size() / 4) * 4;
    swap(vertices[i + 2].position.y, vertices[index_random + 2].position.y);
    swap(vertices[i + 3].position.y, vertices[index_random + 3].position.y);
  }
  cout << "shuffling made" << endl;
}

int Blocks::cmp(int i, int j) {
  float y1 = vertices[i * 4 + 2].position.y;
  float y2 = vertices[j * 4 + 2].position.y;
  if (y1 < y2) {
    return -1;
  } else if (y1 == y2) {
    return 0;
  } else {
    return 1;
  }
}

void Blocks::swapBlocks(int i, int j) {
  counter.swaps++;
  swap(vertices[i * 4 + 2].position.y, vertices[j * 4 + 2].position.y);
  swap(vertices[i * 4 + 3].position.y, vertices[j * 4 + 3].position.y);
}

float Blocks::getValueY(int i) {
  counter.reads++;
  return vertices[i * 4 + 2].position.y;
}

void Blocks::assignValue(int i, int value) {
  counter.swaps++;
  vertices[i * 4 + 2].position.y = value;
  vertices[i * 4 + 3].position.y = value;
}

void Blocks::resetColor() {
  for (int i = 0; i < nBlocks; ++i) {
    unmark(i);
  }
}

void Blocks::mark(int i) {
  int offset = i * 4;
  vertices[offset + 0].color = GREEN;
  vertices[offset + 1].color = GREEN;
  vertices[offset + 2].color = GREEN;
  vertices[offset + 3].color = GREEN;
}

void Blocks::unmark(int i) {
  int offset = i * 4;
  vertices[offset + 0].color = WHITE;
  vertices[offset + 1].color = WHITE;
  vertices[offset + 2].color = WHITE;
  vertices[offset + 3].color = WHITE;
}