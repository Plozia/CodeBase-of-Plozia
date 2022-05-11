/*
========= Plozia =========
	Author:Plozia
	Problem:CF55D Beautiful numbers
	Date:2021/8/15
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
// const int MAXN = ;
int T, a[30], f[20][2521][50];
int book[2521];

LL Read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
LL gcd(LL x, LL y) { return (y == 0) ? x : gcd(y, x % y); }
LL lcm(LL x, LL y) { return (x == 0 || y == 0) ? (x + y) : (x / gcd(x, y) * y); }

LL dfs(int pos, int Mod, int Lcm, int zero, int limit)
{
	if (pos == 0) return (Mod % Lcm == 0);
	if (!zero && !limit && f[pos][Mod][book[Lcm]] != -1) return f[pos][Mod][book[Lcm]];
	int t = limit ? a[pos] : 9; LL ans = 0;
	for (int i = 0; i <= t; ++i)
	{
		if (zero && i == 0) ans += dfs(pos - 1, (Mod * 10) % 2520, Lcm, 1, 0);
		else if (i == 0) ans += dfs(pos - 1, (Mod * 10) % 2520, Lcm, 0, 0);
		else ans += dfs(pos - 1, (Mod * 10 + i) % 2520, lcm(Lcm, i), 0, limit && (i == a[pos]));
	}
	return f[pos][Mod][book[Lcm]] = ans;
}

LL Solve(LL now)
{
	a[0] = 0;
	while (now) a[++a[0]] = now % 10, now /= 10;
	return dfs(a[0], 0, 1, 1, 1);
}

int main()
{
	T = Read(); memset(f, -1, sizeof(f));
	for (int i = 1; i * i <= 2520; ++i)
		if (2520 % i == 0) { book[i] = ++book[0]; book[2520 / i] = ++book[0]; }
	while (T--)
	{
		LL l = Read(), r = Read();
		printf("%lld\n", Solve(r) - Solve(l - 1));
	}
	return 0;
}