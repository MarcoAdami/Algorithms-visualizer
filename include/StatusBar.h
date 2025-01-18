#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include "../include/Blocks.h"
#include "../include/Algorithm.h"

using namespace std;

class Statusbar : public sf::Sprite {
private:
    void initTexture();

public:
    float width;
    float height;

    sf::RenderTexture texture;
    sf::Text text;
    sf::Font font;

    Blocks* blocks;
    Algorithms* algo;

    Statusbar(Blocks* blocks, Algorithms* algo, float h, float w);
    void render();
};

#endif // STATUSBAR_H