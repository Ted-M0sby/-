#include <stdio.h>
#include <stdlib.h>
#define MAX 100
// 打印最优括号化方案
void print_optimal_parens(int s[MAX][MAX], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}
// 矩阵连乘动态规划算法
int matrix_chain_order(int p[], int n) {
    int dp[MAX][MAX], s[MAX][MAX];
    int l, i, j, k, q;
    // 初始化对角线元素为零
    for (i = 1; i < n; i++) {
        dp[i][i] = 0;
    }
    // 链长从2到n
    for (l = 2; l < n; l++) {
        for (i = 1; i < n - l + 1; i++) {
            j = i + l - 1;
            dp[i][j] = 999999;  // 初始化为一个很大的值
            for (k = i; k <= j - 1; k++) {
                q = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < dp[i][j]) {
                    dp[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    // 打印最优括号化方案
    printf("最优括号化方案: ");
    print_optimal_parens(s, 1, n - 1);
    printf("\n");
    return dp[1][n - 1];
}
int main() {
    int p[] = {5, 10, 3, 12, 5};  // 矩阵的维度数组
    int n = sizeof(p) / sizeof(p[0]);
    int optimal_cost = matrix_chain_order(p, n);
    printf("最优值: %d\n", optimal_cost);
    return 0;
}


