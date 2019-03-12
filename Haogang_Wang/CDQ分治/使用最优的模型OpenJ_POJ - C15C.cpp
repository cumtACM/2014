// 等价于与在每个时间删除一些边后求可达点对
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
#include <iomanip>

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

pii edge[maxn<<1];
lolo ans[maxn];

vector<int> C[maxn];
int n, m, k;

struct DisjointSet{
    // save() is like recursive
    // undo() is like return
    int n, pa[ maxn ], sz[ maxn ];
    vector< pair<int,int> > h;
    vector<int> sp;
    lolo pcnt;
    void init( int tn ){
        n=tn;
        pcnt=0;
        FOR(i, 1, n) {
            pa[i]=i;
            sz[i]=1;
        }
        sp.clear(); h.clear();
    }

    int findset(int x) {
        while(pa[x]!=x) {
            x=pa[x];
        }
        return x;
    }
    void uni( int x , int y ){
        int fx = findset(x), fy = findset(y);
        if(fx!=fy) {
            if(sz[fx]<sz[fy]) swap(fx, fy);
            h.push_back(make_pair(fx, fy));
            pcnt += 1LL*sz[fx]*sz[fy];
            pa[fy]=fx;
            sz[fx]+=sz[fy];
        }
    }
    void save(){ sp.push_back(h.size());}
    void undo(){
        int last=sp.back(); sp.pop_back();
        while( h.size()!=last ){
            int x=h.back().first,y=h.back().second;
            h.pop_back();
            sz[x]-=sz[y];
            pa[y]=y;
            pcnt -= 1LL*sz[x]*sz[y];
        }
    }
} djs;


void solve(int L,int R);
void process(int L,int R, int OL,int OR) {
    djs.save();
    FOR(i, OL, OR) {          // 把外部的先处理，就是把边连起来
        for (int j = 0; j < C[i].size(); ++j) {
            djs.uni(edge[C[i][j]].first, edge[C[i][j]].second);
        }
    }
    solve(L, R);
    djs.undo();
}
void solve(int L,int R) {
    if (L == R) {            // 达到只有这个时间的边没有连的效果
        ans[L]=djs.pcnt;
    } else {
        int M = L + R >> 1;
        process(L, M, M+1, R);
        process(M + 1, R, L, M);
    }
}

int main() {
    int c;
    while (scanf("%d%d%d",&n,&m,&k)==3) {
        djs.init(n);
        FOR(j, 1, k) C[j].clear();            // 记住初始化
        FOR(j, 1, m) {
            scanf("%d %d %d",&edge[j].first, &edge[j].second ,&c);
            if (c <= k) {
                C[c].push_back(j);            // 除了这个时间点以外都有这个边
                continue;
            }
            djs.uni(edge[j].first, edge[j].second);
        }
        solve(1, k);
        FOR(j, 1, k) {
            out(ans[j]);
            putchar('\n');
        }
    }
    return 0;
}