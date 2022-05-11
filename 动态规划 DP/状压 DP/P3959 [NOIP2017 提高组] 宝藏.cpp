/*
========= Plozia =========
	Author:Plozia
	Problem:P3959 [NOIP2017 提高组] 宝藏
	Date:2021/9/7
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 15;
int n, m, Edge[MAXN][MAXN], f[15][1 << MAXN][15], dep[MAXN], ans;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void dfs(int State, int sum, int depth)
{
	if (sum >= ans) return ;
	if (State == ((1 << n) - 1)) { ans = sum; return ; }
	for (int i = 1; i <= n; ++i)
	{
		if (State & (1 << (i - 1)))
		{
			for (int j = 1; j <= n; ++j)
			{
				if ((!(State & (1 << (j - 1)))) && Edge[i][j] < 0x3f3f3f3f)
				{
					if (f[j][State | (1 << (j - 1))][depth + 1] <= sum + dep[i] * Edge[i][j]) continue ;
					f[j][State | (1 << (j - 1))][depth + 1] = sum + dep[i] * Edge[i][j];
					dep[j] = dep[i] + 1;
					dfs(State | (1 << (j - 1)), f[j][State | (1 << (j - 1))][depth + 1], depth + 1);
				}
			}
		}
	}
}

int main()
{
	n = Read(), m = Read(); memset(Edge, 0x3f, sizeof(Edge));
	for (int i = 1; i <= m; ++i)
	{
		int x = Read(), y = Read(), z = Read();
		Edge[x][y] = Edge[y][x] = Min(Edge[x][y], z);
	}
	ans = 0x7f7f7f7f;
	for (int i = 1; i <= n; ++i)
	{
		memset(f, 0x3f, sizeof(f));
		memset(dep, 0, sizeof(dep));
		dep[i] = 1;
		dfs(1 << (i - 1), 0, 0);
	}
	printf("%d\n", ans); return 0;
}