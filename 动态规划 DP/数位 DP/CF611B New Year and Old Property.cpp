#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
//const int MAXN = ;
int l, r, a[70], cnt;
LL f[70][2][2][2];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

LL dfs(int pos, int sum, int zero, int limit)
{
	if (pos == 0) return 1;
	if (f[pos][sum][zero][limit] != -1) return f[pos][sum][zero][limit];
	int t = limit ? a[pos] : 1; LL ans = 0;
	for (int i = 0; i <= t; ++i)
	{
		if (i == 0 && zero) ans += dfs(pos - 1, sum, 1, i == a[pos] && limit);
		else if (i == 0 && sum == 0) ans += dfs(pos - 1, 1, 0, i == a[pos] && limit);
		else if (i == 1) ans += dfs(pos - 1, sum, 0, i == a[pos] && limit);
	}
	f[pos][sum][zero][limit] = ans;
	return ans;
}

LL Get(int k)
{
	cnt = 0; memset(a, 0, sizeof(a));
	while (k) {a[++cnt] = k & 1; k >>= 1;}
	return dfs(cnt, 0, 1, 1);
}

int main()
{
	l = read(), r = read();
	memset(f, -1, sizeof(f));
	printf("%lld\n", Get(r) - Get(l - 1));
	return 0;
}
