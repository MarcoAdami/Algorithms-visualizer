#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

#include "config.h"
#include "algorithm.cpp"

using namespace std;

float height_rect = 0;
bool isOrdered = false;

float nElements = 10000;

bool isSorting = false;

void initArray(vector<int>& arr) {
  for (int i = 0; i < arr.size(); ++i) {
    arr[i] = i + 1;
  }
}

void shuffleArray(vector<int>& arr) {
  srand(time(NULL));
  for (int i = 0; i < arr.size(); ++i) {
    int index_random = rand() % arr.size();
    int temp = arr[i];
    arr[i] = arr[index_random];
    arr[index_random] = temp;
  }
}

void update_render(vector<int>& data, sf::RenderWindow& window,
                   sf::RectangleShape& rect) {
  // clear the window with black color
  window.clear(sf::Color::Black);

  // draw everything here...
  // window.draw(...);

  for (int i = 0; i < data.size(); ++i) {
    sizeX = width / nElements;
    sizeY = height / nElements;
    height_rect = data[i] * sizeY;

    rect.setSize({sizeX, height_rect});
    rect.setPosition({(float)(i * sizeX), height - height_rect});
    rect.setFillColor(sf::Color::White);

    window.draw(rect);
  }

  // end the current frame
  window.display();
}

void render_check(vector<int>& data, sf::RenderWindow& window,
                  sf::RectangleShape rect) {
  window.clear(sf::Color::Black);

  // draw everything here...
  // window.draw(...);

  for (int i = 0; i < data.size(); ++i) {
    sizeX = width / nElements;
    sizeY = height / nElements;
    height_rect = data[i] * sizeY;

    rect.setSize({sizeX, height_rect});
    rect.setPosition({(float)(i * sizeX), height - height_rect});

    rect.setFillColor(sf::Color::Green);

    window.draw(rect);
  }

  // end the current frame
  window.display();
}


void initThread(void (*fun)(vector<int>&), vector<int>& data) {
  // init thread

  if (!isSorting) {
    isSorting = true;
    thread t1([fun, &data] {
      fun(data);  // Call the function
      isSorting = false;
    });
    t1.detach();
  } else {
    cout << "You can't launch another sorting because one is already "
            "started"
         << endl;
  }
}

int main() {
  // create the window
  sf::RenderWindow window(sf::VideoMode(width, height), "Show of algorithm");
  sf::RectangleShape rect;

  vector<int> data(nElements);
  initArray(data);

  window.setFramerateLimit(30);

  // run the program as long as the window is open
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::S:
            if (!isSorting) {
              shuffleArray(data);
            } else {
              cout << "You can't launch the shuffling because sorting is going"
                   << endl;
            }

            break;

          case sf::Keyboard::Num1:
            initThread(&startMergeSort, data);
            break;

          case sf::Keyboard::Num2:
            initThread(&bubbleSort, data);

          default:
            break;
        }
      }
    }

    // if(!isOrdered){

    //     startMergeSort(data, data.size());
    //     // bubbleSort(data);

    //     isOrdered=true;

    //     render_check(data);
    // }

    update_render(data, window, rect);
  }
  return 0;
}