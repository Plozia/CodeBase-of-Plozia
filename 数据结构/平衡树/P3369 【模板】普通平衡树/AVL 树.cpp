//AVL Ê÷
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
int n, cnt, root;
struct node
{
	int l, r, size, hei, val;
}tree[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void Make_Node(int &now, int val)
{
	tree[now = ++cnt].val = val;
	tree[cnt].size = 1;
}

int BF(int x) {return tree[tree[x].l].hei - tree[tree[x].r].hei;}
void update(int x)
{
	tree[x].size = tree[tree[x].l].size + tree[tree[x].r].size + 1;
	tree[x].hei = max(tree[tree[x].l].hei, tree[tree[x].r].hei) + 1;
}

void lrotate(int &now)
{
	int r = tree[now].r;
	tree[now].r = tree[r].l;
	tree[r].l = now;
	now = r;
	update(tree[now].l), update(now);
}

void rrotate(int &now)
{
	int l = tree[now].l;
	tree[now].l = tree[l].r;
	tree[l].r = now;
	now = l;
	update(tree[now].r), update(now);
}

void check(int &now)
{
	int nf = BF(now);
	if (nf > 1)
	{
		int lf = BF(tree[now].l);
		if (lf > 0) rrotate(now);
		else lrotate(tree[now].l), rrotate(now);
	}
	else if (nf < -1)
	{
		int rf = BF(tree[now].r);
		if (rf < 0) lrotate(now);
		else rrotate(tree[now].r), lrotate(now);
	}
	else if(now) update(now);
}

int Find(int &now, int fa)
{
	int sum;
	if (!tree[now].l)
	{
		sum = now;
		tree[fa].l = tree[now].r;
	}
	else
	{
		sum = Find(tree[now].l, now);
		check(now);
	}
	return sum;
}

void Insert(int &now, int val)
{
	if (!now) Make_Node(now, val);
	else if (tree[now].val > val) Insert(tree[now].l, val);
	else Insert(tree[now].r, val);
	check(now);
}

void Delete(int &now, int val)
{
	if (val == tree[now].val)
	{
		int l = tree[now].l, r = tree[now].r;
		if (!l || !r) now = l + r;
		else
		{
			now = Find(r, r);
			if (now != r) tree[now].r = r;
			tree[now].l = l;
		}
	}
	else if (tree[now].val > val) Delete(tree[now].l, val);
	else Delete(tree[now].r, val);
	check(now);
}

int Find_Rank(int val)
{
	int now = root, ans = 1;
	while (now)
	{
		if (val <= tree[now].val) now = tree[now].l;
		else {ans += tree[tree[now].l].size + 1; now = tree[now].r;}
	}
	return ans;
}

int Find_kth(int val)
{
	int now = root;
	while (now)
	{
		if (tree[tree[now].l].size + 1 == val) break;
		if (tree[tree[now].l].size >= val) now = tree[now].l;
		else {val -= tree[tree[now].l].size + 1; now = tree[now].r;}
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
			case 5: printf("%d\n", Find_kth(Find_Rank(x) - 1));  break;
			case 6: printf("%d\n", Find_kth(Find_Rank(x + 1))); break;
		}
	}
	return 0;
}
