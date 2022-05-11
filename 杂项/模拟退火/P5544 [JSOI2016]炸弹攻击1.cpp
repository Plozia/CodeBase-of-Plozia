/*
========= Plozia =========
	Author:Plozia
	Problem:P5544 [JSOI2016]炸弹攻击1
	Date:2022/1/28
========= Plozia =========
*/

#include <bits/stdc++.h>
std::mt19937 rng(std::random_device{}());

typedef long long LL;
const int MAXN = 1e3 + 5;
int n, m, ans, sum;
double ansx, ansy, sx, sy, r, StartTime;
struct node { double x, y, r; } Building[15];
struct node2 { double x, y; } Enemy[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void Calc()
{

}

void SA()
{
	sx = ansx; sy = ansy;
	for (double t0 = 4514; t0 >= 1e-14; t0 *= 0.995)
	{
		if ((clock() - StartTime) / CLOCKS_PER_SEC > 0.9) { printf("%d\n", ans); exit(0); }
		unsigned int u = rng() % 20000;
		sx = sx + (int)u % 20000 * t0;
		sy = sy + (int)u % 20000 * t0;
		Calc();
	}
}

int main()
{
	StartTime = clock(); n = Read(), m = Read(), r = Read();
	for (int i = 1; i <= n; ++i) Building[i].x = Read(), Building[i].y = Read(), Building[i].r = Read();
	for (int i = 1; i <= m; ++i) ansx += (Enemy[i].x = Read()), ansy += (Enemy[i].y = Read());
	sx = ansx / m, sy = ansy / m; Calc(); ans = sum;
	for (; ; ) SA();
}