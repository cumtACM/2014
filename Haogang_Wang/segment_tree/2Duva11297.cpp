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

const int maxn = 2010;
const int maxm = 1000005;
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
    if (x > 9) out(x / 10);
    x = x % 10;
    putchar('0' + x);
}
int a[505][505];
struct IntervalTree2D {
    int Max[maxn][maxn], Min[maxn][maxn], n, m;
    int xo, xleaf, x1, x2, y1, y2, x, y, v, vmax, vmin, row;

    void query1D(int o, int L, int R) {
        if (y1 <= L && R <= y2) {
            vmax = max(vmax, Max[xo][o]);
            vmin = min(vmin, Min[xo][o]);
        } else {
            int M = (L + R) >> 1;
            if (y1 <= M) query1D(o << 1, L, M);
            if (y2 > M) query1D(o << 1 | 1, M + 1, R);
        }
    }

    void query2D(int o, int L, int R) {
        if (x1 <= L && R <= x2) {
            xo = o;
            query1D(1, 1, m);
        } else {
            int M = (L + R) >> 1;
            if (x1 <= M) query2D(o << 1, L, M);
            if (x2 > M) query2D(o << 1 | 1, M + 1, R);
        }
    }

    void modify1D(int o, int L, int R) {
        if (L == R) {
            if (xleaf) {
                Max[xo][o] = Min[xo][o] = v;
                return;
            }
            Max[xo][o] = max(Max[xo << 1][o], Max[xo << 1 | 1][o]);
            Min[xo][o] = min(Min[xo << 1][o], Min[xo << 1 | 1][o]);
        } else {
            int M = (L + R) >> 1;
            if (y <= M) modify1D(o << 1, L, M);    
            else modify1D(o << 1 | 1, M + 1, R);
            // 修改y轴
            Max[xo][o] = max(Max[xo][o << 1], Max[xo][o << 1 | 1]);
            Min[xo][o] = min(Min[xo][o << 1], Min[xo][o << 1 | 1]);
        }
    }

    void modify2D(int o, int L, int R) {
        if (L == R) {
            xleaf = L, xo = o;
            modify1D(1, 1, m);
        } else {
            int M = (L + R) >> 1;
            if (x <= M) modify2D(o << 1, L, M);
            else modify2D(o << 1 | 1, M + 1, R);
            xo = o;
            xleaf = 0;
            modify1D(1, 1, m);        // 更新非叶子节点对应的y轴
        }
    }

    void build1D(int o, int L, int R) {
        if (L == R) {
            Max[xo][o] = Min[xo][o] = a[row][L];
        } else {
            int M = (L + R) >> 1;
            build1D(o << 1, L, M);
            build1D(o << 1 | 1, M + 1, R);
            Max[xo][o] = max(Max[xo][o << 1], Max[xo][o << 1 | 1]);
            Min[xo][o] = min(Min[xo][o << 1], Min[xo][o << 1 | 1]);
        }
    }

    void build2D(int o, int L, int R) {
        if (L == R) {
            row = L, xo = o;
            build1D(1, 1, m);
        } else {
            int M = (L + R) >> 1;
            build2D(o << 1, L, M);
            build2D(o << 1 | 1, M + 1, R);
            FOR(i, 1, m << 2) {
                Max[o][i] = max(Max[o << 1][i], Max[o << 1 | 1][i]);     // 更新y轴所有的值
                Min[o][i] = min(Min[o << 1][i], Min[o << 1 | 1][i]);
            }
        }
    }

    void query() {
        vmin = INF, vmax = -INF;
        query2D(1, 1, n);
    }

    void modify() {    // 单点修改
        modify2D(1, 1, n);
    }
}itd;
int main() {
    int n,q;
    read(n);
    itd.n=itd.m=n;
    FOR(i, 1, n) {
        FOR(j, 1, n) {
            read(a[i][j]);
        }
    }
    itd.build2D(1, 1, n);
    read(q);
    char op[3];
    while (q--) {
        scanf("%s",op);
        if(op[0]=='q') {
            read(itd.x1);
            read(itd.y1);
            read(itd.x2);
            read(itd.y2);
            itd.query();
            out(itd.vmax);
            putchar(' ');
            out(itd.vmin);
            putchar('\n');
        } else {
            read(itd.x);
            read(itd.y);
            read(itd.v);
            itd.modify();
        }
    }
    return 0;
}
