#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 10;
int n, minn, cnt, root, ans, delta;
struct node
{
	int l, r, val, size, key;
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
	++cnt; tree[cnt].val = val;
	tree[cnt].size = 1;
	tree[cnt].key = rand();
	return cnt;
}

void update(int now) {tree[now].size = tree[tree[now].l].size + tree[tree[now].r].size + 1;}

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
	int x, y; split(root, val, x, y);
	root = merge(merge(x, Make_Node(val)), y);
}

void Find_kth(int val)
{
	int now = root;
	while (now)
	{
		if (tree[tree[now].r].size + 1 == val) break;
		if (tree[tree[now].r].size >= val) now = tree[now].r;
		else {val -= tree[tree[now].r].size + 1; now = tree[now].l;}
	}
	printf("%d\n", tree[now].val + delta);
}

void deal(int val)
{
	int x, y; split(root, val - 1, x, y);
	ans += tree[x].size;
	root = y;
}

int main()
{
	srand(time(0));
	n = read(); minn = read();
	for (int i = 1; i <= n; ++i)
	{
		char ch; cin >> ch;
		int k = read();
		switch(ch)
		{
			case 'I':
				if (k < minn) break;
				Insert(k - delta); break;
			case 'A':
				delta += k; break;
			case 'S':
				delta -= k; break;
			case 'F':
				if (k > cnt - ans) printf("-1\n");
				else Find_kth(k);
				break;
		}
		deal(minn - delta);
	}
	printf("%d\n", ans);
	return 0;
}
