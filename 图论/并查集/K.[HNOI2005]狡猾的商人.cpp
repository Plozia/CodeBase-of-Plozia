#include<bits/stdc++.h>
using namespace std;

const int MAXN=100+10;
int t,n,m,dis[MAXN],cnt[MAXN];
bool book[MAXN],vis[MAXN];
vector<int>Num[MAXN],Next[MAXN];

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*fh;
}

bool SPFA(int qsd)
{
	queue<int>q;
	for(int i=1;i<=n;i++) dis[i]=-0x3f3f3f3f;
	q.push(qsd);book[qsd]=1;dis[qsd]=0;
	while(!q.empty())
	{
		int x=q.front();q.pop();book[x]=0;cnt[x]++;
		if(cnt[x]>=n) return 1;
		for(int i=0;i<Num[x].size();i++)
		{
			int w=Num[x][i],u=Next[x][i];
			if(dis[x]+w>dis[u])
			{
				dis[u]=dis[x]+w;vis[u]=1;
				if(!book[u]) {book[u]=1;q.push(u);}
			}
		}
	}
	return 0;
}

int main()
{
	t=read();
	while(t--)
	{
		n=read();m=read();
		memset(cnt,0,sizeof(cnt));
		memset(vis,0,sizeof(vis));
		memset(book,0,sizeof(book));
		for(int i=0;i<=n;i++) Next[i].clear(),Num[i].clear();
		for(int i=1;i<=m;i++)
		{
			int x=read();int y=read();int z=read();
			Next[x-1].push_back(y);Next[y].push_back(x-1);
			Num[x-1].push_back(z);Num[y].push_back(-z);
		}
		bool flag=0;
		for(int i=0;i<=n;i++)
		{
			if(!vis[i]) flag=SPFA(i);
			if(flag) break;
		}
		if(flag) cout<<"false\n";
		else cout<<"true\n";
	}
	return 0;
}
