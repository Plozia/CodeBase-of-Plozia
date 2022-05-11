#include<bits/stdc++.h>
#define Max(a,b) ((a>b)?a:b)
using namespace std;

const int MAXN=1e4+10;
int n,m,w,c[MAXN],d[MAXN],money[MAXN],value[MAXN],fa[MAXN],ys[MAXN],tmp,f[MAXN];

int gf(int x) {return (fa[x]==x)?x:fa[x]=gf(fa[x]);}
void hb(int x,int y) {if(gf(x)!=gf(y)) fa[fa[x]]=fa[y];}

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*fh;
}

int main()
{
	n=read();m=read();w=read();
	for(int i=1;i<=n;i++) {c[i]=read();d[i]=read();fa[i]=i;}
	for(int i=1;i<=m;i++)
	{
		int x,y;
		x=read();y=read();
		hb(x,y);
	}
	for(int i=1;i<=n;i++) if(gf(i)==i) ys[i]=++tmp;
	for(int i=1;i<=n;i++)
	{
		money[ys[fa[i]]]+=c[i];
		value[ys[fa[i]]]+=d[i];
	}
	for(int i=1;i<=tmp;i++)
		for(int j=w;j>=money[i];j--)
			f[j]=Max(f[j],f[j-money[i]]+value[i]);
	cout<<f[w]<<"\n";
	return 0;
}
