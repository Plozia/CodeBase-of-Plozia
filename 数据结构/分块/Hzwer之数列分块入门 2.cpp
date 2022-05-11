#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN=1e5+10;
int n,opt,l,r,c,block;
LL a[MAXN],tag[MAXN],ys[MAXN];
vector<LL>v[MAXN];

LL read()
{
	LL sum=0,fh=1;char ch=getchar();
	while(ch<'0'&&ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+(ch^48);ch=getchar();}
	return sum*fh;
}

void add(int l,int r,int c)
{
	if(ys[l]==ys[r])
	{
		for(int i=l;i<=r;i++) a[i]+=c;
		v[ys[l]].clear();
		for(int i=(ys[l]-1)*block+1;i<=min((LL)n,ys[l]*block);i++) v[ys[l]].push_back(a[i]);
		sort(v[ys[l]].begin(),v[ys[l]].end());
	}
	else
	{
		for(int i=l;i<=min((LL)n,ys[l]*block);i++) a[i]+=c;v[ys[l]].clear();
		for(int i=(ys[l]-1)*block+1;i<=min((LL)n,ys[l]*block);i++) v[ys[l]].push_back(a[i]);
		sort(v[ys[l]].begin(),v[ys[l]].end());
		for(int i=(ys[r]-1)*block+1;i<=r;i++) a[i]+=c;v[ys[r]].clear();
		for(int i=(ys[r]-1)*block+1;i<=min((LL)n,ys[r]*block);i++) v[ys[r]].push_back(a[i]);
		sort(v[ys[r]].begin(),v[ys[r]].end());
		for(int i=ys[l]+1;i<=ys[r]-1;i++) tag[i]+=c;
	}
}

int ask(int l,int r,LL k)
{
	int sum=0;
	if(ys[l]==ys[r])
	{
		k-=tag[ys[l]];
		for(int i=l;i<=r;i++)
			if(a[i]<k) sum++;
	}
	else
	{
		for(int i=l;i<=min((LL)n,ys[l]*block);i++)
			if(a[i]+tag[ys[l]]<k) sum++;
		for(int i=(ys[r]-1)*block+1;i<=r;i++)
			if(a[i]+tag[ys[r]]<k) sum++;
		for(int i=ys[l]+1;i<=ys[r]-1;i++)
			sum+=lower_bound(v[i].begin(),v[i].end(),k-tag[i])-v[i].begin();
	}
	return sum;
}

int main()
{
	block=sqrt(n=read());
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) ys[i]=(i-1)/block+1;
	for(int i=1;i<=n;i++) v[ys[i]].push_back(a[i]);
	for(int i=1;i<=ys[n];i++) sort(v[i].begin(),v[i].end());
	for(int i=1;i<=n;i++)
	{
		opt=read();l=read();r=read();c=read();
		if(opt==0) add(l,r,c);
		if(opt==1) cout<<ask(l,r,(LL)c*c)<<"\n";
	}
	return 0;
}
