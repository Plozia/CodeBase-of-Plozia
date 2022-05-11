#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 1e6 + 10;
int n, m, Next[MAXN];
char s1[MAXN], s2[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

int main()
{
	scanf("%s", s1 + 1);
	scanf("%s", s2 + 1);
	n = strlen(s1 + 1); m = strlen(s2 + 1);
	int j = 0;
	for (int i = 2; i <= m; ++i)
	{
		while (j && s2[j + 1] != s2[i]) j = Next[j];
		if (s2[j + 1] == s2[i]) ++j;
		Next[i] = j;
	}
	j = 0;
	for (int i = 1; i <= n; ++i)
	{
		while (j && s2[j + 1] != s1[i]) j = Next[j];
		if (s2[j + 1] == s1[i]) ++j;
		if (j == m) {printf("%d\n", i - m + 1); j = Next[j];}
	}
	for (int i = 1; i <= m; ++i) printf("%d ", Next[i]);
	printf("\n"); return 0;
}
