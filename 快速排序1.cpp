#include <stdio.h>
#include <stdlib.h>
void quick_sort (int *a, int n) {
    if (n < 2) return;
    int p = a[n / 2];
    //left 开始左边的指针
    int *l = a;
    //right 开始右边的指针
    int *r = a + n - 1;
    while (l <= r) {
        while (*l < p) l++; //左边找到比p大的数后，就从右边找比p小的数
        while (*r > p) r--; //交换找到的左右两边的大数和小数
        if (l <= r) {
            int t = *l;
            *l++ = *r;
            *r-- = t;
        }
    }
    //进行完第一轮快速排序后，递归X(p)左右两边分别排序
    quick_sort(a, r - a + 1);
    quick_sort(l, a + n - l);
}
int main () {
    int a[] = {2,1,8,3,5,4,6};
    int n = sizeof a / sizeof a[0];
    quick_sort(a, n);
    for(int i = 0; i < n; i++) {
        printf("%d", a[i]);
        printf("\n");
    }
    return 0;
}

