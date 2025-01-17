#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "config.h"

using namespace std;

void checkSort(vector<int>& data){
  isSorted=true;
  for(int i=0; i<data.size()-1; ++i){
    if(data[i]>data[i+1]){
      isSorted = false;
    }
  }
  // color the blocks green
  // if()
}

void mergeSort(vector<sf::Vertex> &vertices, int start, int middle, int end) {
  // Check that the remaining array is more than 2 elements
  if (end - start >= 2) {
    // Recursive call - Divide the array in left and right

    mergeSort(vertices, start, (middle + start) / 2,
              middle);  // Call mergesort on the left array
    mergeSort(vertices, middle, (middle + end) / 2,
              end);  // Call mergesort on right array

    int la = middle - start;
    int lb = end - middle;

    // Create temp vector
    vector<int> A, B;
    for (int i = start; i < middle; ++i) {
      A.push_back(vertices[i * 4 + 2].position.y);
    }
    for (int i = middle; i < end; ++i) {
      B.push_back(vertices[i * 4 + 2].position.y);
    }

    int i = start;
    int j = 0;
    int k = 0;

    // Merge
    while (j < la || k < lb) {
      if ((A[j] < B[k] && j < la) || k >= lb) {
        vertices[i * 4 + 2].position.y = A[j];
        vertices[i * 4 + 3].position.y = A[j];
        // update_render(arr, i);
        j++;
      } else {
        vertices[i * 4 + 2].position.y = B[k];
        vertices[i * 4 + 3].position.y = B[k];
        // update_render(arr, i);
        k++;
      }
      i++;
      this_thread::sleep_for(
          chrono::microseconds(100));  // Slow down for visualization
    }
  }
}

void startMergeSort(vector<sf::Vertex> &vertices) {
  mergeSort(vertices, 0, vertices.size() / 4 / 2, vertices.size() / 4);
}

void bubbleSort(vector<sf::Vertex> &vertices) {
  for (int i = 0; i < vertices.size(); i = i + 4) {
    for (int j = 0; j < vertices.size() - 4 - i; j = j + 4) {
      if (vertices[j + 2].position.y > vertices[j + 4 + 2].position.y) {
        // update_render(data, j);

        swap(vertices[j + 2].position.y, vertices[j + 4 + 2].position.y);
        swap(vertices[j + 3].position.y, vertices[j + 4 + 3].position.y);
      }
    }
    this_thread::sleep_for(
          chrono::microseconds(100));
  }
  cout << "bubblesort made" << endl;
}

void shakerSort(vector<sf::Vertex> &vertices) {
  for (int i = 0; i < vertices.size() / 4; i = i + 4) {
    // loop going forward for bigger number
    for (int j = 0; j < vertices.size() - 4 - i; j = j + 4) {
      if (vertices[j + 2].position.y > vertices[j + 4 + 2].position.y) {
        // update_render(data, j);

        swap(vertices[j + 2].position.y, vertices[j + 4 + 2].position.y);
        swap(vertices[j + 3].position.y, vertices[j + 4 + 3].position.y);
      }
    }

    // loop going backward for lower number
    for (int j = vertices.size() - 4 - i; j >= 4 + i; j = j - 4) {
      if (vertices[j + 2].position.y < vertices[j - 4 + 2].position.y) {
        // update_render(data, j);

        swap(vertices[j + 2].position.y, vertices[j - 4 + 2].position.y);
        swap(vertices[j + 3].position.y, vertices[j - 4 + 3].position.y);
      }
    }
    this_thread::sleep_for(
          chrono::microseconds(100));
  }
}

int partition(vector<sf::Vertex> &vec, int low, int high) {
  // Selecting last element as the pivot
  int pivot = vec[high * 4 + 2].position.y;

  // Index of elemment just before the last element
  // It is used for swapping
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
    // If current element is smaller than or
    // equal to pivot
    if (vec[j * 4 + 2].position.y <= pivot) {
      i++;
      swap(vec[i * 4 + 2].position.y, vec[j * 4 + 2].position.y);
      swap(vec[i * 4 + 3].position.y, vec[j * 4 + 3].position.y);
      this_thread::sleep_for(chrono::microseconds(100));
    }
  }

  // Put pivot to its position
  swap(vec[(i + 1) * 4 + 2].position.y, vec[high * 4 + 2].position.y);
  swap(vec[(i + 1) * 4 + 3].position.y, vec[high * 4 + 3].position.y);

  // Return the point of partition
  return (i + 1);
}

void quickSort(vector<sf::Vertex> &vec, int low, int high) {
  // Base case: This part will be executed till the starting
  // index low is lesser than the ending index high
  if (low < high) {
    // pi is Partitioning Index, arr[p] is now at
    // right place
    int pi = partition(vec, low, high);

    // Separately sort elements before and after the
    // Partition Index pi
    quickSort(vec, low, pi - 1);
    quickSort(vec, pi + 1, high);
  }
}

void startQuickSort(vector<sf::Vertex> &vec) {
  quickSort(vec, 0, vec.size() / 4 - 1);
}

// A utility function to get maximum
// value in arr[]
int getMax(vector<sf::Vertex> &vec, int n) {
  float mx = vec[2].position.y;
  for (int i = 1; i < n; i++)
    if (vec[i * 4 + 2].position.y > mx) mx = vec[i * 4 + 2].position.y;
  return mx;
}

// A function to do counting sort of arr[]
// according to the digit
// represented by exp.
void countSort(vector<sf::Vertex> &vec, int n, int exp) {
  // Output array
  float output[n];
  int i;
  float count[10] = {0};

  // Store count of occurrences
  // in count[]
  for (i = 0; i < n; i++) count[(int)(vec[i * 4 + 2].position.y / exp) % 10]++;

  // Change count[i] so that count[i]
  // now contains actual position
  // of this digit in output[]
  for (i = 1; i < 10; i++) count[i] += count[i - 1];

  // Build the output array
  for (i = n - 1; i >= 0; i--) {
    output[(int)count[(int)(vec[i * 4 + 2].position.y / exp) % 10] - 1] =vec[i * 4 + 2].position.y;
    count[(int)(vec[i * 4 + 2].position.y / exp) % 10]--;
  }

  // Copy the output array to arr[],
  // so that arr[] now contains sorted
  // numbers according to current digit
  for (i = 0; i < n; i++) {
    vec[i * 4 + 2].position.y = output[i];
    vec[i * 4 + 3].position.y = output[i];
    this_thread::sleep_for(
        chrono::microseconds(100));  // Slow down for visualization
  }
}

// The main function to that sorts arr[]
// of size n using Radix Sort
void radixSort(vector<sf::Vertex> &vec) {
  // Find the maximum number to
  // know number of digits
  int n = vec.size() / 4;
  int m = getMax(vec, n);

  // Do counting sort for every digit.
  // Note that instead of passing digit
  // number, exp is passed. exp is 10^i
  // where i is current digit number
  for (int exp = 1; m / exp > 0; exp *= 10) {
    countSort(vec, n, exp);
  }
}

/* function to sort arr using shellSort */
void shellSort(vector<sf::Vertex> &vec) {
  int n = vec.size() / 4;
  // Start with a big gap, then reduce the gap
  for (int gap = n / 2; gap > 0; gap /= 2) {
    // Do a gapped insertion sort for this gap size.
    // The first gap elements a[0..gap-1] are already in gapped order
    // keep adding one more element until the entire array is
    // gap sorted
    for (int i = gap; i < n; i += 1) {
      // add a[i] to the elements that have been gap sorted
      // save a[i] in temp and make a hole at position i
      int temp = vec[i * 4 + 2].position.y;

      // shift earlier gap-sorted elements up until the correct
      // location for a[i] is found
      int j;
      for (j = i; j >= gap && vec[(j - gap) * 4 + 2].position.y > temp;j -= gap) {
        vec[j * 4 + 2].position.y = vec[(j - gap) * 4 + 2].position.y;
        vec[j * 4 + 3].position.y = vec[(j - gap) * 4 + 3].position.y;
        this_thread::sleep_for(
            chrono::microseconds(100));  // Slow down for visualization
      }

      //  put temp (the original a[i]) in its correct location
      vec[j * 4 + 2].position.y = temp;
      vec[j * 4 + 3].position.y = temp;
    }
  }
}
