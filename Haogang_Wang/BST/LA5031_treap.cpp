/*
名次树，时光倒流
先得到最终的图，再反向操作
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <ctime>
#include <cmath>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 20005;
const int maxm = 60005;
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
    int r;
    int v;
    int s;
    Node() {r=v=s=0;}
    int cmp(const int& x) const {
        if(x==v) return -1;
        return x<v?0:1;
    }
    void maintain() {
        s=ch[0]->s+ch[1]->s+1;
    }
}node[maxn],nullNode;
Node* null;
queue<Node*> freenodes;
Node* newnode(int x) {
    Node *u=freenodes.front();freenodes.pop();
    u->ch[0]=u->ch[1]=null;
    u->v=x;
    u->r = rand();
    u->s=1;
    return u;
}
void deletenode(Node *u) {
    freenodes.push(u);
}
void rotate(Node *&o,int d) {
    Node *k=o->ch[d^1];o->ch[d^1]=k->ch[d];k->ch[d]=o;
    o->maintain();k->maintain();o=k;
}
void insert(Node *&o,int x) {
    if(o==null) o = newnode(x);
    else {
        int d=(x<o->v?0:1);
        insert(o->ch[d], x);
        if(o->ch[d]->r>o->r) rotate(o, d^1);
    }
    o->maintain();
}
void remove(Node *&o,int x) {
    int d=o->cmp(x);
    if(d==-1) {
        Node *u=o;
        if(o->ch[0]!=null&&o->ch[1]!=null) {
            int d2=(o->ch[0]->r>o->ch[1]->r?1:0);
            rotate(o, d2);
            remove(o->ch[d2], x);
        } else {
            if(o->ch[0]==null) o=o->ch[1]; else o=o->ch[0];
            deletenode(u);
        }
    } else {
        remove(o->ch[d], x);
    }
    if(o!=null) o->maintain();
}
struct Command {
    char op;
    int x,p;
}command[500005];
int n,m,weight[maxn],from[maxm],to[maxm],removed[maxm];
int pa[maxn];
int findset(int x) {return pa[x]==x?x:pa[x]= findset(pa[x]);}
Node *root[maxn];
int kth(Node* o,int k) {
    if(o==null||k<=0||k>o->s) return 0;
    int s=o->ch[1]->s;
    if(k==s+1) return o->v;
    else if(k<=s) return kth(o->ch[1], k);
    else return kth(o->ch[0], k-s-1);
}
void mergeto(Node *&src,Node *&dest) {
    if(src==null) return;
    if(src->ch[0]!=null) mergeto(src->ch[0], dest);
    if(src->ch[1]!=null) mergeto(src->ch[1], dest);
    insert(dest, src->v);
    deletenode(src);
    src=null;
}
void removetree(Node *&o) {
    if(o==null) return;
    if(o->ch[0]!=null) removetree(o->ch[0]);
    if(o->ch[1]!=null) removetree(o->ch[1]);
    deletenode(o);
    o=null;
}
void AddEdge(int x) {
    int u= findset(from[x]),v= findset(to[x]);
    if(v!=u) {
        if(root[u]->s<root[v]->s) {
            pa[u]=v;
            mergeto(root[u], root[v]);
        } else {
            pa[v]=u;
            mergeto(root[v], root[u]);
        }
    }
}
int query_cnt;
lolo query_tot;
void query(int x,int k) {
    ++query_cnt;
    query_tot+= kth(root[findset(x)], k);
}
void ChangeWeight(int x,int v) {
    int u= findset(x);
    remove(root[u], weight[x]);
    insert(root[u], v);
    weight[x]=v;
}
void init() {
    for (int i = 0; i < maxn; ++i) {
        freenodes.push(&node[i]);
        root[i]=null;
    }
}
int main() {
    srand(time(NULL));
    null=&nullNode;
    null->ch[0]=null->ch[1]=null;
    int cas=0,x,p,v;
    init();
    char op;
    while(true) {
        read(n);
        read(m);
        if(!(n|m)) break;
        FOR(j, 1, n) read(weight[j]);
        FOR(j, 1, m) read(from[j]),read(to[j]),removed[j]=false;
        int ccnt=0;
        for(;;) {
            p=v=0;
            do {
                op = getchar();
            } while(op==' '||op=='\n');
            if(op=='E') break;
            read(x);
            if(op=='D') removed[x]=true;
            else if(op=='Q') read(p);
            else {
                read(v);
                p=weight[x];
                weight[x]=v;
            }
            command[ccnt].op=op;command[ccnt].x=x;command[ccnt].p=p;
            ++ccnt;
        }
        FOR(j, 1, n) {
            pa[j]=j;if(root[j]!=null) removetree(root[j]);
            root[j]= newnode(weight[j]);
        }
        FOR(j, 1, m) {
            if(!removed[j]) AddEdge(j);
        }
        query_tot=query_cnt=0;
        IFOR(i, ccnt-1, 0) {
            if(command[i].op=='D') AddEdge(command[i].x);
            else if(command[i].op=='Q') query(command[i].x, command[i].p);
            else ChangeWeight(command[i].x, command[i].p);
        }
        FOR(j, 1, n) {
            if(root[j]!=null) removetree(root[j]);
        }
        printf("Case %d: %.6f\n",++cas,(double)query_tot/query_cnt);
    }
    return 0;
}