#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 1e6 + 10;
int t, n, cnt, pd, root;
struct node
{
	int ch[10];
	bool flag;
	void init()
	{
		for (int i = 0; i < 10; ++i) ch[i] = 0;
		flag = 0;
	}
}Trie[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void Insert(const string &tmp, int root)
{
	int len = tmp.size(), upd = 12 - len;
	int p = root, cp = cnt;
	for (int i = 1; i <= len; ++i)
	{
		int j;
		if (i <= upd) j = 0;
		else j = tmp[i - upd - 1] - '0';
		if (Trie[p].ch[j])
		{
			p = Trie[p].ch[j];
			if (Trie[p].flag) pd = 1;
		}
		else
		{
			Trie[p].ch[j] = ++cnt;
			p = cnt;
		}
	}
	Trie[p].flag = 1;
	if (cnt == cp) pd = 1;
}

int main()
{
	t = read();
	while (t--)
	{
		n = read(); cnt = root = 1; pd = 0; memset(Trie, 0, sizeof(Trie));
		for (int i = 1; i <= n; ++i)
		{
			string tmp;
			cin >> tmp;
			Insert(tmp, root);
		}
		if (pd == 0) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
