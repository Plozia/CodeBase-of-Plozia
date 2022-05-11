/*
========= Plozia =========
	Author:Plozia
	Problem:CF527D Clique Problem
	Date:2021/6/24
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2e5 + 5;
int n;
struct node
{
	int l, r;
}a[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
bool cmp(const node &fir, const node &sec) { return (fir.r ^ sec.r) ? (fir.r < sec.r) : (fir.l < sec.l); }

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i)
	{
		int x = Read(), w = Read();
		a[i].l = x - w, a[i].r = x + w;
	}
	std::sort(a + 1, a + n + 1, cmp);
	int ans = 0, r = -2000000000;
	for (int i = 1; i <= n; ++i)
	{
		if (a[i].l < r) continue ;
		++ans; r = a[i].r;
	}
	printf("%d\n", ans); return 0;
}