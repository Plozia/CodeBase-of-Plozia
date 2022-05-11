/*
========= Plozia =========
	Author:Plozia
	Problem:P2704 [NOI2001] �ڱ����
	Date:2021/3/2
========= Plozia =========
*/

#include <bits/stdc++.h>
#define Max(a, b) ((a > b) ? a : b)

typedef long long LL;
const int MAXN = (1 << 10) + 10, MAXP = 60 + 10;
int n, m, cnt, State[MAXN], Sum[MAXN], a[100 + 10][100 + 10], Map[100 + 10], f[100 + 10][MAXP][MAXP], ans = 0;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

void dfs(int pos, int sum, int num)
{
	if (pos >= m) {State[++cnt] = sum; Sum[cnt] = num; return ;}
	dfs(pos + 1, sum, num);
	dfs(pos + 3, sum + (1 << pos), num + 1);
}

int main()
{
	n = read(), m = read();
	Map[0] = (1 << m) - 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			char ch; std::cin >> ch;
			if (ch == 'P') a[i][j] = 1;
			Map[i] += a[i][j] * (1 << (m - j));
		}
	dfs(0, 0, 0);
	for (int i = 1; i <= cnt; ++i)
		for (int j = 1; j <= cnt; ++j)
			f[1][i][j] = Sum[i];
	for (int i = 2; i <= n; ++i)
	{
		for (int j = 1; j <= cnt; ++j)
		{
			if (!((Map[i] & State[j]) == State[j])) continue;
			for (int k = 1; k <= cnt; ++k)
			{
				if (!((Map[i - 1] & State[k]) == State[k])) continue;
				for (int l = 1; l <= cnt; ++l)
				{
					if (!((Map[i - 2] & State[l]) == State[l])) continue;
					if ((State[j] & State[k]) || (State[k] & State[l]) || (State[j] & State[l])) continue;
					f[i][j][k] = Max(f[i][j][k], f[i - 1][k][l] + Sum[j]);
				}
			}
		}
	}
	for (int i = 1; i <= cnt; ++i)
		for (int j = 1; j <= cnt; ++j)
			ans = Max(ans, f[n][i][j]);
	printf("%lld\n", ans);
	return 0;
}
