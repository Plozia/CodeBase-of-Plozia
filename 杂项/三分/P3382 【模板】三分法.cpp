/*
========= Plozia =========
	Author:Plozia
	Problem:P3382 【模板】三分法
	Date:2021/10/28
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 13 + 5;
const double eps = 1e-10;
int n;
double l, r, a[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

double check(double x)
{
	double sum = 0.0, tmp = 1.0;
	for (int i = n + 1; i >= 1; --i)
		{ sum += tmp * a[i]; tmp *= x; }
	return sum;
}

int main()
{
	n = Read(); scanf("%lf %lf", &l, &r);
	for (int i = 1; i <= n + 1; ++i) scanf("%lf", &a[i]);
	double ans = 0.0;
	while (fabs(r - l) > eps)
	{
		double mid = (l + r) / 2;
		if (check(mid + eps) > check(mid - eps)) { ans = mid + eps; l = mid + eps; }
		else { ans = mid - eps; r = mid - eps; }
	}
	printf("%.5lf\n", ans); return 0;
}