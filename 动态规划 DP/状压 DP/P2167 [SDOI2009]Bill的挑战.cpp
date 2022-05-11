/*
========= Plozia =========
	Author:Plozia
	Problem:P2167 [SDOI2009]Bill的挑战
	Date:2021/6/4
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::string;

typedef long long LL;
const int MAX_State = (1 << 15) - 1, P = 1000003;
int t, n, f[MAX_State], g[MAX_State][55], m, a[21][55], Size, ans;
bool book[MAX_State];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

int main()
{
	t = Read();
	while (t--)
	{
		n = Read(), m = Read(); ans = 0;
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		memset(book, 0, sizeof(book));
		for (int i = 1; i <= n; ++i)
		{
			string str; std::cin >> str;
			Size = str.size();
			for (int j = 0; j < Size; ++j)
				if (str[j] != '?') a[i][j + 1] = str[j];
				else a[i][j + 1] = 0;
		}
		f[0] = 1;
		for (int i = 1; i <= (1 << n) - 1; ++i)
		{
			bool pd = 0;
			for (int j = 1; j <= n; ++j)
			{
				if (((1 << (j - 1)) & i) == 0) continue ;
				bool flag = 0;
				if (book[i - (1 << (j - 1))] == 1) { pd = 1; continue ; }
				for (int k = 1; k <= Size; ++k)
				{
					if (g[i - (1 << (j - 1))][k] == 0 || g[1 << (j - 1)][k] == 0) continue ;
					if (g[i - (1 << (j - 1))][k] != g[1 << (j - 1)][k]) flag = 1;
				}
				pd |= flag;
				for (int k = 1; k <= Size; ++k)
				{
					if (g[i - (1 << (j - 1))][k] == 0 || g[1 << (j - 1)][k] == 0) g[i][k] = g[i - (1 << (j - 1))][k] + g[1 << (j - 1)][k];
					g[i][k] = g[1 << (j - 1)][k];
				}
			}
			if (pd == 1) { book[i] = 1; continue ; }
			for (int j = 1; j <= n; ++j)
			{
				if (((1 << (j - 1)) & i) != 0) continue ;
				f[i | (1 << (j - 1))] = (f[i | (1 << (j - 1))] + f[i]) % P;
			}
		}
		for (int i = 1; i <= (1 << n) - 1; ++i)
		{
			int sum = 0;
			for (int j = 1; j <= n; ++j) sum += i & (1 << (j - 1));
			if (sum == m && book[i] == 0) ans = (ans + f[i]) % P;
		}
		printf("%d\n", ans);
	}
}