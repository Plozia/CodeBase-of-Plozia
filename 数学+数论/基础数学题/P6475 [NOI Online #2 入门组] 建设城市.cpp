/*
========= Plozia =========
	Author:Plozia
	Problem:P6475 [NOI Online #2 入门组] 建设城市
	Date:2022/3/17
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2e5 + 5;
const LL P = 998244353;
int n, m, x, y;
LL fact[MAXN], inv[MAXN], ans;

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
	LL s = 1 % p;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) s = s * a % p;
	return s;
}

LL C(int n, int m)
{
	if (n < m) return 0;
	return fact[n] * inv[m] % P * inv[n - m] % P;
}

void Work1()
{
	if (x > n) x = (2 * n + 1 - x), y = (2 * n + 1 - y);
	if (x > y) std::swap(x, y);
	for (int i = 1; i <= m; ++i)
		ans = (ans + C(n + m - 1, m - 1) * C((x - 1) + i - 1, i - 1) % P * C((n - (y + 1) + 1) + (m - i + 1) - 1, (m - i + 1) - 1) % P) % P;
}

void Work2()
{
	if (x > n) x = (n - (x - n) + 1);
	if (y > n) y = (n - (y - n) + 1);
	for (int i = 1; i <= m; ++i)
		ans = (ans + C((x - 1) + i - 1, i - 1) * C((n - (x + 1) + 1) + (m - i + 1) - 1, (m - i + 1) - 1) % P * C((y - 1) + i - 1, i - 1) % P * C((n - (y + 1) + 1) + (m - i + 1) - 1, (m - i + 1) - 1) % P) % P;
}

int main()
{
	m = Read(), n = Read(), x = Read(), y = Read(); fact[0] = inv[0] = 1;
	for (int i = 1, tmp = Max(n, m); i <= 2 * tmp + 2; ++i) fact[i] = fact[i - 1] * i % P;
	inv[Max(n, m) * 2 + 2] = ksm(fact[Max(n, m) * 2 + 2]);
	for (int i = Max(n, m) * 2 + 1; i >= 1; --i) inv[i] = inv[i + 1] * (i + 1) % P;
	if ((x <= n && y <= n) || (x > n && y > n)) Work1();
	else Work2();
	printf("%lld\n", ans); return 0;
}