#include <bits/stdc++.h>
#define PI acos(-1.0)
#define lson o<<1, l, mid
#define rson o<<1|1, mid+1, r
#define ll o<<1
#define rr o<<1|1
using namespace std;
typedef long long LL;
const int MAXN = 200005;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9+7;
const int eps = 1e-6;
void add(LL &x, LL y) {x += y, x %= MOD;}
struct Tree{
    int l, r; int Max;
};
Tree tree[MAXN<<2];
void PushUp(int o){
    tree[o].Max = max(tree[ll].Max, tree[rr].Max);
}
void Build(int o, int l, int r)
{
    tree[o].l = l; tree[o].r = r;
    tree[o].Max = 0;
    if(l == r) return ;
    int mid = (l + r) >> 1;
    Build(lson); Build(rson);
}
void Update(int o, int pos, int val)
{
    if(tree[o].l == tree[o].r)
    {
        tree[o].Max = val;
        return ;
    }
    int mid = (tree[o].l + tree[o].r) >> 1;
    if(pos <= mid) Update(ll, pos, val);
    else Update(rr, pos, val);
    PushUp(o);
}
int Query(int o, int L, int R)
{
    if(tree[o].l == L && R == tree[o].r)
        return tree[o].Max;
    int mid = (tree[o].l + tree[o].r) >> 1;
    if(R <= mid) return Query(ll, L, R);
    else if(L > mid) return Query(rr, L, R);
    else return max(Query(ll, L, mid), Query(rr, mid+1, R));
}
int val[MAXN], rec[MAXN],a[MAXN];
int main() {
    int n=0,x;
    while(scanf("%d",&x)!=EOF) {
//        if(x==-100) break;
        if (x < 0) {
            continue;
        } else if (x >= 10000) {
            rec[n+1] = x - 10000;
            x -= 10000;
            val[n] = 5;
        } else {
            rec[n+1]=x;
            val[n] = 1;
        }
        a[n]=rec[n+1];
        n++;
    }
    sort(rec+1, rec+n+1);
    int top = unique(rec+1, rec+n+1) - rec;
    int ans = 0; Build(1, 0, top-1);
    for(int i = 0; i < n; i++) {
        int pos = lower_bound(rec, rec+top, a[i]) - rec;
        if(rec[pos]>a[i]) {
            int res = Query(1, 0, pos - 1) + val[i];
            Update(1, pos, res);
            ans = max(ans, res);
        } else {
            int res = Query(1, 0, pos) + val[i];
            Update(1, pos, res);
            ans = max(ans, res);
        }
    }
    printf("%d\n", ans);
    return 0;
}