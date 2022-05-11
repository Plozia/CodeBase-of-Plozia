/*
========= Plozia =========
	Author:Plozia
	Problem:P1829 [国家集训队]Crash的数字表格 / JZPTAB
	Date:2022/2/23
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 1e7 + 5;
const LL P = 20101009;
LL n, m;
LL mu[MAXN];
bool book[MAXN];
vector <int> v;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }

void init()
{
	book[1] = 1; mu[1] = 1;
	for (int i = 2; i <= m; ++i)
	{
		if (!book[i]) { v.push_back(i); mu[i] = -1; }
		for (int j = 0; j < v.size(); ++j)
		{
			if (i * v[j] > m) break ;
			book[i * v[j]] = 1;
			if (i % v[j] == 0) { mu[i * v[j]] = 0; break ; }
			mu[i * v[j]] = -mu[i];
		}
	}
	for (int i = 2; i <= m; ++i) mu[i] = 1ll * i * i * mu[i] % P;
	for (int i = 1; i <= m; ++i) mu[i] = (mu[i] + mu[i - 1]) % P;
}
 
const LL inv2 = (1 + P) / 2;

int main()
{
	n = Read(), m = Read(); if (n > m) std::swap(n, m);
	LL ans = 0; init();
	for (LL l1 = 1, r1; l1 <= n; l1 = r1 + 1)
	{
		r1 = Min(n, Min(n / (n / l1), m / (m / l1)));
		LL sum = 0;
		for (LL l = 1, r; l <= n / l1; l = r + 1)
		{
			r = Min(n / l1, Min((n / l1) / ((n / l1) / l), (m / l1) / ((m / l1) / l)));
			sum = (sum + 1ll * ((mu[r] - mu[l - 1]) % P + P) % P * (1 + ((n / l1) / l)) % P * ((n / l1) / l) % P * inv2 % P
						* (1 + (m / l1) / l) % P * ((m / l1) / l) % P * inv2 % P) % P;
		}
		ans = (ans + 1ll * (r1 + l1) * (r1 - l1 + 1) % P * inv2 % P * sum % P) % P;
	}
	printf("%lld\n", ans); return 0;
}