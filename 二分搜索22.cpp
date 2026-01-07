#include <stdio.h>
int BinarySearch(int *arr, int left, int right, int num) {
    if (left > right) {
        return -1; 
    }
    int mid = left + (right - left) / 2;
    if (num == arr[mid]) {
        return mid; 
    } else if (num < arr[mid]) {
        return BinarySearch(arr, left, mid - 1, num); 
    } else if (num > arr[mid]) {
        return BinarySearch(arr, mid + 1, right, num);
    }
}
int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int num = 8;
    int result = BinarySearch(arr, 0, n - 1, num);
    if (result != -1) {
        printf("数字 %d 在数组中的位置是 %d\n", num, result);
    } else {
        printf("数字 %d 不在数组中\n", num);
    }
    return 0;
}

