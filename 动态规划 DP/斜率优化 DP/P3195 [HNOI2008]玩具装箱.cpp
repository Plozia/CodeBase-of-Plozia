/*
========= Plozia =========
	Author:Plozia
	Problem:P3195 [HNOI2008]玩具装箱
	Date:2021/4/15
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 5e4 + 10;
int n, L, l, r, q[MAXN];
LL f[MAXN], c[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }

double K(int i) { return 2.0 * (i + c[i]); }
double X(int i) { return 1.0 * i + c[i]; }
double Y(int i) { return 1.0 * f[i] + (i + c[i]) * (i + c[i]) + 2 * (i + c[i]) * (L + 1); }
double Slope(int x, int y) { return (Y(x) - Y(y)) / (X(x) - X(y)); }

int main()
{
	n = read(), L = read();
	for (int i = 1; i <= n; ++i) c[i] = read() + c[i - 1];
	q[l = r = 1] = 0;
	for (int i = 1; i <= n; ++i)
	{
		while (l < r && Slope(q[l], q[l + 1]) <= K(i)) ++l;
		int j = q[l]; f[i] = f[j] + (i - j - 1 + c[i] - c[j] - L) * (i - j - 1 + c[i] - c[j] - L);
		while (l < r && Slope(q[r], i) <= Slope(q[r], q[r - 1])) --r;
		q[++r] = i;
	}
	printf("%lld\n", f[n]); return 0;
}