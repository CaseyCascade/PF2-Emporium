#include "database.h"

#include <iostream>
#include <vector>
#include <limits> 

void countingSort(vector<pair<Item, int>>& arr) {
    // Find the maximum element in the array
    int maxElement = numeric_limits<int>::min();
    for (const auto& pair : arr)
        maxElement = max(maxElement, pair.second);

    // Create a count array to store the count of each element
    vector<int> count(static_cast<int>(maxElement) + 1, 0);

    // Count the occurrences of each element
    for (const auto& pair : arr)
        count[static_cast<int>(pair.second)]++;

    // Update the count array to store the actual position of each element
    for (int i = 1; i <= maxElement; ++i)
        count[i] += count[i - 1];

    // Create a temporary array to store the sorted output
    vector<pair<Item, int>> output(arr.size());

    // Build the sorted output array
    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[static_cast<int>(arr[i].second)] - 1] = arr[i];
        count[static_cast<int>(arr[i].second)]--;
    }

    // Copy the sorted output back to the original array
    for (int i = 0; i < arr.size(); ++i)
        arr[i] = output[i];
}

// Merge two sorted subvectors [left..mid] and [mid+1..right]
void merge(vector<pair<Item, int>>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors
    vector<pair<Item, int>> L(n1), R(n2);

    // Copy data to temporary vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary vectors back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].second <= R[j].second) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge sort function
void mergesort(vector<pair<Item, int>>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void print_table(vector<pair<Item, int>>& arr) {
    for (auto& p : arr) {
        cout << "(" << p.first.get_name() << ", " << p.second << ") " << endl; 
    }
    cout << endl;
}