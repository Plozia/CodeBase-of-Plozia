#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 1000 + 10;
char a[MAXN][MAXN];
int t, n, cnt, root;
struct node
{
	int flag, ch[2];
	void init() {flag = 0, ch[0] = ch[1] = 0;}
}tree[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void Insert(int k)
{
	int len = strlen(a[k] + 1);
	int p = root;
	for (int i = 1; i <= len; ++i)
	{
		int q = a[k][i] - '0';
		if (!tree[p].ch[q])
		{
			++cnt; tree[cnt].init();
			tree[p].ch[q] = cnt;
		}
		p = tree[p].ch[q];
	}
	tree[p].flag = 1;
}

bool check(int k)
{
	int len = strlen(a[k] + 1);
	int p = root;
	for (int i = 1; i < len; ++i)
	{
		int q = a[k][i] - '0';
		if (tree[tree[p].ch[q]].flag == 1) return 1;
		p = tree[p].ch[q];
	}
	return 0;
}

int main()
{
	while (~scanf("%s", a[1] + 1))
	{
		n = 1, ++t; cnt = root = 1; tree[1].init();
		while (1)
		{
			scanf("%s", a[n + 1] + 1);
			if (a[n + 1][1] == '9') break;
			++n;
		}
		for (int i = 1; i <= n; ++i) Insert(i);
		bool flag = 0;
		for (int i = 1; i <= n; ++i)
			if (check(i)) flag = 1;
		if (flag == 1) printf("Set %d is not immediately decodable\n", t);
		else printf("Set %d is immediately decodable\n", t);
	}
	return 0;
}
