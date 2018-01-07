// 最小割最小边sap版本 HDU6217
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <map>
#include <set>
#include <cmath>

#define MIN(a,b) (a)<(b)?(a):(b)
#define MAX(a,b) (a)>(b)?(a):(b)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 205;
const int maxm = 3005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;
const int mod = 100010;

inline void read(int &x) {
    x=0;
    char c;
    do {
        c= getchar();
    } while (c<'0'||c>'9');
    do {
        x = x*10+c-'0';
        c= getchar();
    } while (c>='0'&&c<='9');
}
struct Edge{
    int to, next;
    lolo cap, flow;
}edge[maxm];
int tol, head[maxn];
int gap[maxn], dep[maxn], pre[maxn], cur[maxn];
void init(){
    tol = 0;
    memset(head, -1, sizeof(head));
}
void addedge(int u, int v, lolo w, int rw = 0){
    edge[tol].to = v; edge[tol].cap = w; edge[tol].next = head[u];
    edge[tol].flow = 0; head[u] = tol++;
    edge[tol].to = u; edge[tol].cap = rw; edge[tol].next = head[v];
    edge[tol].flow = 0; head[v] = tol++;
}
int sap(int st, int ed, int N){
    memset(gap, 0 ,sizeof(gap));
    memset(dep, 0 ,sizeof(dep));
    memcpy(cur, head, sizeof(head));
    int u = st;
    pre[u] = -1;
    gap[0] = N;
    int ans = 0;
    while(dep[st] < N){
        if(u == ed){
            lolo Min = inf;
            for(int i = pre[u]; i != -1; i = pre[edge[i^1].to])
                if(Min > edge[i].cap - edge[i].flow)
                    Min = edge[i].cap - edge[i].flow;
            for(int i = pre[u]; i != -1; i = pre[edge[i^1].to]){
                edge[i].flow += Min;
                edge[i^1].flow -= Min;
            }
            u = st;
            ans += Min;
            continue;
        }
        bool flag = false;
        int v;
        for(int i = cur[u]; i != -1; i = edge[i].next){
            v = edge[i].to;
            if(edge[i].cap - edge[i].flow && dep[v] + 1 == dep[u]){
                flag = true;
                cur[u] = pre[v] = i;
                break;
            }
        }
        if(flag){
            u = v;
            continue;
        }
        int Min = N;
        for(int i = head[u]; i!= -1; i = edge[i].next){
            if(edge[i].cap - edge[i].flow && dep[edge[i].to] < Min){
                Min = dep[edge[i].to];
                cur[u] = i;
            }
        }
        gap[dep[u]]--;
        if(!gap[dep[u]]) return ans;
        dep[u] = Min + 1;
        gap[dep[u]]++;
        if(u != st) u = edge[pre[u]^1].to;
    }
    return ans;
}

int main(){
    //freopen("in.txt","r",stdin);
    int T,s,t;
    int n, m, a, b, c;
    read(T);
    while(T--) {
        init();
        read(n);
        read(m);
        read(s);
        read(t);
        for(int i=0;i<m;i++) {
            read(a);read(b);read(c);
            addedge(a,b,c*mod+1);
        }
        printf("%d\n", sap(s, t, n)%mod);
    }
    return 0;
}
