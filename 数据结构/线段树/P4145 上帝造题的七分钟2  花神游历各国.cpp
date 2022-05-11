#include <bits/stdc++.h>
#define Max(a, b) ((a > b) ? a : b)
using namespace std;

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, m;
LL a[MAXN];
struct node
{
	int l, r;
	LL sum, maxn;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
	#define m(p) tree[p].maxn
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
	l(p) = l, r(p) = r;
	if(l == r) {s(p) = m(p) = a[l]; return ;}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	s(p) = s(p << 1) + s(p << 1 | 1);
	m(p) = Max(m(p << 1), m(p << 1 | 1));
}

void change(int p, int l, int r)
{
	if (l(p) == r(p)) {s(p) = sqrt(s(p)); m(p) = sqrt(m(p)); return ;}
	if (m(p) == 1) return ;
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid) change(p << 1, l, r);
	if (r > mid) change(p << 1 | 1, l, r);
	s(p) = s(p << 1) + s(p << 1 | 1);
	m(p) = Max(m(p << 1), m(p << 1 | 1));
}

LL ask(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return s(p);
	int mid = (l(p) + r(p)) >> 1; LL val = 0;
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
		int opt = read(), l = read(), r = read();
		if (l > r) swap(l, r);
		if (opt == 0) change(1, l, r);
		else printf("%lld\n", ask(1, l, r));
	}
	return 0;
}
