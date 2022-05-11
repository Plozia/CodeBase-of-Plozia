/*
========= Plozia =========
	Author:Plozia
	Problem:P2260 [清华集训2012]模积和
	Date:2022/2/21
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e6 + 5;
const LL P = 19940417;
int n, m, Left[MAXN], Right[MAXN], cnt, inv2 = (1 + P) / 2;
LL ans = 0, sum = 0;

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
	n = Read(), m = Read(); ans = 1ll * n * n % P * m % P * m % P;
	if (n > m) std::swap(n, m);
	for (int l = 1, r; l <= n; l = r + 1)
	{
		r = n / (n / l);
		ans = ((ans - 1ll * m * m % P * (n / l) % P * (l + r) % P * (r - l + 1) % P * inv2 % P) % P + P) % P;
	}
	for (int l = 1, r; l <= m; l = r + 1)
	{
		r = m / (m / l);
		ans = ((ans - 1ll * n * n % P * (m / l) % P * (l + r) % P * (r - l + 1) % P * inv2 % P) % P + P) % P;
	}
	for (int l = 1, r; l <= m; l = r + 1)
	{
		r = m / (m / l);
		sum = (sum + 1ll * (l + r) * (r - l + 1) % P * inv2 % P * (m / l) % P) % P;
	}
	for (int l = 1, r; l <= n; l = r + 1)
	{
		r = n / (n / l);
		ans = (ans + 1ll * (l + r) * (r - l + 1) % P * inv2 % P * (n / l) % P * sum % P) % P;
	}
	printf("%lld\n", ans); return 0;
}