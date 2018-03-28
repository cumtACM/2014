#include <bits/stdc++.h>


#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define IFOR(i,a,b) for(int i=(a);i>=(b);--i)

using namespace std;

typedef long long lolo;
typedef pair<lolo, int> pii;

const int maxn = 100000 + 5;

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
// 如果几个区间连续存放，就以最前面一个作为根节点
int n,x,fa[maxn];   
lolo pos[maxn],sz[maxn],dis[maxn],ss[maxn];      // pos表示存放起始位置，sz表示总大小（包括子连续区间），dis表示相对于根节点的便宜量
set<pii> S;
set<pii>::iterator it,itt;
int findset(int x) {
    if(fa[x]==x) return x;
    int y=findset(fa[x]);
    dis[x]+=dis[fa[x]];   // 此时已经求出了fa[x]对于根的便宜量，据此更新x的便宜量
    return fa[x]=y;
}
void Union(int x,int y) {
    x=findset(x),y=findset(y);
    if(x==y) return;
    if(pos[x]>pos[y]||pos[x]==pos[y]&&x>y) swap(x,y);
    dis[y]=sz[x];       // 新区间加在原区间的末尾，偏移量是原区间的大小
    sz[x]+=sz[y];       // 大小也会变化 
    fa[y]=x;            // 但是其实y的子节点的偏移量还没有处理，在findset中处理
}
int main() {
    read(n);
    FOR(i,1,n) dis[i]=0,fa[i]=i;
    int m=0;
    char op[4];
    FOR(i,1,n) {
        scanf("%s",op);
        if(op[0]=='I') {
            ++m;
            read(pos[m]);read(sz[m]);
            ss[m]=sz[m];
            pii tmp=make_pair(pos[m],m);
            it=S.upper_bound(tmp);
            if(it!=S.begin()) {
                --it;
                int y=it->second;
                if(pos[y]+sz[y]>=pos[m]) Union(m,y);
                else S.insert(tmp),it=S.find(tmp);
            } else S.insert(tmp),it=S.begin();
            for(;;) {
                itt=it;
                ++itt;
                if(itt==S.end()) break;
                int X=it->second,Y=itt->second;
                if(pos[X]+sz[X]>=pos[Y]) { S.erase(itt);Union(X,Y);}
                else break;
            }
        } else {
            read(x);
            int y=findset(x);
            printf("%lld %lld\n",pos[y]+dis[x],pos[y]+dis[x]+ss[x]-1);
        }
    }
    return 0;
}
