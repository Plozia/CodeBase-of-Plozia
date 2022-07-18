/*
========= Plozia =========
	Author:Plozia
	Problem:P2915 [USACO08NOV]Mixed Up Cows G
	Date:2022/7/18
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;

const int MAXN = 16 + 5, MAXState = (1 << 16);
int n, k, a[MAXN];
LL f[MAXState][MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Abs(int x) { return (x < 0) ? -x : x; }

int main()
{
	n = Read(), k = Read(); for (int i = 1; i <= n; ++i) a[i] = Read(), f[1 << (i - 1)][i] = 1;
	for (int s = 1; s < (1 << n); ++s)
		for (int i = 1; i <= n; ++i)
		{
			if (!(s & (1 << (i - 1)))) continue ;
			for (int j = 1; j <= n; ++j)
			{
				if (!(s & (1 << (j - 1)))) continue ;
				if (Abs(a[i] - a[j]) <= k) continue ;
				int s_ = s ^ (1 << (i - 1));
				f[s][i] += f[s_][j];
			}
		}
	LL ans = 0; for (int i = 1; i <= n; ++i) ans += f[(1 << n) - 1][i];
	printf("%lld\n", ans); return 0;
}