/*
http://codeforces.com/contest/576/problem/E
显然可以将改变颜色转为加边、删边的操作，再用线段树式分治维护，就变成只要加边。
二分图的判定就用并查集维护就好了，每种颜色一个并查集，因为是在分治中，修改是
需要撤销的，所以用按秩合并，将操作压入栈里。
但是每一个操作会受前面操作的影响，这不符合分治所有操作互相独立的要求。
考虑线段树式分治中，所有叶子节点是按顺序被遍历到的，所以可以在遍历到叶子的时
候判断这个操作是否能被应用，并应用操作。
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
#include <iomanip>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IN(x,L,R) ((x)>=L&&(x)<=R)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 501010;
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
pii edge[maxn],qry[maxn];
vector<pii> e[maxn<<2];        // 在这个区间有的边
bool ans[maxn];
int lst[maxn],nxt[maxn],color[maxn];
vector< pair<int*,int> > h;
vector<int> sp;
int n, m, k, q, x, c;
void save(){ sp.push_back(h.size()); }
void undo(){
    int last=sp.back(); sp.pop_back();
    while( h.size()!=last ){
        auto x=h.back(); h.pop_back();
        *x.first = x.second;
    }
}
struct DisjointSet{
    // save() is like recursive
    // undo() is like return
    int n, pa[ maxn ], rk[ maxn ], dpt[maxn];
    void init( int tn ){
        n=tn;
        FOR(i, 1, n) {
            pa[i]=i;
            rk[i]=1;
            dpt[i]=1;
        }
        sp.clear(); h.clear();
    }
    void assign( int *k, int v ){
        h.push_back( {k, *k} );
        *k = v;
    }
    int findset(int &x) {
        int d=0;
        while(pa[x]!=x) {
            d^=dpt[x];
            x=pa[x];
        }
        d^=dpt[x];
        return d;
    }
    bool uni( int x , int y ){
        int fx=x,fy=y;
        int xs = findset(fx),ys = findset(fy);
        if(fx==fy) {
            if(!(xs^ys)) {
                return false;
            }
        } else {
            if(rk[fx]<rk[fy]) swap(fx, fy);
            if(rk[fx]==rk[fy]) {
                assign(rk+fx, rk[fx]+1);
            }
            assign(pa+fy, fx);
            assign(dpt+fy, dpt[fy]^xs^ys);
        }
        return true;
    }
} djs[55];
int ql,qr;
pii eg;
void ins(int o,int L,int R) {        // 向区间[L,R]中加入边
    if(ql<=L&&qr>=R) {
        e[o].push_back(eg);
        return;
    }
    int M=(L+R)>>1;
    if(ql<=M) ins(o<<1, L, M);
    if(qr>M) ins(o<<1|1, M+1, R);
}
void solve(int o,int L,int R) {
    save();
    for (int i = 0; i < e[o].size(); ++i) {
        int &x = edge[e[o][i].first].first, &y = edge[e[o][i].first].second;
        djs[e[o][i].second].uni(x, y);
    }
    if (L == R) {
        int &eid=qry[L].first,&clr=qry[L].second;
        int &x = edge[eid].first, &y = edge[eid].second;
        if(djs[clr].uni(x, y)) {
            ans[L]=true;
            color[eid]=clr;
        } else ans[L]=false;
        if(L<q&&color[eid]) {          // 无论边的颜色变不变，都要传下去，因为之前没有记录
            ql=L+1;
            qr=nxt[L]-1;
            eg.first=eid;
            eg.second=color[eid];
            ins(1, 1, q);
        }
    } else {
        int M = L + R >> 1;
        solve(o<<1, L, M);
        solve(o<<1|1, M + 1, R);
    }
    undo();
}

int main() {
    read(n);
    read(m);
    read(k);
    read(q);
    FOR(j, 1, k) djs[j].init(n);
    FOR(j, 1, m) {
        read(edge[j].first);
        read(edge[j].second);
    }
    FOR(j, 1, q) {
        read(x);
        read(c);
        if(lst[x]) nxt[lst[x]]=j;
        nxt[j]=q+1;                    // 更新边的有效区间
        lst[x]=j;
        qry[j].first=x;
        qry[j].second=c;
    }
    solve(1, 1, q);
    FOR(j, 1, q) {
        puts(ans[j]?"YES":"NO");
    }
    putchar('\n');
    return 0;
}
