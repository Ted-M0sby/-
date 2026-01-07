#include <stdio.h>
#include <string.h>
#define MAX_LEN 100
// 函数用于求两个数的最大值
int max(int a, int b) {
    return (a > b)? a : b;
}
// 函数用于求解最长公共子序列的长度
int lcs(char *s1, char *s2) {
    int n1 = strlen(s1);
    int n2 = strlen(s2);
    int dp[MAX_LEN + 1][MAX_LEN + 1];
    // 初始化 dp 数组
    for (int i = 0; i <= n1; i++) {
        for (int j = 0; j <= n2; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n1][n2];
}
int main() {
    char s1[MAX_LEN], s2[MAX_LEN];
    printf("请输入第一个字符串: ");
    scanf("%s", s1);
    printf("请输入第二个字符串: ");
    scanf("%s", s2);
    int result = lcs(s1, s2);
    printf("最长公共子序列的长度为: %d\n", result);
    return 0;
}

