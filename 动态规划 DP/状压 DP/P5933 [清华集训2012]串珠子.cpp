/*
========= Plozia =========
	Author:Plozia
	Problem:P5933 [清华集训2012]串珠子
	Date:2021/10/26
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 16 + 5, MAXS = (1 << 16) + 5, P = 1e9 + 7;
int n, c[MAXN][MAXN], f[MAXS];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int Add(int fir, int sec) { return ((fir + sec) >= P) ? (fir + sec - P) : (fir + sec); }

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			c[i][j] = Read();
	for (int s = 1; s < (1 << n); ++s)
	{
		for (int x = 1; x <= n; ++x)
		{
			if (!((1 << (x - 1)) & s)) continue ;
			int s_ = s ^ (1 << (x - 1));
			
		}
	}
	printf("%d\n", f[(1 << n) - 1]); return 0;
}
/*
n <= 16 考虑状压
设 f[State] 表示 State 情况下花费
设状态集为 S
取个点 x
补集为 S'
考虑到会有容斥
O(n^3) 枚举一波
复杂度 O(n^3 \times 2^n)
*/