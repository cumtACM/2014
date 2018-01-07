/*��������
����ĳ��˾Ҫ����һ�������Ե��������⡣
������n�����У���i��������ÿ�ܵĵ�j(1��j��7) �������aij��ĳ�ֻ��ͬʱ��Ҫ����bij�ָ��ֻ����֪ÿ�ܵĲ�����������������aij֮�͵���bij֮�ͣ���
��������֮����m����·����k����·�����˳���sk��tk��һ����·������1�ֻ�����һ���̶��ĳɱ�ck����·������˫��ʹ�á�ÿ������Ļ�����û�����ơ�����֮��ľ��벢��Զ��������Դ�����һ���������䵽������һ�����в����ڵ��쵽�
������������ڵ���û�б����ĵ�������Ҫ����ڲֿ����ҹ����i�����еĲֿ�����Ϊvi�����1 �ֻ����һҹ����ĳɱ���wi��
�����������ù�˾���ÿ��ѭ���Եذ���һ���̶������̵��Ȼ���Ļ����ù�˾�����ŷ�����ÿ����ҪΪ���������ʹ洢���Ķ��ٳɱ���
�����ʽ
��������ĵ�һ��������������n��m�������еĸ����͵�·��������
������������n�У�ÿ�а���16������������������i�����е�������ݡ����е�i�а�������Ϊai1, ai2, ai3, ai4, ai5, ai6, ai7, bi1, bi2, bi3, bi4, bi5, bi6, bi7, vi, wi��
������������m�У�ÿ�а���3����������������һ����·��������ݡ����е�k�а�������Ϊsk, tk��ck��
�������������г��еı�ž�Ϊ1��n֮�䡣�������ݵ�ÿ�е�������β����֤û�пո�������֮��ǡ�ñ�һ���ո������
�����ʽ
������ֻ��Ҫ���һ�����������ŷ�����ÿ�ܵ�֧����
��������
3 3
0 0 0 0 5 0 0 0 0 0 0 0 0 0 2 4
0 0 0 0 0 0 0 2 0 0 0 0 0 0 2 1
0 0 0 0 0 0 0 0 0 3 0 0 0 0 2 5
1 2 1
1 3 5
2 3 1
�������
67
����˵��
��������1 ÿ��������5 �ֻ��������2 ���˵��洢���õ����ĳ���2 �洢����1 ���˵�����3 �洢��ʣ�µ�2 �����ڳ���1��
�����ڴ���һ��ʱ�����2 �����ĵ�����������2 �ֻ��Ϊ�˽�Լ�洢�ɱ������ڷ��ڳ���1 �Ļ����˵�����2 ��š������ٽ����л����˵�����3 ������ó��е�����
�����ڴ˷����£�ÿ�ܵ�����ɱ�Ϊ8��ÿ�ܵĴ洢�ɱ�Ϊ59�����ÿ�ܵ���֧��Ϊ67��
����������ģ��Լ��
��������100%�����ݣ�1��n��100��1��m��500��0��aij,bij,vi��100��1��wi,ck��100��*/
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
				solve.AddEdge(0,7*i+j,x,0);   // Դ�����i�����е�j��������a[ij]����0�ı�
			}
			for(int j=1;j<=7;j++){
				scanf("%d",&x);
				solve.AddEdge(7*i+j,t,x,0);   // ��i�����е�j������������b[ij][����0�ı�
			}
			scanf("%d %d",&v,&w);
			for(int j=1;j<7;j++)
				solve.AddEdge(7*i+j,7*i+j+1,v,w); // ��i������ÿһ�춼����һ��������v[i]����w[i]�ı�
			solve.AddEdge(7*i+7,7*i+1,v,w);        // PS:��һ�ܵ����һ�����һ������һ�ܵĵ�һ��
		}
		while(m--){
			int sk,tk,ck;
			scanf("%d %d %d",&sk,&tk,&ck);
			sk--;tk--;
			for(int i=1;i<=7;i++){
				solve.AddEdge(7*sk+i,7*tk+i,inf,ck);  // ��s������ÿһ������ĵ�t������������INF����c�ı�
				solve.AddEdge(7*tk+i,7*sk+i,inf,ck);  // ��t������ÿһ������ĵ�s������������INF����c�ı�
			}
		}
		printf("%d\n",solve.Mincost(s,t));
	}
    return 0;
}