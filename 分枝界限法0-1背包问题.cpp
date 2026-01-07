#include <stdio.h>
#include <stdlib.h>
#define MAX_N 10
// 物品结构体
typedef struct {
    int weight;
    int value;
    double ratio;  // 价值重量比
} Item;
// 节点结构体
typedef struct {
    int level;  // 当前所在层
    int profit; // 当前价值
    int weight; // 当前重量
    double bound; // 上界
} Node;
// 比较函数，用于按价值重量比排序
int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    return (itemB->ratio > itemA->ratio) - (itemB->ratio < itemA->ratio);
}
// 计算节点的上界
double bound(Node u, int n, int capacity, Item items[]) {
    if (u.weight >= capacity) {
        return 0;
    }
    double profitBound = u.profit;
    int j = u.level + 1;
    int totalWeight = u.weight;
    while (j < n && totalWeight + items[j].weight <= capacity) {
        totalWeight += items[j].weight;
        profitBound += items[j].value;
        j++;
    }
    if (j < n) {
        profitBound += (capacity - totalWeight) * items[j].ratio;
    }
    return profitBound;
}
int knapsack(int n, int capacity, Item items[]) {
    // 按价值重量比排序
    for (int i = 0; i < n; i++) {
        items[i].ratio = (double)items[i].value / items[i].weight;
    }
    qsort(items, n, sizeof(Item), compare);
    // 初始化队列
    Node queue[MAX_N * 100];
    int front = 0, rear = 0;
    // 根节点入队
    Node u, v;
    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = bound(u, n, capacity, items);
    queue[rear++] = u;
    int maxProfit = 0;
    while (front < rear) {
        u = queue[front++];
        if (u.bound > maxProfit) {
            // 左子节点
            v.level = u.level + 1;
            v.weight = u.weight + items[v.level].weight;
            v.profit = u.profit + items[v.level].value;
            if (v.weight <= capacity && v.profit > maxProfit) {
                maxProfit = v.profit;
            }
            v.bound = bound(v, n, capacity, items);
            if (v.bound > maxProfit) {
                queue[rear++] = v;
            }
            // 右子节点
            v.weight = u.weight;
            v.profit = u.profit;
            v.bound = bound(v, n, capacity, items);
            if (v.bound > maxProfit) {
                queue[rear++] = v;
            }
        }
    }
    return maxProfit;
}
int main() {
    int n, capacity;
    Item items[MAX_N];
    printf("请输入物品数量和背包容量：");
    scanf("%d %d", &n, &capacity);
    printf("请依次输入每个物品的重量和价值：\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &items[i].weight, &items[i].value);
    }
    int result = knapsack(n, capacity, items);
    printf("背包能装下的最大价值为：%d\n", result);
    return 0;
}

