#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;
int n, m, a[MAXN], Next[MAXN], step[MAXN], block, ys[MAXN], bnum;

int read()
{
	int sum = 0; char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum;
}

int ask(int x)
{
	int sum = 0;
	while(x <= n)
	{
		sum += step[x];
		x = Next[x];
	}
	return sum;
}

void exchange(int op)
{
	int l = (ys[op] - 1) * block + 1, r = ys[op] * block;
	if(r > n) r = n;
	for(int i = r; i >= l; --i)
	{
		if(i + a[i] > r)
		{
			Next[i] = i + a[i];
			step[i] = 1;
		}
		else
		{
			Next[i] = Next[i + a[i]];
			step[i] = step[i + a[i]] + 1;
		}
	}
}

int main()
{
	n = read(); block = sqrt(n); bnum = ceil((double)n / block);
	for(int i = 1; i <= n; ++i) {ys[i] = (i - 1) / block + 1; a[i] = read();}
	for(int i = bnum; i >= 1; --i)
	{
		int l = (i - 1) * block + 1, r = min(n, i * block);
		for(int j = r; j >= l; --j)
		{
			if(j + a[j] > r)
			{
				Next[j] = j + a[j];
				step[j] = 1;
			}
			else
			{
				Next[j] = Next[j + a[j]];
				step[j] = step[j + a[j]] + 1;
			}
		}
	}
	m = read();
	for(int i = 1; i <= m; ++i)
	{
		int opt, j, k;
		opt = read(); j = read() + 1;
		if(opt == 1) printf("%d\n", ask(j));
		else
		{
			k = read();
			a[j] = k;
			exchange(j);
		}
	}
	return 0;
}
