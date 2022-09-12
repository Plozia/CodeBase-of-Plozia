/*
========= Plozia =========
	Author:Plozia
	Problem:CF149D Coloring Brackets
	Date:2022/9/12
========= Plozia =========
*/

#include <bits/stdc++.h>
typedef long long LL;
using std::stack;

const int MAXN = 700 + 5, P = 1e9 + 7;
int n, Match[MAXN], f[MAXN][MAXN][3][3];
char str[MAXN];
stack <int> s;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}

void dfs(int l, int r)
{
	if (r == l + 1)
	{
		f[l][r][0][1] = f[l][r][0][2] = f[l][r][1][0] = f[l][r][2][0] = 1;
		return ;
	}
	if (Match[l] == r)
	{
		dfs(l + 1, r - 1);
		for (int i = 0; i <= 2; ++i)
			for (int j = 0; j <= 2; ++j)
			{
				if (j != 1) f[l][r][0][1] = (f[l][r][0][1] + f[l + 1][r - 1][i][j]) % P;
				if (j != 2) f[l][r][0][2] = (f[l][r][0][2] + f[l + 1][r - 1][i][j]) % P;
				if (i != 1) f[l][r][1][0] = (f[l][r][1][0] + f[l + 1][r - 1][i][j]) % P;
				if (i != 2) f[l][r][2][0] = (f[l][r][2][0] + f[l + 1][r - 1][i][j]) % P;
			}
	}
	else
	{
		dfs(l, Match[l]); dfs(Match[l] + 1, r);
		for (int i = 0; i <= 2; ++i)
			for (int j = 0; j <= 2; ++j)
				for (int k = 0; k <= 2; ++k)
					for (int p = 0; p <= 2; ++p)
					{
						if (j == k && j != 0) continue ;
						f[l][r][i][p] = (f[l][r][i][p] + 1ll * f[l][Match[l]][i][j] * f[Match[l] + 1][r][k][p] % P) % P;
					}
	}
}

int main()
{
	scanf("%s", str + 1); n = strlen(str + 1);
	for (int i = 1; i <= n; ++i)
	{
		if (str[i] == '(') s.push(i);
		else { Match[i] = s.top(); Match[s.top()] = i; s.pop(); }
	}
	dfs(1, n); int ans = 0;
	for (int i = 0; i <= 2; ++i)
		for (int j = 0; j <= 2; ++j)
			ans = (ans + f[1][n][i][j]) % P;
	printf("%d\n", ans); return 0;
}