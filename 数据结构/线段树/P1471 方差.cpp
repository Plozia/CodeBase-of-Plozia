/*
========= Plozia =========
	Author:Plozia
	Problem:P1471 方差
	Date:2022/1/2
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, q;
double a[MAXN];
struct node
{
	int l, r;
	double sum1, sum2, add;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define sum1(p) tree[p].sum1
	#define sum2(p) tree[p].sum2
	#define add(p) tree[p].add
}tree[MAXN << 2];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
void Update(int p)
{
	sum1(p) = sum1(p << 1) + sum1(p << 1 | 1);
	sum2(p) = sum2(p << 1) + sum2(p << 1 | 1);
}

void Build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) { sum1(p) = a[l]; sum2(p) = 1ll * a[l] * a[l]; return ; }
	int mid = (l + r) >> 1; Build(p << 1, l, mid); Build(p << 1 | 1, mid + 1, r);
	Update(p);
}

void Spread(int p)
{
	if (add(p) != 0)
	{
		sum2(p << 1) += 2 * add(p) * sum1(p << 1) + add(p) * add(p) * (r(p << 1) - l(p << 1) + 1);
		sum1(p << 1) += add(p) * (r(p << 1) - l(p << 1) + 1); add(p << 1) += add(p);
		sum2(p << 1 | 1) += 2 * add(p) * sum1(p << 1 | 1) + add(p) * add(p) * (r(p << 1 | 1) - l(p << 1 | 1) + 1);
		sum1(p << 1 | 1) += add(p) * (r(p << 1 | 1) - l (p << 1 | 1) + 1); add(p << 1 | 1) += add(p);
		add(p) = 0.0;
	}
}

void Add(int p, int l, int r, double k)
{
	if (l(p) >= l && r(p) <= r)
	{
		sum2(p) += 2 * k * sum1(p) + k * k * (r(p) - l(p) + 1);
		sum1(p) += k * (r(p) - l(p) + 1); add(p) += k;
		return ;
	}
	Spread(p); int mid = (l(p) + r(p)) >> 1;
	if (l <= mid) Add(p << 1, l, r, k);
	if (r > mid) Add(p << 1 | 1, l, r, k);
	Update(p);
}

double Ask1(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return sum1(p);
	Spread(p); int mid = (l(p) + r(p)) >> 1; double val = 0.0;
	if (l <= mid) val += Ask1(p << 1, l, r);
	if (r > mid) val += Ask1(p << 1 | 1, l, r);
	return val;
}

double Ask2(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return sum2(p);
	Spread(p); int mid = (l(p) + r(p)) >> 1; double val = 0.0;
	if (l <= mid) val += Ask2(p << 1, l, r);
	if (r > mid) val += Ask2(p << 1 | 1, l, r);
	return val;
}

int main()
{
	n = Read(), q = Read();
	for (int i = 1; i <= n; ++i) std::cin >> a[i];
	Build(1, 1, n);
	while (q--)
	{
		int opt = Read();
		if (opt == 1) { int x = Read(), y = Read(); double k; std::cin >> k; Add(1, x, y, k); }
		else if (opt == 2)
		{
			int x = Read(), y = Read();
			printf("%.4lf\n", Ask1(1, x, y) / (y - x + 1));
		}
		else
		{
			int x = Read(), y = Read(); double t1 = Ask1(1, x, y), t2 = Ask2(1, x, y);
			printf("%.4lf\n", (t2 - 2 * t1 * t1 / (y - x + 1) + t1 / (y - x + 1) * t1) / (y - x + 1));
		}
	}
	return 0;
}