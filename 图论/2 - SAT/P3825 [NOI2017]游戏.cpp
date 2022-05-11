/*
========= Plozia =========
	Author:Plozia
	Problem:P3825 [NOI2017] 游戏
	Date:2021/8/14
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 5e4 + 5, MAXM = 1e5 + 5;
int n, m, d, Head[MAXN << 1], str[MAXN], cnt_Edge = 1, Color[MAXN << 1], col, sta[MAXN << 1], Top, Pos_x[10];
struct node { int to, val, Next; } Edge[MAXM << 1];
struct query {int p1, flag1, p2, flag2; } q[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

int Change(int p, int flag)
{
	if (str[p] == 1) return (flag == 2) ? p : p + n;
	if (str[p] == 2) return (flag == 1) ? p : p + n;
	if (str[p] == 3) return (flag == 1) ? p : p + n;
}

void Solve()
{
	memset(Head, 0, sizeof(Head)); cnt_Edge = 1; memset(Color, 0, sizeof(Color)); col = 0;
	memset(sta, 0, sizeof(Top)); Top = 0; memset(Edge, 0, sizeof(Edge));
	for (int i = 1; i <= m; ++i)
	{
		
	}
}

void dfs(int k)
{
	if (k > d) { Solve(); return ; }
	str[k] = 1; dfs(k + 1);
	str[k] = 2; dfs(k + 1);
}

int main()
{
	n = Read(), d = Read();
	for (int i = 1; i <= n; ++i)
	{
		char ch = getchar(); while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
		if (ch == 'a') str[i] = 1;
		if (ch == 'b') str[i] = 2;
		if (ch == 'c') str[i] = 3;
		if (ch == 'x') str[i] = 4, Pos_x[++Pos_x[0]] = i;
	}
	m = Read();
	for (int i = 1; i <= m; ++i)
	{
		char ch1, ch2;
		q[i].p1 = Read(); ch1 = getchar(); while (ch1 == ' ' || ch1 == '\r' || ch1 == '\n') ch1 = getchar();
		q[i].p2 = Read(); ch2 = getchar(); while (ch2 == ' ' || ch2 == '\r' || ch2 == '\n') ch2 = getchar();
		if (ch1 == 'A') q[i].flag1 = 1; else if (ch1 == 'B') q[i].flag1 == 2; else q[i].flag1 = 3;
		if (ch2 == 'A') q[i].flag2 = 1; else if (ch2 == 'B') q[i].flag2 == 2; else q[i].flag2 = 3;
	}
	dfs(1); printf("-1\n"); return 0;
}