/*
========= Plozia =========
	Author:Plozia
	Problem:P5309 [Ynoi2011] 初始化
	Date:2021/11/23
========= Plozia =========
*/

#include <bits/stdc++.h>
#define Add(x, y) ((((x) += (y)) >= P) && ((x) -= P))
using namespace std;

typedef long long LL;
const int MAXN = 2e5 + 5;
const int MaxBlock = 1000 + 5;
const int P = 1e9 + 7;
int n, m, a[MAXN], Block, ans[MaxBlock], Pre[MaxBlock][MaxBlock], Suf[MaxBlock][MaxBlock], ys[MAXN], Pl[MAXN], Pr[MAXN];

int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
// constexpr void Add(int &x, int y) { ((x += y) >= P) ? (x -= P) : 0;}

struct FastIO
{
	static const int S=1048576;char buf[S],*L,*R;int stk[20],Top;~FastIO(){clear();}
	inline char nc(){return L==R&&(R=(L=buf)+fread(buf,1,S,stdin),L==R)?EOF:*L++;}inline void clear(){fwrite(buf,1,Top,stdout);Top=0;}
	inline void pc(char ch){Top==S&&(clear(),0);buf[Top++]=ch;}inline void endl(){pc('\n');}
	FastIO& operator >> (char&ch){while(ch=nc(),ch==' '||ch=='\n');return *this;}
	template<typename T>FastIO& operator >> (T&ret)
	{
		ret=0;int f=1;char ch=nc();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=nc();}
		while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=nc();}ret*=f;return *this;
	}
	FastIO& operator >> (char* s){int Len=0;char ch=nc();while(ch!='\n'){*(s+Len)=ch;Len++;ch=nc();}}
	template<typename T>FastIO& operator << (T x)
	{
		if(x<0){pc('-');x=-x;}do{stk[++stk[0]]=x%10;x/=10;}while(x);
		while(stk[0]) pc('0'+stk[stk[0]--]);return *this;
	}
	FastIO& operator << (char ch){pc(ch);return *this;}
	FastIO& operator << (string str){int Len=str.size()-1;for(stk[0]=0;Len>=0;Len--) stk[++stk[0]]=str[Len];while(stk[0]) pc(stk[stk[0]--]);return *this;}
}fin,fout; // By OdtreePrince

int main()
{
	fin >> n >> m; Block = 500;
	for (int i = 1; i <= n; ++i) fin >> a[i];
	for (int i = 1; i <= n; ++i) ys[i] = (i - 1) / Block + 1;
	for (int i = 1; i <= ys[n]; ++i) Pl[i] = (i - 1) * Block + 1, Pr[i] = i * Block;
	Pr[ys[n]] = n;
	for (int i = 1; i <= n; ++i) Add(ans[ys[i]], a[i]);
	for (int i = 1; i <= m; ++i)
	{
		int opt; fin >> opt;
		if (opt == 1)
		{
			int x, y, z; fin >> x >> y >> z;
			if (x >= 100)
			{
				for (int j = y; j <= n; j += x) Add(a[j], z), Add(ans[ys[j]], z);
			}
			else
			{
				for (int j = y; j <= x; ++j) Add(Pre[x][j], z);
				for (int j = 1; j <= y; ++j) Add(Suf[x][j], z);
			}
		}
		else
		{
			int l, r, val = 0; fin >> l >> r;
			if (ys[l] == ys[r])
			{
				for (int j = l; j <= r; ++j) Add(val, a[j]);
			}
			else
			{
				for (int j = l; j <= Pr[ys[l]]; ++j) Add(val, a[j]);
				for (int j = Pl[ys[r]]; j <= r; ++j) Add(val, a[j]);
				for (int j = ys[l] + 1; j <= ys[r] - 1; ++j) Add(val, ans[j]);
			}
			for (int j = 1; j < 100; ++j)
			{
				int ysl = (l - 1) / j + 1, ysr = (r - 1) / j + 1;
				if (ysl == ysr) Add(val, (Pre[j][(r - 1) % j + 1] - Pre[j][(l - 1) % j] + P) % P);
				else Add(val, (1ll * (ysr - ysl - 1) * Pre[j][j] % P + 1ll * Suf[j][(l - 1) % j + 1] + 1ll * Pre[j][(r - 1) % j + 1]) % P);
			}
			fout << val; fout << '\n';
		}
	}
	return 0;
}
