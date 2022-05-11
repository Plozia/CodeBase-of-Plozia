/*
========= Plozia =========
	Author:Plozia
	Problem:P4254 [JSOI2008]Blue Mary开公司
	Date:2022/1/8
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
typedef double db;
const int MAXN = 1e5 + 5;
int q, cntn;
char str[20];
db k[MAXN], b[MAXN];
struct node
{
	int l, r, tag;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define tag(p) tree[p].tag
}tree[MAXN << 2];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
db Max(db fir, db sec) { return (fir > sec) ? fir : sec; }
db Min(db fir, db sec) { return (fir < sec) ? fir : sec; }
db Calc(int p, db x) { return k[p] * (x - 1) + b[p]; }

void Build(int p, int l, int r)
{
	l(p) = l, r(p) = r; if (l == r) return ;
	int mid = (l + r) >> 1; Build(p << 1, l, mid); Build(p << 1 | 1, mid + 1, r);
	return ;
}

void Change(int p, int Num)
{
	if (l(p) == r(p))
	{
		if (Calc(tag(p), l(p)) < Calc(Num, l(p))) { tag(p) = Num; }
		return ;
	}
	int mid = (l(p) + r(p)) >> 1;
	if (tag(p) == 0) { tag(p) = Num; return ;}
	double s1 = Calc(tag(p), mid), s2 = Calc(Num, mid);
	if (k[tag(p)] < k[Num])
	{
		if (s1 <= s2) { Change(p << 1, tag(p)); tag(p) = Num; }
		else Change(p << 1 | 1, Num);
	}
	else if (k[tag(p)] > k[Num])
	{
		if (s1 <= s2) { Change(p << 1 | 1, tag(p)); tag(p) = Num; }
		else Change(p << 1, Num);
	}
	else if (b[tag(p)] < b[Num]) tag(p) = Num;
}

db Ask(int p, int x)
{
	if (l(p) == r(p)) return Calc(tag(p), x);
	int mid = (l(p) + r(p)) >> 1;
	if (x <= mid) return Max(Ask(p << 1, x), Calc(tag(p), x));
	else return Max(Ask(p << 1 | 1, x), Calc(tag(p), x));
}

int main()
{
	Build(1, 1, 50000); q = Read();
	while (q--)
	{
		scanf("%s", str + 1);
		if (str[1] == 'P')
		{
			++cntn; scanf("%lf %lf", &b[cntn], &k[cntn]);
			Change(1, cntn);
		}
		else
		{
			int t = Read(); db ans = Ask(1, t);
			if (cntn == 0) printf("0\n");
			else printf("%d\n", (int)ans / 100);
		}
	}
	return 0;
}