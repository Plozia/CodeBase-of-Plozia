#include <bits/stdc++.h>
#define Max(a, b) ((a > b) ? a : b)
using namespace std;

typedef long long LL;
const int MAXN = 2e5 + 10;
int n, m, cnt, root;
struct node
{
	int ch[2], val, size, fa;
	int pre, aft, maxn, sum;
}tree[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void update(int now)
{
	tree[now].size = tree[tree[now].ch[0]].size + tree[tree[now].ch[1]].size + 1;
	tree[now].pre = Max(tree[tree[now].ch[0]].pre, Max(tree[tree[now].ch[0]].sum + tree[now].val, tree[tree[now].ch[0]].sum + tree[now].val + tree[tree[now].ch[1]].pre));
	tree[now].aft = Max(tree[tree[now].ch[1]].aft, Max(tree[tree[now].ch[1]].sum + tree[now].val, tree[tree[now].ch[1]].sum + tree[now].val + tree[tree[now].ch[0]].aft));
	tree[now].sum = tree[tree[now].ch[0]].sum + tree[now].val + tree[tree[now].ch[1]].sum;
	tree[now].maxn = Max(Max(tree[tree[now].ch[0]].maxn, tree[tree[now].ch[1]].maxn), Max(Max(tree[tree[now].ch[0]].aft + tree[now].val, tree[tree[now].ch[1]].pre + tree[now].val), tree[tree[now].ch[0]].aft + tree[now].val + tree[tree[now].ch[1]].pre));
}
bool rson(int x, int f) {return tree[f].ch[1] == x;}
void connect(int x, int f, int s)
{
	tree[f].ch[s] = x;
	tree[x].fa = f;
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
	if (target == 0) root = now;
	while (tree[now].fa != target)
	{
		int f = tree[now].fa, gf = tree[f].fa;
		if (gf == target) {rotate(now); return ;}
		if (rson(now, f) == rson(f, gf)) rotate(f);
		else rotate(now);
		rotate(now);
	}
}

void Make_Node(int val, int &now, int f)
{
	now = ++cnt;
	tree[cnt].val = tree[cnt].maxn = tree[cnt].sum = val;
	tree[cnt].pre = tree[cnt].aft = Max(val, 0);
	tree[cnt].fa = f; tree[cnt].size = 1;
}

void Insert(int pos, int val)
{
	//找到 pos - 1 Splay -> root
	int now = root, ans = pos;
	while (now)
	{
		if (tree[tree[now].ch[0]].size + 1 == ans) {Splay(now, 0); break;}
		if (tree[tree[now].ch[0]].size >= ans) {now = tree[now].ch[0];}
		else {ans -= tree[tree[now].ch[0]].size + 1; now = tree[now].ch[1];}
	}
	//找到 pos + 1 Splay -> root.son
	now = root, ans = pos + 1;
	while (now)
	{
		if (tree[tree[now].ch[0]].size + 1 == ans) {Splay(now, root); break;}
		if (tree[tree[now].ch[0]].size >= ans) {now = tree[now].ch[0];}
		else {ans -= tree[tree[now].ch[0]].size + 1; now = tree[now].ch[1];}
	}
	//往 pos + 1 的左子树挂一个节点
	int tag;
	Make_Node(val, tag, tree[root].ch[1]);
	connect(tag, tree[root].ch[1], 0);
	Splay(tag, 0);
}

void Delete(int pos)
{
	//pos - 1 -> root
	int now = root, ans = pos - 1;
	while (now)
	{
		if (tree[tree[now].ch[0]].size + 1 == ans) {Splay(now, 0); break;}
		if (tree[tree[now].ch[0]].size >= ans) {now = tree[now].ch[0];}
		else {ans -= tree[tree[now].ch[0]].size + 1; now = tree[now].ch[1];}
	}
	//pos + 1 -> root.ch
	now = root, ans = pos + 1;
	while (now)
	{
		if (tree[tree[now].ch[0]].size + 1 == ans) {Splay(now, root); break;}
		if (tree[tree[now].ch[0]].size >= ans) {now = tree[now].ch[0];}
		else {ans -= tree[tree[now].ch[0]].size + 1; now = tree[now].ch[1];}
	}
	tree[tree[root].ch[1]].ch[0] = 0;
	update(tree[root].ch[1]);
	Splay(tree[root].ch[1], 0);
}

void Change(int pos, int val)
{
	int now = root, ans = pos;
	while (now)
	{
		if (tree[tree[now].ch[0]].size + 1 == ans) {Splay(now, 0); break;}
		if (tree[tree[now].ch[0]].size >= ans) {now = tree[now].ch[0];}
		else {ans -= tree[tree[now].ch[0]].size + 1; now = tree[now].ch[1];}
	}
	tree[root].val = val;
}

int ask(int l, int r)
{
	int now = root, ans = l - 1;
	while (now)
	{
		if (tree[tree[now].ch[0]].size + 1 == ans) {Splay(now, 0); break;}
		if (tree[tree[now].ch[0]].size >= ans) {now = tree[now].ch[0];}
		else {ans -= tree[tree[now].ch[0]].size + 1; now = tree[now].ch[1];}
	}
	now = root, ans = r + 1;
	while (now)
	{
		if (tree[tree[now].ch[0]].size + 1 == ans) {Splay(now, root); break;}
		if (tree[tree[now].ch[0]].size >= ans) {now = tree[now].ch[0];}
		else {ans -= tree[tree[now].ch[0]].size + 1; now = tree[now].ch[1];}
	}
	return tree[tree[tree[now].ch[1]].ch[0]].maxn;
}

int main()
{
	n = read();
	Insert(1, -0x7f7f7f7f);
	for (int i = 2; i <= n + 1; ++i) {int val = read(); Insert(i, val);}
	Insert(n + 2, 0x7f7f7f7f);
	m = read();
	for (int i = 1; i <= m; ++i)
	{
		char ch;
		cin >> ch;
		switch(ch)
		{
			case 'I':
			{
				int p = read(), val = read();
				Insert(p, val); break;
			}
			case 'D':
			{
				int p = read();
				Delete(p + 1); break;
			}
			case 'R':
			{
				int p = read(), val = read();
				Change(p + 1, val); break;
			}
			case 'Q':
			{
				int l = read(), r = read();
				printf("%d\n", ask(l + 1, r + 1)); break;
			}
		}
	}
	return 0;
}
