/*
========= Plozia =========
	Author:Plozia
	Problem:CF156D Clues
	Date:2022/2/17
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, m, k, fa[MAXN], Size[MAXN];
LL ans, P;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int gf(int x) { return (x == fa[x]) ? x : (fa[x] = gf(fa[x])); }
LL ksm(LL a, LL b = P - 2, LL p = P)
{
	LL s = 1 % p;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) s = s * a % p;
	return s;
}

int main()
{
	n = Read(), m = Read(), P = Read(); k = n;
	if (n == 1)
	{
		if (P != 1) puts("1"); else puts("0");
		return 0;
	}
	for (int i = 1; i <= n; ++i) fa[i] = i, Size[i] = 1;
	for (int i = 1; i <= m; ++i)
	{
		int x = Read(), y = Read();
		if (gf(x) != gf(y))
		{
			Size[fa[y]] += Size[fa[x]];
			fa[fa[x]] = fa[y]; --k;
		}
	}
	if (k == 1) { printf("%d\n", 1 % P); return 0;}
	ans = ksm(n, k - 2);
	for (int i = 1; i <= n; ++i)
		if (gf(i) == i) ans = 1ll * Size[i] * ans % P;
	printf("%lld\n", ans); return 0; 
}