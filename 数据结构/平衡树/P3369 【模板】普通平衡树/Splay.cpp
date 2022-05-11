//Splay
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
int n, cnt, root;
struct node
{
	int l, r, size, cnt, val;
}tree[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void update(int x) {tree[x].size = tree[tree[x].l].size + tree[tree[x].r].size + tree[x].cnt;}

void Make_Node(int &now, int &val)
{
	tree[now = ++cnt].val = val;
	tree[cnt].size++; tree[cnt].cnt++;
}

void zig(int &now)
{
	int l = tree[now].l;
	tree[now].l = tree[l].r;
	tree[l].r = now;
	now = l;
	update(tree[now].r), update(now);
}

void zag(int &now)
{
	int r = tree[now].r;
	tree[now].r = tree[r].l;
	tree[r].l = now;
	now = r;
	update(tree[now].l), update(now);
}

void Splay(int x, int &y)
{
	if (x == y) return ;
	int &l = tree[y].l, &r = tree[y].r;
	if (l == x) zig(y);
	else if (r == x) zag(y);
	else
	{
		if (tree[x].val < tree[y].val)
		{
			if (tree[x].val < tree[l].val) Splay(x, tree[l].l), zig(y), zig(y);
			else Splay(x, tree[l].r), zag(l), zig(y);
		}
		else
		{
			if (tree[x].val > tree[r].val) Splay(x, tree[r].r), zag(y), zag(y);
			else Splay(x, tree[r].l), zig(r), zag(y);
		}
	}
}

void del(int now)
{
	Splay(now, root);
	if (tree[now].cnt > 1) {tree[now].size--; tree[now].cnt--; return ;}
	if (tree[root].r)
	{
		int o = tree[root].r;
		while (tree[o].l) o = tree[o].l;
		Splay(o, tree[root].r);
		tree[tree[root].r].l = tree[root].l;
		root = tree[root].r;
		update(root);
	}
	else root = tree[root].l;
}

void Insert(int &now, int &val)
{
	if (!now) Make_Node(now, val), Splay(now, root);
	else if (tree[now].val > val) Insert(tree[now].l, val);
	else if (tree[now].val < val) Insert(tree[now].r, val);
	else tree[now].size++, tree[now].cnt++, Splay(now, root);
}

void Delete(int now, int &val)
{
	if (tree[now].val == val) del(now);
	else if (tree[now].val > val) Delete(tree[now].l, val);
	else Delete(tree[now].r, val);
}

int Find_Rank(int val)
{
	int now = root, ans = 1;
	while (now)
	{
		if (tree[now].val == val)
		{
			ans += tree[tree[now].l].size;
			Splay(now, root); break;
		}
		if (val <= tree[now].val) now = tree[now].l;
		else {ans += tree[tree[now].l].size + tree[now].cnt; now = tree[now].r;}
	}
	return ans;
}

int Find_kth(int val)
{
	int now = root;
	while (now)
	{
		if (tree[tree[now].l].size < val && tree[tree[now].l].size + tree[now].cnt >= val) {Splay(now, root); break;}
		else if (tree[tree[now].l].size >= val) now = tree[now].l;
		else {val -= tree[tree[now].l].size + tree[now].cnt; now = tree[now].r;}
	}
	return tree[now].val;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i)
	{
		int opt = read(), x = read();
		switch(opt)
		{
			case 1: Insert(root, x); break;
			case 2: Delete(root, x); break;
			case 3: printf("%d\n", Find_Rank(x)); break;
			case 4: printf("%d\n", Find_kth(x)); break;
			case 5: printf("%d\n", Find_kth(Find_Rank(x) - 1)); break;
			case 6: printf("%d\n", Find_kth(Find_Rank(x + 1))); break;
		}
	}
	return 0;
}
