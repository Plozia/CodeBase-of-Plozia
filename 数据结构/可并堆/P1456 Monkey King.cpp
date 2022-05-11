/*
========= Plozia =========
	Author:Plozia
	Problem:P1456 Monkey King
	Date:2021/9/28
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, m, cnt, ys[MAXN];
struct node
{
	int Son[2], val, Root, dis;
}lt[MAXN << 2];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int gf(int x) { return (lt[x].Root == x) ? x : (lt[x].Root = gf(lt[x].Root)); }

int Merge(int x, int y)
{
	if (!x || !y) return x + y;
	if (lt[x].val < lt[y].val) std::swap(x, y);
	lt[x].Son[1] = Merge(lt[x].Son[1], y);
	if (lt[lt[x].Son[0]].dis < lt[lt[x].Son[1]].dis) std::swap(lt[x].Son[0], lt[x].Son[1]);
	lt[x].dis = lt[lt[x].Son[1]].dis + 1; lt[x].Root = lt[lt[x].Son[0]].Root = lt[lt[x].Son[1]].Root = x; return x;
}

void Pop(int x)
{
	node tmp = (node){{0, 0}, lt[x].val >> 1, x, 0};
	lt[x].val = -1; int fir = lt[x].Son[0], sec = lt[x].Son[1];
	lt[lt[x].Son[0]].Root = lt[x].Son[0];
	lt[lt[x].Son[1]].Root = lt[x].Son[1];
	lt[x].Root = Merge(lt[x].Son[0], lt[x].Son[1]);
	lt[x] = tmp;
	lt[x].Root = Merge(((gf(fir) == fir) ? fir : sec), x);
}

int main()
{
	while (scanf("%d %d", &n, &m) == 2)
	{
		lt[0].dis = -1; cnt = n;
		for (int i = 1; i <= n; ++i)
			lt[i].val = Read(), lt[i].Root = i, lt[i].Son[0] = lt[i].Son[1] = lt[i].dis = 0, ys[i] = i;
		for (int i = 1; i <= m; ++i)
		{
			int x = Read(), y = Read();
			if (gf(ys[x]) == gf(ys[y])) puts("-1");
			else
			{
				Pop(gf(ys[x])); Pop(gf(ys[y]));
				printf("%d\n", lt[gf(ys[x])].val);
			}
		}
	}
	return 0;
}