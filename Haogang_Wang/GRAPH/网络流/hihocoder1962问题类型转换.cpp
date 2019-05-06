#include <bits/stdc++.h>

using namespace std;

const int maxn = 505;
const int INF = 0x3f3f3f3f;

template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') { c = '0', flag = -1;}
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}

struct Con {
        int s, e, w;
    }cons[255];
struct Edge {
    int from,to,cap,flow;
    int cost;
    Edge(){}
    Edge(int f,int t,int c,int fl,int co):from(f),to(t),cap(c),flow(fl),cost(co){}
};
struct MCMF {
    int n,m,s,t;
    vector<Edge>edges;
    vector<int>g[maxn];
    bool inq[maxn];
    int d[maxn];
    int p[maxn];
    int a[maxn];
    void init(int n,int s,int t) {
        this->n=n;
        this->s=s;
        this->t=t;
        edges.clear();
        for(int i = 0;i<=n;i++)g[i].clear();
    }
    void AddEdge(int from,int to,int cap,int cost) {
        edges.push_back(Edge(from,to,cap,0,cost));
        edges.push_back(Edge(to,from,0,0,-cost));
        m=edges.size();
        g[from].push_back(m-2);
        g[to].push_back(m-1);
    }
    bool BellmanFord(int &flow,int &cost) {
        for(int i = 0;i<=n;i++)d[i]=INF;
        memset(inq,0,sizeof(inq));
        d[s]=0,a[s]=INF,inq[s]=1,p[s]=0;
        queue<int>q;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u]=0;
            for(int i = 0;i<g[u].size();i++) {
                Edge &e = edges[g[u][i]];
                if(e.cap>e.flow&&d[e.to]>d[u]+e.cost) {
                    d[e.to]=d[u]+e.cost;
                    p[e.to]=g[u][i];
                    a[e.to]=min(a[u],e.cap-e.flow);
                    if(!inq[e.to]) {
                        q.push(e.to);
                        inq[e.to]=1;
                    }
                }
            }
        }
        if(d[t]==INF)return false;
        flow+=a[t];
        cost+=a[t]*d[t];
        int u = t;
        while(u!=s) {
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
            u=edges[p[u]].from;
        }
        return true;
    }
    void Mincost(int &flow,int &cost) {
        flow=0,cost=0;
        while(BellmanFord(flow,cost));
    }
}mcmf;
map<int, int> mp;
int main() {
    int n, m;
    read(n);
    read(m);
    for (int i = 0; i < n; ++i) {
        read(cons[i].s);
        read(cons[i].e);
        read(cons[i].w);
        mp[cons[i].s] = 0;
        mp[cons[i].e] = 0;
    }
    int id = 2;
    for (map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
        mp[it->first] = ++id;
    }
    mcmf.init(id, 1, 2);
    for (int i = 3; i < id; ++i) {
        mcmf.AddEdge(i, i+1, m, 0);
    }
    for (int i = 0; i < n; ++i) {
        mcmf.AddEdge(mp[cons[i].s], mp[cons[i].e], 1, -cons[i].w);
    }
    mcmf.AddEdge(1, 3, m, 0);
    mcmf.AddEdge(id, 2, m, 0);
    int flow = 0;
    int ans = 0;
    mcmf.Mincost(flow, ans);
    printf("%d\n", -ans);
    return 0;
}
