/*
========= Plozia =========
	Author:Plozia
	Problem:P3704 [SDOI2017]数字表格
	Date:2022/3/9
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e6 + 5;
const LL P = 1e9 + 7;
int t, n, m, mu[MAXN], Prime[MAXN], cnt_Prime;
LL f[MAXN], sum[MAXN], inv[MAXN];
bool book[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
LL ksm(LL a, LL b = P - 2, LL p = P)
{
	if (b == -1) b = P - 2;
	LL s = 1 % p;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) s = s * a % p;
	return s;
}

void init()
{
	f[1] = 1; book[1] = mu[1] = 1; inv[1] = 1; int tmp = MAXN - 5;
	for (int i = 2; i <= tmp; ++i) f[i] = (f[i - 1] + f[i - 2]) % P, inv[i] = ksm(f[i]);
	for (int i = 2; i <= tmp; ++i)
	{
		if (!book[i]) { Prime[++cnt_Prime] = i; mu[i] = -1; }
		for (int j = 1; j <= cnt_Prime; ++j)
		{
			if (i * Prime[j] > tmp) break ;
			book[i * Prime[j]] = 1;
			if (i % Prime[j] == 0) { mu[i * Prime[j]] = 0; break ; }
			mu[i * Prime[j]] = -mu[i];
		}
	}
	for (int i = 1; i <= tmp; ++i) sum[i] = 1;
	for (int i = 1; i <= tmp; ++i)
	{
		if (!mu[i]) continue ;
		for (int j = i; j <= tmp; j += i)
			sum[j] = sum[j] * ((mu[i] == 1) ? f[j / i] : inv[j / i]) % P;
	}
	sum[0] = 1; inv[0] = 1;
	for (int i = 1; i <= tmp; ++i) sum[i] = sum[i - 1] * sum[i] % P;
	for (int i = 1; i <= tmp; ++i) inv[i] = ksm(sum[i]);
}

int main()
{
	t = Read(); init();
	while (t--)
	{
		n = Read(), m = Read(); LL ans = 1;
		if (n > m) std::swap(n, m);
		for (int l = 1, r; l <= n; l = r + 1)
		{
			r = Min(n / (n / l), m / (m / l));
			ans = ans * ksm(sum[r] * inv[l - 1] % P, 1ll * (n / l) * (m / l)) % P;
		}
		printf("%lld\n", ans);
	}
	return 0;
}