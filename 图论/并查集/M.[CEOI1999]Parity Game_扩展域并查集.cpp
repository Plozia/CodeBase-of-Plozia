#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+10;
int n,m,a[MAXN],fa[MAXN],tmp,l[MAXN],r[MAXN],q[MAXN];

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
	for(int i=0;i<=(n<<1);i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int x=lower_bound(a+1,a+n+1,l[i]-1)-a;
		int y=lower_bound(a+1,a+n+1,r[i])-a;
		if(q[i]==1)
			if(gf(x)==gf(y)||gf(x+n)==gf(y+n)) {cout<<i-1<<"\n";return 0;}
			else hb(x,y+n),hb(x+n,y);
		else
			if(gf(x+n)==gf(y)||gf(x)==gf(y+n)) {cout<<i-1<<"\n";return 0;}
			else hb(x,y),hb(x+n,y+n);
	}
	cout<<m<<"\n";
	return 0;
}
