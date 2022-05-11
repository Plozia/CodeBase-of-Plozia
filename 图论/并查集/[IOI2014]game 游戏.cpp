#include<bits/stdc++.h>
using namespace std;

const int MAXN=1500+10;
int n,m,fa[MAXN],q1[MAXN*MAXN],q2[MAXN*MAXN];

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
	n=read();m=n*(n-1)/2;
	for(int i=1;i<=m;i++) {q1[i]=read();q2[i]=read();}
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<m;i++)
	{
		int x=q1[i],y=q2[i];
		int fx=gf(x),fy=gf(y);
		int x1=q1[m],y1=q2[m];
		int fx1=gf(x1),fy1=gf(y1);
		if(fx>fy) swap(fx,fy);
		if(fx1>fy1) swap(fx1,fy1);
		if(fx==fx1&&fy==fy1) cout<<"0\n";
		else
		{
			cout<<"1\n";
			hb(x,y);
		}
	}
	cout<<"1\n";
	return 0;
}
