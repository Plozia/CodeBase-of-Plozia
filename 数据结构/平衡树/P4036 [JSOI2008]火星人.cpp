/*
========= Plozia =========
	Author:Plozia
	Problem:P4036 [JSOI2008]火星人
	Date:2022/1/2
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef unsigned long long ull;
const int MAXN = 1.5e5 + 5;
const int Base = 131;
int n, q, Root, cnt_node;
ull BasePow[MAXN];
char str[MAXN];
struct node
{
	int l, r, Size, val, Key;
	ull Hash;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define Size(p) tree[p].Size
	#define val(p) tree[p].val
	#define Key(p) tree[p].Key
	#define Hash(p) tree[p].Hash
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

int Make_Node(int val)
{
	int p = ++cnt_node; l(p) = r(p) = 0;
	Key(p) = rand(); Size(p) = 1; val(p) = val;
	Hash(p) = val; return p;
}

void Update(int p)
{
	Hash(p) = Hash(l(p)) * BasePow[Size(r(p)) + 1] + val(p) * BasePow[Size(r(p))] + Hash(r(p));
	Size(p) = Size(l(p)) + Size(r(p)) + 1;
}

void Split(int now, int val, int &x, int &y)
{
	if (now == 0) { x = y = 0; return ; }
	if (Size(l(now)) + 1 <= val) { x = now; Split(r(now), val - Size(l(now)) - 1, r(x), y); }
	else { y = now; Split(l(now), val, x, l(y)); }
	Update(now);
}

int Merge(int x, int y)
{
	if (!x || !y) return x + y;
	if (Key(x) < Key(y)) { r(x) = Merge(r(x), y); Update(x); return x; }
	else { l(y) = Merge(x, l(y)); Update(y); return y; }
}

int Build(int l, int r)
{
	if (l == r) return Make_Node(str[l]);
	int mid = (l + r) >> 1, x = Build(l, mid), y = Build(mid + 1, r);
	return Merge(x, y);
}

ull LCQ(int s, int len)
{
	int x, y, z; Split(Root, s - 1, x, y);
	Split(y, len, y, z); ull ans = Hash(y);
	Root = Merge(Merge(x, y), z); return ans;
}

void Ask()
{
	int x = Read(), y = Read();
	if (x < y) std::swap(x, y);
	int l = 1, r = cnt_node - y + 1, ans = 0;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (LCQ(x, mid) == LCQ(y, mid)) { ans = mid; l = mid + 1; }
		else r = mid - 1;
	}
	printf("%d\n", ans);
}

void Change()
{
	int len = Read(); char ch; std::cin >> ch;
	int x, y, z; Split(Root, len - 1, x, y);
	Split(y, 1, y, z); val(y) = Hash(y) = ch;
	Root = Merge(Merge(x, y), z);
}

void Insert()
{
	int len = Read(); char ch; std::cin >> ch;
	int x, y; Split(Root, len, x, y);
	Root = Merge(Merge(x, Make_Node(ch)), y);
}

int main()
{
	scanf("%s", str + 1); q = Read();
	n = strlen(str + 1); BasePow[0] = 1;
	for (int i = 1; i <= 150000; ++i) BasePow[i] = BasePow[i - 1] * Base;
	Root = Build(1, n);
	while (q--)
	{
		char ch; std::cin >> ch;
		if (ch == 'Q') Ask();
		else if (ch == 'R') Change();
		else Insert();
	}
	return 0;
}