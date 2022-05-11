/*
========= Plozia =========
	Author:Plozia
	Problem:P3374 【模板】树状数组 1
	Date:2022/4/5
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 5e5 + 5;
int n, q, a[MAXN], tree[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void Add(int p, int s)
{
	for (; p <= n; p += p & (-p)) tree[p] += s;
}
int Ask(int p)
{
	int val = 0;
	for (; p > 0; p -= p & (-p)) val += tree[p];
	return val;
}

int main()
{
	n = Read(), q = Read();
	for (int i = 1; i <= n; ++i) a[i] = Read();
	for (int i = 1; i <= n; ++i) Add(i, a[i]);
	while (q--)
	{
		int opt = Read();
		if (opt == 1) { int x = Read(), k = Read(); Add(x, k); }
		else { int l = Read(), r = Read(); printf("%d\n", Ask(r) - Ask(l - 1)); }
	}
	return 0;
}