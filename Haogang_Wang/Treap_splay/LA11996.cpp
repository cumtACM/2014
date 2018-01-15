/*
建立虚拟点使操作更灵活，克服splay时k!=0的要求
*/
#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 400005;
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
char str[110];
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
ulolo powers[maxn];
struct Node* null;
struct Node {
    Node *ch[2];
    int flip;
    int v;
    int s;
    ulolo hp,hs;
    Node(int v=0) {this->v=hp=hs=v;flip=0;s=1;ch[0]=ch[1]=null;}
    void init(int x) {
        s=1;flip=0;
        hp=hs=v=x;
        ch[0]=ch[1]=null;
    }
    int cmp(const int& x) const {
        int d = x - ch[0]->s;
        if(d == 1) return -1;
        return d <= 0 ? 0 : 1;
    }
    void maintain() {
        s=ch[0]->s+ch[1]->s+1;
        hp=ch[0]->hp*powers[ch[1]->s+1]+v*powers[ch[1]->s]+ch[1]->hp;
        hs=ch[1]->hs*powers[ch[0]->s+1]+v*powers[ch[0]->s]+ch[0]->hs;
    }
    void reverse() {
        swap(ch[0], ch[1]);
        swap(hp, hs);
        flip^=1;
    }
    void pushdown() {
        if(flip) {
            flip=0;
            ch[0]->reverse();
            ch[1]->reverse();
        }
    }
}nullNode;


void rotate(Node *&o,int d) {
    Node *k=o->ch[d^1];o->ch[d^1]=k->ch[d];k->ch[d]=o;
    o->maintain();k->maintain();o=k;
}

void splay(Node *&o, int k) {
    o->pushdown();
    int d=o->cmp(k);
    if(d==1) k-=o->ch[0]->s+1;
    if(d!=-1) {
        Node* p=o->ch[d];
        p->pushdown();
        int d2=p->cmp(k);
        int k2=(d2==0?k:k-p->ch[0]->s-1);
        if(d2!=-1) {
            splay(p->ch[d2], k2);
            if(d==d2) rotate(o, d^1);else rotate(o->ch[d], d);
        }
        rotate(o, d^1);
    }
}

char s[maxn];
int n,m;
struct SplaySequence {
    int n;
    Node seq[maxn];
    Node *root;
    void update_dummy() {
        root->ch[1]->maintain();
        root->maintain();
    }
    Node* last() const {
        return root->ch[1]->ch[0];
    }
    Node *build(int sz) {
        if(!sz) return null;
        Node *left= build(sz/2);
        Node *o=&seq[++n];
        o->v=s[n]-'0';
        o->ch[0]=left;
        o->ch[1]= build(sz-sz/2-1);
        o->flip=0;
        o->maintain();
        return o;
    }
    void init(int sz) {
        n=0;
        root->ch[1]->ch[0]= build(sz);
        update_dummy();
    }

    Node *&range(int L,int R) {       // 取到区间的[L,R)
        splay(root, L);
        splay(root->ch[1], R-L+1);
        return root->ch[1]->ch[0];
    }
}ss;


int main() {
//    freopen("/Users/wanghaogang/Public/AppCodeProjects/ACPP/ACPP/in.txt", "r", stdin);
    powers[0]=1;
    for (int i = 1; i < maxn; ++i) {
        powers[i]=powers[i-1]*123;
    }
    int p1,p2,op;
    null = &nullNode;
    null->s=0;
    ss.root=new Node('['-'0');
    ss.root->ch[1]=new Node(']'-'0');
    null->s=0;
    null->ch[0] = null->ch[1] = null;
    while(scanf("%d%d",&n,&m)!=EOF) {
        scanf("%s", s + 1);
        ss.init(n);
        FOR(j, 1, m) {
            read(op);
            read(p1);
            if (op == 1) {
                read(p2);
                Node *&u=ss.range(p1+1, p1+1);
                u=&ss.seq[++ss.n];
                u->init(p2);
                ss.update_dummy();
            } else if (op == 2) {
                ss.range(p1, p1+1)=null;
                ss.update_dummy();
            } else if (op == 3) {
                read(p2);
                ss.range(p1, p2+1)->reverse();
                ss.update_dummy();
            } else {
                read(p2);
                int L = 0, R = ss.root->s - p2;
                while (L < R-1) {
                    int M = L + (R - L) / 2;
                    ulolo h1=ss.range(p1, p1+M)->hp;
                    ulolo h2=ss.last()->hs;
                    h1-=ss.range(p2, p2+M)->hp;
                    h2-=ss.last()->hs;
                    if(!h1||!h2) L=M; else R=M;
                }
                printf("%d\n",L);
            }
        }
    }
    return 0;
}