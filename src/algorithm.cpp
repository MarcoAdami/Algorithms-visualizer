#include "../include/Algorithm.h"

using namespace std;

Algorithms::Algorithms(Blocks *blocks) { this->blocks = blocks; }

void Algorithms::start(int id) {
  selectedAlgo = id;
  if (!isSorting && !isSorted) {
    thread t1([this] {
      this->isSorting = true;
      blocks->reset_counter();
      chooseAlgorithm();
      this->isSorting = false;
      this->isSorted = checkSort();
    });
    t1.detach();
  } else if (isSorted) {
    cout << "Array already sorted" << endl;
  } else {
    cout << "You can't launch another sorting because one is already started"
         << endl;
  }
}

// Continue with all other methods, adding Algorithms:: before each method name
void Algorithms::chooseAlgorithm() {
  switch (selectedAlgo) {
    case 1:
      bubbleSort();
      break;
    case 2:
      startMergeSort();
      break;
    case 3:
      shakerSort();
      break;
    case 4:
      startQuickSort();
      break;
    case 5:
      radixSort();
      break;
    case 6:
      shellSort();
      break;
    default:
      break;
  }
}

void Algorithms::increaseSpeed() {
  if (speed * 10 < 100000000) {
    speed *= 10;
  }
}

void Algorithms::decreaseSpeed() {
  if (speed / 10 > 0) {
    speed /= 10;
  }
}

void Algorithms::increaseBlocks() {
  if (!isSorting) {
    blocks->increaseBlocks();
  } else {
    cout << "a sorting is going on, please wait or stop the sort";
  }
}

void Algorithms::decreaseBlocks() {
  if (!isSorting) {
    blocks->decreaseBlocks();
  } else {
    cout << "a sorting is going on, please wait or stop the sort";
  }
}

void Algorithms::shuffleBlocks() {
  blocks->resetColor();
  if (!isSorting) {
    blocks->shuffleBlocks();
  } else {
    cout << "You can't launch the shuffling because sorting is going" << endl;
  }
  isSorted = false;
}

bool Algorithms::checkSort() {
  int n = blocks->nBlocks;
  int i = 0;
  for (; i < n - 1; ++i) {
    if (blocks->cmp(i, i + 1) == 1) {
      return false;
    }
    blocks->mark(i);
    this_thread::sleep_for(
        chrono::microseconds((int)(100000 / blocks->nBlocks)));
  }
  blocks->mark(i);
  return true;
}

void Algorithms::bubbleSort() {
  for (int i = 0; i < blocks->nBlocks; ++i) {
    for (int j = 0; j < blocks->nBlocks - 1 - i; ++j) {
      if (blocks->cmp(j, j + 1) == 1) {
        blocks->mark(j);
        blocks->mark(j + 1);

        blocks->swapBlocks(j, j + 1);
        this_thread::sleep_for(chrono::microseconds(time / speed));

        blocks->unmark(j);
        blocks->unmark(j + 1);
      }
    }
  }
  cout << "bubblesort made" << endl;
}

void Algorithms::mergeSort(int start, int middle, int end) {
  // Check that the remaining array is more than 2 elements
  if (end - start >= 2) {
    // Recursive call - Divide the array in left and right

    mergeSort(start, (middle + start) / 2,
              middle);  // Call mergesort on the left array
    mergeSort(middle, (middle + end) / 2,
              end);  // Call mergesort on right array

    int la = middle - start;
    int lb = end - middle;

    // Create temp vector
    vector<int> A, B;
    for (int i = start; i < middle; ++i) {
      A.push_back(blocks->getValueY(i));
    }
    for (int i = middle; i < end; ++i) {
      B.push_back(blocks->getValueY(i));
    }

    int i = start;
    int j = 0;
    int k = 0;

    // Merge
    while (j < la || k < lb) {
      if ((A[j] < B[k] && j < la) || k >= lb) {
        blocks->mark(i);
        blocks->assignValue(i, A[j]);

        j++;
      } else {
        blocks->mark(i);
        blocks->assignValue(i, B[k]);
        k++;
      }

      this_thread::sleep_for(
          chrono::microseconds(time / speed));  // Slow down for visualization

      blocks->unmark(i);
      i++;
    }
  }
}

void Algorithms::startMergeSort() {
  mergeSort(0, blocks->nBlocks / 2, blocks->nBlocks);
}

void Algorithms::shakerSort() {
  for (int i = 0; i < blocks->nBlocks / 2; ++i) {
    // loop going forward for bigger number
    for (int j = i; j < blocks->nBlocks - 1 - i; ++j) {
      if (blocks->cmp(j, j + 1) == 1) {
        blocks->swapBlocks(j, j + 1);
        this_thread::sleep_for(chrono::microseconds(time / speed));
      }
    }

    // loop going backward for lower number
    for (int j = blocks->nBlocks - 1 - i; j >= 1 + i; --j) {
      if (blocks->cmp(j, j - 1) == -1) {
        blocks->swapBlocks(j, j - 1);
        this_thread::sleep_for(chrono::microseconds(time / speed));
      }
    }
  }
}

int Algorithms::partition(int low, int high) {
  // Selecting last element as the pivot
  float pivot = blocks->getValueY(high);

  // Index of elemment just before the last element
  // It is used for swapping
  int i = (low - 1);

  for (int j = low; j <= high - 1; ++j) {
    // If current element is smaller than or
    // equal to pivot
    if (blocks->getValueY(j) <= pivot) {
      i++;
      blocks->mark(i);
      blocks->mark(j);
      blocks->swapBlocks(i, j);
      this_thread::sleep_for(chrono::microseconds(time / speed));

      blocks->unmark(i);
      blocks->unmark(j);
    }
  }

  blocks->swapBlocks(i + 1, high);

  return (i + 1);
}

void Algorithms::quickSort(int low, int high) {
  if (low < high) {
    int pi = partition(low, high);

    quickSort(low, pi - 1);
    quickSort(pi + 1, high);
  }
}

void Algorithms::startQuickSort() { quickSort(0, blocks->nBlocks - 1); }

int Algorithms::getMax(int n) {
  float mx = blocks->getValueY(0);
  for (int i = 1; i < n; ++i)
    if (blocks->getValueY(i) > mx) mx = blocks->getValueY(i);
  return mx;
}

void Algorithms::countSort(int n, int exp) {
  // Output array
  float output[n];
  int i;
  float count[10] = {0};

  for (i = 0; i < n; i++) count[(int)(blocks->getValueY(i) / exp) % 10]++;

  for (i = 1; i < 10; i++) count[i] += count[i - 1];

  // Build the output array
  for (i = n - 1; i >= 0; i--) {
    output[(int)count[(int)(blocks->getValueY(i) / exp) % 10] - 1] =
        blocks->getValueY(i);
    count[(int)(blocks->getValueY(i) / exp) % 10]--;
  }
  for (i = 0; i < n; i++) {
    blocks->assignValue(i, output[i]);
    this_thread::sleep_for(
        chrono::microseconds(time / speed));  // Slow down for visualization
  }
}

void Algorithms::radixSort() {
  int n = blocks->nBlocks;
  int m = getMax(n);

  for (int exp = 1; m / exp > 0; exp *= 10) {
    countSort(n, exp);
  }
}

void Algorithms::shellSort() {
  int n = blocks->nBlocks;
  // Start with a big gap, then reduce the gap
  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i += 1) {
      int temp = blocks->getValueY(i);

      int j;
      for (j = i; j >= gap && blocks->getValueY(j - gap) > temp; j -= gap) {
        blocks->assignValue(j, blocks->getValueY(j - gap));

        this_thread::sleep_for(
            chrono::microseconds(time / speed));  // Slow down for visualization
      }

      //  put temp (the original a[i]) in its correct location
      blocks->assignValue(j, temp);
    }
  }
}