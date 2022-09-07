/*
========= Plozia =========
	Author:Plozia
	Problem:CF893E Counting Arrays
	Date:2022/9/7
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 1e6 + 5;
const LL P = 1e9 + 7;
int t, x, y, p[MAXN], k[MAXN], cntp, Prime[MAXN], cntPrime;
LL fact[MAXN << 1], inv[MAXN << 1];
bool book[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
LL ksm(LL a, LL b = P - 2, LL p = P)
{
	LL s = 1 % p;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) s = s * a % p;
	return s;
}

void init()
{
	book[1] = 1;
	for (int i = 2; i <= MAXN - 5; ++i)
	{
		if (!book[i]) Prime[++cntPrime] = i;
		for (int j = 1; j <= cntPrime; ++j)
		{
			if (i * Prime[j] > MAXN - 5) break ;
			book[i * Prime[j]] = 1;
			if (i % Prime[j] == 0) break ;
		}
	}
	fact[0] = 1;
	for (int i = 1; i <= 2000000; ++i) fact[i] = fact[i - 1] * i % P;
	inv[2000000] = ksm(fact[2000000]);
	for (int i = 1999999; i >= 0; --i) inv[i] = inv[i + 1] * (i + 1) % P;
}

LL C(LL n, LL m)
{
	return fact[n] * inv[m] % P * inv[n - m] % P;
}

void Solve()
{
	x = Read(), y = Read(); LL ans = 1;
	for (int i = 1; i <= cntp; ++i) k[i] = 0;
	for (int i = 1; i <= cntPrime && Prime[i] * Prime[i] <= x; ++i)
	{
		if (x % Prime[i] != 0) continue ;
		int sum = 0; while (x % Prime[i] == 0) ++sum, x /= Prime[i];
		ans = ans * C(sum + y - 1, y - 1) % P;
	}
	if (x > 1) ans = ans * C(1 + y - 1, y - 1) % P;
	ans = ans * ksm(2, y - 1) % P;
	printf("%lld\n", ans);
}

int main()
{
	init(); t = Read(); while (t--) Solve(); return 0;
}