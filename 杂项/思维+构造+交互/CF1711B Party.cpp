/*
========= Plozia =========
	Author:Plozia
	Problem:CF1711B Party
	Date:2022/8/3
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 1e5 + 5;
int t, n, m, a[MAXN], d[MAXN];
struct node { int x, y; } Edge[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

void Solve()
{
	n = Read(), m = Read(); for (int i = 1; i <= n; ++i) a[i] = Read(), d[i] = 0;
	for (int i = 1; i <= m; ++i) Edge[i].x = Read(), Edge[i].y = Read(), ++d[Edge[i].x], ++d[Edge[i].y];
	int ans = 0x7f7f7f7f; if (m % 2 == 0) { puts("0"); return ; }
	for (int i = 1; i <= n; ++i)
		if (d[i] & 1) ans = std::min(ans, a[i]);
	for  (int i = 1; i <= m; ++i)
		if (d[Edge[i].x] % 2 == 0 && d[Edge[i].y] % 2 == 0) ans = std::min(ans, a[Edge[i].x] + a[Edge[i].y]);
	printf("%d\n", ans);
}

int main()
{
	t = Read(); while (t--) Solve(); return 0;
}