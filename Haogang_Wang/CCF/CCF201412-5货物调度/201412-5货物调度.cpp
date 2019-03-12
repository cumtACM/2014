#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

const int maxn=702;
const int inf=0x3f3f3f3f;
struct Edge{
	int from,to,cap,flow,cost;
	Edge(){}
	Edge(int f,int t,int c,int fw,int ct){
		from=f;to=t;cap=c;flow=fw;cost=ct;
	}
};

struct MCMF{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool inq[maxn];
	int d[maxn],p[maxn],a[maxn];

	void init(int n){
		this->n=n;
		for(int i=0;i<n;i++) G[i].clear();
		edges.clear();
	}
	void AddEdge(int from,int to,int cap,int cost){
		edges.push_back(Edge(from,to,cap,0,cost));
		edges.push_back(Edge(to,from,0,0,-cost));
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	bool BellmanFord(int s,int t,int& flow,int& cost){
		for(int i=0;i<n;i++) d[i]=inf;
		memset(inq,false,sizeof(inq));
		d[s]=0;inq[s]=true;p[s]=0;a[s]=inf;
		queue<int> Q;
		Q.push(s);
		while(!Q.empty()){
			int u=Q.front();Q.pop();
			inq[u]=false;
			for(int i=0;i<G[u].size();i++){
				Edge& e=edges[G[u][i]];
				if(e.cap>e.flow&&d[e.to]>d[u]+e.cost){
					d[e.to]=d[u]+e.cost;
					p[e.to]=G[u][i];
					a[e.to]=min(a[u],e.cap-e.flow);
					if(!inq[e.to]){
						Q.push(e.to);
						inq[e.to]=true;
					}
				}
			}
		}
		if(d[t]==inf) return false;
		flow+=a[t];
		cost+=d[t]*a[t];
		int u=t;
		while(u!=s){
			edges[p[u]].flow+=a[t];
			edges[p[u]^1].flow-=a[t];
			u=edges[p[u]].from;
		}
		return true;
	}
	int Mincost(int s,int t){
		int flow=0,cost=0;
		while(BellmanFord(s,t,flow,cost));
		return cost;
	}
}solve;


int main(void){
	int n,m;
	while(scanf("%d %d",&n,&m)==2){
		int x,v,w;
		int s=0,t=7*n+1; 
		solve.init(7*n+2);
		for(int i=0;i<n;i++){
			for(int j=1;j<=7;j++){
				scanf("%d",&x);
				solve.AddEdge(0,7*i+j,x,0);   // 源点向第i个城市第j天连容量a[ij]费用0的边
			}
			for(int j=1;j<=7;j++){
				scanf("%d",&x);
				solve.AddEdge(7*i+j,t,x,0);   // 第i个城市第j天向汇点连容量b[ij][费用0的边
			}
			scanf("%d %d",&v,&w);
			for(int j=1;j<7;j++)
				solve.AddEdge(7*i+j,7*i+j+1,v,w); // 第i个城市每一天都向下一天连容量v[i]费用w[i]的边
			solve.AddEdge(7*i+7,7*i+1,v,w);        // PS:这一周的最后一天的下一天是下一周的第一天
		}
		while(m--){
			int sk,tk,ck;
			scanf("%d %d %d",&sk,&tk,&ck);
			sk--;tk--;
			for(int i=1;i<=7;i++){
				solve.AddEdge(7*sk+i,7*tk+i,inf,ck);  // 第s个城市每一天向当天的第t个城市连容量INF费用c的边
				solve.AddEdge(7*tk+i,7*sk+i,inf,ck);  // 第t个城市每一天向当天的第s个城市连容量INF费用c的边
			}
		}
		printf("%d\n",solve.Mincost(s,t));
	}
	return 0;
}