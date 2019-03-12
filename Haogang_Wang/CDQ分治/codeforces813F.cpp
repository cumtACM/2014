/*
You are given an undirected graph consisting of n vertices. 
Initially there are no edges in the graph. Also you are given
 q queries, each query either adds one undirected edge to the 
 graph or removes it. After each query you have to check if the
  resulting graph is bipartite 
*/
#include <iostream>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#include <stack>
#include <map>
#include <set>
#include <ctime>
#include <cmath>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IN(x,L,R) ((x)>=L&&(x)<=R)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 101010;
const int maxm = 200005;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;
const int MOD = 1000000007;

template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') c = '0', flag = -1;
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}
char str[1100];
string scf() {
    scanf("%s",str);
    return str;
}
template<class T>
inline void out(T x) {
    if(x>9) out(x/10);
    x=x%10;
    putchar('0'+x);
}
int pa[maxn],rk[maxn],dpt[maxn];
pii edge[maxn];
vector<pii> e[maxn<<2];        // 在这个区间有的边
bool ans[maxn];
pii findset(int x) {
    int d=0;
    while(pa[x]!=x) {
        d^=dpt[x];
        x=pa[x];
    }
    d^=dpt[x];
    return make_pair(x, d);
}
void solve(int o,int L,int R) {
    bool flag=true;
    vector<pair<int*,int> > sta;
    for (int i = 0; i <e[o].size(); ++i) {
        int &x=e[o][i].first,&y=e[o][i].second;
        pii fx = findset(x),fy = findset(y);
        if(fx.first==fy.first) {
            if(!(fx.second^fy.second)) {
                flag=false;
                break;
            }
        } else {
            if(rk[fx.first]<rk[fy.first]) swap(fx, fy);
            if(rk[fx.first]==rk[fy.first]) {
                sta.push_back(make_pair(rk+fx.first, rk[fx.first]));
                rk[fx.first]++;
            }
            sta.push_back(make_pair(pa+fy.first, pa[fy.first]));
            sta.push_back(make_pair(dpt+fy.first,dpt[fy.first]));
            pa[fy.first]=fx.first;
            dpt[fy.first]^=(fx.second^fy.second);
        }
    }
    if(!flag) {
        fill(ans+L, ans+R+1, false);      // 无需继续分治
    } else {
        if (L == R) {
            ans[L] = flag;
        } else {
            int M = L + R >> 1, lson = o << 1, rson = o << 1 | 1;
            solve(lson, L, M);
            solve(rson, M + 1, R);
        }
    }
    IFOR(j, sta.size()-1, 0) {          // 回溯
        *sta[j].first=sta[j].second;
    }
}

int ql,qr;
void ins(int o,int L,int R,const pii& eg) {        // 向区间[L,R]中加入边
    if(ql<=L&&qr>=R) {
        e[o].push_back(eg);
        return;
    }
    int M=(L+R)>>1;
    if(ql<=M) ins(o<<1, L, M, eg);
    if(qr>M) ins(o<<1|1, M+1, R, eg);
}
map<pii,vector<int> > ecnt;
int main() {
    int n, q;
    read(n);
    read(q);
    FOR(j, 1, n) {
        pa[j] = j;
        rk[j] = 1;
        dpt[j] = 1;
    }
    FOR(j, 1, q) {
        read(edge[j].first);
        read(edge[j].second);
        if(!ecnt.count(edge[j])) ecnt[edge[j]]=vector<int>();
        vector<int> &vec=ecnt[edge[j]];
        vec.push_back(j);
        if(!(vec.size()&1)) {
            ql=vec[vec.size()-2];
            qr=j-1;                   // 边的加入时间和撤销时间
            ins(1, 1, q, edge[j]);
        }
    }
    FOR(j, 1, q) {                        // 加入到最后都不会被撤销的边
        vector<int> &vec=ecnt[edge[j]];
        if(vec.size()&1) {
            if(j==vec[vec.size()-1]) {
                ql=j;qr=q;
                ins(1, 1, q, edge[j]);
            }
        }
    }
    solve(1, 1, q);
    FOR(j, 1, q) {
        puts(ans[j]?"YES":"NO");
    }
    putchar('\n');
    return 0;
}