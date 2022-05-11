#include <bits/stdc++.h>
#define Max(a, b) ((a > b) ? a : b)
#define Min(a, b) ((a < b) ? a : b)
using namespace std;

const int MAXN = 1e5 + 10;
typedef long long LL;
int n;
struct node
{
	int l, r, maxn, minn;
	LL sumw, sumc;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define maxn(p) tree[p].maxn
	#define minn(p) tree[p].minn
	#define sumw(p) tree[p].sumw
	#define sumc(p) tree[p].sumc
}tree[MAXN << 2];
bool book[(MAXN << 3) + (MAXN << 1)];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) {sumw(p) = sumc(p) = maxn(p) = 0; minn(p) = 0x7f7f7f7f; return ;}
	int mid = (l(p) + r(p)) >> 1;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	sumw(p) = sumc(p) = maxn(p) = 0; minn(p) = 0x7f7f7f7f;
}

void change(int p, int l, int r, int w, int c)
{
	if (book[c]) return ;
	if (l(p) >= l && r(p) <= r)
	{
		sumw(p) += w;
		sumc(p) += c;
		maxn(p) = Max(maxn(p), c);
		minn(p) = Min(minn(p), c);
		book[c] = 1;
		return ;
	}
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid) change(p << 1, l, r, w, c);
	if (r > mid) change(p << 1 | 1, l, r, w, c);
	sumw(p) = sumw(p << 1) + sumw(p << 1 | 1);
	sumc(p) = sumc(p << 1) + sumc(p << 1 | 1);
	maxn(p) = Max(maxn(p << 1), maxn(p << 1 | 1));
	minn(p) = Min(minn(p << 1), minn(p << 1 | 1));
}

void Delete_the_cheapest(int p)
{
	if (l(p) == r(p))
	{
		book[sumc(p)] = 0;
		sumw(p) = sumc(p) = 0;
		maxn(p) = 0; minn(p) = 0x7f7f7f7f;
		return ;
	}
	if (minn(p) == 0x7f7f7f7f) return ;
	if (minn(p << 1) == minn(p)) Delete_the_cheapest(p << 1);
	else Delete_the_cheapest(p << 1 | 1);
	sumw(p) = sumw(p << 1) + sumw(p << 1 | 1);
	sumc(p) = sumc(p << 1) + sumc(p << 1 | 1);
	maxn(p) = Max(maxn(p << 1), maxn(p << 1 | 1));
	minn(p) = Min(minn(p << 1), minn(p << 1 | 1));
}

void Delete_the_most_expensive(int p)
{
	if (l(p) == r(p))
	{
		book[sumc(p)] = 0;
		sumw(p) = sumc(p) = 0;
		maxn(p) = 0; minn(p) = 0x7f7f7f7f;
		return ;
	}
	if (maxn(p) == 0) return ;
	if (maxn(p << 1) == maxn(p)) Delete_the_most_expensive(p << 1);
	else Delete_the_most_expensive(p << 1 | 1);
	sumw(p) = sumw(p << 1) + sumw(p << 1 | 1);
	sumc(p) = sumc(p << 1) + sumc(p << 1 | 1);
	maxn(p) = Max(maxn(p << 1), maxn(p << 1 | 1));
	minn(p) = Min(minn(p << 1), minn(p << 1 | 1));
}

int main()
{
	build(1, 1, 100000);
	while (1)
	{
		int opt = read();
		if (opt == -1) break;
		if (opt == 1)
		{
			int w = read(), c = read();
			++n; change(1, n, n, w, c);
		}
		if (opt == 3) Delete_the_cheapest(1);
		if (opt == 2) Delete_the_most_expensive(1);
		//附录：我劝送花这道题的出题人耗子尾汁，耗耗反思，不要搞这种小聪明
	}
	printf("%lld %lld\n", tree[1].sumw, tree[1].sumc);
	return 0;
}
