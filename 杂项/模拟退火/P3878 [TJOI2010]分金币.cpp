/*
========= Plozia =========
	Author:Plozia
	Problem:P3878 [TJOI2010]分金币
	Date:2022/1/27
========= Plozia =========
*/

#include <bits/stdc++.h>
std::mt19937 rng(std::random_device{}());

typedef long long LL;
const int MAXN = 30 + 5;
int t, n;
LL a[MAXN], ans, sum, fir, sec;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
LL Abs(LL x) { return (x < 0) ? -x : x; }

void SA()
{
	double t0 = 6081, tEnd = 1e-14, Deltat = 0.995;
	for (; t0 >= tEnd; t0 *= Deltat)
	{
		int x = rng() % (n >> 1) + 1, y = n - rng() % ((n >> 1) + (n & 1));
		sum = Abs(fir - (a[x] << 1) + (a[y] << 1) - sec);
		if (sum < ans) { ans = sum; fir = fir - a[x] + a[y]; sec = sec - a[y] + a[x]; std::swap(a[x], a[y]); }
		else if (exp((ans - sum) / t0) > (rng() * 1.0 / ((1u << 31) - 1 + (1u << 31)))) { fir = fir - a[x] + a[y]; sec = sec - a[y] + a[x]; std::swap(a[x], a[y]); }
	}
}

int main()
{
	t = Read();
	while (t--)
	{
		n = Read(); ans = sum = fir = sec = 0;
		for (int i = 1; i <= n; ++i)
		{
			a[i] = Read();
			if (i <= (n >> 1)) fir += a[i];
			else sec += a[i];
		}
		if (n == 1) { printf("%lld\n", a[1]); continue; }
		ans = Abs(fir - sec);
		for (int i = 1; i <= 20; ++i) SA();
		printf("%d\n", ans);
	}
	return 0;
}