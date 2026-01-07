#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[], int low, int high) {
    int p = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < p) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
int randomizedpartition(int arr[], int low, int high) {
    srand(time(NULL));
    int randomindex = low + rand() % (high - low + 1);
    swap(&arr[randomindex], &arr[high]);
    return partition(arr, low, high);
}
int randomizedselect(int arr[], int low, int high, int k) {
    if (low == high)
        return arr[low];
    int pivotindex = randomizedpartition(arr, low, high);
    int rank = pivotindex - low + 1;
    if (k == rank)
        return arr[pivotindex];
    else if (k < rank)
        return randomizedselect(arr, low, pivotindex - 1, k);
    else
        return randomizedselect(arr, pivotindex + 1, high, k - rank);
}
int main() {
    int n, k;
    printf("请输入元素个数 n 和要查找的第 k 小元素: ");
    scanf("%d %d", &n, &k);
    int arr[n];
    printf("请输入 %d 个元素: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int result = randomizedselect(arr, 0, n - 1, k);
    printf("第 %d 小的元素是: %d\n", k, result);
    return 0;
}

