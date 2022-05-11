/*
========= Plozia =========
	Author:Plozia
	Problem:P2042 [NOI2005] 维护数列
	Date:2021/12/28
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::stack;
using std::string;

typedef long long LL;
const int MAXN = 5e5 + 5;
int n, q, Root, a[MAXN], cnt_Node;
struct node
{
	int l, r, Size, val, Key;
	int pre, aft, sum, Maxn;
	bool flag, rev;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define Size(p) tree[p].Size
	#define val(p) tree[p].val
	#define Key(p) tree[p].Key
	#define pre(p) tree[p].pre
	#define aft(p) tree[p].aft
	#define sum(p) tree[p].sum
	#define Maxn(p) tree[p].Maxn
	#define flag(p) tree[p].flag
	#define rev(p) tree[p].rev
}tree[MAXN];
stack <int> Rub;

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
	int tmp = 0; if (Rub.empty()) tmp = ++cnt_Node; else { tmp = Rub.top(); Rub.pop(); }
	l(tmp) = r(tmp) = 0; val(tmp) = val; Size(tmp) = 1;
	sum(tmp) = Maxn(tmp) = val; pre(tmp) = aft(tmp) = Max(val, 0);
	flag(tmp) = rev(tmp) = 0; Key(tmp) = rand();
	return tmp;
} // 新建节点

void Cover(int p, int val)
{
	if (!p) return ;
	val(p) = val; sum(p) = Size(p) * val;
	pre(p) = aft(p) = ((val > 0) ? sum(p) : 0);
	Maxn(p) = (val > 0) ? sum(p) : val; flag(p) = 1;
} // 区间推平

void Reverse(int p)
{
	if (!p) return ;
	std::swap(l(p), r(p));
	std::swap(pre(p), aft(p));
	rev(p) ^= 1;
} // 区间反转

void Update(int p)
{
	if (!p) return ;
	Size(p) = Size(l(p)) + Size(r(p)) + 1; sum(p) = sum(l(p)) + sum(r(p)) + val(p);
	pre(p) = Max(pre(l(p)), Max(sum(l(p)) + val(p) + pre(r(p)), 0));
	aft(p) = Max(aft(r(p)), Max(sum(r(p)) + val(p) + aft(l(p)), 0));
	Maxn(p) = Max(val(p), aft(l(p)) + val(p) + pre(r(p)));
	if (l(p)) Maxn(p) = Max(Maxn(p), Maxn(l(p)));
	if (r(p)) Maxn(p) = Max(Maxn(p), Maxn(r(p)));
} // 就是 Pushup

void Spread(int p)
{
	if (!p) return ;
	if (flag(p))
	{
		if (l(p)) Cover(l(p), val(p));
		if (r(p)) Cover(r(p), val(p));
		flag(p) = 0;
	}
	if (rev(p))
	{
		if (l(p)) Reverse(l(p));
		if (r(p)) Reverse(r(p));
		rev(p) = 0;
	}
} // 就是 Pushdown

void Split(int now, int val, int &x, int &y)
{
	if (now == 0) { x = y = 0; return ; }
	Spread(now);
	if (Size(l(now)) + 1 <= val) { x = now; Split(r(now), val - Size(l(now)) - 1, r(now), y); }
	else { y = now; Split(l(now), val, x, l(now)); }
	Update(now);
}

int Merge(int x, int y)
{
	if (!x || !y) return x + y;
	Spread(x); Spread(y);
	if (Key(x) < Key(y))
	{
		r(x) = Merge(r(x), y);
		Update(x); return x;
	}
	else
	{
		l(y) = Merge(x, l(y));
		Update(y); return y;
	}
}

int Build(int l, int r)
{
	if (l == r) return Make_Node(a[l]);
	int mid = (l + r) >> 1;
	int x = Build(l, mid);
	int y = Build(mid + 1, r);
	return Merge(x, y);
} // 递归建树

void Recycle(int p)
{
	Rub.push(p);
	if (l(p)) Recycle(l(p));
	if (r(p)) Recycle(r(p));
} // 垃圾回收

void Insert()
{
	int pos = Read(), len = Read();
	for (int i = 1; i <= len; ++i) a[i] = Read();
	int x, y; Split(Root, pos, x, y);
	Root = Merge(Merge(x, Build(1, len)), y);
}

void Delete()
{
	int pos = Read(), len = Read();
	int x, y, z; Split(Root, pos - 1, x, y);
	Split(y, len, y, z); Root = Merge(x, z); Recycle(y);
}

void Change_Cover()
{
	int pos = Read(), len = Read(), val = Read();
	int x, y, z; Split(Root, pos - 1, x, y);
	Split(y, len, y, z); Cover(y, val);
	Root = Merge(Merge(x, y), z);
}

void Change_Reverse()
{
	int pos = Read(), len = Read();
	int x, y, z; Split(Root, pos - 1, x, y);
	Split(y, len, y, z); Reverse(y);
	Root = Merge(Merge(x, y), z);
}

void Ask_sum()
{
	int pos = Read(), len = Read();
	int x, y, z; Split(Root, pos - 1, x, y);
	Split(y, len, y, z); printf("%d\n", sum(y));
	Root = Merge(Merge(x, y), z);
}

void Ask_Maxn()
{
	printf("%d\n", Maxn(Root));
}

int main()
{
	n = Read(), q = Read(); srand(time(0));
	for (int i = 1; i <= n; ++i) a[i] = Read();
	Root = Build(1, n);
	for (int i = 1; i <= q; ++i)
	{
		string str; std::cin >> str;
		if (str == "INSERT") Insert();
		if (str == "DELETE") Delete();
		if (str == "MAKE-SAME") Change_Cover();
		if (str == "REVERSE") Change_Reverse();
		if (str == "GET-SUM") Ask_sum();
		if (str == "MAX-SUM") Ask_Maxn();
	}
	return 0;
}