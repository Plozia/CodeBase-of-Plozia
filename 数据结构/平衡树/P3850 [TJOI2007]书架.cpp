#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 2e5 + 10;
int n, m, cnt, root, q;
struct node
{
	string val;
	int l, r, key, size;
}tree[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void update(int now) {tree[now].size = tree[tree[now].l].size + tree[tree[now].r].size + 1;}
int Make_Node(string val)
{
	int now = ++cnt; tree[cnt].val = val;
	tree[cnt].key = rand(); tree[cnt].size = 1;
	return now;
}

void split(int now, int val, int &x, int &y)
{
	if (now == 0) x = y = 0;
	else
	{
		if (tree[tree[now].l].size < val)
		{
			x = now;
			split(tree[now].r, val - tree[tree[now].l].size - 1, tree[now].r, y);
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
	if (tree[x].key < tree[y].key)
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

void Insert(int pos, string val)
{
	int x, y;
	split(root, pos - 1, x, y);
	root = merge(merge(x, Make_Node(val)), y);
}

string ask(int pos)
{
	int x, y, z;
	split(root, pos, y, z);
	split(y, pos - 1, x, y);
	string str = tree[y].val;
	root = merge(merge(x, y), z);
	return str;
}

int main()
{
	srand(time(0));
	n = read();
	for (int i = 1; i <= n; ++i)
	{
		string str; cin >> str;
		Insert(i, str);
	}
	m = read();
	for (int i = 1; i <= m; ++i)
	{
		string str; int pos;
		cin >> str; pos = read();
		Insert(pos + 1, str);
	}
	q = read();
	for (int i = 1; i <= q; ++i)
	{
		int pos = read();
		cout << ask(pos + 1) << "\n";
	}
	return 0;
}
