#include<bits/stdc++.h>
using namespace std;

const int MAXN=5e5+10,BLOCK=700+10;
int n,m,a[MAXN],lastans,s[BLOCK][MAXN],b[MAXN],lastn,ys[MAXN],lsh[MAXN],block,bnum,cnt[MAXN];
struct node
{
	int cnt,num;
}ans[BLOCK][BLOCK];

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+(ch^48);ch=getchar();}
	return sum*fh;
}

int ask(int l,int r)
{
	node tmp=ans[ys[l]+1][ys[r]-1];
	if(ys[l]==ys[r])
	{
		memset(cnt,0,sizeof(cnt));tmp=(node){0,0};
		for(int i=l;i<=r;i++)
		{
			cnt[lsh[i]]++;
			if(cnt[lsh[i]]>tmp.cnt) {tmp.cnt=cnt[lsh[i]];tmp.num=lsh[i];}
			else if(cnt[lsh[i]]==tmp.cnt) {tmp.cnt=cnt[lsh[i]];tmp.num=min(tmp.num,lsh[i]);}
		}
	}
	else
	{
		memset(cnt,0,sizeof(cnt));
		int ll=(ys[l]-1)*block+1,lr=ys[l]*block,rl=(ys[r]-1)*block+1,rr=min(n,ys[r]*block);
		for(int i=l;i<=lr;i++)
		{
			cnt[lsh[i]]++;int t=s[ys[r]-1][lsh[i]]-s[ys[l]][lsh[i]];
			if(cnt[lsh[i]]+t>tmp.cnt) {tmp.cnt=cnt[lsh[i]]+t;tmp.num=lsh[i];}
			else if(cnt[lsh[i]]+t==tmp.cnt) {tmp.cnt=cnt[lsh[i]]+t;tmp.num=min(tmp.num,lsh[i]);}
		}
		for(int i=rl;i<=r;i++)
		{
			cnt[lsh[i]]++;int t=s[ys[r]-1][lsh[i]]-s[ys[l]][lsh[i]];
			if(cnt[lsh[i]]+t>tmp.cnt) {tmp.cnt=cnt[lsh[i]]+t;tmp.num=lsh[i];}
			else if(cnt[lsh[i]]+t==tmp.cnt) {tmp.cnt=cnt[lsh[i]]+t;tmp.num=min(tmp.num,lsh[i]);}
		}
	}
//	for(int i=1; i<=n; ++i) cout << cnt[lsh[i]] << "\n";
	return b[tmp.num];
}

int main()
{
	n=read();m=read();block=sqrt(n);bnum=ceil((double)n/block);
	for(int i=1;i<=n;i++) {a[i]=read();ys[i]=(i-1)/block+1;b[i]=a[i];}
	sort(b+1,b+n+1);lastn=unique(b+1,b+n+1)-(b+1);
	for(int i=1;i<=n;i++) lsh[i]=lower_bound(b+1,b+lastn+1,a[i])-b;
	for(int i=1;i<=bnum;i++)
	{
		for(int j=1;j<=lastn;j++) s[i][j]=s[i-1][j];
		int l=(i-1)*block+1,r=i*block;
		if(r>n) r=n;
		for(int j=l;j<=r;j++) s[i][lsh[j]]++;
	}
//	for(int i=1;i<=lastn;i++) cout << b[i] << " ";
//	cout << "\n";
//	for(int i=1;i<=n;i++) cout << lsh[i] << " ";
	for(int i=1;i<=bnum;i++)
	{
		node tmp=(node){0,0};
		memset(cnt,0,sizeof(cnt));
		for(int j=i;j<=bnum;j++)
		{
			for(int k=(j-1)*block+1;k<=min(n,j*block);k++)
			{
				cnt[lsh[k]]++;
				if(cnt[lsh[k]]>tmp.cnt) {tmp.cnt=cnt[lsh[k]];tmp.num=lsh[k];}
				else if(cnt[lsh[k]]==tmp.cnt) {tmp.cnt=cnt[lsh[k]];tmp.num=min(tmp.num,lsh[k]);}
			}
			ans[i][j]=tmp;
		}
	}
//	cout << block << "\n" << bnum << "\n";
//	for(int i=1;i<=bnum;i++)
//		for(int j=1;j<=bnum;j++) cout << i << " " << j << " " << ans[i][j].cnt << " " << ans[i][j].num << "\n";
	for(int i=1;i<=m;i++)
	{
		int l=read(),r=read();
		l=l ^ lastans;r=r ^ lastans;
		if(l>r) swap(l,r);
		printf("%d\n",lastans=ask(l,r));
	}
	return 0;
}
