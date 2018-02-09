// 在线更新，实现点修改，点删除（假，其实是赋值为0），找到比当前值小的数的个数
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IN(x,L,R) ((x)>=L&&(x)<=R)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 100010;
const int maxm = 4000105;
const int INF = 1000000000;
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
struct Node {
    Node *ch[2];
    int s;
    Node(int s=0):s(s) {}
    void maintain() {
        s=ch[0]->s+ch[1]->s+1;
    }
}nullNode;
Node* null;
Node* newnode(int x) {
    Node *u=new Node(x);
    u->ch[0]=u->ch[1]=null;
    return u;
}
int p,_add,ql,qr;
Node *root[maxn],*nroot[maxn];  // nroot中存放当前的名字对应的优先级，root中只存放优先级
Node* copynode(Node* src) {
    if(src==null) {
        Node *ret = newnode(0);
        return ret;
    }
    Node* ret= newnode(src->s);
    ret->ch[0]=src->ch[0];
    ret->ch[1]=src->ch[1];
    return ret;
}
void modify(Node *o,int L,int R) {
    if(L==R) {
        o->s+=_add;
        return;
    }
    int M=(L+R)>>1;
    if(p<=M) {
        o->ch[0]= copynode(o->ch[0]);   // 动态备份，只有修改时才有必要使用新结点，保留旧结点
        modify(o->ch[0], L, M);
    }
    else {
        o->ch[1]= copynode(o->ch[1]);
        modify(o->ch[1], M+1, R);
    }
    o->s=o->ch[0]->s+o->ch[1]->s;
}
int query(Node *o,int L,int R) {
    if(o==null||qr<L||ql>R) return 0;
    if(ql<=L&&qr>=R) return o->s;
    int M=(L+R)>>1;
    return query(o->ch[0], L, M)+ query(o->ch[1], M+1, R);
}

unordered_map<string,int> nid;
int ncnt=0;
int nameId(const string& a) {
    if(!nid.count(a)) nid[a]=++ncnt;
    return nid[a];
}
int main() {
    null=&nullNode;
    null->s=0;
    null->ch[0]=null->ch[1]=null;
    int q,x;
    read(q);
    char s[20];
    root[0]=nroot[0]=null;
    FOR(j, 1, q) {
        scanf("%s",s);
        if(s[0]=='u') {
            read(x);
            root[j]= copynode(root[j-x-1]);      // 复制x个操作之前的状态
            nroot[j]= copynode(nroot[j-x-1]);
            continue;
        }
        root[j]= copynode(root[j-1]);      // 复制前一个状态
        nroot[j]= copynode(nroot[j-1]);
        scanf("%s",str);
        ql= nameId(str);
        qr= ql;
        int orz= query(nroot[j], 1, q);  // 得到原来的值，没有赋值是0
        if(s[0]=='s') {
            read(x);
            if(orz) p=orz,_add=-1,modify(root[j], 1, INF);    // 把原来的值删去
            _add=x-orz;p=ql;
            modify(nroot[j], 1, q);
            p=x;_add=1;
            modify(root[j], 1, INF);
        } else if(s[0]=='r') {
            if(orz) {
                p=ql;_add=-orz;
                modify(nroot[j], 1, q);
                p=orz;_add=-1;
                modify(root[j], 1, INF);
            }
        } else if(s[0]=='q') {
            if(orz) {
                ql=1,qr=orz-1;              // 比它小的数是1~orz-1，查找这些数有几个
                out(query(root[j], 1, INF));
                putchar('\n');
            } else puts("-1");
            fflush(stdout);
        }
    }
    return 0;
}

// better version
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define IFOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IN(x,L,R) ((x)>=L&&(x)<=R)

using namespace std;

typedef long long lolo;
typedef pair<int, int> pii;
typedef unsigned long long ulolo;

const int maxn = 101010;
const int maxm = 200005;
const int INF = 1000000000;
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
map<string,int> _id;
int mid,q,di,xi;
inline int id( const string& s ){
    map<string,int>::iterator it = _id.find( s );
    if( it != _id.end() ) return it->second;
    return _id[ s ] = ++ mid;
}
#define mid ((l+r)>>1)
struct Node{
    int sum;
    Node *ch[2];
    Node(){
        ch[0] = ch[1] = NULL;
        sum = 0;
    }
};
inline Node* copy( Node* x ){
    Node* ret = new Node();
    if( x ){
        ret->sum = x->sum;
        ret->ch[0] = x->ch[0];
        ret->ch[1] = x->ch[1];
    }
    return ret;
}
inline int Sum( Node* now ){ return now ? now->sum : 0; }
void add( Node* now , int l , int r , int p , int dlt ){
    if( l == r ){
        now->sum += dlt;
        return;
    }
    if( p <= mid ){
        now->ch[0] = copy( now->ch[0] );
        add( now->ch[0] , l , mid , p , dlt );
    }else{
        now->ch[1] = copy( now->ch[1] );
        add( now->ch[1] , mid + 1 , r , p , dlt );
    }
    now->sum = Sum( now->ch[0] ) + Sum( now->ch[1] );
}

int query( Node* now , int l , int r , int ql , int qr ){
    if( !now or r < ql or l > qr ) return 0;
    if( ql <= l and r <= qr ) return now->sum;
    return query( now->ch[0] , l , mid , ql , qr ) +
           query( now->ch[1] , mid + 1 , r , ql , qr );
}

Node *vl[maxn] , *ps[maxn];  // vl中存放当前的名字对应的优先级，ps中只存放优先级
char cmd[20],ai[20];
void solve(){
    for( int i = 1 ; i <= q ; i ++ ){
        scanf("%s",cmd);
        if( cmd[0] == 'u' ){
            read(di);
            vl[ i ] = copy( vl[ i - di - 1 ] );
            ps[ i ] = copy( ps[ i - di - 1 ] );
            continue;
        }
        vl[ i ] = copy( vl[ i - 1 ] );
        ps[ i ] = copy( ps[ i - 1 ] );
        scanf("%s",ai);
        int nid = id( ai );
        int ori = query( vl[ i ] , 1 , q , nid , nid );
        if( cmd[0] == 's' ){
            read(xi);
            if( ori ) add( ps[ i ] , 0 , INF , ori , -1 );
            add( ps[ i ] , 0 , INF , xi , +1 );
            add( vl[ i ] , 1 , q , nid , xi - ori );
            continue;
        }
        if( cmd[0] == 'r' ){
            if( ori ) add( ps[ i ] , 0 , INF , ori , -1 );
            add( vl[ i ] , 1 , q , nid , -ori );
            continue;
        }
        if( ori == 0 ) puts( "-1" );
        else printf( "%d\n" , query( ps[ i ] , 0 , INF , 0 , ori - 1 ) );
        fflush( stdout );
    }
}
int main(){
    read(q);
        solve();
    return 0;
}