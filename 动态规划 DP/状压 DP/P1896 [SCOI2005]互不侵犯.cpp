#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 9 + 5, MAXP = (1 << 9) + 10, MAXK = 9 * 9 + 10;
int n, p, State[MAXP], sum[MAXP], cnt;
LL f[MAXN][MAXK][MAXP];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9' ; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

void dfs(int pos, int num, int one)
{
	if (pos >= n) {State[++cnt] = num; sum[cnt] = one; return ;}
	dfs(pos + 1, num, one);
	dfs(pos + 2, num + (1 << pos), one + 1);
}

int main()
{
	n = read(), p = read();
	dfs(0, 0, 0);
	cout << cnt << "\n";
	for (int i = 1; i <= cnt; ++i) f[1][sum[i]][i] = 1;
	for (int i = 2; i <= n; ++i)
		for (int j = 1; j <= cnt; ++j)
			for (int k = 1; k <= cnt; ++k)
			{
				if (State[j] & State[k]) continue;
				if ((State[j] << 1) & State[k]) continue;
				if ((State[j] >> 1) & State[k]) continue;
				for (int l = sum[j]; l <= p; ++l) f[i][l + sum[k]][k] += f[i - 1][l][j];
			}
	LL ans = 0;
	for (int i = 1; i <= cnt; ++i) ans += f[n][p][i];
	printf("%lld\n", ans);
	return 0;
}
