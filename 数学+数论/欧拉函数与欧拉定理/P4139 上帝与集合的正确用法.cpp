/*
========= Plozia =========
	Author:Plozia
	Problem:P4139 上帝与集合的正确用法
	Date:2021/5/19
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 1e7 + 10;
int t;
LL p, phi[MAXN];
vector <int> v;
bool book[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void init()
{
	book[1] = 1; phi[1] = 1;
	for (int i = 2; i <= MAXN - 10; ++i)
	{
		if (!book[i]) { v.push_back(i); phi[i] = i - 1; }
		for (int j = 0; j < v.size(); ++j)
		{
			if (i * v[j] > MAXN - 10) break ;
			book[i * v[j]] = 1;
			if (i % v[j] == 0) { phi[i * v[j]] = phi[i] * v[j]; break ; }
			phi[i * v[j]] = phi[i] * (v[j] - 1);
		}
	}
}

LL ksm(LL a, LL b, LL p)
{
	LL ans = 1 % p;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) ans = ans * a % p;
	return ans;
}

LL Get(LL p)
{
	if (p == 1) return 1;
	return ksm(2, Get(phi[p]) + phi[p], p);
}

int main()
{
	t = read(); init();
	while (t--)
	{
		p = read();
		printf("%lld\n", Get(p) % p);
	}
	return 0;
}