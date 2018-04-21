#include <iostream>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cctype>
#include <stack>
#include <bitset>
#include <map>
#include <set>
#include <ctime>
#include <cmath>
#include <iomanip>
//#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define IFOR(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
typedef long long lolo;
typedef long double lodo;
typedef pair<lolo,lolo> pii;
typedef unsigned long long ulolo;

const int maxn = (int)1e2 + 5;
const int maxm = (int)2e3 + 5;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-18;
const int MOD = (int)1e9+7;

template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') { c = '0', flag = -1;}
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}
template<class T>
inline void out(T x) {
    if (x > 9) out(x / 10);
    x = x % 10;
    putchar('0' + x);
}

int level[maxn],que[maxn];
int head[maxn],lon;
struct EDGE {
    int next,to;
    int c;
}e[maxm];
void edgeinit() {
    memset(head,-1,sizeof(head));
    lon=-1;
}
void edgemake(int from,int to,int c) {
    e[++lon].c=c;
    e[lon].to=to;
    e[lon].next=head[from];
    head[from]=lon;
}
void make(int from,int to,int c) {
    edgemake(from,to,c);
    edgemake(to,from,0);
}

bool makelevel(int s,int t) {
    memset(level,0,sizeof(level));
    int FRONT=1,End=0;
    que[++End]=s;
    level[s]=1;
    while(FRONT<=End)
    {
        int u=que[FRONT++];
        if(u==t) return true;
        for(int k=head[u];k!=-1;k=e[k].next)
        {
            int v=e[k].to;
            if(!level[v]&&e[k].c)
            {
                que[++End]=v;
                level[v]=level[u]+1;
            }
        }
    }
    return false;
}

int dfs(int now,int t,int maxf) {
    if(now==t||maxf==0) return maxf;
    int ret=0;
    for(int k=head[now];k!=-1;k=e[k].next) {
        int u=e[k].to;
        if(level[u]==level[now]+1&&e[k].c) {
            int f=dfs(u,t,min(e[k].c,maxf-ret));
            e[k].c-=f;
            e[k^1].c+=f;
            ret+=f;
            if(ret==maxf) return ret;
        }
    }
    if(ret==0) level[now]=0;
    return ret;
}

int maxflow(int s,int t) {
    int ret=0;
    while(makelevel(s,t)) {
        ret+=dfs(s,t,inf);
    }
    return ret;
}

int n,m;
struct Node {
    int u,v,c;
}node[505];
int main() {
    read(n);read(m);
    for (int i = 0; i < m; ++i) {
        read(node[i].u);read(node[i].v);read(node[i].c);
    }
    sort(node,node+m,[](const Node& a,const Node& b){return a.c<b.c;});
    int ans=0;
    for (int i = 0; i < m; ++i) {
        edgeinit();
        for (int j = 0; j < i; ++j) {
            if(node[j].c>=node[i].c) break;
            make(node[j].u,node[j].v,1);make(node[j].v,node[j].u,1);
        }
        ans+=maxflow(node[i].u,node[i].v);
    }
    out(ans);
    return 0;
}