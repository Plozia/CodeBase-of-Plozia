/*
========= Plozia =========
	Author:Plozia
	Problem:CF1720E Misha and Paintings
	Date:2022/9/20
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 500 + 5;
int n, k, a[MAXN][MAXN], sum[MAXN][MAXN], cnt, fir[MAXN * MAXN][2], sec[MAXN * MAXN][2];
bool book[MAXN * MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

int main()
{
	n = Read(), k = Read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			book[a[i][j] = Read()] = 1;
	for (int i = 1; i <= n * n; ++i) cnt += book[i];
	if (cnt <= k) { printf("%d\n", k - cnt); return 0; }
	memset(fir, 0x7f, sizeof(fir));
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			fir[a[i][j]][0] = std::min(fir[a[i][j]][0], i);
			fir[a[i][j]][1] = std::min(fir[a[i][j]][1], j);
			sec[a[i][j]][0] = std::max(sec[a[i][j]][0], i);
			sec[a[i][j]][1] = std::max(sec[a[i][j]][1], j);
		}
	int flag = 0;
	for (int len = 1; len <= n; ++len)
	{
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) sum[i][j] = 0;
		for (int i = 1; i <= n * n; ++i)
		{
			if (!book[i]) continue ;
			if (len < std::max(sec[i][0] - fir[i][0], sec[i][1] - fir[i][1])) continue ;
			int Line = sec[i][0] - fir[i][0] + 1, Col = sec[i][1] - fir[i][1] + 1;
			int r1 = std::max(1, fir[i][0] - (len - Line)), c1 = std::max(1, fir[i][1] - (len - Col));
			int r2 = std::min(n - len + 1, fir[i][0]), c2 = std::min(n - len + 1, fir[i][1]);
			++sum[r1][c1]; --sum[r2 + 1][c1]; --sum[r1][c2 + 1]; ++sum[r2 + 1][c2 + 1];
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				sum[i][j] = sum[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (cnt - sum[i][j] == k || cnt - sum[i][j] == k - 1) flag = 1;
	}
	if (flag == 1) printf("1\n");
	else printf("2\n");
	return 0;
}