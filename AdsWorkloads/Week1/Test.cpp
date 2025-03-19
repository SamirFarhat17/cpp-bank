#include <vector>
#include <algorithm>
#include <iterator> // For std::copy

double findMedian(int arr_count, int* arr) {
    // Copy the array into a vector using std::copy
    std::vector<int> arrV(arr, arr + arr_count);

    // Sort the vector
    std::sort(arrV.begin(), arrV.end());

    // Calculate the median
    if (arr_count % 2 == 0) {
        // Even case: return the average of the two middle elements
        return (arrV[arr_count / 2] + arrV[(arr_count / 2) - 1]) / 2.0;
    } else {
        // Odd case: return the middle element
        return arrV[arr_count / 2];
    }
}