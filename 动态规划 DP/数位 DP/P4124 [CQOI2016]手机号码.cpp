#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
//const int MAXN = ;
int cnt, a[15];
LL l, r, f[15][15][15][2][3][2];

LL read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

LL dfs(int pos, int pre1, int pre2, int tri, int num, int limit)
{
	if (pos == 0) return tri;
	if (f[pos][pre1][pre2][tri][num][limit] != -1) return f[pos][pre1][pre2][tri][num][limit];
	int t = limit ? a[pos] : 9; LL ans = 0;
	for (int i = (pos == cnt) ? 1 : 0; i <= t; ++i)
	{
		if (i == 4 && num == 2) continue;
		if (i == 8 && num == 1) continue;
		if (pre1 == pre2 && pre2 == i) ans += dfs(pos - 1, pre2, i, 1, num ? num : ((i == 4) ? 1 : ((i == 8) ? 2 : 0)), i == a[pos] && limit);
		else ans += dfs(pos - 1, pre2, i, tri, num ? num : ((i == 4) ? 1 : ((i == 8) ? 2 : 0)), i == a[pos] && limit);
	}
	return f[pos][pre1][pre2][tri][num][limit] = ans;
}

LL Get(LL k)
{
	if (k < 1e10) return 0;
	memset(f, -1, sizeof(f)); cnt = 0;
	for (; k; k /= 10) a[++cnt] = k % 10;
	return dfs(cnt, 0, 0, 0, 0, 1);
}

int main()
{
	l = read(), r = read();
	printf("%lld\n", Get(r) - Get(l - 1));
	return 0;
}
