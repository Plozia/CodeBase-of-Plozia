/*
========= Plozia =========
	Author:Plozia
	Problem:P5482 [JLOI2011]不等式组
	Date:2021/12/30
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::string;

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, cnt, Right;
struct node
{
	int a, b, c, x, t;
	bool flag;
}s[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

struct FHQ_Treap
{
	int cnt_Node = 0, Root = 0;
	struct Tree
	{
		int l, r, val, Key, Size;
		#define l(p) tree[p].l
		#define r(p) tree[p].r
		#define val(p) tree[p].val
		#define Key(p) tree[p].Key
		#define Size(p) tree[p].Size
	}tree[MAXN];
	void Update(int p) { Size(p) = Size(l(p)) + Size(r(p)) + 1; }
	int Make_Node(int val)
	{
		int p = ++cnt_Node;
		l(p) = r(p) = 0; val(p) = val; Size(p) = 1;
		Key(p) = rand(); return p;
	}
	void Split(int now, int val, int &x, int &y)
	{
		if (!now) { x = y = 0; return ; }
		if (val(now) <= val) { x = now; Split(r(now), val, r(x), y); }
		else { y = now; Split(l(now), val, x, l(y)); }
		Update(now);
	}
	int Merge(int x, int y)
	{
		if (!x || !y) return x + y;
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
	void Insert(int val)
	{
		int x, y; Split(Root, val, x, y);
		Root = Merge(Merge(x, Make_Node(val)), y);
	}
	void Delete(int val)
	{
		int x, y, z; Split(Root, val, y, z);
		Split(y, val - 1, x, y);
		y = Merge(l(y), r(y)); Root = Merge(Merge(x, y), z);
	}
	int Find_Rank(int val, int opt)
	{
		int x, y, ans;
		if (opt == 1)
		{
			Split(Root, val, x, y);
			ans = Size(x); Root = Merge(x, y);
		}
		else
		{
			Split(Root, val - 1, x, y);
			ans = Size(y); Root = Merge(x, y);
		}
		return ans;
	}
}s1, s2;

int main()
{
	n = Read();
	for (int i = 1; i <= n; ++i)
	{
		string str; std::cin >> str;
		if (str == "Add")
		{
			++cnt; s[cnt].a = Read(); s[cnt].b = Read(); s[cnt].c = Read(); s[cnt].flag = 1;
			if (s[cnt].a == 0)
			{
				if (s[cnt].b > s[cnt].c) ++Right, s[cnt].t = 0;
				else s[cnt].t = -2;
			}
			else if (s[cnt].a > 0)
			{
				s[cnt].x = floor((1.0 * s[cnt].c - s[cnt].b) / s[cnt].a) + 1;
				s1.Insert(s[cnt].x); s[cnt].t = 1;
				// x > c - b / a
			}
			else
			{
				s[cnt].x = ceil((1.0 * s[cnt].c - s[cnt].b) / s[cnt].a) - 1;
				s2.Insert(s[cnt].x); s[cnt].t = -1;
				// x < c - b / a
			}
		}
		else if (str == "Query")
		{
			int x = Read(), ans = Right;
			ans += s1.Find_Rank(x, 1) + s2.Find_Rank(x, 2);
			printf("%d\n", ans);
		}
		else if (str == "Del")
		{
			int x = Read();
			if (!s[x].flag) continue ;
			s[x].flag = 0;
			if (s[x].t == 0) --Right;
			else if (s[x].t == 1) s1.Delete(s[x].x);
			else if (s[x].t == -1) s2.Delete(s[x].x);
		}
	}
	return 0;
}