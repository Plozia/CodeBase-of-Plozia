#include <bits/stdc++.h>
#define Max(a, b) ((a > b) ? a : b)
using namespace std;

typedef long long LL;
const int MAXN = 1e5 + 10;
LL l, r, f[70][MAXN];
int k, cnt, a[70];

LL read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

LL dfs1(int pos, int sum, int limit)
{
	if (pos == 0) return sum;
	if (!limit && f[pos][sum] != -1) return f[pos][sum];
	int t = limit ? a[pos] : k - 1; LL ans = 0;
	for (int i = 0; i <= t; ++i) ans += dfs1(pos - 1, sum + i * (pos - 1), limit && i == a[pos]);
	if (!limit) f[pos][sum] = ans;
	return ans;
}

LL dfs2(int pos, int sum, int tag, int limit)
{
	if (sum < 0) return 0;
	if (pos == 0) return sum;
	if (!limit && f[pos][sum] != -1) return f[pos][sum];
	int t = limit ? a[pos] : k - 1; LL ans = 0;
	for (int i = 0; i <= t; ++i) ans += dfs2(pos - 1, sum + ((pos < tag) ? -i : i), tag, limit && i == a[pos]);
	if (!limit) f[pos][sum] = ans;
	return ans;
}

LL Get(LL p)
{
	memset(f, -1, sizeof(f)); cnt = 0;
	for (; p; p /= k) a[++cnt] = p % k;
	LL sum = dfs1(cnt, 0, 1);
	for (int i = 2; i <= cnt; ++i)
	{
		memset(f, -1, sizeof(f));
		sum -= dfs2(cnt, 0, i, 1);
	}
	return sum;
}

int main()
{
	l = read(), r = read(), k = read();
	printf ("%lld\n", Get(r) - Get(l - 1));
	return 0;
}
