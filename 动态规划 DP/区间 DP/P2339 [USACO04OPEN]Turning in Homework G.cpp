/*
========= Plozia =========
	Author:Plozia
	Problem:P2339 [USACO04OPEN]Turning in Homework G
	Date:2022/7/17
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 1e3 + 5;
int n, h, b, f[MAXN][MAXN][2];
struct node { int x, t; bool operator <(const node &fir)const { return (x < fir.x); } } a[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int Abs(int x) { return (x < 0) ? -x : x; }

int main()
{
	n = Read(), h = Read(), b = Read();
	for (int i = 1; i <= n; ++i) a[i].x = Read(), a[i].t = Read();
	std::sort(a + 1, a + n + 1); memset(f, 0x3f, sizeof(f));
	f[1][n][0] = Max(a[1].x, a[1].t); f[1][n][1] = Max(a[n].x, a[n].t);
	for (int i = 1; i <= n; ++i)
		for (int j = n; j >= i; --j)
		{
			f[i][j][0] = Min(f[i][j][0], Min(Max(f[i][j + 1][1] + a[j + 1].x - a[i].x, a[i].t), Max(f[i - 1][j][0] + a[i].x - a[i - 1].x, a[i].t)));
			f[i][j][1] = Min(f[i][j][1], Min(Max(f[i][j + 1][1] + a[j + 1].x - a[j].x, a[j].t), Max(f[i - 1][j][0] + a[j].x - a[i - 1].x, a[j].t)));
		}
	int ans = 0x7f7f7f7f;
	for (int i = 1; i <= n; ++i) ans = Min(ans, Min(f[i][i][0], f[i][i][1]) + Abs(b - a[i].x));
	printf("%d\n", ans); return 0;
}