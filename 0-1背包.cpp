#include <stdio.h>
#define MAX_ITEMS 30
int n;          // 物品数量
int W;          // 背包容量
int weights[MAX_ITEMS];  // 物品重量
int values[MAX_ITEMS];   // 物品价值
int max_value = 0;       // 最大价值
int current_weight = 0;  // 当前重量
int current_value = 0;   // 当前价值
int best_choice[MAX_ITEMS];  // 最优选择
int current_choice[MAX_ITEMS]; // 当前选择
// 回溯函数
void backtrack(int i) {
    if (i == n) {
        if (current_value > max_value) {
            max_value = current_value;
            for (int j = 0; j < n; j++) {
                best_choice[j] = current_choice[j];
            }
        }
        return;
    }
    // 不选择当前物品
    current_choice[i] = 0;
    backtrack(i + 1);
    // 选择当前物品
    if (current_weight + weights[i] <= W) {
        current_weight += weights[i];
        current_value += values[i];
        current_choice[i] = 1;
        backtrack(i + 1);
        current_weight -= weights[i];
        current_value -= values[i];
    }
}
int main() {
    printf("请输入物品数量和背包容量: ");
    scanf("%d %d", &n, &W);
    printf("请依次输入每个物品的重量和价值:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &weights[i], &values[i]);
    }
    backtrack(0);
    printf("最大价值为: %d\n", max_value);
    printf("选择的物品为: ");
    for (int i = 0; i < n; i++) {
        if (best_choice[i]) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
    return 0;
}

