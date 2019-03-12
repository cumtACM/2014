/*
 * 线段树
 * op = 1表示将[l, r]区间中的数字依次加上1, 2, 3, ..., r-l+1.
 * op = 2表示查询[l, r]区间中的数字的和.
*/
#include <bits/stdc++.h>

#define MIN(a,b) (a)<(b)?(a):(b)
#define MAX(a,b) (a)>(b)?(a):(b)

using namespace std;


typedef long long lolo;
typedef pair<int, int> pii;

const int maxn = 200005;
const int inf = 0x3f3f3f3f;

int a[maxn],op,ql,qr;
lolo sum[maxn<<1],addv[maxn<<1];
int cnt[maxn<<1];
void init(int o,int l,int r) {
    if(r<l) return;
    cnt[o]=0;
    addv[o]=0;
    if(l==r) {
        sum[o]=a[l];
        return;
    }
    int m=l+((r-l)>>1),lc=o<<1;
    int rc=lc|1;
    init(lc,l,m);
    init(rc,m+1,r);
    sum[o]=sum[lc]+sum[rc];
}
void pushdown(int o,int l,int r) {
    if(addv[o]||cnt[o]) {
        int m=l+((r-l)>>1),lc=o<<1,rc=o<<1|1;
        addv[lc]+=addv[o];
        cnt[lc]+=cnt[o];
        addv[rc]+=addv[o]+cnt[o]*(m-l+1);
        cnt[rc]+=cnt[o];
        sum[lc]+=(addv[o]+addv[o]+cnt[o]*(m-l))*(m-l+1)/2;
        sum[rc]+=(addv[o]+cnt[o]*(m-l+1)+addv[o]+cnt[o]*(r-l))*(r-m)/2;
        addv[o]=cnt[o]=0;
    }
}

void update(int o,int l,int r) {
    if(l>qr||r<ql)
        return;
    if(l>=ql&&r<=qr) {
        addv[o]+=l-ql+1;
        cnt[o]++;
        sum[o]+=1LL*(l-ql+1+r-ql+1)*(r-l+1)/2;
//        cout<<o<<" "<<l<<" "<<r<<" "<<sum[o]<<endl;
    } else {
        int lc=o<<1;
        int rc=lc|1;
        int m=l+((r-l)>>1);
        pushdown(o, l, r);
        if(ql<=m) update(lc, l, m);
        if(m<qr) update(rc, m+1, r);
        sum[o]=sum[lc]+sum[rc];
    }
}

lolo query(int o,int l,int r) {
    if(ql<=l&&qr>=r) {
        return sum[o];
    }
    else if(r<ql||l>qr) {
        return 0;
    }
    else {
        int m=l+((r-l)>>1);
        pushdown(o,l,r);
        return query(o<<1, l, m)+query(o<<1|1, m+1, r);
    }
}
int main() {
    int n,T,q;
    scanf("%d",&T);
    while (T--) {
        scanf("%d %d",&n,&q);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        init(1,1,n);
        while (q--) {
            scanf("%d %d %d",&op,&ql,&qr);
            if(op==1) update(1,1,n);
            else {
                query(1,1,n);
                printf("%lld\n",query(1, 1, n));
            }
        }
    }
}
// #include <bits/stdc++.h>
// using namespace std;

// struct AP
// {
//     long long st, k;
// };
// long long a[100005];
// long long data[100005 << 2];
// AP lazy[100005 << 2];

// void seq_build(int o, int l, int r)
// {
//     lazy[o] = {0, 0};
//     if (l == r)
//         data[o] = a[l];
//     else
//     {
//         int mid = (l + r) >> 1;
//         seq_build(o << 1, l, mid);
//         seq_build(o << 1 | 1, mid + 1, r);
//         data[o] = data[o << 1] + data[o << 1 | 1];
//     }
// }

// void pushdown(int o, int l, int r)
// {
//     if (lazy[o].st || lazy[o].k)
//     {
//         int mid = (l + r) >> 1;
//         lazy[o << 1].st += lazy[o].st;
//         lazy[o << 1].k += lazy[o].k;
//         lazy[o << 1 | 1].st += lazy[o].st + lazy[o].k * (mid - l + 1);
//         lazy[o << 1 | 1].k += lazy[o].k;
//         data[o << 1] += (lazy[o].st + lazy[o].st + (mid - l) * lazy[o].k) * (mid - l + 1) / 2;
//         data[o << 1 | 1] += (lazy[o].st + (mid - l + 1) * lazy[o].k + lazy[o].st + (r - l) * lazy[o].k) * (r - mid) / 2;
//         lazy[o] = {0, 0};
//     }
// }

// long long seq_query(int o, int l, int r, int ql, int qr)
// {
//     if (ql <= l && r <= qr)
//         return data[o];
//     if (r < ql || qr < l)
//         return 0;
//     int mid = (l + r) >> 1;
//     pushdown(o, l, r);
//     return seq_query(o << 1, l, mid, ql, qr) + seq_query(o << 1 | 1, mid + 1, r, ql, qr);
// }

// void seq_modify(int o, int l, int r, int ql, int qr)
// {
//     if (ql <= l && r <= qr)
//     {
//         lazy[o].st += l - ql + 1;
//         lazy[o].k++;
//         data[o] += 1LL * (l - ql + 1 + r - ql + 1) * (r - l + 1) / 2;
//         return;
//     }
//     if (r < ql || qr < l)
//         return;
//     int mid = (l + r) >> 1;
//     pushdown(o, l, r);
//     seq_modify(o << 1, l, mid, ql, qr);
//     seq_modify(o << 1 | 1, mid + 1, r, ql, qr);
//     data[o] = data[o << 1] + data[o << 1 | 1];
// }

// int main()
// {
// //    freopen("F.in.txt", "r", stdin);
// //    freopen("F.out1.txt", "w", stdout);
//     int t;
//     scanf("%d", &t);
//     while (t--)
//     {
//         int n, q;
//         scanf("%d%d", &n, &q);
//         for (int i = 1; i <= n; i++)
//             scanf("%d", a + i);
//         seq_build(1, 1, n);
//         while (q--)
//         {
//             int op, l, r;
//             scanf("%d%d%d", &op, &l, &r);
//             if (op == 1)
//             {
// //                for (int i = l; i <= r; i++)
// //                    a[i] += i - l + 1;
//                 seq_modify(1, 1, n, l, r);
//             }
//             else
//             {
// //                long long sum = 0;
// //                for (int i = l; i <= r; i++)
// //                    sum += a[i];
// //                printf("%lld\n", sum);
//                 printf("%lld\n", seq_query(1, 1, n, l, r));
//             }
//         }
//     }
//     return 0;
// }

//    printf("%d\n", 5);
//    for (int i = 0; i < 5; i++)
//    {
//        int n, q;
//        if (i < 3)
//            n = rand() % 50000 + 50000, q = rand() % 50000 + 50000;
//        else
//            n = rand() % 10 + 10, q = rand() % 10 + 50;
//        printf("%d %d\n", n, q);
//        for (int i = 0; i < n; i++)
//            printf("%d ", rand() % 100);
//        puts("");
//        while (q--)
//        {
//            int l = rand() % n + 1, r = rand() % n + 1;
//            if (l > r)
//                swap(l, r);
//            printf("%d %d %d\n", rand() % 2 + 1, l, r);
//        }
//    }
//    return 0;
