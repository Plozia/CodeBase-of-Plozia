/*
========= Plozia =========
	Author:Plozia
	Problem:网络流 24 题#2——P4011 孤岛营救问题
	Date:2021/3/26
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;
using std::queue;

typedef long long LL;
const int MAXN = 10 + 10, MAXK = 150 + 10, MAXS = 14;
int n, m, p, k, s, book[MAXN][MAXN][1 << MAXS], ans, Door[MAXN][MAXN][4];
int Next[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
vector <int> Key[MAXN][MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 1) + (sum << 3) + (ch ^ 48);
	return (fh == 1) ? sum : -sum;
}

void bfs()
{
	queue <int> qx, qy, qs, qState;
	qx.push(1), qy.push(1), qs.push(0);
	int Plozia = 0;
	for (int i = 0; i < Key[1][1].size(); ++i) Plozia |= (1 << Key[1][1][i]);
	book[1][1][Plozia] = 1; qState.push(Plozia);
	while (!qx.empty())
	{
		int x = qx.front(), y = qy.front(), s = qs.front(), State = qState.front();
		qx.pop(), qy.pop(), qs.pop(), qState.pop();
		if (x == n && y == m) {ans = s; printf("%d\n", ans); return ;}
		for (int i = 0; i < 4; ++i)
		{
			int tx = x + Next[i][0], ty = y + Next[i][1];
			int ts = s + 1, tState = State;
			if (tx < 1 || ty < 1 || tx > n || ty > m) continue ;
			if (Door[x][y][i] != -1)
			{
				if (Door[x][y][i] == 0) continue ;
				else if (!(State & (1 << Door[x][y][i]))) continue ;
			}
			for (int j = 0; j < Key[tx][ty].size(); ++j) tState |= (1 << Key[tx][ty][j]);
			if (book[tx][ty][tState]) continue ;
			book[tx][ty][tState] = 1;
			qx.push(tx), qy.push(ty), qs.push(ts), qState.push(tState);
		}
	}
	printf("-1\n"); return ;
}

int main()
{
	n = read(), m = read(), p = read(), k = read();
	memset(Door, -1, sizeof(Door));
	for (int i = 1; i <= k; ++i)
	{
		int r1 = read(), c1 = read(), r2 = read(), c2 = read(), g = read();
		if (r1 > r2) std::swap(r1, r2), std::swap(c1, c2);
		if (c1 > c2) std::swap(r1, r2), std::swap(c1, c2);
		if (r1 < r2) Door[r1][c1][1] = Door[r2][c2][3] = g;
		else Door[r1][c1][0] = Door[r2][c2][2] = g;
	}
	s = read();
	for (int i = 1; i <= s; ++i)
	{
		int x = read(), y = read(), g = read();
		Key[x][y].push_back(g);
	}
	bfs(); return 0;
}
