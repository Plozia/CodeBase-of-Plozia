//FHQ Treap
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
int n, cnt, root;
struct node
{
	int l, r, size, key, val;
}tree[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

int Make_Node(int x)
{
	++cnt;
	tree[cnt].size = 1;
	tree[cnt].val = x;
	tree[cnt].key = rand();
	return cnt;
}

void update(int x)
{
	tree[x].size = tree[tree[x].l].size + tree[tree[x].r].size + 1;
}

void split(int now, int val, int &x, int &y)
{
	if (!now) { x = y = 0; return ; }
	if (tree[now].val <= val) { x = now; split(tree[now].r, val, tree[now].r, y); }
	else { y = now; split(tree[now].l, val, x, tree[now].l); }
	update(now);
}

int merge(int x, int y)
{
	if (!x || !y) return x + y;
	if (tree[x].key > tree[y].key) { tree[x].r = merge(tree[x].r, y); update(x); return x; }
	else { tree[y].l = merge(x, tree[y].l); update(y); return y; }
}

void Insert(int val)
{
	int x, y;
	split(root, val, x, y);
	root = merge(merge(x, Make_Node(val)), y);
}

void Delete(int val)
{
	int x, y, z;
	split(root, val, x, z); split(x, val - 1, x, y);
	y = merge(tree[y].l, tree[y].r); root = merge(merge(x, y), z);
}

void Find_Rank_of_x(int val)
{
	int x, y;
	split(root, val - 1, x, y);
	printf("%d\n", tree[x].size + 1);
	root = merge(x, y);
}

void Find_xth(int val)
{
	int now = root;
	while (now)
	{
		if (tree[tree[now].l].size + 1 == val) break;
		if (tree[tree[now].l].size >= val) now = tree[now].l;
		else {val -= tree[tree[now].l].size + 1; now = tree[now].r;}
	}
	printf("%d\n", tree[now].val);
}

void Find_pre(int val)
{
	int x, y;
	split(root, val - 1, x, y);
	int now = x;
	while (tree[now].r) now = tree[now].r;
	printf("%d\n", tree[now].val);
	root = merge(x, y);
}

void Find_aft(int val)
{
	int x, y;
	split(root, val, x, y);
	int now = y;
	while (tree[now].l) now = tree[now].l;
	printf("%d\n", tree[now].val);
	root = merge(x, y);
}

int main()
{
	srand(233);
	n = read();
	while (n--)
	{
		int opt = read(), x = read();
		switch(opt)
		{
			case 1: Insert(x); break;
			case 2: Delete(x); break;
			case 3: Find_Rank_of_x(x); break;
			case 4: Find_xth(x); break;
			case 5: Find_pre(x); break;
			case 6: Find_aft(x); break;
		}
	}
	return 0;
}
