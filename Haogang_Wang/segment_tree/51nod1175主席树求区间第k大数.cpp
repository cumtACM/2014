#include <bits/stdc++.h>


#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define IFOR(i,a,b) for(int i=(a);i>=(b);--i)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 100000 + 5;
const int maxm = 1<<17|15;
const int INF = 0x3f3f3f3f;
const lolo inf = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-6;
const int MOD = (int)1e9+9;

template<class T>
inline void read(T &x) {
    x = 0; T flag = 1;char c;
    do { c = (char) getchar(); if (c == '-') break; } while (c < '0' || c > '9');
    if (c == '-') c = '0', flag = -1;
    do { x = x * 10 + c - '0';c = (char) getchar();} while (c >= '0' && c <= '9');
    x *= flag;
}
template<class T>
inline void out(T x) {
    if (x > 9) out(x / 10);
    x = x % 10;
    putchar('0' + x);
}
int n,a[maxn],Rank[maxn],cnt;
int root[maxn];   // root[i]是前缀a[1~i]的线段树的跟节点
pii p[maxn];
struct Node {
    int ch[2];      // 左右子节点
    int sum;       // 这个区间内数的个数
    Node() {sum=0;}
}node[maxn*20];
void init() {
    cnt=1;
    node[0].ch[0]=node[0].ch[1]=node[0].sum=0;
}
void update(int num,int &rt,int L,int R) {
    node[cnt++]=node[rt];
    rt=cnt-1;
    node[rt].sum++;
    if(L==R) return;
    int mid=(L+R)>>1;
    if(num<=mid) update(num,node[rt].ch[0],L,mid);
    else update(num,node[rt].ch[1],mid+1,R);
}
int query(int l,int r,int k,int L,int R) {
    if(L==R) return L;
    int d=node[node[r].ch[0]].sum-node[node[l].ch[0]].sum; // 区间l~r内L~mid的数的数量
    int mid=(L+R)>>1;
    if(k<=d) return query(node[l].ch[0],node[r].ch[0],k,L,mid);
    else return query(node[l].ch[1],node[r].ch[1],k-d,mid+1,R);
}
int main() {
    read(n);
    FOR(i,1,n) {
        read(a[i]);
        p[i].first=a[i];
        p[i].second=i;
    }
    int nn=1;
    sort(p+1,p+n+1);
    Rank[p[1].second]=1;
    vector<int> vc;
    vc.push_back(0);
    vc.push_back(p[1].first);
    FOR(i,2,n) {              // 离散化
        if(p[i].first==p[i-1].first) {
            Rank[p[i].second]=nn;
        } else Rank[p[i].second]=++nn,vc.push_back(p[i].first);
    }
    init();
    FOR(i,1,n) {
        root[i]=root[i-1];
        update(Rank[i],root[i],1,nn);
    }
    int l,r,k,q;
    read(q);
    while (q--) {
        read(l);read(r);read(k);
        ++l,++r;
        printf("%d\n",vc[query(root[l-1],root[r],r-l+2-k,1,nn)]);
    }
    return 0;
}
