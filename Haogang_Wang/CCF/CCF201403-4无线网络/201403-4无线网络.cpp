#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int inf=0x3f3f3f3f;
typedef long long ll;
struct Point{
	int x,y;
}p[202];
struct node{
	int t,pn;
};
int n,m,k;ll r;
ll dist2(int x,int y){
	return (ll)(p[x].x-p[y].x)*(p[x].x-p[y].x)
		+(ll)(p[x].y-p[y].y)*(p[x].y-p[y].y);
}
bool vis[202][101];
int d[202][101],gr[202][202];

void spfa(){
	queue<node> Q;
	memset(d,inf,sizeof(d));
	memset(vis,false,sizeof(vis));
	node u,v;
	int tp;
	u.pn=u.t=0;
	vis[0][0]=true;
	d[0][0]=0;
	Q.push(u);
	while(!Q.empty()){
		u=Q.front();Q.pop();
		vis[u.t][u.pn]=false;
		for(int i=0;i<n+m;i++)
			if(gr[u.t][i]){
				tp=u.pn;
				if(i>=n) tp++;
				if(tp<=k&&d[i][tp]>d[u.t][u.pn]+1){
					d[i][tp]=d[u.t][u.pn]+1;
					if(!vis[i][tp]){
						vis[i][tp]=true;
						v.pn=tp;v.t=i;
						Q.push(v);
					}
				}
			} 	 
	}
	int ans=inf;
	for(int i=0;i<=k;i++) ans=min(ans,d[1][i]);
	printf("%d\n",ans-1);
}
int main(void){
	while(scanf("%d%d%d%lld",&n,&m,&k,&r)==4){
		r*=r;
		memset(gr,false,sizeof(gr));
		for(int i=0;i<n+m;i++) scanf("%d%d",&p[i].x,&p[i].y);
		for(int i=0;i<n+m;i++)
			for(int j=i+1;j<n+m;j++)
				if(dist2(i,j)<=r) gr[i][j]=gr[j][i]=true;
		spfa();
	}
    return 0;
}