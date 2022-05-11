#include<bits/stdc++.h>
using namespace std;

const int MAXN=5e4+10;
int n,k,fa[MAXN*3],ans=0;

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
	n=read();k=read();
	for(int i=1;i<=n*3;i++) fa[i]=i;
	for(int i=1;i<=k;i++)
	{
		int op,x,y;
		op=read();x=read();y=read();
		if(x>n||y>n) ans++;
		else if(op==2&&x==y) ans++;
		else
		{
			if(op==1)
			{
				if(gf(x)==gf(y+n)||gf(x+n)==gf(y)) ans++;
				else hb(x,y),hb(x+n,y+n),hb(x+n+n,y+n+n);
			}
			else
			{
				if(gf(x)==gf(y)||gf(y)==gf(x+n)) ans++;
				else hb(x,y+n),hb(x+n,y+n+n),hb(x+n+n,y);
			}
		}
	}
	cout<<ans<<"\n";
	return 0;
}
