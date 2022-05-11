#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
//const int MAXN = ;
LL l, r, f[15][15][2][2];
int cnt, a[15];

LL read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == -1) ? -sum : sum;
}

LL dfs(int pos, int sum, int zero, int limit, int d)
{
	if (pos == 0) return sum;
	if (f[pos][sum][zero][limit] != -1) return f[pos][sum][zero][limit];
	int t = limit ? a[pos] : 9; LL ans = 0;
	for (int i = 0; i <= t; ++i)
	{
		if (i == 0 && zero) ans += dfs(pos - 1, sum, 1, i == a[pos] && limit, d);
		else ans += dfs(pos - 1, sum + (i == d), 0, i == a[pos] && limit, d);
	}
	return f[pos][sum][zero][limit] = ans;
}

LL Get(LL k, int d)
{
	memset(f, -1, sizeof(f)); cnt = 0;
	for (; k; k /= 10) a[++cnt] = k % 10;
	return dfs(cnt, 0, 1, 1, d);
}

int main()
{
	l = read(), r = read();
	for (int i = 0; i < 10; ++i)
		printf("%lld ", Get(r, i) - Get(l - 1, i));
	printf("\n"); return 0;
}
