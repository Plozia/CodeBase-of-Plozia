#include<bits/stdc++.h>
using namespace std;

const int MAXN=5e3+10;
int n,m,a[MAXN<<1],l[MAXN],r[MAXN],q[MAXN],tmp,fa[MAXN<<1],d[MAXN<<1];

int gf(int x)
{
	if(fa[x]==x) return x;
	int f=gf(fa[x]);d[x]^=d[fa[x]];return fa[x]=f;
}

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*fh;
}

int main()
{
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		string str;
		l[i]=read();r[i]=read();cin>>str;
		q[i]=(str=="odd")?1:0;
		a[++tmp]=l[i]-1;a[++tmp]=r[i];
	}
	sort(a+1,a+tmp+1);
	n=unique(a+1,a+tmp+1)-a-1;
	for(int i=0;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int x=lower_bound(a+1,a+n+1,l[i]-1)-a;
		int y=lower_bound(a+1,a+n+1,r[i])-a;
		int fx=gf(x),fy=gf(y);
		if(fx==fy)
		{
			if((d[x]^d[y])!=q[i])
			{
				cout<<i-1<<"\n";
				return 0;
			}
		}
		else
		{
			fa[fx]=fy;d[fx]=d[x]^d[y]^q[i];
		}
	}
	cout<<m<<"\n";
	return 0;
}
