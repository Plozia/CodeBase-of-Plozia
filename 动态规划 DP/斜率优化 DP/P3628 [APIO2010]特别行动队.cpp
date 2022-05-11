/*
========= Plozia =========
	Author:Plozia
	Problem:P3628 [APIO2010]特别行动队
	Date:2021/4/15
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e6 + 10;
int n, l, r, q[MAXN];
LL a, b, c, x[MAXN], f[MAXN];

LL read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }

double K(int i) { return 2.0 * a * x[i]; }
double X(int i) { return 1.0 * x[i]; }
double Y(int i) { return 1.0 * f[i] + a * x[i] * x[i] - b * x[i]; }
double Slope(int x, int y) { return (Y(x) - Y(y)) / (X(x) - X(y)); }

int main()
{
	n = read(), a = read(), b = read(), c = read();
	memset(f, -0x3f, sizeof(f)); f[0] = 0;
	for (int i = 1; i <= n; ++i) x[i] = read() + x[i - 1];
	q[l = r = 1] = 0;
	for (int i = 1; i <= n; ++i)
	{
		while (l < r && Slope(q[l], q[l + 1]) >= K(i)) ++l;
		int j = q[l]; f[i] = f[j] + a * (x[i] - x[j]) * (x[i] - x[j]) + b * (x[i] - x[j]) + c;
		while (l < r && Slope(q[r], q[r - 1]) <= Slope(q[r], i)) --r;
		q[++r] = i;
	}
	printf("%lld\n", f[n]); return 0;
}