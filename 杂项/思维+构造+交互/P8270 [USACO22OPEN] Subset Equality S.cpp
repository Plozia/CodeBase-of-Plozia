/*
========= Plozia =========
	Author:Plozia
	Problem:P8270 [USACO22OPEN] Subset Equality S
	Date:2022/6/7
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::string;
using std::queue;

typedef long long LL;
const int MAXN = 1e5 + 5;
int cnt1[27], cnt2[27], Last1[MAXN][27], q, Last2[MAXN][27], fa[27];
bool book[27][27];
string s, t;
queue <int> q1[27], q2[27];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}

int main()
{
	std::cin >> s >> t;
	for (int i = (int)s.size() - 1; i >= 0; --i)
	{
		for (int j = 1; j <= 26; ++j) Last1[i][j] += Last1[i + 1][j];
		++Last1[i][s[i] - 'a' + 1]; ++cnt1[s[i] - 'a' + 1];
		q1[s[i] - 'a' + 1].push(i);
	}
	for (int i = (int)t.size() - 1; i >= 0; --i)
	{
		for (int j = 1; j <= 26 ; ++j) Last2[i][j] += Last2[i + 1][j];
		++Last2[i][t[i] - 'a' + 1]; ++cnt2[t[i] - 'a' + 1];
		q2[t[i] - 'a' + 1].push(i);
	}
	for (int i = 1; i <= 26; ++i) fa[i] = i;
	for (int i = 1; i <= 26; ++i)
	{
		for (int j = 1; j <= 26; ++j) book[i][j] = 1;
		while (!q1[i].empty() && !q2[i].empty())
		{
			for (int k = 1; k <= 26; ++k)
				if (Last1[q1[i].front()][k] != Last2[q2[i].front()][k])
					book[i][k] = 0;
			q1[i].pop(); q2[i].pop();
		}
	}
	q = Read();
	while (q--)
	{
		string str; std::cin >> str; bool flag = 1;
		for (int i = 0; i < str.size(); ++i)
		{
			flag &= (cnt1[str[i] - 'a' + 1] == cnt2[str[i] - 'a' + 1]);
			for (int j = 0; j < str.size(); ++j)
				flag &= book[str[i] - 'a' + 1][str[j] - 'a' + 1];
		}
		if (flag) printf("Y"); else printf("N");
	}
	puts(""); return 0;
}