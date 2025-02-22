#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>
#include "Blocks.h"

class Algorithms {
 public:
  bool isSorted = true;
  bool isSorting = false;
  bool working = false;
  int selectedAlgo = 0;
  int speed = 1;
  int time = 1000000;
  vector<string> nameAlgo = {"Nothing", "BubbleSort", "MergeSort",
                            "ShakerSort", "QuickSort", "RadixSort",
                            "ShellSort"};

  Blocks* blocks;

  Algorithms(Blocks* blocks);
  void start(int id);
  void chooseAlgorithm();
  void increaseSpeed();
  void decreaseSpeed();
  void increaseBlocks();
  void decreaseBlocks();
  void shuffleBlocks();
  bool checkSort();
  void bubbleSort();
  void mergeSort(int start, int middle, int end);
  void startMergeSort();
  void shakerSort();
  int partition(int low, int high);
  void quickSort(int low, int high);
  void startQuickSort();
  int getMax(int n);
  void countSort(int n, int exp);
  void radixSort();
  void shellSort();
};

#endif // ALGORITHMS_H