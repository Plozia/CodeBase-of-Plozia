#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+10;
int n, k, a[MAXN], block, ys[MAXN],ans;
vector<int>v[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-') fh = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void change(int l, int r)
{
	swap(a[l], a[r]);
	v[ys[l]].clear(); v[ys[r]].clear();
	int ll = (ys[l] - 1) * block + 1, lr = ys[l] * block;
	int rl = (ys[r] - 1) * block + 1, rr = min(n, ys[r] * block);
	for(int i = ll; i <= lr; ++i) v[ys[l]].push_back(a[i]);
	for(int i = rl; i <= rr; ++i) v[ys[r]].push_back(a[i]);
	sort(v[ys[l]].begin(), v[ys[l]].end());
	sort(v[ys[r]].begin(), v[ys[r]].end());
}

int ask(int l, int r, int x, int y)
{
	int fh = 1;
	if(x > y) swap(x, y);
	else fh = -1;
	int sum = 0;
	l++; r--;
	if(l > r)
	{
		if(l - r == 2) return 0;
		return fh;
	}
	if(ys[l] == ys[r])
	{
		for(int i = l; i <= r; ++i)
			if(a[i] > x && a[i] < y) sum++;
	}
	else
	{
		int ll = (ys[l] - 1) * block + 1, lr = ys[l] * block;
		int rl = (ys[r] - 1) * block + 1, rr = min(n, ys[r] * block);
		for(int i = l; i <= lr; ++i)
			if(a[i] > x && a[i] < y) sum++;
		for(int i = rl; i <= r; ++i)
			if(a[i] > x && a[i] < y) sum++;
		for(int i = ys[l] + 1; i <= ys[r] - 1; ++i)
			sum += upper_bound(v[i].begin(), v[i].end(), y) - upper_bound(v[i].begin(), v[i].end(), x);
	}
	return ((sum << 1) + 1) * fh;
}

int main()
{
	n = read(); k = read(); block = sqrt(n);
	for(int i = 1; i <= n; ++i) a[i] = i;
	for(int i = 1; i <= n; ++i) ys[i] = (i - 1) / block + 1;
	for(int i = 1; i <= n; ++i) v[ys[i]].push_back(a[i]);
	for(int i = 1; i <= ys[n]; ++i) sort(v[i].begin(), v[i].end());
	for(int i = 1; i <= k; ++i)
	{
		int l = read(), r = read();
		change(l, r);
		ans += ask(l, r, a[l], a[r]);
		printf("%d\n", ans);
	}
	return 0;
}
