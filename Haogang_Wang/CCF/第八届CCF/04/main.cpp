#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int N=10010;
const int inf=0x3f3f3f3f;
struct Edge{
	int from,to,dist;
	Edge(int a=0,int b=0,int c=0){
		from=a;to=b;dist=c;
	}
};
struct node{
	int u,d;
	node(int a=0,int b=0){
		u=a;d=b;
	}
	bool operator<(const node& b) const{
		return d>b.d;
	}
};
struct node2{
	int u,d;
	node2(int a=0,int b=0){
		u=a;d=b;
	}
	bool operator<(const node2& b) const{
		return d<b.d;
	}
};
bool cmp(int a,int b);
struct Solver{
	int n,m;
	int d[N];
	set<int> pa[N];
	bool done[N];
	bool ct[200010];
	vector<int> G[N];
	vector<Edge> e;
	int add[N];
	int p[N];
	int findp(int x){
		return p[x]==x?x:p[x]=findp(p[x]);
	}
	
	void init(int nn){
		n=nn;
		for(int i=1;i<=n;i++){
			pa[i].clear();
			G[i].clear();
			p[i]=i;
		} 
		e.clear();
	}
	void addEdge(){
		int u,v,d;
		scanf("%d%d%d",&u,&v,&d);
		e.push_back(Edge(u,v,d));
		e.push_back(Edge(v,u,d));
		m=e.size();
		G[u].push_back(m-2);
		G[v].push_back(m-1);
	}
	void dijkstra(){
		priority_queue<node> Q;
		Q.push(node(1,0));
		memset(d,inf,sizeof(d));
		memset(done,false,sizeof(done));
		d[1]=0;
		while(!Q.empty()){
			node t=Q.top();Q.pop();
			int u=t.u;
			if(done[u]) continue;
			done[u]=true;
			for(int i=0;i<G[u].size();i++) {
				Edge& x=e[G[u][i]];
				if(d[x.to]>d[u]+x.dist){
					d[x.to]=d[u]+x.dist;
					pa[x.to].clear();
					pa[x.to].insert(G[u][i]);
					Q.push(node(x.to,d[x.to]));
				}
				else if(d[x.to]==d[u]+x.dist){
					pa[x.to].insert(G[u][i]);
				}
			}
		}
	}
	int prim(){
		dijkstra();
		memset(ct,false,sizeof(ct));
		memset(done,false,sizeof(done));
		memset(add,0,sizeof(add));
		int ans=0;
		for(int i=2;i<=n;i++){
			for(set<int>::iterator j=pa[i].begin();j!=pa[i].end();j++)
				if(!ct[*j]) {
					ct[*j]=true;
				}	
		}
		int cnt=1;
		priority_queue<node2> Q;
		Q.push(node2(1,0));
		done[1]=true;
		while(!Q.empty()){
			node2 t=Q.top();Q.pop();
			int u=t.u;
			for(int i=0;i<G[u].size();i++){
				if(!ct[G[u][i]]) continue;
				Edge& x=e[G[u][i]];
				if(done[x.to]){
					if(x.dist<add[x.to]&&d[u]+x.dist==d[x.to]){
						ans-=add[x.to];
						ans+=x.dist;
						add[x.to]=x.dist;
					}
				}
				else{
					ans+=x.dist;
					add[x.to]=x.dist;
					Q.push(node2(x.to,t.d+x.dist));
					done[x.to]=true;
				} 
			}
		}
		return ans;
	}
}solver;
bool cmp(int a,int b){
		return solver.e[a].dist<solver.e[b].dist;
}
int main(void) {
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF){
		solver.init(n);
		for(int i=0;i<m;i++)
			solver.addEdge();
		printf("%d\n",solver.prim());
	}
	return 0;
} 
