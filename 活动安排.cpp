#include<stdio.h>
#include <stdlib.h>
void greedy(int s[],int f[],int a[],int k);
int main() {
    int s[] = {1,3,5,7,9};
    int f[] = {10,11,12,13,14};
    int k;
    k = sizeof(f)/sizeof(f[0]);
    int *a;
    a = (int*)malloc(sizeof(int)*k);
    greedy(s,f,a,k);
    system("PAUSE");
    return 0;
}
/*
 * s[]：活动的开始时间
 * f[]:活动的结束时间（非降序排列）
 * a[]:0或者1，为0表示活动不被安排，1表示活动被安排
 * k:活动个数
 */
void greedy(int s[],int f[],int a[],int k) {
    int i;
    int j = 0;
    for(i=0;i<k;i++) {
        a[i] = 0; // 初始所有活动都未被安排
    }
    a[0] = 1;
    printf("第1个活动被安排\n");
    int count = 1;
    for(i=1;i<k;i++) {
        if(s[i] > f[j]) {
            a[i] = 1;
            printf("开始%d,结束%d.",s[i],f[i]);
            j = i;
            count++;
            printf("第%d个活动被安排\n",i+1);
        }
    }
    printf("总计%d个活动被安排\n",count);
}

