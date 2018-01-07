/*
Write a program to transform the permutation 1, 2, 3, . . . , n
 according to m instructions. Each instruction(a, b) means to 
 take out the subsequence from the a-th to the b-th element, 
 reverse it, then appendit to the end.
 使用splay的分裂合并
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 100005;
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
struct Node {
    Node *ch[2];
    int flip;
    int v;
    int s;
    Node() {flip=v=s=0;}
    int cmp(const int& x) const {
        int d = x - ch[0]->s;
        if(d == 1) return -1;
        return d <= 0 ? 0 : 1;
    }
    void maintain() {
        s=ch[0]->s+ch[1]->s+1;
    }
    void pushdown() {
        if(flip) {
            flip=0;
            swap(ch[0], ch[1]);
            ch[0]->flip^=1;
            ch[1]->flip^=1;
        }
    }
}nullNode;
Node* null;

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
Node* merge(Node* left, Node* right) {
    splay(left, left->s);
    left->ch[1]=right;
    left->maintain();
    return left;
}
void split(Node* o,int k,Node *&left,Node *&right) {
    splay(o, k);
    left=o;
    right=o->ch[1];
    o->ch[1]=null;
    left->maintain();
}
int n,m;
struct SplaySequence {
    int n;
    Node seq[maxn];
    Node *root;
    Node *build(int sz) {
        if(!sz) return null;
        Node *left= build(sz/2);
        Node *o=&seq[++n];
        o->v=n;
        o->ch[0]=left;
        o->ch[1]= build(sz-sz/2-1);
        o->flip=o->s=0;
        o->maintain();
        return o;
    }
    void init(int sz) {
        n=0;
        root= build(sz);
    }
}ss;
void print(Node *o) {
    if(o!=null) {
        o->pushdown();
        print(o->ch[0]);
        out(o->v);
        putchar('\n');
        print(o->ch[1]);
    }
}

int main() {
    int a, b;
    null = &nullNode;
    null->ch[0] = null->ch[1] = null;
    read(n);
    ss.init(n);
    read(m);
    Node *left, *mid, *right, *o;
    FOR(j, 1, m) {
        read(a);
        read(b);
        if (a == 1) {
            split(ss.root, b, mid, right);
            mid->flip ^= 1;
            ss.root = merge(right, mid);
        } else {
            split(ss.root, a - 1, left, o);
            split(o, b - a + 1, mid, right);
            mid->flip ^= 1;
            ss.root = merge(merge(left, right), mid);
        }
    }
    print(ss.root);
    return 0;
}