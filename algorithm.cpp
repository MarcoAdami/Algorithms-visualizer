#include<iostream>
#include<vector>
using namespace std;

void bubbleSort(vector<int>& data) {
  for (int i = 0; i < data.size(); ++i) {
    for (int j = 0; j < data.size() - 1 - i; ++j) {
      if (data[j] > data[j + 1]) {
        // update_render(data, j);
        data[j] = data[j] ^ data[j + 1];
        data[j + 1] = data[j] ^ data[j + 1];
        data[j] = data[j] ^ data[j + 1];
        // update_render(data, j);
      }
    }
  }
}

void mergeSort(vector<int>& arr, int start, int middle, int end) {
  // Check that the remaining array is more than 2 elements
  if (end - start >= 2) {
    // Recursive call - Divide the array in left and right

    mergeSort(arr, start, (middle + start) / 2,
              middle);  // Call mergesort on the left array
    mergeSort(arr, middle, (middle + end) / 2,
              end);  // Call mergesort on right array

    int la = middle - start;
    int lb = end - middle;

    // Create temp vector
    vector<int> A, B;
    for (int i = start; i < middle; ++i) {
      A.push_back(arr[i]);
    }
    for (int i = middle; i < end; ++i) {
      B.push_back(arr[i]);
    }

    int i = start;
    int j = 0;
    int k = 0;

    // Merge
    while (j < la || k < lb) {
      if ((A[j] <= B[k] && j < la) || k >= lb) {
        arr[i] = A[j];
        // update_render(arr, i);
        j++;
      } else {
        arr[i] = B[k];
        // update_render(arr, i);
        k++;
      }
      i++;
      this_thread::sleep_for(
          chrono::microseconds(100));  // Slow down for visualization
    }
  }
}

void startMergeSort(vector<int>& arr) {
  mergeSort(arr, 0, arr.size() / 2, arr.size());
}
