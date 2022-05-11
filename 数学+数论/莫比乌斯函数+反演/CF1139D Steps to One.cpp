	/*
	========= Plozia =========
		Author:Plozia
		Problem:CF1139D Steps to One
		Date:2022/3/1
	========= Plozia =========
	*/

	#include <bits/stdc++.h>

	typedef long long LL;
	const int MAXN = 1e5 + 5;
	const LL P = 1e9 + 7;
	int t, n, cntPrime, Prime[MAXN];
	LL mu[MAXN], inv[MAXN];
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
		LL s = 1 % p;
		for (; b; b >>= 1, a = a * a % p)
			if (b & 1) s = s * a % p;
		return s;
	}

	void init()
	{
		book[1] = mu[1] = 1;
		for (int i = 2; i <= n; ++i)
		{
			if (!book[i]) { Prime[++cntPrime] = i; mu[i] = -1; }
			for (int j = 1; j <= cntPrime; ++j)
			{
				if (i * Prime[j] > n) break ;
				book[i * Prime[j]] = 1;
				if(i % Prime[j] == 0) { mu[i * Prime[j]] = 0; break ; }
				mu[i * Prime[j]] = -mu[i];
			}
		}
		for (int i = 2; i <= n; ++i) mu[i] = mu[i - 1] + mu[i];
	}

	int main()
	{
		n = Read(); init(); LL ans = 0;
		for (int i = 1; i <= n; ++i) inv[i] = ksm(i);
		for (int l = 2, r; l <= n; l = r + 1)
		{
			r = Min(n / (n / l), n);
			ans = (ans + (mu[r] - mu[l - 1]) * (n / l) % P * inv[n - (n / l)] % P) % P;
		}
		ans = ((1 - ans) % P + P) % P;
		printf("%lld\n", ans);
		return 0;
	}