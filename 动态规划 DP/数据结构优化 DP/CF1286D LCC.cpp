/*
========= Plozia =========
	Author:Plozia
	Problem:CF1286D LCC
	Date:2021/6/15
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 10;
const LL P = 998244353;
int n, cnta;
LL x[MAXN], v[MAXN], pro[MAXN][2], ans, ys[MAXN], inv;
bool book[MAXN][2][2];

struct node
{
	int u, d1, d2;
	LL x, v;
}a[MAXN << 1];

struct node2
{
	int l, r;
	LL p[2][2];
}tree[MAXN << 2];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
LL ksm(LL aa, LL bb, LL P)
{
	LL ans = 1 % P;
	for (; bb; bb >>= 1, aa = aa * aa % P)
		if (bb & 1) ans = ans * aa % P;
	return ans;
}
bool cmp(const node &fir, const node &sec) { return (fir.x * sec.v) < (sec.x * fir.v); }
//这里不推荐直接使用 double 除，可能会失精度。

void Update(int p)
{
	int mid = (tree[p].l + tree[p].r) >> 1;
	for (int firx = 0; firx < 2; ++firx)
		for (int firy = 0; firy < 2; ++firy)
		{
			tree[p].p[firx][firy] = 0;
			for (int secx = 0; secx < 2; ++secx)
				for (int secy = 0; secy < 2; ++secy)
					if (!book[mid][secx][secy]) ((tree[p].p[firx][firy] += tree[p << 1].p[firx][secx] * tree[p << 1 | 1].p[secy][firy] % P) >= P) ? (tree[p].p[firx][firy] %= P) : 0;
		}
}

void build(int p, int l, int r)
{
	tree[p].l = l, tree[p].r = r;
	if (l == r) { tree[p].p[0][0] = pro[l][0]; tree[p].p[1][1] = pro[l][1]; return ; }
	int mid = (l + r) >> 1; ys[mid] = p;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	Update(p);
}

int main()
{
	n = Read(); inv = ksm(100, P - 2, P);//注意这里的 inv 一定要开 long long！
	for (int i = 1; i <= n; ++i)
	{
		x[i] = Read(), v[i] = Read();
		pro[i][1] = Read() * inv % P;
		pro[i][0] = (1 - pro[i][1] + P) % P;
		//小心，题目中是输入向右边走的概率
	}
	for (int i = 1; i < n; ++i)
	{
		++cnta; a[cnta] = (node){i, 1, 0, x[i + 1] - x[i], v[i + 1] + v[i]};
		if (v[i] > v[i + 1]) { ++cnta; a[cnta] = (node){i, 1, 1, x[i + 1] - x[i], v[i] - v[i + 1]}; }
		else if (v[i] < v[i + 1]) { ++cnta; a[cnta] = (node){i, 0, 0, x[i + 1] - x[i], v[i + 1] - v[i]}; }
	}
	std::sort(a + 1, a + cnta + 1, cmp); build(1, 1, n);
	LL Last = 1;
	for (int i = 1; i <= cnta; ++i)
	{
		book[a[i].u][a[i].d1][a[i].d2] = 1;
		for (int j = ys[a[i].u]; j; j >>= 1) Update(j);
		LL now = (tree[1].p[0][0] + tree[1].p[1][0] + tree[1].p[0][1] + tree[1].p[1][1]) % P;
		((ans += a[i].x * ksm(a[i].v, P - 2, P) % P * (Last - now + P) % P) >= P) ? (ans %= P) : 0;
		//第 i 次碰撞的概率 = 前 i - 1 次不碰撞的概率 - 前 i 次不碰撞的概率
		//注意随时取模，可能你 WA 了就是在某个你不注意的地方没有取模
		Last = now;
	}
	printf("%lld\n", ans); return 0;
}