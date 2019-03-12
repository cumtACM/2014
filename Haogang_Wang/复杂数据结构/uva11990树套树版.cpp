/*
You are given a permutation {1,2,3,. . . ,n}. Remove m of them
 one by one, and output the number of inversion pairs before 
 each removal. The number of inversion pairs of an array A is 
 the number of ordered pairs (i, j) such that i < j and A[i] > A[j].
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

const int maxn = 200010;
const int maxm = 100005;
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
#define lowbit(x) ((x)&(-(x)))
int a[maxn],n,m,b[maxm],pos[maxn];
lolo ans;
int C[maxn];
struct Node {
    Node* ch[2];
    int v;
    int s;
    int d;
    Node(int tv=0):v(tv),d(0),s(1) {ch[0]=ch[1]=NULL;}
    int ch_s(int d) {
        return ch[d]==NULL?0:ch[d]->s;
    }
};
struct RankTree {
    Node *node,*root;
    int *v,n,sz;
    RankTree(int tn,int *A) {
        n=tn;
        v=new int[n];
        node=new Node[n];
        memcpy(v, A, sizeof(int)*n);
        sort(v, v+n);
        sz=0;
        root= build(0, tn-1);
    }
    Node* build(int L,int R) {
        if (L > R) return NULL;
        int u = sz++;
        int M = (L + R) >> 1;
        node[u].v = v[M];
        node[u].ch[0] = build(L, M - 1);
        node[u].ch[1] = build(M + 1, R);
        node[u].s = node[u].ch_s(0) + node[u].ch_s(1) + 1;
        return node + u;
    }
    // 0表示求比x小的个数，1表示求比x大的个数
    int count(int v,int d) {
        Node *u=root;
        int cnt=0;
        while (u!=NULL) {
            if(u->v==v) {cnt+=u->ch_s(d);break;}    // 等于取一侧即可
            int c=(v<u->v?0:1);
            if(d!=c) cnt+=u->s-u->ch_s(c);           // 要加上另一侧符合条件的值个数
            u=u->ch[c];
        }
        return cnt;
    }

    void erase(int v) {
        Node* u=root;
        while (u!=NULL) {
            --u->s;
            if(u->v==v) {u->d=1;break;}
            int c=(v<u->v?0:1);
            u=u->ch[c];
        }
    }
    ~RankTree() {
        delete []node;
        delete []v;
    }
};

struct BitRankTree {
    int n;
    vector<RankTree*> C;
    void init(int tn,int *A) {
        n=tn;
        C.resize(n+1);
        FOR(i, 1, n) {
            C[i]=new RankTree(lowbit(i),A+i-lowbit(i)+1);
        }
    }
    void clear() {
        FOR(i, 1, n) delete C[i];
    }
    void erase(int x) {
        int p=pos[x];
        while (p<=n) {
            C[p]->erase(x);p += lowbit(p);
        }
    }
    int count(int v,int R,int d) {
        int ret=0;
        while (R) {
            ret+=C[R]->count(v, d);
            R-= lowbit(R);
        }
        return ret;
    }
}brt;
int sum(int x) {
    int ret=0;
    while (x) {
        ret+=C[x];
        x-= lowbit(x);
    }
    return ret;
}
void add(int x,int d) {
    while (x<=n) {
        C[x]+=d;
        x+= lowbit(x);
    }
}
int main() {
    freopen("/Users/wanghaogang/Public/AppCodeProjects/ACPP/ACPP/in.txt", "r", stdin);
//    freopen("/Users/wanghaogang/Public/AppCodeProjects/ACPP/ACPP/out.txt", "w", stdout);
    while (scanf("%d",&n)!=EOF) {
        read(m);
        ans=0;
        memset(C+1, 0, sizeof(int)*n);
        FOR(i, 1, n) {
            read(a[i]);
            pos[a[i]]=i;
            ans += i-1-sum(a[i]-1);
            add(a[i], 1);
        }
        brt.init(n, a);
        memset(C+1, 0, sizeof(int)*n);
        FOR(i, 1, m) {
            out(ans);
            putchar('\n');
            read(b[i]);
            add(b[i], 1);
            int x=brt.count(b[i], pos[b[i]]-1, 1);    // 在左侧比b[i]大的数
            int y=b[i]-1;
            int z= sum(b[i]-1);                        // 已经被删掉的比b[i]小的数
            int w= brt.count(b[i], pos[b[i]]-1, 0);    // 在左侧比b[i]小的数
            y-=z+w;                                    // 得到在右侧比b[i]小的数
            ans-=x+y;
            brt.erase(b[i]);
        }
        brt.clear();
    }
    return 0;
}
