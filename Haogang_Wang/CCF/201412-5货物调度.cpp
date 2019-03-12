/*问题描述
　　某公司要处理一个周期性的物流问题。
　　有n个城市，第i个城市在每周的第j(1≤j≤7) 天会生产aij吨某种货物，同时需要消耗bij吨该种货物。已知每周的产量等于消耗量（即aij之和等于bij之和）。
　　城市之间有m条道路，第k条道路连接了城市sk和tk。一条道路上运输1吨货物有一个固定的成本ck。道路都可以双向使用。每天运输的货物量没有限制。城市之间的距离并不远，货物可以从任意一个城市运输到任意另一个城市并且在当天到达。
　　货物如果在当天没有被消耗掉，就需要存放在仓库里过夜。第i个城市的仓库容量为vi，存放1 吨货物过一夜所需的成本是wi。
　　请你计算该公司如果每周循环性地按照一个固定的流程调度货物的话，该公司在最优方案下每周需要为货物的运输和存储消耗多少成本。
输入格式
　　输入的第一行有两个正整数n和m，即城市的个数和道路的条数。
　　接下来有n行，每行包含16个整数，用以描述第i个城市的相关数据。其中第i行包含的数为ai1, ai2, ai3, ai4, ai5, ai6, ai7, bi1, bi2, bi3, bi4, bi5, bi6, bi7, vi, wi。
　　接下来有m行，每行包含3个整数，用以描述一条道路的相关数据。其中第k行包含的数为sk, tk和ck。
　　输入数据中城市的编号均为1到n之间。输入数据的每行的行首行尾均保证没有空格，两个数之间恰好被一个空格隔开。
输出格式
　　你只需要输出一个数，即最优方案下每周的支出。
样例输入
3 3
0 0 0 0 5 0 0 0 0 0 0 0 0 0 2 4
0 0 0 0 0 0 0 2 0 0 0 0 0 0 2 1
0 0 0 0 0 0 0 0 0 3 0 0 0 0 2 5
1 2 1
1 3 5
2 3 1
样例输出
67
样例说明
　　城市1 每周五生产5 吨货物，把其中2 吨运到存储费用低廉的城市2 存储，把1 吨运到城市3 存储，剩下的2 吨留在城市1。
　　在次周一的时候城市2 会消耗掉存放在那里的2 吨货物。为了节约存储成本，将囤放在城市1 的货物运到城市2 存放。周三再将所有货物运到城市3 以满足该城市的需求。
　　在此方案下，每周的运输成本为8，每周的存储成本为59，因此每周的总支出为67。
评测用例规模与约定
　　对于100%的数据，1≤n≤100，1≤m≤500，0≤aij,bij,vi≤100，1≤wi,ck≤100。*/
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