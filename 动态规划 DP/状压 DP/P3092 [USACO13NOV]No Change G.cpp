/*
========= Plozia =========
	Author:Plozia
	Problem:P3092 [USACO13NOV]No Change G
	Date:2021/5/31
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 100000 + 10, Max_State = (1 << 16) - 1;
int k, Coin[20], n, a[MAXN], f[Max_State];
LL sum[MAXN], ans = -1;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }

int Plozia_Search(int fir, int sec, int c)
{
	int l = fir, r = sec, s = sec + 1;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (sum[mid] - sum[fir - 1] > c) { s = mid; r = mid - 1; }
		else l = mid + 1;
	}
	return s - 1;
}

int main()
{
	k = Read(), n = Read();
	for (int i = 1; i <= k; ++i) Coin[i] = Read();
	for (int i = 1; i <= n; ++i) { a[i] = Read(); sum[i] = sum[i - 1] + (LL)a[i]; }
	for (int i = 0; i <= (1 << k) - 1; ++i)
	{
		if (f[i] == n)
		{
			LL val = 0;
			for (int j = 1; j <= k; ++j)
				if ((i & (1 << (j - 1))) == 0) val += (LL)Coin[j];
			ans = Max(ans, val);
			continue ;
		}
		for (int j = 1; j <= k; ++j)
		{
			if (!((i & (1 << (j - 1))) == 0)) continue ;
			int pos = Plozia_Search(f[i] + 1, n, Coin[j]);
			f[i | (1 << (j - 1))] = Max(f[i | (1 << (j - 1))], pos);
		}
	}
	printf("%lld\n", ans);
	return 0;
}