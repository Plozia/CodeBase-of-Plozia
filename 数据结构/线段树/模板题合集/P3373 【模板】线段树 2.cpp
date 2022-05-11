#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
typedef long long LL;
int n, m, P;
LL a[MAXN];
struct node
{
	int l, r;
	LL mul, add, sum;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define m(p) tree[p].mul
	#define a(p) tree[p].add
	#define s(p) tree[p].sum
}tree[MAXN << 2];

LL read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void build(int p, int l, int r)
{
	l(p) = l, r(p) = r, m(p) = 1;
	if (l == r) {s(p) = a[l] % P; return ;}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	s(p) = (s(p << 1) + s(p << 1 | 1)) % P;
}

void spread(int p)
{
	s(p << 1) = (s(p << 1) * m(p) + a(p) * (r(p << 1) - l(p << 1) + 1)) % P;
	s(p << 1 | 1) = (s(p << 1 | 1) * m(p) + a(p) * (r(p << 1 | 1) - l(p << 1 | 1) + 1)) % P;
	m(p << 1) = m(p << 1) * m(p) % P; m(p << 1 | 1) = m(p << 1 | 1) * m(p) % P;
	a(p << 1) = (a(p << 1) * m(p) + a(p)) % P; a(p << 1 | 1) = (a(p << 1 | 1) * m(p) + a(p)) % P;
	m(p) = 1; a(p) = 0;
}

void mul(int p, int l, int r, LL k)
{
	if (l(p) >= l && r(p) <= r) {s(p) = s(p) * k % P; m(p) = m(p) * k % P; a(p) = a(p) * k % P; return ;}
	spread(p);
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid) mul(p << 1, l, r, k);
	if (r > mid) mul(p << 1 | 1, l, r, k);
	s(p) = (s(p << 1) + s(p << 1 | 1)) % P;
}

void add(int p, int l, int r, LL k)
{
	if (l(p) >= l && r(p) <= r) {s(p) = (s(p) + k * (r(p) - l(p) + 1)) % P; a(p) = (a(p) + k) % P; return ;}
	spread(p);
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid) add(p << 1, l, r, k);
	if (r > mid) add(p << 1 | 1, l, r, k);
	s(p) = (s(p << 1) + s(p << 1 | 1)) % P;
}

LL ask(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return s(p);
	spread(p);
	int mid = (l(p) + r(p)) >> 1; LL val = 0;
	if (l <= mid) val += ask(p << 1, l, r);
	if (r > mid) val += ask(p << 1 | 1, l, r);
	return val % P;
}

int main()
{
	n = read(); m = read(); P = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	build(1, 1, n); 
	for (int i = 1; i <= m; ++i)
	{
		int opt = read();
		if (opt == 1)
		{
			int l = read(), r = read(); LL k = read();
			mul(1, l, r, k);
		}
		else if (opt == 2)
		{
			int l = read(), r = read(); LL k = read();
			add(1, l, r, k);
		}
		else
		{
			int l = read(), r = read();
			printf ("%lld\n", ask(1, l, r) % P);
		}
	}
	return 0;
}
