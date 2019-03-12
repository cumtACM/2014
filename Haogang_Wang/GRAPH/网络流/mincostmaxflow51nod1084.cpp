/* 51NOD1084
原题的真正要求的是从原点到终点的两条路径，他们覆盖的方格的和最大。
本题正统解法是dp,dp[i][x1][x2]代表第i步第一号路径在第x1行，二号路径在第x2行是的最大和。
在左上面建一个源点，与(1,1)点连上，容量为2，费用为0。在右下建一个汇点，与(n,m)连上，容量为2，费用为0.
然后在中间的每个点(i,j)，拆成两个点，建立两条边，一条是容量为1，费用为A[i][j]。另一条容量也是1，费用为0。再把右边和下边的点都连上。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 100005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

template<class T>
inline void read(T &x) {
    x = 0;
    T flag=1;
    char c;
    do {
        c = (char)getchar();
        if(c=='-') break;
    } while (c < '0' || c > '9');
    if(c=='-')
        c='0',flag=-1;
    do {
        x = x * 10 + c - '0';
        c = (char)getchar();
    } while (c >= '0' && c <= '9');
    x*=flag;
}

int m,n;
int a[205][205];
struct Edge{
    int from,to,cap,flow,cost;
    Edge(){}
    Edge(int f,int t,int c,int fw,int ct){
        from=f;to=t;cap=c;flow=fw;cost=ct;
    }
};

struct MCMF{
    int n,m;
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
        for(int i=0;i<n;i++) d[i]=INF;
        memset(inq,false,sizeof(inq));
        d[s]=0;inq[s]=true;p[s]=0;a[s]=INF;
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
        if(d[t]==INF) return false;
        flow+=a[t];
        cost+=d[t]*a[t];
//        printf("%d:%d\n",t,d[t]);
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
int main() {
    read(m);read(n);
    solve.init(n*m*2+2);
    int s,e;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            read(a[i][j]);
            s=((i-1)*m+j)*2-1;
            e=s+1;
            solve.AddEdge(s,e,1,-a[i][j]);
            solve.AddEdge(s,e,1,0);
            if(i+1<=n) {
                s=((i-1)*m+j)<<1;
                e=(i*m+j)*2-1;
                solve.AddEdge(s,e,2,0);
            }
            if(j+1<=m) {
                s=((i - 1)*m + j) << 1;
                e=((i - 1)*m + j + 1) * 2 - 1;
                solve.AddEdge(s,e,2,0);
            }
        }
    }
    solve.AddEdge(0,1,2,0);
    solve.AddEdge(n*m*2,n*m*2+1,2,0);
    printf("%d\n",-solve.Mincost(0,n*m*2+1));
    return 0;
}
