/*
========= Plozia =========
	Author:Plozia
	Problem:CF1717D Madoka and The Corruption Scheme
	Date:2022/9/5
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 1e5 + 5;
const LL P = 1e9 + 7;
int n, k;
LL fact[MAXN], inv[MAXN];

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

int main()
{
	n = Read(), k = Read(); k = std::min(n, k);
	fact[0] = 1; for (int i = 1; i <= n; ++i) fact[i] = i * fact[i - 1] % P;
	for (int i = 0; i <= n; ++i) inv[i] = ksm(fact[i]);
	LL ans = 0;
	for (int i = 0; i <= k; ++i) ans = (ans + fact[n] * inv[i] % P * inv[n - i] % P) % P;
	printf("%lld\n", ans); return 0;
}