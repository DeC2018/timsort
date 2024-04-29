#include <stdio.h>
#include <stdlib.h>

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void merge(int arr[], int left[], int right[], int size) {
    int i = 0, j = 0, k = 0;
    while (i < size/2 && j < size/2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < size/2) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < size/2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void timsort(int arr[], int n) {
    int minrun = 32;
    while (minrun < n) {
        minrun *= 2;
    }
    for (int i = 0; i < n; i += minrun) {
        insertionSort(arr + i, (n - i < minrun) ? n - i : minrun);
    }
    int size = minrun;
    while (size < n) {
        for (int start = 0; start < n; start += size * 2) {
            int mid = start + size - 1;
            int end = (start + size * 2 < n) ? start + size * 2 - 1 : n - 1;
            int leftSize = mid - start + 1;
            int rightSize = end - mid;
            int* left = (int*)malloc(leftSize * sizeof(int));
            int* right = (int*)malloc(rightSize * sizeof(int));
            for (int i = 0; i < leftSize; i++) {
                left[i] = arr[start + i];
            }
            for (int i = 0; i < rightSize; i++) {
                right[i] = arr[mid + 1 + i];
            }
            merge(arr + start, left, right, leftSize + rightSize);
            free(left);
            free(right);
        }
        size *= 2;
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    timsort(arr, n);

    printf("Sorted array:   ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}