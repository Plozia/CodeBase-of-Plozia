//Ìæ×ïÑòÊ÷
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
const double alpha = 0.75;
int n, cnt, root;
struct node
{
	int l, r, size, fact, val;
	bool exist;
}tree[MAXN];
vector<int>v;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

bool Isimbalance(int x)
{
	if (max(tree[tree[x].l].size, tree[tree[x].r].size) > tree[x].size * alpha || tree[x].size - tree[x].fact > tree[x].size * 0.3) return 1;
	return 0;
}

void Get_ldr(int now)
{
	if (!now) return ;
	Get_ldr(tree[now].l);
	if (tree[now].exist) v.push_back(now);
	Get_ldr(tree[now].r);
}

void lift(int l, int r, int &now)
{
	if (l == r)
	{
		now = v[l];
		tree[now].l = tree[now].r = 0;
		tree[now].size = tree[now].fact = 1;
		return ;
	}
	int mid = (l + r) >> 1;
	while (mid && l < mid && tree[v[mid - 1]].val == tree[v[mid]].val) mid--;
	now = v[mid];
	if (l < mid) lift(l, mid - 1, tree[now].l);
	else tree[now].l = 0;
	lift(mid + 1, r, tree[now].r);
	tree[now].size = tree[tree[now].l].size + tree[tree[now].r].size + 1;
	tree[now].fact = tree[tree[now].l].fact + tree[tree[now].r].fact + 1;
}

void rebuild(int &now)
{
	v.clear(); Get_ldr(now);
	if (v.empty()) {now = 0; return ;}
	lift(0, v.size() - 1, now);
}

void update(int now, int end)
{
	if (!now) return ;
	if (tree[end].val >= tree[now].val) update(tree[now].r, end);
	else update(tree[now].l, end);
	tree[now].size = tree[tree[now].l].size + tree[tree[now].r].size + 1;
	tree[now].fact = tree[tree[now].l].fact + tree[tree[now].r].fact + tree[now].exist;
}

void check(int &now, int end)
{
	if (now == end) return ;
	if (Isimbalance(now)) {rebuild(now); update(root, now); return ;}
	if (tree[now].val > tree[end].val) check(tree[now].l, end);
	else check(tree[now].r, end);
}

void make_node(int &now, int x)
{
	now = ++cnt;
	tree[now].size = tree[now].fact = 1;
	tree[now].val = x;
	tree[now].exist = 1;
}

void Insert(int &now, int x)
{
	if (!now)
	{
		make_node(now, x);
		check(root, now);
		return ;
	}
	tree[now].size++;
	tree[now].fact++;
	if (x >= tree[now].val) Insert(tree[now].r, x);
	else Insert(tree[now].l, x);
	return ;
}

void Delete(int now, int x)
{
	if (tree[now].exist && tree[now].val == x)
	{
		tree[now].exist = false;
		tree[now].fact--;
		check(root, now);
		return ;
	}
	tree[now].fact--;
	if (x >= tree[now].val) Delete(tree[now].r, x);
	else Delete(tree[now].l, x);
	return ;
}

int Find_Rank(int x)
{
	int o = root, ans = 1;
	while (o)
	{
		if (x <= tree[o].val) o = tree[o].l;
		else {ans += tree[tree[o].l].fact + tree[o].exist; o = tree[o].r;}
	}
	return ans;
}

int Find_kth(int x)
{
	int o = root;
	while (o)
	{
		if (tree[o].exist && tree[tree[o].l].fact + tree[o].exist == x) return tree[o].val;
		if (tree[tree[o].l].fact < x) {x -= tree[tree[o].l].fact + tree[o].exist; o = tree[o].r;}
		else o = tree[o].l;
	}
}

int main()
{
	n = read();
	while (n--)
	{
		int op = read(), x = read();
		switch(op)
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
