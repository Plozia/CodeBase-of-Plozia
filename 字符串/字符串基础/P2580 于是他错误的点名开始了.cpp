#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
int n, m;
map <string, bool> book1, book2;
string str;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i) {cin >> str; book1[str] = 1;}
	m = read();
	for (int i = 1; i <= m; ++i)
	{
		cin >> str;
		if (book1[str] && !book2[str]) {book2[str] = 1; printf("OK\n");}
		else if (!book1[str]) printf("WRONG\n");
		else printf("REPEAT\n");
	}
	return 0;
}
