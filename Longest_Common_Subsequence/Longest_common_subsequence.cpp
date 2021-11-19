#include <iostream>
#include <string>
#include <vector>

using namespace std;
// ��������������еĳ���

// �ݹ�
// ��������A[0,n]��B[0,M],LCS(A,B)�޷��������
// 1����n=-1��m=-1����ȡ�������� (" ")												//�ݹ��
// 2����A[n] = 'X' = B[m],��ȡ�� LCS(A[0,n) , B[0,m)) + 'X'							//������֮
// 3����A[n] �� B[m],���� LCS(A[0,n] , B[0,m)) �� LCS(A[0,n) , B[0,m]) ��ȡ������	//�ֶ���֮

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
// ʱ�临�Ӷȣ�O(mn)   ���� m �� n �ֱ����ַ��� text1 �� text2 �ĳ���;
//             ��ά���� dp �� m+1 �к� n+1 �У���Ҫ�� dp �е�ÿ��Ԫ�ؽ��м���
// �ռ临�Ӷȣ�O(mn)   ���� m �� n �ֱ����ַ��� text1 �� text2 �ĳ���;
//             ������ m+1 �У�n+1�ж�ά����dp


int main()
{
    string a = "conquer";
    string b = "center";
    int length = longestCommonSubsequence(a, b);
    cout << "����������г���Ϊ��" <<  length << endl;
}