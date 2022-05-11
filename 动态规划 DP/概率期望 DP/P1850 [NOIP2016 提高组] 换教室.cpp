/*
========= Plozia =========
	Author:Plozia
	Problem:P1850 [NOIP2016 提高组] 换教室
	Date:2021/4/29
========= Plozia =========
*/

#include <bits/stdc++.h>
#define Min(a, b) ((a < b) ? a : b)

typedef double db;
typedef long long LL;
const int MAXN = 2e3 + 10, MAXV = 3e2 + 10;
int n, m, v, e, c[MAXN], d[MAXN], dis[MAXV][MAXV];
db k[MAXN], f[MAXN][MAXN][2], ans = 1e17 + 5;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == -1) ? -sum : sum;
}

int main()
{
	n = read(), m = read(), v = read(), e = read();
	for (int i = 1; i <= n; ++i) c[i] = read();
	for (int i = 1; i <= n; ++i) d[i] = read();
	for (int i = 1; i <= n; ++i) scanf("%lf", &k[i]);
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= n; ++i) dis[i][i] = 0;
	for (int i = 1; i <= e; ++i)
	{
		int x = read(), y = read(), z = read();
		dis[x][y] = std::min(dis[x][y], z);
		dis[y][x] = std::min(dis[y][x], z);
	}
	for (int k = 1; k <= v; ++k)
		for (int i = 1; i <= v; ++i)
			for (int j = 1; j <= v; ++j)
				dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= m; ++j)
			f[i][j][0] = f[i][j][1] = 1e17 + 5;
	f[1][0][0] = f[1][1][1] = 0;
	for (int i = 2; i <= n; ++i)
	{
		f[i][0][0] = f[i - 1][0][0] + dis[c[i - 1]][c[i]];
		for (int j = 1; j <= std::min(i, m); ++j)
		{
			f[i][j][0] = std::min(f[i - 1][j][0] + dis[c[i - 1]][c[i]], f[i - 1][j][1] + dis[d[i - 1]][c[i]] * k[i - 1] + dis[c[i - 1]][c[i]] * (1 - k[i - 1]));
			if (j == 0) continue;
			f[i][j][1] = std::min(f[i - 1][j - 1][0] + dis[c[i - 1]][c[i]] * (1 - k[i]) + dis[c[i - 1]][d[i]] * k[i], f[i - 1][j - 1][1] + dis[d[i - 1]][d[i]] * k[i] * k[i - 1] + dis[c[i - 1]][d[i]] * k[i] * (1 - k[i - 1]) + dis[d[i - 1]][c[i]] * (1 - k[i]) *  k[i - 1] + dis[c[i - 1]][c[i]] * (1 - k[i]) * (1 - k[i - 1]));
		}
	}
	for (int i = 0; i <= m; ++i) ans = std::min(ans, std::min(f[n][i][0], f[n][i][1]));
	printf ("%.2lf\n", ans);
	return 0;
}
