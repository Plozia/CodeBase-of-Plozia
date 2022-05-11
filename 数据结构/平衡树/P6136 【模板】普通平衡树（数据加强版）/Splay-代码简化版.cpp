#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 1e6 + 1e5 + 10;
int n, m, lastans, ans, cnt, root;
struct node
{
	int ch[2], fa, size, cnt, val;
}tree[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void update(int x) {tree[x].size = tree[tree[x].ch[0]].size + tree[tree[x].ch[1]].size + tree[x].cnt;}
bool rson(int x, int f) {return (tree[f].ch[1] == x) ? 1 : 0;}
void connect(int x, int y, int f)
{
	tree[y].ch[f] = x;
	tree[x].fa = y;
}

void rotate(int x)
{
	int f = tree[x].fa, gf = tree[f].fa, k = rson(x, f);
	connect(tree[x].ch[k ^ 1], f, k);
	connect(x, gf, rson(f, gf));
	connect(f, x, k ^ 1);
	update(f), update(x);
}
void Splay(int now, int target)
{
	if (!target) root = now;
	while (tree[now].fa != target)
	{
		int f = tree[now].fa, gf = tree[f].fa;
		if (gf == target) {rotate(now); return ;}
		if (rson(now, f) == rson(f, gf)) rotate(f);
		else rotate(now);
		rotate(now);
	}
}

void Make_Node(int &now, int val, int f)
{
	now = ++cnt;
	tree[now].size = tree[now].cnt = 1;
	tree[now].val = val; tree[now].fa = f;
}

void Insert(int val, int &now = root, int f = 0)
{
	if (now == 0) Make_Node(now, val, f), Splay(now, 0);
	else if (tree[now].val < val) Insert(val, tree[now].ch[1], now);
	else if (tree[now].val > val) Insert(val, tree[now].ch[0], now);
	else tree[now].cnt++, Splay(now, 0);
}

void del(int now)
{
	Splay(now, 0);
	if (tree[now].cnt > 1) tree[now].cnt--, tree[now].size--;
	else if (tree[now].ch[1])
	{
		int o = tree[now].ch[1];
		while (tree[o].ch[0]) o = tree[o].ch[0];
		Splay(o, now);
		connect(tree[now].ch[0], o, 0);
		root = o; tree[o].fa = 0;
		update(root);
	}
	else root = tree[now].ch[0], tree[root].fa = 0;
}

void Delete(int val, int now)
{
	if (val == tree[now].val) del(now);
	else if (tree[now].val < val) Delete(val, tree[now].ch[1]);
	else Delete(val, tree[now].ch[0]);
}

int Find_Rank(int val)
{
	int ans = 1, now = root;
	while (now)
	{
		if (tree[now].val == val) {ans += tree[tree[now].ch[0]].size; Splay(now, 0); break;}
		if (tree[now].val >= val) now = tree[now].ch[0];
		else {ans += tree[tree[now].ch[0]].size + tree[now].cnt; now = tree[now].ch[1];}
	}
	return ans;
}

int Find_kth(int val)
{
	int ans, now = root;
	while (now)
	{
		if (tree[tree[now].ch[0]].size < val && tree[tree[now].ch[0]].size + tree[now].cnt >= val) break;
		if (tree[tree[now].ch[0]].size >= val) now = tree[now].ch[0];
		else {val -= tree[tree[now].ch[0]].size + tree[now].cnt; now = tree[now].ch[1];}
	}
	ans = tree[now].val;
	Splay(now, 0);
	return ans;
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) Insert(read(), root);
	for (int i = 1; i <= m; ++i)
	{
		int opt = read(), x = read() ^ lastans;
		switch(opt)
		{
			case 1:
				Insert(x, root); break;
			case 2:
				Delete(x, root); break;
			case 3:
			{
				int t = Find_Rank(x);
				ans ^= t; lastans = t; break;
			}
			case 4:
			{
				int t = Find_kth(x);
				ans ^= t; lastans = t; break;
			}
			case 5:
			{
				int t = Find_kth(Find_Rank(x) - 1);
				ans ^= t; lastans = t; break;
			}
			case 6:
			{
				int t = Find_kth(Find_Rank(x + 1));
				ans ^= t; lastans = t; break;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
