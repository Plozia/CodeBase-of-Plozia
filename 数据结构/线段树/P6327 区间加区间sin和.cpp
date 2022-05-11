#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 2e5 + 10;
int n, a[MAXN], m;
struct node
{
	int l, r;
	LL add;
	double Sin, Cos;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].Sin
	#define c(p) tree[p].Cos
	#define a(p) tree[p].add
}tree[MAXN << 2];

int read()
{
	int sum = 0; char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum;
}

void build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) {s(p) = sin(a[l]), c(p) = cos(a[l]); return ;}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	s(p) = s(p << 1) + s(p << 1 | 1);
	c(p) = c(p << 1) + c(p << 1 | 1);
}

void spread(int p)
{
	if (a(p))
	{
		double s = s(p << 1), c = c(p << 1);
		s(p << 1) = s * cos(a(p)) + c * sin(a(p));
		c(p << 1) = c * cos(a(p)) - s * sin(a(p));
		s = s(p << 1 | 1), c = c(p << 1 | 1);
		s(p << 1 | 1) = s * cos(a(p)) + c * sin(a(p));
		c(p << 1 | 1) = c * cos(a(p)) - s * sin(a(p));
		a(p << 1) += a(p), a(p << 1 | 1) += a(p); a(p) = 0;
	}
}

void change(int p, int l, int r, int val)
{
	if (l(p) >= l && r(p) <= r)
	{
		double s = s(p), c = c(p);
		s(p) = s * cos(val) + c * sin(val);
		c(p) = c * cos(val) - s * sin(val);
		a(p) += val; return ;
	}
	spread(p);
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid) change(p << 1, l, r, val);
	if (r > mid) change(p << 1 | 1, l, r, val);
	s(p) = s(p << 1) + s(p << 1 | 1);
	c(p) = c(p << 1) + c(p << 1 | 1);
}

double ask(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return s(p);
	spread(p);
	int mid = (l(p) + r(p)) >> 1; double val = 0;
	if (l <= mid) val += ask(p << 1, l, r);
	if (r > mid) val += ask(p << 1 | 1, l, r);
	return val;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	build(1, 1, n);
	m = read();
	for (int i = 1; i <= m; ++i)
	{
		int opt = read();
		if (opt == 1)
		{
			int l = read(), r = read(), val = read();
			change(1, l, r, val);
		}
		else
		{
			int l = read(), r = read();
			printf("%.1lf\n", ask(1, l, r));
		}
	}
	return 0;
}
