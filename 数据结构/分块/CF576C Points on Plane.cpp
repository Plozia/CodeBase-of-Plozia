#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e6+10;
int n,block;
struct node
{
	int l,r,id,b;
}que[MAXN];

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+(ch^48);ch=getchar();}
	return sum*fh;
}

bool cmp(const node &fir,const node &sec)
{
	if(fir.b!=sec.b) return fir.b<sec.b;
	if(fir.b&1) return fir.r<sec.r;
	return fir.r>sec.r;
}

int main()
{
	ios::sync_with_stdio(false);
	n=read();block=1000;
	for(int i=1;i<=n;i++) {que[i].l=read();que[i].r=read();que[i].id=i;que[i].b=(que[i].l-1)/block+1;}
	sort(que+1,que+n+1,cmp);
	for(int i=1;i<=n;i++) cout<<que[i].id<<" ";
	cout<<"\n";
	return 0;
}
