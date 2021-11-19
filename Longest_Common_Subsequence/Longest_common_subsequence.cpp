#include <iostream>
#include <string>
#include <vector>

using namespace std;
// 计算最长公共子序列的长度

// 递归
// 对于序列A[0,n]和B[0,M],LCS(A,B)无非三种情况
// 1、若n=-1或m=-1，则取做空序列 (" ")												//递归基
// 2、若A[n] = 'X' = B[m],则取做 LCS(A[0,n) , B[0,m)) + 'X'							//减而治之
// 3、若A[n] ≠ B[m],则在 LCS(A[0,n] , B[0,m)) 与 LCS(A[0,n) , B[0,m]) 中取更长者	//分而治之

int longestCommonSubsequence(string text1, string text2) 
{
    int m = text1.length(), n = text2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 1; i <= m; i++) {
        char c1 = text1.at(i - 1);
        for (int j = 1; j <= n; j++) {
            char c2 = text2.at(j - 1);
            if (c1 == c2) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}
// https://leetcode-cn.com/problems/longest-common-subsequence/solution/zui-chang-gong-gong-zi-xu-lie-by-leetcod-y7u0/
// 时间复杂度：O(mn)   其中 m 和 n 分别是字符串 text1 和 text2 的长度;
//             二维数组 dp 有 m+1 行和 n+1 列，需要对 dp 中的每个元素进行计算
// 空间复杂度：O(mn)   其中 m 和 n 分别是字符串 text1 和 text2 的长度;
//             创建了 m+1 行，n+1列二维数组dp


int main()
{
    string a = "conquer";
    string b = "center";
    int length = longestCommonSubsequence(a, b);
    cout << "最长公共子序列长度为：" <<  length << endl;
}