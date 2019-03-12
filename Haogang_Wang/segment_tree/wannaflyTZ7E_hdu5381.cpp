//http://www.voidcn.com/article/p-tpiuvsld-oe.html
#include <bits/stdc++.h>
#define ls (o<<1)
#define rs (o<<1|1)
#define lson ls, L, M
#define rson rs, M+1, R
using namespace std;
typedef long long ll;
const int N = (int)1e5 + 5;
const int MOD = 1000000007;
template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') c = '0', flag = -1;
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}
template <class T>
void out(T x){
    if(x>9)
        out(x/10);
    putchar(x%10+'0');
}
typedef long long LL;

int gcd(int a, int b) {
    for (int t; b; t = a, a = b, b = t % b);
    return a;
}

struct part {
    int cnt, g;
};

struct node {
    vector<part> L, R;
    LL sum;

    void upd(const node& rhs) {
        sum = (sum + rhs.sum)%MOD;
        if(sum<0) sum+=MOD;
        for (int i = 0; i < R.size(); ++ i) {
            int ng = R[i].g;
            for (int j = 0; j < rhs.L.size(); ++ j) {
                ng = gcd(ng, rhs.L[j].g);
                sum = (sum+(LL)(ng)  * R[i].cnt%MOD * rhs.L[j].cnt%MOD)%MOD;
                if(sum<0) sum+=MOD;
            }
        }

        for (int i = 0; i < rhs.L.size(); ++ i) Insert(L, rhs.L[i]);
        vector<part> tmp(rhs.R);
        for (int i = 0; i < R.size(); ++ i) Insert(tmp, R[i]);
        R.swap(tmp);
    }

    static void Insert(vector<part>& vec, const part& x) {
        int ng = gcd(vec.back().g, x.g);
        if ( ng == vec.back().g ) {
            vec.back().cnt += x.cnt;
        } else {
            vec.push_back( (part) {x.cnt, ng} );
        }
    }
};

node tree[N*4];
#define lc o<<1
#define rc o<<1|1

void build(int o, int l, int r) {
    if ( l != r ) {
        int m = (l + r) >> 1;
        build(lc, l, m);
        build(rc, m+1, r);
        tree[o] = tree[lc];
        tree[o].upd(tree[rc]);
    } else {
        int x;
        read(x);
        tree[o].sum = x;
        vector<part>().swap(tree[o].L);
        vector<part>().swap(tree[o].R);
        tree[o].L.push_back( (part) { 1, x } );
        tree[o].R.push_back( (part) { 1, x } );
    }
    //print(tree[o], l, r);
}

int qL, qR;
node qres;
void query(int o, int l, int r) {
    if ( qL <= l && r <= qR ) {
        if ( l == qL )
            qres = tree[o];
        else
            qres.upd(tree[o]);
        return;
    }
    int m = (l + r) >> 1;
    if ( qL <= m ) query(lc, l, m);
    if ( qR > m ) query(rc, m+1, r);
}

int main() {
    int t;
    int n, q;
    read(n);
    read(q);
    build(1, 1, n);
    for (int i = 1; i <= q; i++) {
        read(qL);
        read(qR);
        //cout << "query " << qL << ' ' << qR << endl;
        query(1, 1, n);
        out(qres.sum);
        putchar('\n');
    }
    return 0;
}