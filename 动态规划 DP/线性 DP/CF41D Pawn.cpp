/*
========= Plozia =========
	Author:Plozia
	Problem:CF41D Pawn
	Date:2022/7/16
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 100 + 5;
int n, m, k, a[MAXN][MAXN], f[MAXN][MAXN][15], g[MAXN][MAXN][15];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}

void Print(int x, int y, int z)
{
	if (x == n) { printf("%d\n", y); return ; }
	if (g[x][y][z] == 1) { Print(x + 1, y + 1, (z - a[x][y] + 10 * k) % k); printf("L"); }
	else { Print(x + 1, y - 1, (z - a[x][y] + 10 * k) % k); printf("R"); }
}

int main()
{
	n = Read(), m = Read(), k = Read(); ++k;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			scanf("%1d", &a[i][j]);
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= m; ++j)
			for (int p = 0; p < k; ++p)
				f[i][j][p] = -0x3f3f3f3f;
	for (int j = 1; j <= m; ++j) f[n][j][a[n][j] % k] = a[n][j] / k;
	for (int i = n - 1; i >= 1; --i)
		for (int j = 1; j <= m; ++j)
			for (int p = 0; p < k; ++p)
			{
				if (j != m && f[i + 1][j + 1][p] + (p + a[i][j]) / k > f[i][j][(p + a[i][j]) % k])
				{
					f[i][j][(p + a[i][j]) % k] = f[i + 1][j + 1][p] + (p + a[i][j]) / k; g[i][j][(p + a[i][j]) % k] = 1; // 1 is UpLeft
				}
				if (j != 1 && f[i + 1][j - 1][p] + (p + a[i][j]) / k > f[i][j][(p + a[i][j]) % k])
				{
					f[i][j][(p + a[i][j]) % k] = f[i + 1][j - 1][p] + (p + a[i][j]) / k; g[i][j][(p + a[i][j]) % k] = 2; // 2 is UpRight
				}
			}
	int ans = -0x3f3f3f3f, flag = 0;
	for (int i = 1; i <= m; ++i)
		if (f[1][i][0] > ans) { ans = f[1][i][0]; flag = i; }
	if (ans < 0) { puts("-1"); return 0; }
	printf("%d\n", ans * k); Print(1, flag, 0); return 0;
}