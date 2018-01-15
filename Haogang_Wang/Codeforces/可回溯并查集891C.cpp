/*
问一个边集可不可以都在用一个最小生成树上。
长度不同的边是互不冲突的，因为不可以彼此替换。将每个询问中长度相同的边分为一组，每次将一组
完全加入，看是否冲突（形成环）。
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
#include <unordered_map>
#include <set>
#include <ctime>
#include <cmath>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)

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
struct DisjointSet{
    // save() is like recursive
    // undo() is like return
    int n, fa[ maxn ], sz[ maxn ];
    vector< pair<int*,int> > h;
    vector<int> sp;
    void init( int tn ){
        n=tn;
        for( int i = 0 ; i < n ; i ++ ){
            fa[ i ]=i;
            sz[ i ]=1;
        }
        sp.clear(); h.clear();
    }
    void assign( int *k, int v ){
        h.push_back( {k, *k} );
        *k = v;
    }
    void save(){ sp.push_back(h.size()); }
    void undo(){
        int last=sp.back(); sp.pop_back();
        while( h.size()!=last ){
            auto x=h.back(); h.pop_back();
            *x.first = x.second;
        }
    }
    int f( int x ){
        while( fa[ x ] != x ) x = fa[ x ];
        return x;
    }
    void uni( int x , int y ){
        x = f( x ); y = f( y );
        if( x == y ) return;
        if( sz[ x ] < sz[ y ] ) swap( x, y );
        assign( &sz[ x ] , sz[ x ] + sz[ y ] );
        assign( &fa[ y ] , x);
    }
} djs;
int from[maxn],to[maxn],w[maxn];
vector<int> bw[maxn];
vector<pii> query[maxn];
bool ans[maxn];

void psolve(vector<pii>& vec,int L,int R) {
    int qid=vec[L].second;
    djs.save();                              // 打点
    FOR(i, L, R) {
        int &x=from[vec[i].first],&y=to[vec[i].first];
        int fx= djs.f(x),fy= djs.f(y);
        if(fx==fy) {
            ans[qid]=true;
        } else {
            djs.uni(fx, fy);
        }
    }
    djs.undo();            // 回到上一个记录点
}
int main() {
//    freopen("/Users/wanghaogang/Public/AppCodeProjects/ACPP/ACPP/in.txt", "r", stdin);
//    freopen("/Users/wanghaogang/Public/AppCodeProjects/ACPP/ACPP/out.txt", "w", stdout);
    int n,m,q,k,x,y;
    read(n);
    read(m);
    int maxw=0;
    djs.init(n);
    FOR(j, 0, m-1) {
        read(from[j]);
        read(to[j]);
        read(w[j]);
        maxw = max(maxw, w[j]);
        bw[w[j]].push_back(j);
    }
    read(q);
    FOR(j, 1, q) {
        read(k);
        while(k--) {
            read(x);
            --x;
            query[w[x]].push_back(make_pair(x, j));
        }
    }
    FOR(j, 1, maxw) {
        if(bw[j].empty()) continue;
        for (int L = 0,R; L < query[j].size();L=R) {
            R=L+1;
            while(R<query[j].size()&&query[j][R].second==query[j][L].second) ++R;
            psolve(query[j], L, R-1);                    // 看这一组是否会产生冲突
        }
        for (int i = 0; i < bw[j].size(); ++i) {
            x=from[bw[j][i]],y=to[bw[j][i]];
            int fx= djs.f(x),fy= djs.f(y);
            if(fx!=fy)  {
                djs.uni(fx, fy);
            }
        }
    }
    FOR(j, 1, q) puts(ans[j]?"NO":"YES");
    return 0;
}
// my version
// #include <iostream>
// #include <cstdio>
// #include <sstream>
// #include <cstring>
// #include <algorithm>
// #include <vector>
// #include <queue>
// #include <cctype>
// #include <stack>
// #include <map>
// #include <unordered_map>
// #include <set>
// #include <ctime>
// #include <cmath>

// #define FOR(i,a,b) for(int i=(a);i<=(b);i++)
// #define IFOR(i,a,b) for(int i=(a);i>=(b);i--)

// using namespace std;

// typedef long long lolo;
// typedef pair<int, int> pii;
// typedef unsigned long long ulolo;

// const int maxn = 501010;
// const int maxm = 200005;
// const int INF = 0x3f3f3f3f;
// const lolo inf = 0x3f3f3f3f3f3f3f3f;
// const double eps = 1e-8;
// const int MOD = 1000000007;

// template<class T>
// inline void read(T &x) {
//     x = 0; T flag = 1;char c;
//     do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
//     if (c == '-') c = '0', flag = -1;
//     do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
//     x *= flag;
// }
// char str[1100];
// string scf() {
//     scanf("%s",str);
//     return str;
// }
// template<class T>
// inline void out(T x) {
//     if(x>9) out(x/10);
//     x=x%10;
//     putchar('0'+x);
// }
// int pa[maxn],rk[maxn];
// pair<int*,int>  sta[maxn<<1];
// int from[maxn],to[maxn],w[maxn];
// vector<int> bw[maxn];
// vector<pii> query[maxn];
// bool ans[maxn];
// int findset(int x) {
//     while(pa[x]!=x) {
//         x=pa[x];
//     }
//     return x;
// }
// void psolve(vector<pii>& vec,int L,int R) {
//     int qid=vec[L].second;
//     int cnt=0;
//     FOR(i, L, R) {
//         int &x=from[vec[i].first],&y=to[vec[i].first];
//         int fx= findset(x),fy= findset(y);
//         if(fx==fy) {
//             ans[qid]=true;
//         } else {
//             if(rk[fx]<rk[fy]) swap(fx, fy);
//             sta[cnt++]=make_pair(pa+fy, pa[fy]);
//             if(rk[fx]==rk[fy]) sta[cnt++]=make_pair(rk+fx, rk[fx]),++rk[fx];
//             pa[fy]=fx;
//         }
//     }
//     IFOR(i, cnt-1, 0) {                // 回溯
//         pair<int*,int> &tmp=sta[i];
//         *tmp.first=tmp.second;
//     }
// }
// int main() {
// //    freopen("/Users/wanghaogang/Public/AppCodeProjects/ACPP/ACPP/in.txt", "r", stdin);
// //    freopen("/Users/wanghaogang/Public/AppCodeProjects/ACPP/ACPP/out.txt", "w", stdout);
//     int n,m,q,k,x,y;
//     read(n);
//     read(m);
//     int maxw=0;
//     FOR(j, 1, n) {
//         pa[j]=j;
//         rk[j]=1;
//     }
//     FOR(j, 1, m) {
//         read(from[j]);
//         read(to[j]);
//         read(w[j]);
//         maxw = max(maxw, w[j]);
//         bw[w[j]].push_back(j);
//     }
//     read(q);
//     FOR(j, 1, q) {
//         read(k);
//         while(k--) {
//             read(x);
//             query[w[x]].push_back(make_pair(x, j));
//         }
//     }
//     FOR(j, 1, maxw) {
//         if(bw[j].empty()) continue;
//         for (int L = 0,R; L < query[j].size(); L=R) {
//             R=L+1;
//             while(R<query[j].size()&&query[j][R].second==query[j][L].second) ++R;
//             psolve(query[j], L, R-1);
//         }
//         for (int i = 0; i < bw[j].size(); ++i) {
//             x=from[bw[j][i]],y=to[bw[j][i]];
//             int fx= findset(x),fy= findset(y);
//             if(fx!=fy)  {
//                 if(rk[fx]<rk[fy]) swap(fx, fy);
//                 if(rk[fx]==rk[fy]) ++rk[fx];
//                 pa[fy]=fx;
//             }
//         }
//     }
//     FOR(j, 1, q) puts(ans[j]?"NO":"YES");
//     return 0;
// }