/*
========= Plozia =========
	Author:Plozia
	Problem:CF235B Let's Play Osu!
	Date:2021/6/22
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef double db;
typedef long long LL;
const int MAXN = 1e5 + 5;
int n;
db p[MAXN], f[MAXN], k[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i) scanf("%lf", &p[i]);
	for (int i = 1; i <= n; ++i)
	{
		k[i] = (k[i - 1] + 1) * p[i];
		f[i] = f[i - 1] + p[i] * (2 * k[i - 1] + 1);
	}
	printf("%.15lf\n", f[n]); return 0;
}