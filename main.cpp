#include <SFML/Graphics.hpp>
#include<vector>
#include<cstdlib>
#include <thread>
#include <iostream>

using namespace std;

float width = 900;
float height = 600;


float sizeX=10;
float sizeY=10;
float height_rect = 0;
bool isOrdered=false;

float nElements = 10000;

bool isSorting = false;


void initArray(vector<int>& arr){
    for(int i=0; i<arr.size(); ++i){
        arr[i] = i+1;
    }
}

void shuffleArray(vector<int>& arr){
    srand(time(NULL));
    for(int i=0; i<arr.size(); ++i){
        int index_random = rand() % arr.size();
        int temp = arr[i];
        arr[i]= arr[index_random];
        arr[index_random] = temp;
    }
}


void update_render(vector<int>& data, sf::RenderWindow& window, sf::RectangleShape& rect){
    // clear the window with black color
    window.clear(sf::Color::Black);

    // draw everything here...
    // window.draw(...);

    
    for(int i=0; i<data.size(); ++i){
        
        sizeX = width/nElements;
        sizeY = height/nElements;
        height_rect = data[i]*sizeY;

        rect.setSize({sizeX, height_rect});
        rect.setPosition({(float)(i*sizeX), height-height_rect});
        rect.setFillColor(sf::Color::White);
        
        window.draw(rect);
    }

    // end the current frame
    window.display();
}

void render_check(vector<int>& data, sf::RenderWindow& window, sf::RectangleShape rect){
    window.clear(sf::Color::Black);

    // draw everything here...
    // window.draw(...);

    
    for(int i=0; i<data.size(); ++i){
        sizeX = width/nElements;
        sizeY = height/nElements;
        height_rect = data[i]*sizeY;

        rect.setSize({sizeX, height_rect});
        rect.setPosition({(float)(i*sizeX), height-height_rect});

        rect.setFillColor(sf::Color::Green);


        window.draw(rect);
    }

    // end the current frame
    window.display();
}

void bubbleSort(vector<int>& data){
    for(int i=0; i<data.size(); ++i){
        for(int j=0; j<data.size()-1-i; ++j){
            if(data[j]>data[j+1]){
                // update_render(data, j);
                data[j] = data[j]^data[j+1];
                data[j+1] = data[j]^data[j+1];
                data[j] = data[j]^data[j+1];
                // update_render(data, j);
            }
        }
    }
}


void mergeSort(vector<int>& arr, int start, int middle, int end)
{
  // Check that the remaining array is more than 2 elements
  if (end - start >= 2)
  {
    // Recursive call - Divide the array in left and right
    
    mergeSort(arr, start, (middle + start) / 2, middle); // Call mergesort on the left array
    mergeSort(arr, middle, (middle + end) / 2, end); //Call mergesort on right array

    int la = middle - start;
    int lb = end - middle;

    //Create temp vector
    vector<int> A, B;
    for (int i = start; i < middle; ++i)
    {
      A.push_back(arr[i]);
    }
    for (int i = middle; i < end; ++i)
    {
      B.push_back(arr[i]);
    }
    
    int i = start;
    int j = 0;
    int k = 0;

    // Merge
    while(j<la || k<lb){
      if ((A[j] <= B[k] && j<la) || k>=lb)
      {
        arr[i] = A[j];
        // update_render(arr, i);
        j++;
      }
      else
      {
        arr[i] = B[k];
        // update_render(arr, i);
        k++;
      }
      i++;
      this_thread::sleep_for(chrono::microseconds(100)); // Slow down for visualization
    }
  }
}

void startMergeSort(vector<int>& arr){
    int n = arr.size();
    isSorting = true;
    thread t1([&]{
        mergeSort(arr, 0, arr.size() / 2, arr.size());
        isSorting = false;
    });
    t1.detach();
//   mergeSort(arr, 0, n/2, n);
}

int main()
{
   
    // create the window
    sf::RenderWindow window(sf::VideoMode(width, height), "Show of algorithm");
    sf::RectangleShape rect;
    
    vector<int> data(nElements);
    initArray(data);
    


    window.setFramerateLimit(30);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
            } else if(event.type == sf::Event::KeyPressed){
                switch (event.key.code)
                {
                case sf::Keyboard::S:
                    if(!isSorting){
                        shuffleArray(data);
                    }else{
                        cout<<"You can't launch the shuffling because sorting is going"<<endl;
                    }
                    
                    break;
                
                case sf::Keyboard::Space:
                    if(!isSorting){
                        startMergeSort(data);
                    }else{
                        cout<<"You can't launch another sorting because one is already started"<<endl;
                    }
                    
                    break;
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