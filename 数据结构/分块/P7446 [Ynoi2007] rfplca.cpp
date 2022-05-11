/*
========= Plozia =========
	Author:Plozia
	Problem:P7446 [Ynoi2007] rfplca
	Date:2021/11/26
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 4e5 + 5;
int n, q, fa[MAXN], tag[MAXN], ys[MAXN], Left[MAXN], Right[MAXN], Block, Lastans, Top[MAXN];
bool book[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int gf(int p) { return Max(fa[p] - tag[ys[p]], 1);}

void Rebuild(int now)
{
	book[now] = 1;
	for (int i = Left[now]; i <= Right[now]; ++i)
	{
		Top[i] = (gf(i) >= Left[now]) ? Top[gf(i)] : i;
		if (Top[i] != i) book[now] = 0;
	}
}

int Ask(int l, int r)
{
	if (l == 1 || r == 1) return 1;
	while (Top[l] != Top[r])
	{
		if (l < r) std::swap(l, r);
		l = gf(Top[l]);
	}
	while (l != r)
	{
		if (l < r) std::swap(l, r);
		l = gf(l);
	}
	return l;
}

int main()
{
	n = Read(), q = Read(); Block = sqrt(n);
	for (int i = 2; i <= n; ++i) fa[i] = Read();
	// 这道题貌似 id = 1 要单独分一个块不然会出事
	// 一开始没注意这点然后就…… /fn
	ys[1] = Left[1] = Right[1] = 1;
	for (int i = 2; ; ++i)
	{
		Left[i] = Right[i - 1] + 1;
		Right[i] = Left[i] + Block - 1;
		if (Right[i] > n) { Right[i] = n; book[0] = 1; }
		for (int j = Left[i]; j <= Right[i]; ++j) ys[j] = i;
		Rebuild(i); if (book[0]) break ;
	}
	while (q--)
	{
		int opt = Read();
		if (opt == 1)
		{
			int l = Read() ^ Lastans, r = Read() ^ Lastans, x = Read() ^ Lastans;
			if (l > r) std::swap(l, r);
			if (ys[l] == ys[r])
			{
				for (int i = l; i <= r; ++i) fa[i] = Max(fa[i] - x, 1);
				Rebuild(ys[l]);
			}
			else
			{
				for (int i = l; i <= Right[ys[l]]; ++i) fa[i] = Max(fa[i] - x, 1);
				Rebuild(ys[l]);
				for (int i = Left[ys[r]]; i <= r; ++i) fa[i] = Max(fa[i] - x, 1);
				Rebuild(ys[r]);
				for (int i = ys[l] + 1; i < ys[r]; ++i)
				{
					tag[i] = Min(tag[i] + x, n);
					if (!book[i]) Rebuild(i);
				}
			}
		}
		else
		{
			int l = Read() ^ Lastans, r = Read() ^ Lastans;
			printf("%d\n", Lastans = Ask(l, r));
		}
	}
	return 0;
}