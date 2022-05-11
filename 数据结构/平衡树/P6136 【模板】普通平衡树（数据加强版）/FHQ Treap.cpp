//FHQ Treap
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 1e5 + 10;
int n, m, cnt, root, last_ans, ans;
struct node
{
	int l, r, size, val, key;
}tree[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

int Make_Node(int val)
{
	++cnt;
	tree[cnt].size = 1;
	tree[cnt].val = val;
	tree[cnt].key = rand();
	return cnt;
}

void update(int now)
{
	tree[now].size = tree[tree[now].l].size + tree[tree[now].r].size + 1;
}

void split(int now, int val, int &x, int &y)
{
	if (!now) x = y = 0;
	else
	{
		if (tree[now].val <= val)
		{
			x = now;
			split(tree[now].r, val, tree[now].r, y);
		}
		else
		{
			y = now;
			split(tree[now].l, val, x, tree[now].l);
		}
		update(now);
	}
}

int merge(int x, int y)
{
	if (!x || !y) return x + y;
	else
	{
		if (tree[x].key > tree[y].key)
		{
			tree[x].r = merge(tree[x].r, y);
			update(x); return x;
		}
		else
		{
			tree[y].l = merge(x, tree[y].l);
			update(y); return y;
		}
	}
}

void Insert(int val)
{
	int x, y; split(root, val - 1, x, y);
	root = merge(merge(x, Make_Node(val)), y);
}

void Delete(int val)
{
	int x, y, z;
	split(root, val, x, z); split(x, val - 1, x, y);
	y = merge(tree[y].l, tree[y].r); root = merge(merge(x, y), z);
}

void Find_Rank(int val)
{
	int x, y;
	split(root, val - 1, x, y);
	last_ans = tree[x].size + 1;
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
	last_ans = tree[now].val;
}

void Find_pre(int val)
{
	int x, y;
	split(root, val - 1, x, y);
	int now = x;
	while (tree[now].r) now = tree[now].r;
	last_ans = tree[now].val;
	root = merge(x, y);
}

void Find_aft(int val)
{
	int x, y;
	split(root, val, x, y);
	int now = y;
	while (tree[now].l) now = tree[now].l;
	last_ans = tree[now].val;
	root = merge(x, y);
}

int main()
{
	srand(time(0));
	n = read(); m = read();
	for (int i = 1; i <= n; ++i) Insert(read());
	for (int i = 1; i <= m; ++i)
	{
		int opt = read(), x = read() ^ last_ans;
		switch(opt)
		{
			case 1: Insert(x); break;
			case 2: Delete(x); break;
			case 3: Find_Rank(x); ans ^= last_ans; break;
			case 4: Find_xth(x); ans ^= last_ans; break;
			case 5: Find_pre(x); ans ^= last_ans; break;
			case 6: Find_aft(x); ans ^= last_ans; break;
		}
	}
	printf("%d\n", ans);
	return 0;
}
