/*
========= Plozia =========
	Author:Plozia
	Problem:P4360 [CEOI2004]锯木厂选址
	Date:2021/4/14
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 20000 + 10;
int n, w[MAXN], d[MAXN], tot, sumw[MAXN], sumd[MAXN], ans = 0x7f7f7f7f, f[MAXN];
int q[MAXN], l, r;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }

int X(int x) { return sumd[x]; }
int Y(int x) { return sumd[x] * sumw[x - 1]; }
int K(int x) { return sumw[x - 1]; }
double Slope(int x, int y) { return ((double)Y(x) - Y(y)) / ((double)X(x) - X(y)); }

int main()
{
	memset(f, 0x7f, sizeof(f));
	n = read();
	for (int i = n; i >= 1; --i) w[i] = read(), d[i] = read();
	for (int i = 1; i <= n; ++i) sumw[i] = sumw[i - 1] + w[i], sumd[i] = sumd[i - 1] + d[i];
	for (int i = 1; i <= n; ++i) tot += w[i] * sumd[i];
	q[l = r = 1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		while (l < r && Slope(q[l], q[l + 1]) <= (double)K(i)) ++l;
		int j = q[l]; f[i] = tot - sumd[j] * (sumw[i - 1] - sumw[j - 1]) - sumd[i] * (sumw[n] - sumw[i - 1]);
		while (l < r && Slope(i, q[r]) <= Slope(q[r], q[r - 1])) --r;
		q[++r] = i;
	}
	for (int i = 2; i <= n; ++i) ans = Min(ans, f[i]);
	printf("%d\n", ans); return 0;
}