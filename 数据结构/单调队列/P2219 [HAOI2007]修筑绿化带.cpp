/*
========= Plozia =========
	Author:Plozia
	Problem:P2219 [HAOI2007]修筑绿化带
	Date:2021/12/19
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::deque;

typedef long long LL;
const int MAXN = 1e3 + 5;
int n, m, a[MAXN][MAXN], sum[MAXN][MAXN], Tx, Ty, Nx, Ny, ansline[MAXN][MAXN], ansrow[MAXN][MAXN];
deque <int> q;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int Get(int r1, int c1, int r2, int c2)
{
	if (r1 > r2) std::swap(r1, r2);
	if (c1 > c2) std::swap(c1, c2);
	return sum[r2][c2] - sum[r2][c1 - 1] - sum[r1 - 1][c2] + sum[r1 - 1][c1 - 1];
}

void Debug()
{
	puts("ansline:");
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			printf("%d%c", ansline[i][j], " \n"[j == m]);
	puts("ansrow:");
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			printf("%d%c", ansrow[i][j], " \n"[j == m]);
}

int main()
{
	n = Read(), m = Read(), Tx = Read(), Ty = Read(), Nx = Read(), Ny = Read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			a[i][j] = Read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
	for (int i = 1; i <= n; ++i)
	{
		q.clear();
		for (int j = Ny; j <= m; ++j)
		{
			while (!q.empty() && q.front() < j - Ty + 3 + Ny) q.pop_front();
			int Insert = Get(i, j, i, j - Ny + 1);
			while (!q.empty() && Insert < Get(i, q.back(), i, q.back() - Ny + 1)) q.pop_back();
			q.push_back(j); ansline[i][j + 1] = Get(i, q.front(), i, q.front() - Ny + 1);
		}
	}
	memset(sum, 0, sizeof(sum));
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m + 1; ++j)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + ansline[i][j];
	for (int j = 1; j <= m; ++j)
	{
		q.clear();
		for (int i = Nx; i <= n; ++i)
		{
			while (!q.empty() && q.front() < i - Tx + 3 + Nx) q.pop_front();
			int Insert = Get(i, j, i - Nx + 1, j);
			while (!q.empty() && Insert < Get(q.back(), j, q.back() - Nx + 1, j)) q.pop_back();
			q.push_back(i); ansrow[i + 1][j] = Get(q.front(), j, q.front() - Nx + 1, j);
		}
	}
	memset(sum, 0, sizeof(sum));
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
	int ans = 0;
	for (int i = Tx; i <= n; ++i)
		for (int j = Ty; j <= m; ++j)
			ans = Max(ans, Get(i, j, i - Tx + 1, j - Ty + 1) - ansrow[i][j]);
	printf("%d\n", ans); return 0;
}
/*
example:
4 5 4 4 2 2
20 19 18 17 16
15 14 13 12 11
10 9 8 7 6
5 4 3 2 1
answer:132 AC
hack:
5 5 4 4 2 2
66 12 58 21 34
69 38 10 54 94
81 96 40 82 44
91 48 21 63 81
48 53 82 96 92
answer:788 AC
hack:
6 10 4 3 2 1
57 32 27 90 69 1 50 58 22 39
16 79 5 71 57 15 85 12 16 4
54 85 47 15 27 9 98 20 77 59
82 99 100 35 44 19 61 53 97 9
73 40 70 79 26 8 62 33 87 32
55 51 41 27 50 36 55 15 63 63
answer:658 AC
*/