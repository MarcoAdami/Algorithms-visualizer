#include <SFML/Graphics.hpp>
#include <atomic>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

#include "algorithm.cpp"
#include "config.h"
#include "render.cpp"

using namespace std;

atomic<bool> updateBuffer(false);

void initVertex(vector<sf::Vertex>& vertices) {
  sf::Color color = sf::Color::White;

  for (size_t i = 0; i < nElements; ++i) {
    height_rect = sizeY * (i + 1);
    sf::Vector2f size(sizeX, height_rect);
    sf::Vector2f position(sizeX * i, 0);  // Adjust positioning

    size_t offset = i * 4;
    vertices[offset + 0].position = position;
    vertices[offset + 1].position = position + sf::Vector2f(size.x, 0);
    vertices[offset + 2].position = position + sf::Vector2f(size.x, size.y);
    vertices[offset + 3].position = position + sf::Vector2f(0, size.y);

    vertices[offset + 0].color = color;
    vertices[offset + 1].color = color;
    vertices[offset + 2].color = color;
    vertices[offset + 3].color = color;
  }
}

void shuffleArray(vector<sf::RectangleShape>& arr) {
  srand(time(NULL));
  isSorted = false;
  for (int i = 0; i < arr.size(); ++i) {
    int index_random = rand() % arr.size();
    // sf::RectangleShape temp = arr[i];
    // arr[i] = arr[index_random];
    // arr[index_random] = temp;
    swap(arr[i], arr[index_random]);
  }
  cout << "shuffling made" << endl;
}

void shuffleArray(vector<sf::Vertex>& arr) {
  srand(time(NULL));
  isSorted = false;
  int temp = 0;
  for (int i = 0; i < arr.size(); i = i + 4) {
    int index_random = (rand() % arr.size() / 4) * 4;
    swap(arr[i + 2].position.y, arr[index_random + 2].position.y);
    swap(arr[i + 3].position.y, arr[index_random + 3].position.y);
  }
  cout << "shuffling made" << endl;
}

// void initThread(void (*fun)(vector<sf::RectangleShape>&),
//                 vector<sf::RectangleShape>& blocks) {
//   // init thread

//   if (!isSorting && !isSorted) {
//     isSorting = true;
//     thread t1([fun, &blocks] {
//       fun(blocks);  // Call the function
//       isSorting = false;
//       // checkSort(blocks);
//     });
//     t1.detach();
//   } else if (isSorted) {
//     cout << "Array already sorted" << endl;
//   } else {
//     cout << "You can't launch another sorting because one is already "
//             "started"
//          << endl;
//   }
// }

void initThread(void (*fun)(vector<sf::Vertex>&),
                vector<sf::Vertex>& vertices) {
  // init thread

  if (!isSorting && !isSorted) {
    thread t1([fun, &vertices] {
      isSorting = true;
      fun(vertices);  // Call the function
      isSorting = false;
      // checkSort(vertices);
    });
    t1.detach();
  } else if (isSorted) {
    cout << "Array already sorted" << endl;
  } else {
    cout << "You can't launch another sorting because one is already "
            "started"
         << endl;
  }
}

int main() {
  // create the window
  sf::RenderWindow window(sf::VideoMode(widthWindow, heightWindow),
                          "Show of algorithm");

  // flip y axis
  sf::View flippedView = window.getDefaultView();
  sf::Vector2f size = flippedView.getSize();
  flippedView.setSize(size.x, -size.y);
  

  sf::View defaultView = window.getDefaultView();

  // Create the array for the blocks
  vector<sf::Vertex> vertices(nElements * 4);
  initVertex(vertices);

  // Create a VertexBuffer and load the VertexArray data into it
  sf::VertexBuffer vBuff(sf::Quads);
  // vBuff.setUsage(sf::VertexBuffer::Static); // stream if the buffer need to
  // change a lot of time
  if (!vBuff.create(nElements * 4)) {
    return -1;  // Failed to create buffer
  }
  vBuff.update(&vertices[0], vertices.size(), 0);

  sf::Text text;
  sf::Font font;
  font.loadFromFile("Arial.ttf");
  text.setFont(font);
  text.setString("Number of elements: "+to_string((int)nElements));
  // text.setPosition({0,0});

  text.setCharacterSize(20);            // Set the text size (in pixels)
  text.setFillColor(sf::Color::Green);  // Set the text color
  text.setStyle(sf::Text::Bold);  // Set the text style (bold, italic, etc.)
  // text.setPosition({50, 50});     // Set the position of the text

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
              shuffleArray(vertices);
            } else {
              cout << "You can't launch the shuffling because sorting is going"
                   << endl;
            }
            break;

          case sf::Keyboard::Num1:
            initThread(&startMergeSort, vertices);

            break;
          case sf::Keyboard::Num2:
            initThread(&bubbleSort, vertices);
            break;
          case sf::Keyboard::Num3:
            initThread(&shakerSort, vertices);
            break;

          case sf::Keyboard::Num4:
            initThread(&startQuickSort, vertices);
            break;

          case sf::Keyboard::Num5:
            initThread(&radixSort, vertices);
            break;
          case sf::Keyboard::Num6:
            initThread(&shellSort, vertices);
            break;
          default:
            break;
        }
      }
    }

    
    vBuff.update(&vertices[0], vertices.size(), 0);

    window.clear();
    window.setView(flippedView);
    window.draw(vBuff); // Draw the vertices

    // Set the default view and draw text
    window.setView(defaultView);
    window.draw(text); // Draw the text
      // updateRender(vBuff, window, text);
    window.display();

  }



  return 0;


}