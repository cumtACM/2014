/*
 换成head会慢一倍
 思路:求网线被破坏的最小概率可以转化为不被破坏的最大概率来求,
 这个概率显然就是你要经过哪些点的(1-p)的乘积嘛，那么取个log就
 变成加法的了，令源点连向人数多余的点，汇点连向食物多余的点，跑
 一次最小费用最大流然后再取回对数就可以了
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 205;
const int maxm = 20005;
const double INF = 1e10;
const double eps = 1e-8;
const int inf=0x3f3f3f3f;
template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') c = '0', flag = -1;
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}

struct Edge
{
    int from,to,cap,flow;
    double cost;
    Edge(){}
    Edge(int f,int t,int c,int fl,double co):from(f),to(t),cap(c),flow(fl),cost(co){}
};
struct MCMF
{
    int n,m,s,t;
    vector<Edge>edges;
    vector<int>g[maxn];
    bool inq[maxn];
    double d[maxn];
    int p[maxn];
    int a[maxn];
    void init(int n,int s,int t)
    {
        this->n=n;
        this->s=s;
        this->t=t;
        edges.clear();
        for(int i = 0;i<=n;i++)g[i].clear();
    }
    void AddEdge(int from,int to,int cap,double cost)
    {
        edges.push_back(Edge(from,to,cap,0,cost));
        edges.push_back(Edge(to,from,0,0,-cost));
        m=edges.size();
        g[from].push_back(m-2);
        g[to].push_back(m-1);
    }
    bool BellmanFord(int &flow,double &cost)
    {
        for(int i = 0;i<=n;i++)d[i]=inf;
        memset(inq,0,sizeof(inq));
        d[s]=0,a[s]=inf,inq[s]=1,p[s]=0;
        queue<int>q;
        q.push(s);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            inq[u]=0;
            for(int i = 0;i<g[u].size();i++)
            {
                Edge &e = edges[g[u][i]];
                if(e.cap>e.flow&&d[e.to]>d[u]+e.cost+eps)
                {
                    d[e.to]=d[u]+e.cost;
                    p[e.to]=g[u][i];
                    a[e.to]=min(a[u],e.cap-e.flow);
                    if(!inq[e.to])
                    {
                        q.push(e.to);
                        inq[e.to]=1;
                    }
                }
            }
        }
        if(d[t]==inf)return false;
        flow+=a[t];
        cost+=a[t]*d[t];
        int u = t;
        while(u!=s)
        {
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
            u=edges[p[u]].from;
        }
        return true;
    }
    void Mincost(int &flow,double &cost) {
        flow=0,cost=0;
        while(BellmanFord(flow,cost));
    }
}mcmf;
int main() {
//    freopen("in.txt","r",stdin);
    int T,n,m,s,b;
    int u,v,c,e;
    double p,ans;
    read(T);
    while(T--) {
        read(n);read(m);
        mcmf.init(n+2,0,n+1);
        for(int i=1;i<=n;i++) {
            read(s);read(b);
            e=s-b;
            if(e>0)
                mcmf.AddEdge(0,i,e,0);
            if(e<0)
                mcmf.AddEdge(i,n+1,-e,0);
        }
        for(int i=0;i<m;i++) {
            read(u);read(v);read(c);
            scanf("%lf",&p);
            if(c<=0) continue;
            p=-log(1.0-p);
            mcmf.AddEdge(u,v,1,0);
            if(c>1) {
                mcmf.AddEdge(u,v,c-1,p);
            }
        }
        int flow;
        double ans;
        mcmf.Mincost(flow,ans);
        ans=exp(-ans);
        printf("%.2f\n",1.0-ans);
    }
}